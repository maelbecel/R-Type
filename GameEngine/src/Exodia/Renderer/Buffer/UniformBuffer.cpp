/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** UniformBuffer
*/

// Exodia Renderer includes
#include "UniformBuffer.hpp"
#include "Renderer/Renderer/RendererAPI.hpp"
#include "Renderer/Renderer/Renderer.hpp"

// Entry point
#include "OpenGL/OpenGLUniformBuffer.hpp"

namespace Exodia {

    /////////////
    // Factory //
    /////////////

    Ref<UniformBuffer> UniformBuffer::Create(uint32_t size, uint32_t binding)
    {
        RendererAPI::API api = Renderer::GetAPI();

        switch (api) {
            case RendererAPI::API::None:
                EXODIA_CORE_ASSERT(false, "RendererAPI::None is not supported !");
                return nullptr;
            case RendererAPI::API::OpenGL:
                return CreateRef<OpenGLUniformBuffer>(size, binding);
            default:
                break;
        }

        EXODIA_CORE_ASSERT(false, "Unknown RendererAPI !");
        return nullptr;
    }
};
