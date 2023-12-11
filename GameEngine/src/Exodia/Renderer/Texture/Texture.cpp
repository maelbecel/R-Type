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

    Ref<Texture2D> Texture2D::Create(const TextureSpecification &spec, Buffer data)
    {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None:
                EXODIA_CORE_ASSERT(false, "RendererAPI::None is not supported !");
                return nullptr;
            case RendererAPI::API::OpenGL:
                return CreateRef<OpenGLTexture>(spec, data);
            default:
                break;
        }

        EXODIA_CORE_ASSERT(false, "Unknown RendererAPI !");
        return nullptr;
    }

    ///////////////////////
    // Getters & Setters //
    ///////////////////////
    
    AssetType Texture2D::GetStaticType()
    {
        return AssetType::Texture2D;
    }

    AssetType Texture2D::GetType() const
    {
        return GetStaticType();
    }
};
