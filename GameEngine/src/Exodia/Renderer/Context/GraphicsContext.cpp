/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** GraphicsContext
*/

// Renderer
#include "GraphicsContext.hpp"
#include "Renderer/Renderer/RendererAPI.hpp"

// Entry point
#include "OpenGL/OpenGLContext.hpp"

namespace Exodia {

    /////////////
    // Factory //
    /////////////

    Scope<GraphicsContext> GraphicsContext::Create(void *window)
    {
        switch (RendererAPI::GetAPI()) {
            case RendererAPI::API::None:
                EXODIA_CORE_ASSERT(false, "RendererAPI::None is not supported !");
            case RendererAPI::API::OpenGL:
                return CreateScope<OpenGLContext>(static_cast<GLFWwindow *>(window));
            default:
                break;
        }
        EXODIA_CORE_ASSERT(false, "Unknown RendererAPI !");
        return nullptr;
    }
};
