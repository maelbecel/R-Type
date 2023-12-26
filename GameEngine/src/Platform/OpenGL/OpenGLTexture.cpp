/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** OpenGLTexture
*/

// OpenGL
#include "OpenGLTexture.hpp"
#include "OpenGLTextureUtils.hpp"

// Exodia Utils
#include "Utils/Assert.hpp"

// Exodia Debug
#include "Debug/Profiling.hpp"

namespace Exodia {

    //////////////////////////////
    // Constructor & Destructor //
    //////////////////////////////

    OpenGLTexture::OpenGLTexture(const TextureSpecification &spec, Buffer data)
        : _Specification(spec), _Width(spec.Width), _Height(spec.Height), _IsLoaded(false) {
        EXODIA_PROFILE_FUNCTION(); // Performance instrumentation profiling for the function

        _InternalFormat = Utils::ExodiaImageFormatToGLInternalFormat(spec.Format);
        _DataFormat = Utils::ExodiaImageFormatToGLDataFormat(spec.Format);

        // Create the texture
        glCreateTextures(GL_TEXTURE_2D, 1, &_RendererID);
        glTextureStorage2D(_RendererID, 1, _InternalFormat, _Width, _Height);

        // Set the texture parameters
        // glTextureParameteri(_RendererID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        // glTextureParameteri(_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTextureParameteri(_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTextureParameteri(_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

        if (data)
            SetData(data);
    }

    OpenGLTexture::~OpenGLTexture() {
        EXODIA_PROFILE_FUNCTION(); // Performance instrumentation profiling for the function

        if (_Data.Size > 0)
            _Data.Release();

        if (_IsLoaded)
            glDeleteTextures(1, &_RendererID); // Delete the OpenGL texture
    }

    /////////////
    // Methods //
    /////////////

    void OpenGLTexture::Bind(uint32_t slot) const {
        EXODIA_PROFILE_FUNCTION(); // Performance instrumentation profiling for the function

        glBindTextureUnit(slot, _RendererID); // Bind the OpenGL texture to a texture slot
    }

    ////////////////
    // Comparator //
    ////////////////

    bool OpenGLTexture::operator==(const Texture &other) const { return _RendererID == other.GetRendererID(); }

    ///////////////////////
    // Getters & Setters //
    ///////////////////////

    uint32_t OpenGLTexture::GetWidth() const { return _Width; }

    uint32_t OpenGLTexture::GetHeight() const { return _Height; }

    uint32_t OpenGLTexture::GetRendererID() const { return _RendererID; }

    void OpenGLTexture::SetData(Buffer data) {
        EXODIA_PROFILE_FUNCTION(); // Performance instrumentation profiling for the function

        // Check if the data size is the entire texture
        uint32_t bpp = _DataFormat == GL_RGBA ? 4 : 3;

        if (data.Size != _Width * _Height * bpp) {
            EXODIA_CORE_ERROR("Data must be entire texture !");

            return;
        }

        // Upload the data to the texture
        glTextureSubImage2D(_RendererID, 0, 0, 0, _Width, _Height, _DataFormat, GL_UNSIGNED_BYTE, data.Data);

        _Data = Buffer::Copy(data);
    }

    Buffer OpenGLTexture::GetData() const
    {
        return _Data;
    }

    bool OpenGLTexture::IsLoaded() const { return _IsLoaded; }

    const TextureSpecification &OpenGLTexture::GetSpecification() const { return _Specification; }
}; // namespace Exodia
