/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** OpenGLFramebuffer
*/

// OpenGL
#include "OpenGLFramebuffer.hpp"
#include "OpenGLFramebufferUtils.hpp"

// External includes
#include <glad/glad.h>

// Exodia Utils
#include "Utils/Assert.hpp"

namespace Exodia {

    //////////////////////
    // Static variables //
    //////////////////////

    static const uint32_t _MaxFramebufferSize = 8192;

    //////////////////////////////
    // Constructor & Destructor //
    //////////////////////////////

    OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpecification &spec)
        : _RendererID(0), _Specification(spec), _DepthAttachmentSpecification(FramebufferTextureFormat::None) {
        for (auto spec : _Specification.Attachments.Attachments) {
            if (!Utils::IsDepthFormat(spec.TextureFormat))
                _ColorAttachmentSpecifications.emplace_back(spec);
            else
                _DepthAttachmentSpecification = spec;
        }

        Invalidate();
    }

    OpenGLFramebuffer::~OpenGLFramebuffer() {
        glDeleteFramebuffers(1, &_RendererID);
        glDeleteTextures((GLsizei)_ColorAttachments.size(), _ColorAttachments.data());
        glDeleteTextures(1, &_DepthAttachment);
    }

    /////////////
    // Methods //
    /////////////

    void OpenGLFramebuffer::Bind() {
        glBindFramebuffer(GL_FRAMEBUFFER, _RendererID);
        glViewport(0, 0, _Specification.Width, _Specification.Height);
    }

    void OpenGLFramebuffer::Unbind() { glBindFramebuffer(GL_FRAMEBUFFER, 0); }

    void OpenGLFramebuffer::Resize(uint32_t width, uint32_t height) {
        if (width == 0 || height == 0 || height > _MaxFramebufferSize || width > _MaxFramebufferSize) {
            EXODIA_CORE_WARN("Attempted to resize framebuffer to ({0}, {1})", width, height);
            return;
        }

        _Specification.Width = width;
        _Specification.Height = height;

        Invalidate();
    }

    int OpenGLFramebuffer::ReadPixel(uint32_t attachmentIndex, int x, int y) {
        int pixelData = 0;

        EXODIA_CORE_ASSERT(attachmentIndex < _ColorAttachments.size(), "Index out of range !");

        glReadBuffer(GL_COLOR_ATTACHMENT0 + attachmentIndex);
        glReadPixels(x, y, 1, 1, GL_RED_INTEGER, GL_INT, &pixelData);
        return pixelData;
    }

    void OpenGLFramebuffer::ClearAttachment(uint32_t attachmentIndex, int value) {
        EXODIA_CORE_ASSERT(attachmentIndex < _ColorAttachments.size(), "Index out of range !");

        auto &spec = _ColorAttachmentSpecifications[attachmentIndex];

        glClearTexImage(_ColorAttachments[attachmentIndex], 0, Utils::ExodiaFBTextureFormatToGL(spec.TextureFormat),
                        GL_INT, &value);
    }

    void OpenGLFramebuffer::Invalidate() {
        // Delete the old framebuffer object
        if (_RendererID) {
            glDeleteFramebuffers(1, &_RendererID);
            glDeleteTextures((GLsizei)_ColorAttachments.size(), _ColorAttachments.data());
            glDeleteTextures(1, &_DepthAttachment);

            _ColorAttachments.clear();
            _DepthAttachment = 0;
        }

        // Create a new framebuffer object
        glCreateFramebuffers(1, &_RendererID);

        // Bind the framebuffer for configuration
        glBindFramebuffer(GL_FRAMEBUFFER, _RendererID);

        ///// ------
        bool multisample = _Specification.Samples > 1;

        // Attachments
        if (_ColorAttachmentSpecifications.size()) {
            _ColorAttachments.resize(_ColorAttachmentSpecifications.size());

            Utils::CreateTextures(multisample, _ColorAttachments.data(), (uint32_t)_ColorAttachments.size());

            for (size_t i = 0; i < _ColorAttachments.size(); i++) {
                Utils::BindTexture(multisample, _ColorAttachments[i]);

                switch (_ColorAttachmentSpecifications[i].TextureFormat) {
                case FramebufferTextureFormat::RGBA8:
                    Utils::AttachColorTexture(_ColorAttachments[i], (int)_Specification.Samples, GL_RGBA8, GL_RGBA,
                                              _Specification.Width, _Specification.Height, (int)i);
                    break;
                case FramebufferTextureFormat::RED_INTEGER:
                    Utils::AttachColorTexture(_ColorAttachments[i], (int)_Specification.Samples, GL_R32I,
                                              GL_RED_INTEGER, _Specification.Width, _Specification.Height, (int)i);
                    break;
                default:
                    break;
                }
            }
        }
        if (_DepthAttachmentSpecification.TextureFormat != FramebufferTextureFormat::None) {
            Utils::CreateTextures(multisample, &_DepthAttachment, 1);
            Utils::BindTexture(multisample, _DepthAttachment);

            switch (_DepthAttachmentSpecification.TextureFormat) {
            case FramebufferTextureFormat::DEPTH24STENCIL8:
                Utils::AttachDepthTexture(_DepthAttachment, _Specification.Samples, GL_DEPTH24_STENCIL8,
                                          GL_DEPTH_STENCIL_ATTACHMENT, _Specification.Width, _Specification.Height);
                break;
            default:
                break;
            }
        }
        if (_ColorAttachments.size() > 1) {
            EXODIA_CORE_ASSERT(_ColorAttachments.size() <= 4, "Only 4 color attachments are supported !");

            GLenum buffers[4] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2,
                                 GL_COLOR_ATTACHMENT3};

            glDrawBuffers((GLsizei)_ColorAttachments.size(), buffers);
        } else if (_ColorAttachments.empty())
            glDrawBuffer(GL_NONE); // Only depth-pass

        // Check if the framebuffer is complete
        EXODIA_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE,
                           "Framebuffer is incomplete !");

        // Unbind the framebuffer
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    ///////////////////////
    // Getters & Setters //
    ///////////////////////

    const FramebufferSpecification &OpenGLFramebuffer::GetSpecification() const { return _Specification; }

    uint32_t OpenGLFramebuffer::GetColorAttachmentRendererID(uint32_t index) const {
        EXODIA_CORE_ASSERT(index < _ColorAttachments.size(), "Index out of range !");

        return _ColorAttachments[index];
    }
}; // namespace Exodia
