/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** Renderer
*/

// Exodia Renderer
#include "Renderer.hpp"
#include "Renderer/Renderer/Renderer2D.hpp"

// Entry Point
#include "OpenGL/OpenGLShader.hpp"

// Exodia Debug
#include "Debug/Profiling.hpp"

namespace Exodia {

    SceneData *Renderer::_SceneData = new SceneData;

    /////////////
    // Methods //
    /////////////

    void Renderer::Init()
    {
        EXODIA_PROFILE_FUNCTION(); // Performance instrumentation profiling for the function

        RenderCommand::Init();
        Renderer2D::Init();
    }

    void Renderer::Shutdown()
    {
        EXODIA_PROFILE_FUNCTION(); // Performance instrumentation profiling for the function

        Renderer2D::Shutdown();
    }

    void Renderer::BeginScene(OrthographicCamera &camera)
    {
        _SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
    }

    void Renderer::EndScene()
    {
        return;
    }

    void Renderer::Submit(const Ref<Shader> &shader, const Ref<VertexArray> &vertexArray, const glm::mat4 &transform)
    {
        shader->Bind();

        std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", _SceneData->ViewProjectionMatrix);
        std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);

        vertexArray->Bind();

        RenderCommand::DrawIndexed(vertexArray);
    }

    void Renderer::OnWindowResize(uint32_t width, uint32_t height)
    {
        RenderCommand::SetViewport(0, 0, width, height);
    }
};
