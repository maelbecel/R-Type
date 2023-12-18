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
        Exodia::World *world = Exodia::World::CreateWorld();
        Exodia::Network::Network network(world, ioContextManager, 8083);
        network.connect("0.0.0.0", 8082);
        network.sendEntity();

        // Exodia::Network::IOContextManager ioContextManager;

        // // Define a local endpoint to listen on
        // asio::ip::udp::endpoint localEndpoint(asio::ip::address::from_string("127.0.0.1"), 8083);
        // asio::ip::udp::endpoint serverEndpoint(asio::ip::address::from_string("127.0.0.1"), 8082);

        // // Create a UDPSocket object for the server
        // Exodia::Network::UDPSocket serverSocket(ioContextManager, localEndpoint);

        // // serverSocket.receive(my_callback);
        // Exodia::Network::Header header(0x0c, 1, 2, 2);
        // Exodia::Network::Packet packet;

        // std::cout << "Header" << header << std::endl;
        // packet.setHeader(header);

        // std::vector<char> buffer(1468, 1);
        // int packet_received = 8;
        // int packet_sent = 12;
        // std::memcpy(buffer.data(), &packet_received, sizeof(int));
        // std::memcpy(buffer.data() + sizeof(int), &packet_sent, sizeof(int));

        // packet.setContent(buffer);

        // serverSocket.send(packet.getBuffer(), 1468, serverEndpoint);
        // Run the IO context to initiate asynchronous operations
        ioContextManager.run();


        if (commandLine.Count > 1) {
            Application::Get().Close();
            return;
        }

        // Create the world
        _World = World::CreateWorld();

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
