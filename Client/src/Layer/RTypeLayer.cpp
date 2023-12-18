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

    RTypeLayer::RTypeLayer() : Layer("R-Type"), _CameraController(1600.0f / 900.0f) {};

    /////////////
    // Methods //
    /////////////

    void RTypeLayer::OnAttach()
    {
        EXODIA_PROFILE_FUNCTION();

        Exodia::Network::IOContextManager ioContextManager;

        // Define a local endpoint to listen on
        // asio::ip::udp::endpoint localEndpoint(asio::ip::address::from_string("127.0.0.1"), 8082);
        _World = Exodia::World::CreateWorld();
        Exodia::Network::Network network(_World, ioContextManager, 8083);
        network.connect("0.0.0.0", 8082);

        auto commandLine = Application::Get().GetSpecification().CommandLineArgs;
    
        if (commandLine.Count > 1) {
            Application::Get().Close();
            return;
        }

        // Register the systems
        _World->RegisterSystem(new AnimationSystem());      // Animation system
        _World->RegisterSystem(new ScriptSystem());         // Script system
        _World->RegisterSystem(new MovingSystem(1.5f));     // Moving system

        CollisionSystem *collisionSystem = new CollisionSystem();
        _World->RegisterSystem(collisionSystem);
        _World->Subscribe<Events::OnCollisionEntered>(collisionSystem);

        // Create the entities
        CreatePlayer(_World);
        CreatePataPata(_World);
        CreateBackground(_World);
        CreateStars(_World);

        // Create the camera
        _CameraController.SetZoomLevel(5.0f);

    }

    void RTypeLayer::OnDetach()
    {
        EXODIA_PROFILE_FUNCTION();
    }

    void RTypeLayer::OnUpdate(Exodia::Timestep ts)
    {
        EXODIA_PROFILE_FUNCTION();

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
