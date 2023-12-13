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
        Exodia::Entity *entity = world->CreateEntity();
        entity->AddComponent<Exodia::TransformComponent>();
        entity->GetComponent<Exodia::TransformComponent>()->Translation = glm::vec3(1, 2, 3);
        entity->GetComponent<Exodia::TransformComponent>()->Rotation = glm::vec3(4, 5, 6);

        network.sendEntity(entity, "TransformComponent");

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
        ioContextManager.run();
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

    void RTypeLayer::OnImGUIRender()
    {
        EXODIA_PROFILE_FUNCTION();

        ImGui::Begin("Settings");

        ImGui::ColorEdit4("Square Color", glm::value_ptr(_SquareColor));

        ImGui::End();
    }

    void RTypeLayer::OnEvent(Exodia::Event &event)
    {
        _CameraController.OnEvent(event);
    }
};
