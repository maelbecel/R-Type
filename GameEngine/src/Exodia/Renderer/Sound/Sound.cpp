/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Sound
*/

// Exodia Renderer
#include "Sound.hpp"
#include "Renderer/Renderer/RendererAPI.hpp"
#include "Renderer/Renderer/Renderer.hpp"

// Exodia Platform
#include "OpenGL/OpenGLSound.hpp"

namespace Exodia {

    /////////////
    // Factory //
    /////////////

    Ref<Sound2D> Sound2D::Create(const std::string &path)
    {
        RendererAPI::API api = Renderer::GetAPI();

        switch (api) {
            case RendererAPI::API::None:
                return nullptr;
            case RendererAPI::API::OpenGL:
                return CreateRef<OpenGLSound>(path);
            default:
                break;
        }

        EXODIA_CORE_ASSERT(false, "Unknown RendererAPI !");
        return nullptr;
    }

    ///////////////////////
    // Getters & Setters //
    ///////////////////////

    AssetType Sound2D::GetStaticType()
    {
        return AssetType::Sound2D;
    }

    AssetType Sound2D::GetType() const
    {
        return GetStaticType();
    }
};
