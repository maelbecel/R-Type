/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Font
*/

// Exodia Renderer includes
#include "Renderer/Renderer/Renderer.hpp"
#include "Font.hpp"

// Exodia OpenGL includes
#include "Platform/OpenGL/OpenGLFont.hpp"

// Exodia Utils includes
#include "Exodia-Debug.hpp"

namespace Exodia {

    /////////////
    // Factory //
    /////////////

    Ref<Font> Font::Create(const std::string &path) {
        RendererAPI::API api = Renderer::GetAPI();

        switch (api) {
        case RendererAPI::API::None:
            return nullptr;
        case RendererAPI::API::OpenGL:
            return CreateRef<OpenGLFont>(path);
        default:
            break;
        }

        EXODIA_CORE_ASSERT(false, "Unknown RendererAPI !");
        return nullptr;
    }

    AssetType Font::GetStaticType() { return AssetType::Font; }

    AssetType Font::GetType() const { return GetStaticType(); }
}; // namespace Exodia
