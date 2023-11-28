/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** DefaultPlayer
*/

#include "DefaultLayer.hpp"
#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Exodia {

    // -- Layer ----------------------------------------------------------------

    //////////////////////////////
    // Constructor & Destructor //
    //////////////////////////////

    DefaultLayer::DefaultLayer() : Layer("DefaultLayer"), _CameraController(1600.0f / 900.0f), _SquareColor({ 0.2f, 0.3f, 0.8f, 1.0f }) {};

    /////////////
    // Methods //
    /////////////

    void DefaultLayer::OnUpdate(Exodia::Timestep ts)
    {
        // Update
        _CameraController.OnUpdate(ts);

        // Renderer Prep
        Exodia::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
        Exodia::RenderCommand::Clear();

        // Renderer Draw
        Exodia::Renderer2D::BeginScene(_CameraController.GetCamera());

        Exodia::Renderer2D::DrawRotatedQuad(
            { -1.0f, 0.0f },      // Position
            {  0.8f, 0.8f },      // Size
            glm::radians(-45.0f), // Rotation
            _SquareColor          // Color
        );

        Exodia::Renderer2D::EndScene();
    }

    void DefaultLayer::OnImGUIRender()
    {
        ImGui::Begin("Settings");
        ImGui::ColorEdit4("Square Color", glm::value_ptr(_SquareColor));
        ImGui::End();
    }

    void DefaultLayer::OnEvent(Exodia::Event &event)
    {
        _CameraController.OnEvent(event);
    }
};
