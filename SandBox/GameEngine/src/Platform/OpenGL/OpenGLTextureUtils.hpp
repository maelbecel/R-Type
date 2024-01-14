/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** OpenGLTextureUtils
*/

#ifndef OPENGLTEXTUREUTILS_HPP_
#define OPENGLTEXTUREUTILS_HPP_

// Exodia Texture
#include "OpenGLTexture.hpp"

// Exodia Utils
#include "Exodia-Debug.hpp"

namespace Exodia::Utils {

    static GLenum ExodiaImageFormatToGLDataFormat(ImageFormat format) {
        switch (format) {
        case ImageFormat::RGB8:
            return GL_RGB;
        case ImageFormat::RGBA8:
            return GL_RGBA;
        default:
            break;
        }

        EXODIA_CORE_ASSERT(false, "Unknown ImageFormat !");
        return 0;
    }

    static GLenum ExodiaImageFormatToGLInternalFormat(ImageFormat format) {
        switch (format) {
        case ImageFormat::RGB8:
            return GL_RGB8;
        case ImageFormat::RGBA8:
            return GL_RGBA8;
        default:
            break;
        }

        EXODIA_CORE_ASSERT(false, "Unknown ImageFormat !");
        return 0;
    }
}; // namespace Exodia::Utils

#endif /* !OPENGLTEXTUREUTILS_HPP_ */
