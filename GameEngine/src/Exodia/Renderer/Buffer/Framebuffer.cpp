/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** Framebuffer
*/

// Exodia Renderer
#include "Framebuffer.hpp"
#include "Renderer/Renderer/Renderer.hpp"

// Exodia Utils
#include "Utils/Assert.hpp"

// Entry Point
#include "OpenGL/OpenGLFramebuffer.hpp"

namespace Exodia {

    /////////////
    // Factory //
    /////////////

    Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification &spec)
    {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None:
                EXODIA_CORE_ASSERT("RendererAPI::None is not supported !");
                return nullptr;
            case RendererAPI::API::OpenGL:
                return CreateRef<OpenGLFramebuffer>(spec);
            default:
                break;
        }

        EXODIA_CORE_ASSERT("Unknown RendererAPI !");
        return nullptr;
    };
};
