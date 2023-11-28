/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** Texture
*/

// Exodia Renderer
#include "Renderer/Renderer/Renderer.hpp"
#include "Texture.hpp"

// Entry Point
#include "OpenGL/OpenGLTexture.hpp"

namespace Exodia {

    /////////////
    // Factory //
    /////////////

    Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
    {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None:
                EXODIA_CORE_ASSERT(false, "RendererAPI::None is not supported !");
                return nullptr;
            case RendererAPI::API::OpenGL:
                return CreateRef<OpenGLTexture>(width, height);
            default:
                break;
        }

        EXODIA_CORE_ASSERT(false, "Unknown RendererAPI !");
        return nullptr;
    }

    Ref<Texture2D> Texture2D::Create(const std::string &path)
    {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None:
                EXODIA_CORE_ASSERT(false, "RendererAPI::None is not supported !");
                return nullptr;
            case RendererAPI::API::OpenGL:
                return CreateRef<OpenGLTexture>(path);
            default:
                break;
        }

        EXODIA_CORE_ASSERT(false, "Unknown RendererAPI !");
        return nullptr;
    }
};
