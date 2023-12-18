/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** ExodiaEngine
*/

#include "RTypeLayer.hpp"
#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Exodia {

    //////////////////////////////
    // Constructor & Destructor //
    //////////////////////////////

    RTypeLayer::RTypeLayer() : Layer("R-Type"), network(_World, ioContextManager, 8083), _CameraController(1600.0f / 900.0f)
    {

    };

    /////////////
    // Methods //
    /////////////

    void RTypeLayer::OnAttach()
    {
        EXODIA_PROFILE_FUNCTION();
        network.Loop();
        network.SendAskConnect("0.0.0.0", 8082);
    }

    void RTypeLayer::OnDetach()
    {
        EXODIA_PROFILE_FUNCTION();
    }

    void RTypeLayer::OnUpdate(Exodia::Timestep ts)
    {
        EXODIA_PROFILE_FUNCTION();


        // Ping server
        network.SendEvent(52);

        // Update
        _CameraController.OnUpdate(ts);

        // Update the world
        _World->Update(ts);

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

            _World->ForEach<CircleRendererComponent>([&](Entity *entity, ComponentHandle<CircleRendererComponent> circle) {
                auto transform = entity->GetComponent<TransformComponent>();
                auto id = entity->GetComponent<IDComponent>();

                if (transform && id) {
                    Renderer2D::DrawCircle(
                        transform.Get().GetTransform(), // Transform
                        circle.Get().Color, // CircleRendererComponent
                        circle.Get().Thickness, // CircleRendererComponent
                        circle.Get().Fade, // CircleRendererComponent
                        (int)id.Get().ID                // Entity ID
                    );
                }
            });

            _World->ForEach<SpriteRendererComponent>([&](Entity *entity, ComponentHandle<SpriteRendererComponent> sprite) {
                auto transform = entity->GetComponent<TransformComponent>();
                auto id = entity->GetComponent<IDComponent>();

                if (transform && id) {
                    Renderer2D::DrawSprite(
                        transform.Get().GetTransform(), // Transform
                        sprite.Get(),                   // SpriteRendererComponent
                        (int)id.Get().ID                // Entity ID
                    );
                }
            });


            Exodia::Renderer2D::EndScene();
        }
    }

    void RTypeLayer::OnImGUIRender()
    {
        EXODIA_PROFILE_FUNCTION();

        // ImGui::Begin("Settings");

        // ImGui::ColorEdit4("Square Color", glm::value_ptr(_SquareColor));

        // ImGui::End();
    }

    void RTypeLayer::OnEvent(Exodia::Event &event)
    {
        _CameraController.OnEvent(event);
    }
};
