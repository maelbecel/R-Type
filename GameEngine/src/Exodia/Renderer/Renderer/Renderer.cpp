/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** Renderer
*/

// Exodia Renderer
#include "Renderer.hpp"
#include "Renderer/Camera/OrthographicCamera.hpp"
#include "Renderer/Renderer/RenderCommand.hpp"
#include "Renderer/Renderer/Renderer2D.hpp"
#include "Renderer/Shader/Shader.hpp"
#include "Renderer/Vertex/VertexArray.hpp"

// Exodia Debug
#include "Debug/Profiling.hpp"

namespace Exodia
{

    Scope<SceneData> Renderer::_SceneData = CreateScope<SceneData>();

    /////////////
    // Methods //
    /////////////

    void Renderer::Init()
    {
        EXODIA_PROFILE_FUNCTION(); // Performance instrumentation profiling for the function

        RenderCommand::Init();
        Renderer2D::Init();
    }

    void Renderer::Shutdown() { Renderer2D::Shutdown(); }

    void Renderer::BeginScene( OrthographicCamera &camera )
    {
        _SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
    }

    void Renderer::EndScene(){};

    void Renderer::Submit( const Ref<Shader> &shader, const Ref<VertexArray> &vertexArray, const glm::mat4 &transform )
    {
        shader->Bind();

        shader->SetMat4( "u_ViewProjection", _SceneData->ViewProjectionMatrix );
        shader->SetMat4( "u_Transform", transform );

        vertexArray->Bind();

        RenderCommand::DrawIndexed( vertexArray );
    }

    void Renderer::OnWindowResize( uint32_t width, uint32_t height )
    {
        RenderCommand::SetViewport( 0, 0, width, height );
    }
}; // namespace Exodia
