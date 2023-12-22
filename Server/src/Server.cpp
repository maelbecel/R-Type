/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** Server
*/

#include "Server.hpp"
#include "R-Type.hpp"
#include <thread>

namespace Exodia {

    Server::Server(short port): _network(_worldNetwork, _ioContextManager, port), _lastTime(0.0f)
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

    void Server::RegisterComponent(std::string name, std::function<IComponentContainer *(Buffer)> factory) {
        _ComponentFactory.emplace(name, factory);
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
            auto entities = _worldNetwork->AllEntities();
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
            std::this_thread::sleep_for(std::chrono::seconds(1)); // Sleep for 1 second
        }
        RendererAPI::SetAPI(RendererAPI::API::None);

        std::cout << "Server is initializing !" << std::endl;
        try {
            // Register components
            RegisterComponent("IDComponent", [](UNUSED(Buffer data)) -> IComponentContainer * { return new ComponentContainer<IDComponent>(); });
            RegisterComponent("TransformComponent", [](UNUSED(Buffer data)) -> IComponentContainer * { return new ComponentContainer<TransformComponent>(); });
            RegisterComponent("SpriteRendererComponent", [](UNUSED(Buffer data)) -> IComponentContainer * { return new ComponentContainer<SpriteRendererComponent>(); });
            RegisterComponent("BoxCollider2DComponent", [](UNUSED(Buffer data)) -> IComponentContainer * { return new ComponentContainer<BoxCollider2DComponent>(); });
            RegisterComponent("CircleRendererComponent", [](UNUSED(Buffer data)) -> IComponentContainer * { return new ComponentContainer<CircleRendererComponent>(); });
            RegisterComponent("RigidBody2DComponent", [](UNUSED(Buffer data)) -> IComponentContainer * { return new ComponentContainer<RigidBody2DComponent>(); });
            RegisterComponent("ScriptComponent", [](UNUSED(Buffer data)) -> IComponentContainer * { return new ComponentContainer<ScriptComponent>(); });
            RegisterComponent("Health", [](UNUSED(Buffer data)) -> IComponentContainer * { return new ComponentContainer<Health>(); });
            RegisterComponent("Animation", [](UNUSED(Buffer data)) -> IComponentContainer * { return new ComponentContainer<Animation>(); });
            RegisterComponent("Clock", [](UNUSED(Buffer data)) -> IComponentContainer * { return new ComponentContainer<Clock>(); });

            // Create world
            _currentScene = GAME;
            _World[GAME] = CreateRef<Scene>();
            _World[MENU] = CreateRef<Scene>();
            _World[GAME]->OnViewportResize(1600, 900);
            _World[MENU]->OnViewportResize(1600, 900);

            RType::EntityEventSubscriber *subscribe = new RType::EntityEventSubscriber(_network);

            _World[GAME]->RegisterSystem(new AnimationSystem());
            _World[GAME]->RegisterSystem(new ScriptSystem());
            _World[GAME]->RegisterSystem(new MovingSystem(1.5f));

            _World[MENU]->RegisterSystem(new AnimationSystem());
            _World[MENU]->RegisterSystem(new ScriptSystem());
            _World[MENU]->RegisterSystem(new MovingSystem(1.5f));

            CollisionSystem *collisionSystem = new CollisionSystem();
            _World[GAME]->RegisterSystem(collisionSystem);

            _World[GAME]->Subscribe<Events::OnEntityCreated>(subscribe);
            _World[GAME]->Subscribe<Events::OnEntityDestroyed>(subscribe);
            _World[GAME]->Subscribe<Events::OnCollisionEntered>(collisionSystem);

            // Create the entities
            for (int i = 0; i < 4; i++)
            {
                CreatePlayer(_World, i);
                Entity *player = _World[GAME]->GetEntityByName("Player_" + std::to_string(i));

                EXODIA_CORE_INFO("Player_{}", i);

                _network.SendComponentOf(player, "TransformComponent");
                _network.SendComponentOf(player, "CircleRendererComponent");
            }

            CreatePataPata(_World);
            CreateBackground(_World);
            CreateStars(_World);

            // Create the camera entity
            Entity *cameraEntity = _World[GAME]->CreateEntity("Camera");
            auto &camera = cameraEntity->AddComponent<CameraComponent>().Get();

            cameraEntity->GetComponent<TransformComponent>().Get().Translation = { 0.0f, 0.0f, 15.0f };
            cameraEntity->GetComponent<TransformComponent>().Get().Rotation = { 0.0f, 0.0f, 45.0f };
            camera.Camera.SetProjectionType(SceneCamera::ProjectionType::Perspective);
            camera.Camera.SetViewportSize(1600, 900);

            auto body_camera = cameraEntity->AddComponent<RigidBody2DComponent>();
            body_camera.Get().Type = RigidBody2DComponent::BodyType::Dynamic;
            body_camera.Get().Mass = 0.0f;
            body_camera.Get().GravityScale = 0.0f;
            body_camera.Get().Velocity = glm::vec2{ 1.5f, 0.0f };

            _World[_currentScene]->OnRuntimeStart();
            _network.SetWorld(_World[_currentScene]->GetWorldPtr());

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

            for (int i = 0; i < 4; i++)
            {
                Entity *player = _World[GAME]->GetEntityByName("Player_" + std::to_string(i));

                if (player != nullptr) {
                    _network.SendComponentOf(player, "TransformComponent");
                    _network.SendComponentOf(player, "CircleRendererComponent");
                }
            }

            if (_currentScene == GAME) {
                auto pata = _World[GAME]->GetEntityByName("Pata-pata");

                if (pata == nullptr) {
                    Entity *patata = _World[GAME]->CreateEntity("Pata-pata");

                    patata->AddComponent<Health>(1);
                    patata->AddComponent<ScriptComponent>().Get().Bind<PataPata>();
                    patata->AddComponent<Animation>(1.0f, 8.0f, 0.075f);
                    patata->AddComponent<Clock>();
                    patata->AddComponent<BoxCollider2DComponent>();

                    auto body_patata = patata->AddComponent<RigidBody2DComponent>();

                    body_patata.Get().Type = RigidBody2DComponent::BodyType::Dynamic;
                    body_patata.Get().Mass = 0.0f;
                    body_patata.Get().GravityScale = 0.0f;
                    body_patata.Get().Velocity.x = -2.0f;
                    patata->AddComponent<CircleRendererComponent>(glm::vec4{ 1.0f, 1.0f, 0.0f, 1.0f});
                }

                _network.SendComponentOf(pata, "TransformComponent");
                _network.SendComponentOf(pata, "CircleRendererComponent");

                auto *bullet = _World[GAME]->GetEntityByName("BE68");
                if (bullet != nullptr) {
                    _network.SendComponentOf(bullet, "TransformComponent");
                    _network.SendComponentOf(bullet, "CircleRendererComponent");
                }
            }

            std::queue<std::pair<std::pair<uint32_t, bool>, asio::ip::udp::endpoint>> events = _network.GetEvents();
            while (!events.empty()) {
                auto event = events.front();
                events.pop();
                int player_id = _network.ConnectionPlace(event.second);

                _World[_currentScene]->GetWorld().ForEach<ScriptComponent, TagComponent>([&](UNUSED(Entity *entity), auto script, auto tag) {
                    auto &sc = script.Get();
                    auto &tc = tag.Get();

                    if (tc.Tag == std::string("Player_" + std::to_string(player_id)) && sc.Instance != nullptr) {
                        std::cout << "Event received: " << event.first.first << std::endl;
                        if (event.first.second)
                            sc.Instance->OnKeyPressed(event.first.first);
                        else
                            sc.Instance->OnKeyReleased(event.first.first);
                    }
                });
            }

            _World[_currentScene]->OnUpdateRuntime(timestep);
        } catch (std::exception &e) {
            std::cerr << "Unable to update the world: " << e.what() << std::endl;
        }
    }


}; // namespace Exodia