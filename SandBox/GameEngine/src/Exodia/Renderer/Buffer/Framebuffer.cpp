/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** Framebuffer
*/

// Exodia Renderer
#include "Framebuffer.hpp"
#include "Renderer/Renderer/RendererAPI.hpp"
#include "Renderer/Renderer/Renderer.hpp"

// Exodia Utils
#include "Exodia-Debug.hpp"

// Entry Point
#include "OpenGL/OpenGLFramebuffer.hpp"

namespace Exodia {

    /////////////
    // Factory //
    /////////////

    Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification &spec) {
        RendererAPI::API api = Renderer::GetAPI();

        switch (api) {
        case RendererAPI::API::None:
            return nullptr;
        case RendererAPI::API::OpenGL:
            return CreateRef<OpenGLFramebuffer>(spec);
        default:
            break;
        }

        EXODIA_CORE_ASSERT(false, "Unknown RendererAPI !");
        return nullptr;
    };
}; // namespace Exodia
