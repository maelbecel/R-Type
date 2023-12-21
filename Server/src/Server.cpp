/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** Server
*/

#include "Server.hpp"
#include "R-Type.hpp"

namespace Exodia {

    Server::Server(short port): _network(_world, _ioContextManager, port)
    {
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

    Server::~Server()
    {
        std::cout << "Server is closing !" << std::endl;
        _inputThread.join();
    }

    void Server::HandleCommand(const std::string &command)
    {
        std::cout << "Command received: " << command << std::endl;
        if (command == "stop") {
            this->_running = false;
            this->Stop();
        }
        if (command == "update") {
            this->Update();
        }
        if (command == "dump") {
            std::cout << "Clients: " << std::endl;
            if (_network.GetConnections().empty())
                std::cout << "No clients connected" << std::endl;
            for (auto connection : _network.GetConnections()) {
                std::cout << "IP: " << connection.second.GetEndpoint().address().to_string() << " Port: " << connection.second.GetEndpoint().port() << std::endl;
            }
            std::cout << "Entities: " << std::endl;
            auto entities = _world->AllEntities();
            std::size_t i = 0;
            for (auto entity : entities) {
                (void)entity;
                i++;
            }
            std::cout << "Total: " << i << std::endl;
        }
        if (command == "packet") {
            _network.SendPacketInfo();
        }
    }

    void Server::Init()
    {
        while (_network.GetConnections().empty()) {
            std::cout << "Waiting for clients to connect..." << std::endl;
            sleep(1);
        }
        RendererAPI::SetAPI(RendererAPI::API::None);

        std::cout << "Server is initializing !" << std::endl;
        try {
            // Register the systems
            _world->RegisterSystem(new AnimationSystem());      // Animation system
            _world->RegisterSystem(new ScriptSystem());         // Script system
            _world->RegisterSystem(new MovingSystem(1.5f));     // Moving system

            CollisionSystem *collisionSystem = new CollisionSystem();
            _world->RegisterSystem(collisionSystem);
            _world->Subscribe<Events::OnCollisionEntered>(collisionSystem);

            // // Create the entities
            // // CreatePlayer(_world);
            // CreatePataPata(_world);
            // CreateBackground(_world);

            Exodia::Entity *entity = _world->CreateEntity();
            entity->AddComponent<IDComponent>();
            entity->AddComponent<CircleRendererComponent>(glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f });
            _network.SendEntity(entity, "CircleRendererComponent");
            Exodia::Entity *entity2 = _world->CreateEntity();
            entity2->AddComponent<IDComponent>();
            entity2->AddComponent<CircleRendererComponent>(glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f });
            entity2->AddComponent<TransformComponent>(glm::vec3{2.0f, 0.0f, 0.0f});
            _network.SendEntity(entity2, "CircleRendererComponent");
            _network.SendEntity(entity2, "TransformComponent");

        } catch (std::exception &e) {
            std::cerr << "Exception: " << e.what() << std::endl;
        }
        std::cout << "Server is initialized !" << std::endl;
    }

    void Server::Run()
    {
        std::cout << "Server is running !" << std::endl;
        try {
            while(_running) {
                this->Update();
            }
        } catch (std::exception &e) {
            std::cerr << "Exception: " << e.what() << std::endl;
        }
        std::cout << "Server is stopped !" << std::endl;
    }

    void Server::Update()
    {
        try {
            float time = _Timer.Elapsed();

            Timestep timestep(time - _lastTime);

            _lastTime = time;

            this->_world->Update(timestep);

            //send entities
            this->_world->ForEach<CircleRendererComponent, TransformComponent>([&](Entity *entity, ComponentHandle<CircleRendererComponent> circle, ComponentHandle<TransformComponent> transform) {
                if (circle && transform) {
                    _network.SendEntity(entity, "CircleRendererComponent");
                    entity->GetComponent<TransformComponent>().Get().Translation.y += 0.01f;
                    entity->GetComponent<TransformComponent>().Get().Translation.z = 0;
                    _network.SendEntity(entity, "TransformComponent");
                }
            });
            usleep(1000000 / 24);

            std::queue<uint32_t> events = _network.flushEvents();
            for (std::size_t i = 0; i < events.size(); i++) {
                this->_world->ForEach<CircleRendererComponent>([&](Entity *entity, ComponentHandle<CircleRendererComponent> circle) {
                    (void)entity;
                    if (circle) {
                        circle.Get().Color = glm::vec4{ 1.0f, 0.0f, 0.0f, 1.0f };
                    }
                });
                events.pop();
            }

        } catch (std::exception &e) {
            std::cerr << "Unable to update the world: " << e.what() << std::endl;
        }
    }


}; // namespace Exodia