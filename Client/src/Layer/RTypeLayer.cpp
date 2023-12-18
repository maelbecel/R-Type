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

        auto commandLine = Application::Get().GetSpecification().CommandLineArgs;

        if (commandLine.Count > 1) {
            Application::Get().Close();
            return;
        }

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
        asio::ip::udp::endpoint localEndpoint(asio::ip::address::from_string("127.0.0.1"), 8081);

        asio::ip::udp::endpoint serverEndpoint(asio::ip::address::from_string("127.0.0.1"), 8080);

        // Create a UDPSocket object for the server
        Exodia::Network::UDPSocket serverSocket(ioContextManager, localEndpoint);

        // serverSocket.receive(my_callback);
        serverSocket.send("Hello World", serverEndpoint);

        // Run the IO context to initiate asynchronous operations
        ioContextManager.run();

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

            // Bind the framebuffer
            _Framebuffer->Bind();

            Exodia::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
            Exodia::RenderCommand::Clear();

            // Clear Entity ID attachment to -1
            _Framebuffer->ClearAttachment(1, -1);
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

        // Get Mouse Position in the Viewport window
        auto[mouseX, mouseY] = ImGui::GetMousePos();

        int pixelData = _Framebuffer->ReadPixel(1, (int)mouseX, (int)mouseY);

        Entity entity = (pixelData == -1) ? Entity() : Entity(_World, pixelData);

        if (entity.GetWorld() != nullptr) {
            if (_LastEntityHovered.GetWorld() == nullptr)
                _World->Emit<Events::OnHoveredEnter>({ &entity });
            if (Input::IsMouseButtonPressed(Mouse::BUTTONLEFT))
                _World->Emit<Events::OnClick>({ &entity });
        } else {
            if (_LastEntityHovered.GetWorld() != nullptr)
                _World->Emit<Events::OnHoveredExit>({ &_LastEntityHovered });
        }

        _LastEntityHovered = entity;

        // Unbind the framebuffer
        _Framebuffer->Unbind();
    }

    void RTypeLayer::OnImGUIRender()
    {
        EXODIA_PROFILE_FUNCTION();
    }

    void RTypeLayer::OnEvent(Exodia::Event &event)
    {
        _CameraController.OnEvent(event);
    }
};
