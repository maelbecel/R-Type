/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** VertexArray
*/

// Exodia Renderer
#include "VertexArray.hpp"
#include "Renderer/Renderer/RendererAPI.hpp"
#include "Renderer/Renderer/Renderer.hpp"

// Entry Point
#include "OpenGL/OpenGLVertexArray.hpp"

namespace Exodia {

    /////////////
    // Factory //
    /////////////

    Ref<VertexArray> VertexArray::Create() {
        RendererAPI::API api = Renderer::GetAPI();

        switch (api) {
        case RendererAPI::API::None:
            EXODIA_CORE_ASSERT(false, "RendererAPI::API::None is currently not supported!");
            return nullptr;
        case RendererAPI::API::OpenGL:
            return CreateRef<OpenGLVertexArray>();
        default:
            break;
        }

        EXODIA_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}; // namespace Exodia
