/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** OpenGLFramebufferUtils
*/

#ifndef OPENGLFRAMEBUFFERUTILS_HPP_
#define OPENGLFRAMEBUFFERUTILS_HPP_

// OpenGL
#include "OpenGLFramebuffer.hpp"

// Exodia Utils includes
#include "Utils/Assert.hpp"

// External includes
#include <glad/glad.h>

namespace Exodia::Utils {

    ///////////////////////////////////////////
    // Utils functions for OpenGLFramebuffer //
    ///////////////////////////////////////////

    static GLenum TextureTarget(bool multisampled) { return multisampled ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D; }

    static void CreateTextures(bool multisampled, uint32_t *outID, uint32_t count) {
        glCreateTextures(TextureTarget(multisampled), count, outID);
    }

    static void BindTexture(bool multisampled, uint32_t id) { glBindTexture(TextureTarget(multisampled), id); }

    static void AttachColorTexture(uint32_t id, int samples, GLenum internalFormat, GLenum format, uint32_t width,
                                   uint32_t height, int index) {
        bool multisampled = samples > 1;

        if (multisampled)
            glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, internalFormat, width, height, GL_FALSE);
        else {
            glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, nullptr);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        }
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, TextureTarget(multisampled), id, 0);
    }

    static void AttachDepthTexture(uint32_t id, int samples, GLenum format, GLenum attachmentType, uint32_t width,
                                   uint32_t height) {
        bool multisampled = samples > 1;

        if (multisampled)
            glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, format, width, height, GL_FALSE);
        else {
            glTexStorage2D(GL_TEXTURE_2D, 1, format, width, height);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        }
        glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, TextureTarget(multisampled), id, 0);
    }

    static bool IsDepthFormat(FramebufferTextureFormat format) {
        switch (format) {
        case FramebufferTextureFormat::DEPTH24STENCIL8:
            return true;
        default:
            break;
        }

        return false;
    }

    static GLenum ExodiaFBTextureFormatToGL(FramebufferTextureFormat format) {
        switch (format) {
        case FramebufferTextureFormat::RGBA8:
            return GL_RGBA8;
        case FramebufferTextureFormat::RED_INTEGER:
            return GL_RED_INTEGER;
        default:
            break;
        }

        EXODIA_CORE_ASSERT(false, "Unknown FramebufferTextureFormat !");
        return GL_NONE;
    }
}; // namespace Exodia::Utils

#endif /* !OPENGLFRAMEBUFFERUTILS_HPP_ */
