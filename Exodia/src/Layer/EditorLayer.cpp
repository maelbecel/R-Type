/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** ExodiaEngine
*/

#include "EditorLayer.hpp"
#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Exodia {

    //////////////////////////////
    // Constructor & Destructor //
    //////////////////////////////

    EditorLayer::EditorLayer() : Layer("Exodia Editor"), _CameraController(1600.0f / 900.0f) {};

    /////////////
    // Methods //
    /////////////

    void EditorLayer::OnAttach()
    {
        EXODIA_PROFILE_FUNCTION();

        auto commandLine = Application::Get().GetSpecification().CommandLineArgs;

        if (commandLine.Count > 1) {
            Application::Get().Close();
            return;
        }
    }

    void EditorLayer::OnDetach()
    {
        EXODIA_PROFILE_FUNCTION();
    }

    void EditorLayer::OnUpdate(Exodia::Timestep ts)
    {
        EXODIA_PROFILE_FUNCTION();

        // Update
        _CameraController.OnUpdate(ts);

        // Renderer Prep
        {
            EXODIA_PROFILE_SCOPE("Renderer Prep");
            Exodia::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
            Exodia::RenderCommand::Clear();
        }

        // Renderer Draw
        {
            EXODIA_PROFILE_SCOPE("Renderer Draw");
            Exodia::Renderer2D::BeginScene(_CameraController.GetCamera());

            Exodia::Renderer2D::DrawRotatedQuad(
                { -1.0f, 0.0f },            // Position
                {  0.8f, 0.8f },            // Size
                glm::radians(-45.0f),       // Rotation
                { _SquareColor }           // Color
            );
            Exodia::Renderer2D::DrawQuad(
                { 0.5f, -0.5f },           // Position
                { 0.5f,  0.75f },          // Size
                { 0.2f, 0.3f, 0.8f, 1.0f } // Color
            );

            Exodia::Renderer2D::EndScene();
        }
    }

    void EditorLayer::OnImGUIRender()
    {
        EXODIA_PROFILE_FUNCTION();

        ImGui::Begin("Settings");

        ImGui::ColorEdit4("Square Color", glm::value_ptr(_SquareColor));

        ImGui::End();
    }

    void EditorLayer::OnEvent(Exodia::Event &event)
    {
        _CameraController.OnEvent(event);
    }
};
