/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** Server
*/

#include "Server.hpp"
#include <thread>

namespace Exodia {

    Server::Server(short port) : _network(_worldNetwork, _ioContextManager, port), _lastTime(0.0f) {
        std::cout << "Server is launching !" << std::endl;

        _inputThread = std::thread([&] {
            while (this->_running) {
                if (std::cin.peek() != EOF) {
                    std::string inputCommand;
                    std::getline(std::cin, inputCommand);

                    HandleCommand(inputCommand);
                }
            }
        });
    }

    Server::~Server() {
        std::cout << "Server is closing !" << std::endl;

        _inputThread.join();
    }

    void Server::HandleCommand(const std::string &command) {
        std::cout << "Command received: " << command << std::endl;

        if (command == "stop") {
            this->_running = false;
            this->Stop();
        }

        if (command == "update")
            this->Update();
        if (command == "dump") {
            std::cout << "Clients : " << std::endl;

            if (_network.GetConnections().empty())
                std::cout << "No clients connected" << std::endl;

            for (auto connection : _network.GetConnections())
                std::cout << "IP: " << connection.second.GetEndpoint().address().to_string()
                          << " Port: " << connection.second.GetEndpoint().port() << std::endl;
            std::cout << "Entities : " << std::endl;
            std::cout << "\tTotal : " << _worldNetwork->GetCount() << std::endl;
        }

        if (command == "packet")
            _network.SendPacketInfo();
    }

    void Server::Init() {
        while (_network.GetConnections().empty()) {
            std::cout << "Waiting for clients to connect..." << std::endl;

            std::this_thread::sleep_for(std::chrono::seconds(1)); // Sleep for 1 second
        }

        std::cout << "Server is initializing !" << std::endl;

        try {
            // Create world
            _World = CreateRef<Scene>();
            _World->OnViewportResize(1600, 900);

            CollisionSystem *collisionSystem = new CollisionSystem();
            _World->RegisterSystem(collisionSystem);
            _World->Subscribe<Events::OnCollisionEntered>(collisionSystem);

            // Create the camera entity
            Entity *cameraEntity = _World->CreateEntity("Camera");
            auto &camera = cameraEntity->AddComponent<CameraComponent>().Get();

            cameraEntity->GetComponent<TransformComponent>().Get().Translation = {0.0f, 0.0f, 15.0f};
            cameraEntity->GetComponent<TransformComponent>().Get().Rotation = {0.0f, 0.0f, 45.0f};
            camera.Camera.SetProjectionType(SceneCamera::ProjectionType::Perspective);
            camera.Camera.SetViewportSize(1600, 900);

            auto body_camera = cameraEntity->AddComponent<RigidBody2DComponent>();
            body_camera.Get().Type = RigidBody2DComponent::BodyType::Dynamic;
            body_camera.Get().Mass = 0.0f;
            body_camera.Get().GravityScale = 0.0f;
            body_camera.Get().Velocity = glm::vec2{1.5f, 0.0f};

            _World->OnRuntimeStart();
        } catch (std::exception &e) {
            std::cerr << "Exception: " << e.what() << std::endl;
        }
        std::cout << "Server is initialized !" << std::endl;
    }

    void Server::Run() {
        std::cout << "Server is running !" << std::endl;

        try {
            while (_running)
                this->Update();
        } catch (std::exception &e) {
            std::cerr << "Exception: " << e.what() << std::endl;
        }
        std::cout << "Server is stopped !" << std::endl;
    }

    void Server::Update() {
        try {
            float time = _Timer.Elapsed();

            Timestep timestep(time - _lastTime);

            _lastTime = time;

            auto pata = _World->GetEntityByName("Pata-pata");

            if (pata == nullptr) {
                Entity *patata = _World->CreateEntity("Pata-pata");

                patata->AddComponent<BoxCollider2DComponent>();

                auto body_patata = patata->AddComponent<RigidBody2DComponent>();

                body_patata.Get().Type = RigidBody2DComponent::BodyType::Dynamic;
                body_patata.Get().Mass = 0.0f;
                body_patata.Get().GravityScale = 0.0f;
                body_patata.Get().Velocity.x = -2.0f;
                // Set entity sprite
                auto sprite = patata->AddComponent<SpriteRendererComponent>(glm::vec4{0.3f, 0.8f, 0.2f, 1.0f});

                sprite.Get().Texture =
                    SubTexture2D::CreateFromCoords(90123456789012678, {0.0f, 0.0f}, {33.3125f, 36.0f}, {1.0f, 1.0f});

                _network.SendComponentOf(patata, "SpriteRendererComponent");
            }
            _World->OnUpdateRuntime(timestep);
        } catch (std::exception &e) {
            std::cerr << "Unable to update the world: " << e.what() << std::endl;
        }
    }

}; // namespace Exodia