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

    //////////////////////////////
    // Constructor & Destructor //
    //////////////////////////////

    Server::Server(short port): _WorldNetwork(World::CreateWorld()), _Network(_WorldNetwork, _IOContextManager, port), _LastTime(0.0f), _Running(true)
    {
        EXODIA_INFO("Server is starting...");

        _InputThread = std::thread([&] {
            while (_Running) {
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
        EXODIA_CORE_INFO("Server is closing...");

        _InputThread.join();
    }

    /////////////
    // Methods //
    /////////////

    void Server::HandleCommand(const std::string &command)
    {
        EXODIA_TRACE("Command received : '{0}'", command);

        if (command == "stop")
            Stop();
        else if (command == "update")
            this->Update();
        else if (command == "dump") {
            EXODIA_TRACE("Clients :");

            if (_Network.GetConnections().empty())
                EXODIA_TRACE("\t-> No clients connected");

            for (auto connection : _Network.GetConnections())
                EXODIA_TRACE("\t-> IP '{0}' : Port '{1}'", connection.second.GetEndpoint().port(), connection.second.GetEndpoint().address().to_string());
            EXODIA_TRACE("\nEntities '{0}'", _WorldNetwork->GetCount());
        } else if (command == "packet")
            _Network.SendPacketInfo();
    }

    void Server::Init()
    {
        while (_Network.GetConnections().empty()) {
            EXODIA_TRACE("Waiting for clients to connect...");

            std::this_thread::sleep_for(std::chrono::seconds(1)); // Sleep for 1 second
        }

        EXODIA_INFO("Server initialisation...");

        try {
            CurrentScene = GAME;

            Scenes[MENU] = CreateRef<Scene>();
            Scenes[MENU]->RegisterSystem(new AnimationSystem());
            Scenes[MENU]->RegisterSystem(new ScriptSystem());
            Scenes[MENU]->RegisterSystem(new MovingSystem(1.5f));

            RType::EntityEventSubscriber *subscribe = new RType::EntityEventSubscriber(_Network);
            CollisionSystem              *collisionSystem = new CollisionSystem();

            Scenes[GAME] = CreateRef<Scene>();
            Scenes[GAME]->RegisterSystem(new AnimationSystem());
            Scenes[GAME]->RegisterSystem(new ScriptSystem());
            Scenes[GAME]->RegisterSystem(new MovingSystem(1.5f));
            Scenes[GAME]->RegisterSystem(collisionSystem);
            Scenes[GAME]->Subscribe<Events::OnEntityCreated>(subscribe);
            Scenes[GAME]->Subscribe<Events::OnEntityDestroyed>(subscribe);
            Scenes[GAME]->Subscribe<Events::OnCollisionEntered>(collisionSystem);

            // TODO: Temp player creation
            for (int i = 0; i < 4; i++) {
                CreatePlayer(Scenes, i);

                Entity *player = Scenes[GAME]->GetEntityByName("Player_" + std::to_string(i));

                _Network.SendComponentOf(player, "TransformComponent");
                _Network.SendComponentOf(player, "CircleRendererComponent");
            }

            CreatePataPata(Scenes);
            CreateBackground(Scenes);
            CreateStars(Scenes);

            // Camera creation
            Entity *cameraEntity = Scenes[GAME]->CreateEntity("Camera");

            auto &camera = cameraEntity->AddComponent<CameraComponent>().Get();

            cameraEntity->GetComponent<TransformComponent>().Get().Translation = { 0.0f, 0.0f, 15.0f };
            cameraEntity->GetComponent<TransformComponent>().Get().Rotation = { 0.0f, 0.0f, 45.0f };
            camera.Camera.SetProjectionType(SceneCamera::ProjectionType::Perspective);

            auto body_camera = cameraEntity->AddComponent<RigidBody2DComponent>();

            body_camera.Get().Type = RigidBody2DComponent::BodyType::Dynamic;
            body_camera.Get().Mass = 0.0f;
            body_camera.Get().GravityScale = 0.0f;
            body_camera.Get().Velocity = glm::vec2{ 1.5f, 0.0f };

            Scenes[CurrentScene]->OnRuntimeStart(); // TODO: Remove and play start only when all players are connected or main player said play

            _Network.SetWorld(Scenes[CurrentScene]->GetWorldPtr());
        } catch (std::exception &error) {
            EXODIA_ERROR("Exception :\n\t{0}", error.what());
        }
        EXODIA_INFO("Server initialised !");
    }

    void Server::Run()
    {
        EXODIA_INFO("Server is running !");

        try {
            while(_Running)
                this->Update();
        } catch (std::exception &error) {
            EXODIA_ERROR("Exception :\n\t{0}", error.what());
        }
        EXODIA_INFO("Server stopped !");
    }

    void Server::Stop()
    {
        _Running = false;
    }

    void Server::Update()
    {
        try {
            float time = _Timer.Elapsed();

            Timestep timestep(time - _LastTime);

            _LastTime = time;

            for (int i = 0; i < 4; i++) {
                Entity *player = Scenes[GAME]->GetEntityByName("Player_" + std::to_string(i));

                if (player != nullptr) {
                    _Network.SendComponentOf(player, "TransformComponent");
                    _Network.SendComponentOf(player, "CircleRendererComponent");
                }
            }

            if (CurrentScene == GAME) {
                auto pata = Scenes[GAME]->GetEntityByName("Pata-pata");

                if (pata == nullptr) {
                    Entity *patata = Scenes[GAME]->CreateEntity("Pata-pata");

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

                _Network.SendComponentOf(pata, "TransformComponent");
                _Network.SendComponentOf(pata, "CircleRendererComponent");

                auto *bullet = Scenes[GAME]->GetEntityByName("BE68");

                if (bullet != nullptr) {
                    _Network.SendComponentOf(bullet, "TransformComponent");
                    _Network.SendComponentOf(bullet, "CircleRendererComponent");
                }
            }

            std::queue<std::pair<std::pair<uint32_t, bool>, asio::ip::udp::endpoint>> events = _Network.GetEvents();

            while (!events.empty()) {
                auto event = events.front();

                events.pop();

                int player_id = _Network.ConnectionPlace(event.second);

                Scenes[CurrentScene]->GetWorld().ForEach<ScriptComponent, TagComponent>([&](Entity *entity, auto script, auto tag) {
                    (void)entity;

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

            Scenes[CurrentScene]->OnUpdateRuntime(timestep);
        } catch (std::exception &error) {
            EXODIA_ERROR("Unable to update the world :\n\t{0}", error.what());
        }
    }
};
