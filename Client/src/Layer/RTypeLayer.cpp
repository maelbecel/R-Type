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


        // if (commandLine.Count > 1) {
        //     Application::Get().Close();
        //     return;
        // }

        FramebufferSpecification fbSpec;

        fbSpec.Width  = Application::Get().GetWindow().GetWidth();
        fbSpec.Height = Application::Get().GetWindow().GetHeight();
        fbSpec.Attachments = {
            FramebufferTextureFormat::RGBA8,
            FramebufferTextureFormat::RED_INTEGER,
            FramebufferTextureFormat::Depth
        };

        _Framebuffer = Framebuffer::Create(fbSpec);

        // Server main
        Exodia::Network::IOContextManager ioContextManager;

        // Define a local endpoint to listen on
        // asio::ip::udp::endpoint localEndpoint(asio::ip::address::from_string("127.0.0.1"), 8082);
        network.loop();
        network.sendAskConnect("0.0.0.0", 8082);

        // Create the world
        _World = World::CreateWorld();

        // Register the systems
        _World->RegisterSystem(new AnimationSystem());      // Animation system
        _World->RegisterSystem(new ScriptSystem());         // Script system
        _World->RegisterSystem(new MovingSystem(1.5f));     // Moving system

        CollisionSystem *collisionSystem = new CollisionSystem();
        EventHover      *eventHover      = new EventHover();

        _World->RegisterSystem(collisionSystem);
        _World->Subscribe<Events::OnCollisionEntered>(collisionSystem);
        _World->Subscribe<Events::OnHoveredEnter>(eventHover);
        _World->Subscribe<Events::OnHoveredExit>(eventHover);
        _World->Subscribe<Events::OnClick>(eventHover);

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

        // Renderer Prep
        {
            EXODIA_PROFILE_SCOPE("Renderer Prep");

            Exodia::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
            Exodia::RenderCommand::Clear();
        }

        // Update
        _CameraController.OnUpdate(ts);

        // Update the world
        _World->Update(ts);

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
    }

    void RTypeLayer::OnEvent(Exodia::Event &event)
    {
        _CameraController.OnEvent(event);
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(RTypeLayer::OnKeyPressedEvent));
        dispatcher.Dispatch<KeyReleasedEvent>(BIND_EVENT_FN(RTypeLayer::OnKeyReleasedEvent));

    }

    bool RTypeLayer::OnKeyPressedEvent(KeyPressedEvent &event) {

        int key = event.GetKeyCode();

        EXODIA_INFO("pressed {0}", key);
        _World->ForEach<ScriptComponent, TagComponent>([&](UNUSED Entity *entity, ComponentHandle<ScriptComponent> script, auto tag) {
            if (tag.Get().Tag.rfind("Player", 0) != std::string::npos && script.Get().Instance != nullptr) {
                script.Get().Instance->OnKeyPressed(key);
            }
        });
        return true;

    };

    bool RTypeLayer::OnKeyReleasedEvent(KeyReleasedEvent &event) {

        int key = event.GetKeyCode();

        EXODIA_INFO("released {0}", key);
       _World->ForEach<ScriptComponent, TagComponent>([&](UNUSED Entity *entity, ComponentHandle<ScriptComponent> script, auto tag) {

            if (tag.Get().Tag.rfind("Player", 0) != std::string::npos && script.Get().Instance != nullptr) {
                script.Get().Instance->OnKeyReleased(key);
            }
        });
        return false;
    };
};
