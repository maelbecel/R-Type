/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** OpenGLTexture
*/

// External includes
#define STB_IMAGE_IMPLEMENTATION
    #include <stb_image.h>

// OpenGL
#include "OpenGLTexture.hpp"

// Exodia Utils
#include "Utils/Assert.hpp"

// Exodia Debug
#include "Debug/Profiling.hpp"

namespace Exodia {

    //////////////////////////////
    // Constructor & Destructor //
    //////////////////////////////

    OpenGLTexture::OpenGLTexture(uint32_t width, uint32_t height) : _Width(width), _Height(height), _InternalFormat(GL_RGBA8), _DataFormat(GL_RGBA), _IsLoaded(false)
    {
        EXODIA_PROFILE_FUNCTION(); // Performance instrumentation profiling for the function

        // Create the texture
        glCreateTextures(GL_TEXTURE_2D, 1, &_RendererID);
        glTextureStorage2D(_RendererID, 1, _InternalFormat, _Width, _Height);

        // Set the texture parameters
        glTextureParameteri(_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTextureParameteri(_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }

    OpenGLTexture::OpenGLTexture(const std::string &path) : _Path(path), _IsLoaded(false)
    {
        EXODIA_PROFILE_FUNCTION(); // Performance instrumentation profiling for the function

        // Load the image using stb_image
        int width = 0;
        int height = 0;
        int channels = 0;

        stbi_set_flip_vertically_on_load(1);
        stbi_uc *data;

        {
            EXODIA_PROFILE_SCOPE("stbi_load - OpenGLTexture::OpenGLTexture(const std::string &path)");

            data = stbi_load(path.c_str(), &width, &height, &channels, 0);
        }

        if (data) {
            _IsLoaded = true;

            _Width = width;
            _Height = height;

            GLenum internalFormat = 0;
            GLenum dataFormat     = 0;

            if (channels == 4) {
                internalFormat = GL_RGBA8;
                dataFormat     = GL_RGBA;
            } else if (channels == 3) {
                internalFormat = GL_RGB8;
                dataFormat     = GL_RGB;
            }

            _InternalFormat = internalFormat;
            _DataFormat = dataFormat;

            EXODIA_CORE_ASSERT(_InternalFormat & _DataFormat, "Format not supported !");

            // Create OpenGL texture and set parameters
            glCreateTextures(GL_TEXTURE_2D, 1, &_RendererID);
            glTextureStorage2D(_RendererID, 1, internalFormat, _Width, _Height);
            glTextureParameteri(_RendererID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTextureParameteri(_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTextureParameteri(_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTextureParameteri(_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

            // Upload image data to the texture
            glTextureSubImage2D(_RendererID, 0, 0, 0, _Width, _Height, dataFormat, GL_UNSIGNED_BYTE, data);

            // Free stb_image data
            stbi_image_free(data);
        }
    }

    OpenGLTexture::~OpenGLTexture()
    {
        EXODIA_PROFILE_FUNCTION(); // Performance instrumentation profiling for the function

        glDeleteTextures(1, &_RendererID); // Delete the OpenGL texture
    }

    /////////////
    // Methods //
    /////////////

    void OpenGLTexture::Bind(uint32_t slot) const
    {
        EXODIA_PROFILE_FUNCTION(); // Performance instrumentation profiling for the function

        glBindTextureUnit(slot, _RendererID); // Bind the OpenGL texture to a texture slot
    }

    ////////////////
    // Comparator //
    ////////////////

    bool OpenGLTexture::operator==(const Texture &other) const
    {
        return _RendererID == other.GetRendererID();
    }

    ///////////////////////
    // Getters & Setters //
    ///////////////////////

    uint32_t OpenGLTexture::GetWidth() const
    {
        return _Width;
    }

    uint32_t OpenGLTexture::GetHeight() const
    {
        return _Height;
    }

    uint32_t OpenGLTexture::GetRendererID() const
    {
        return _RendererID;
    }

    std::string OpenGLTexture::GetFilepath() const
    {
        return _Path;
    }

    void OpenGLTexture::SetData(void *data, uint32_t size)
    {
        EXODIA_PROFILE_FUNCTION(); // Performance instrumentation profiling for the function

        // Check if the data size is the entire texture
        uint32_t bpp = _DataFormat == GL_RGBA ? 4 : 3;

        EXODIA_ASSERT(size == _Width * _Height * bpp, "Data must be entire texture !");

        // Upload the data to the texture
        glTextureSubImage2D(_RendererID, 0, 0, 0, _Width, _Height, _DataFormat, GL_UNSIGNED_BYTE, data);

        // -- To remove the warning of unused variable -- //
        (void)size;
        (void)bpp;
    }

    bool OpenGLTexture::IsLoaded() const
    {
        return _IsLoaded;
    }
};
