/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** Server
*/

#include "Server.hpp"
#include "R-Type.hpp"
#include <thread>

using namespace RType;

namespace Exodia {

    //////////////////////////////
    // Constructor & Destructor //
    //////////////////////////////

    /**
     * The Server constructor initializes a server object with a specified port and starts a separate
     * thread to handle user input commands.
     *
     * @param port The "port" parameter is the port number on which the server will listen for incoming
     * network connections.
     */
    Server::Server(short port)
        : _WorldNetwork(World::CreateWorld()), _Network(_WorldNetwork, _IOContextManager, port), _LastTime(0.0f),
          _Running(true) {
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

    /**
     * The Server destructor logs a closing message, sets the _Running flag to false, and joins the
     * _InputThread if it is joinable.
     */
    Server::~Server() {
        EXODIA_CORE_INFO("Server is closing...");

        _Running = false;
        if (_InputThread.joinable())
            _InputThread.join();
    }

    /////////////
    // Methods //
    /////////////

    /**
     * The function `HandleCommand` in the `Server` class handles different commands received and
     * performs corresponding actions based on the command.
     *
     * @param command The `command` parameter is a `std::string` that represents the command received
     * by the server.
     */
    void Server::HandleCommand(const std::string &command) {
        EXODIA_TRACE("Command received : '{0}'", command);

        if (command == "stop")
            Stop();
        else if (command == "update")
            this->Update();
        else if (command == "dump") {
            EXODIA_TRACE("Clients :");

            if (_Network.GetConnections().empty())
                EXODIA_TRACE("\t-> No clients connected");

            for (std::pair<const std::string, Connection> connection : _Network.GetConnections())
                EXODIA_TRACE("\t-> IP '{0}' : Port '{1}'", connection.second.GetEndpoint().port(),
                             connection.second.GetEndpoint().address().to_string());
            EXODIA_TRACE("\nEntities '{0}'", _WorldNetwork->GetCount());
        } else if (command == "packet")
            _Network.SendPacketInfo();
    }

    /**
     * The function initializes a scene and registers optional entity systems to it.
     *
     * @param scene The `scene` parameter is of type `SceneType` and represents the type of scene that
     * will be initialized.
     * @param systems The `systems` parameter is an optional parameter of type
     * `std::optional<std::vector<Exodia::EntitySystem *>>`. It represents a collection of
     * `Exodia::EntitySystem` pointers. The `std::optional` wrapper indicates that the parameter is
     * optional and may or may not have
     */
    void Server::InitScene(SceneType scene, std::optional<std::vector<Exodia::EntitySystem *>> systems) {
        Scenes[scene] = CreateRef<Scene>();

        if (systems.has_value()) {
            for (EntitySystem *system : systems.value()) {
                Scenes[scene]->RegisterSystem(system);
            }
        }
    }

    /**
     * The function waits for clients to connect to the server.
     */
    void Server::WaitForClient() {
        while (_Network.GetConnections().empty()) {
            EXODIA_TRACE("Waiting for clients to connect...");

            std::this_thread::sleep_for(std::chrono::seconds(1)); // Sleep for 1 second
        }
    }

    /**
     * The function initializes scenes in a server, including subscribing to entity events and
     * collision events.
     */
    void Server::InitScenes() {
        CurrentScene = GAME;

        std::vector<Exodia::EntitySystem *> systems = {new AnimationSystem(), new MovingSystem(1.5f)};
        InitScene(MENU, systems);

        RType::EntityEventSubscriber *subscribe = new RType::EntityEventSubscriber(_Network);
        CollisionSystem *collisionSystem = new CollisionSystem();
        systems.push_back(collisionSystem);
        InitScene(GAME, systems);

        Scenes[GAME]->Subscribe<Events::OnEntityCreated>(subscribe);
        Scenes[GAME]->Subscribe<Events::OnEntityDestroyed>(subscribe);
        Scenes[GAME]->Subscribe<Events::OnCollisionEntered>(collisionSystem);
    }

    /**
     * The function initializes entities in a server by creating a "pata-pata" entity and a camera
     * entity.
     */
    void Server::InitEntities() {
        // Create pata-pata
        Entity *patata = Scenes[GAME]->CreateEntity("Pata-pata");
        patata->AddComponent<ScriptComponent>().Get().Bind("PataPata");

        // Camera creation
        Entity *cameraEntity = Scenes[GAME]->CreateEntity("Camera");

        CameraComponent &camera = cameraEntity->AddComponent<CameraComponent>().Get();

        cameraEntity->GetComponent<TransformComponent>().Get().Translation = {0.0f, 0.0f, 15.0f};
        cameraEntity->GetComponent<TransformComponent>().Get().Rotation = {0.0f, 0.0f, 45.0f};
        camera.Camera.SetProjectionType(SceneCamera::ProjectionType::Perspective);
    }

    /**
     * The function initializes the server by waiting for a client, initializing scenes and entities,
     * and setting up the network.
     */
    void Server::Init() {

        WaitForClient();
        EXODIA_INFO("Server initialisation...");

        try {
            InitScenes();
            InitEntities();
            /* Removing rigid body for static camera
            auto body_camera = cameraEntity->AddComponent<RigidBody2DComponent>();
            body_camera.Get().Type = RigidBody2DComponent::BodyType::Dynamic;
            body_camera.Get().Mass = 0.0f;
            body_camera.Get().GravityScale = 0.0f;
            body_camera.Get().Velocity = glm::vec2{ 1.5f, 0.0f };
            */
            Scenes[CurrentScene]->OnRuntimeStart(); // TODO: Remove and play start only when all players are connected
                                                    // or main player said play
            _Network.SetWorld(Scenes[CurrentScene]->GetWorldPtr());
        } catch (std::exception &error) {
            EXODIA_ERROR("Exception :\n\t{0}", error.what());
        }
        EXODIA_INFO("Server initialised !");
    }

    /**
     * The function `Server::Run()` runs the server and performs various tasks such as checking for new
     * clients, updating the server, and logging information about entities.
     */
    void Server::Run() {
        EXODIA_INFO("Server is running !");

        try {
            while (_Running) {
                CheckForNewClients();
                this->Update();
                /*
                Scenes[CurrentScene]->GetWorld().ForEach<IDComponent, TagComponent>([&](Entity *entity, auto id, auto
                tag) { (void)entity;

                    EXODIA_INFO("Entity '{0}': {1}", (uint64_t)id.Get().ID, tag.Get().Tag);
                });
                count += 1;
                */
                std::this_thread::sleep_for(std::chrono::milliseconds(16)); // Sleep for 32 milliseconds (30 FPS)
            }
        } catch (std::exception &error) {
            EXODIA_ERROR("Exception :\n\t{0}", error.what());
        }
        EXODIA_INFO("Server stopped !");
    }

    /**
     * The function "Stop" sets the value of the variable "_Running" to false.
     */
    void Server::Stop() { _Running = false; }

    /**
     * The function `HandleEvent` handles events received by the server, updating the corresponding
     * script instances and sending component data over the network.
     *
     * @param event The event parameter is a std::pair<std::pair<uint32_t, bool>,
     * asio::ip::udp::endpoint>. It consists of two parts:
     */
    void Server::HandleEvent(std::pair<std::pair<uint32_t, bool>, asio::ip::udp::endpoint> event) {
        int32_t player_id = _Network.ConnectionPlace(event.second);

        Scenes[CurrentScene]->GetWorld().ForEach<ScriptComponent, TagComponent, TransformComponent>(
            [&](Entity *entity, ComponentHandle<ScriptComponent> script, ComponentHandle<TagComponent> tag,
                UNUSED(ComponentHandle<TransformComponent> transform)) {
                ScriptComponent &sc = script.Get();
                TagComponent &tc = tag.Get();

                if (tc.Tag == std::string("Player_" + std::to_string(player_id)) && sc.Instance != nullptr) {
                    if (event.first.second) {
                        sc.Instance->OnKeyPressed(event.first.first);
                    } else {
                        sc.Instance->OnKeyReleased(event.first.first);
                    }
                }
                if (count % 50 == 0) {
                    _Network.SendComponentOf(entity, "TransformComponent");
                }
                _Network.SendComponentOf(entity, "RigidBody2DComponent");
            });

        Scenes[CurrentScene]->GetWorld().ForEach<TagComponent, TransformComponent>(
            [&](Entity *entity, ComponentHandle<TagComponent> tag,
                UNUSED(ComponentHandle<TransformComponent> transform)) {
                if (tag.Get().Tag.rfind("Bullet") != std::string::npos) {
                    _Network.SendComponentOf(entity, "TagComponent");
                    _Network.SendComponentOf(entity, "SpriteRendererComponent");
                }
            });
    }

    /**
     * The function `Server::Update()` updates the server's state and handles network events.
     */
    void Server::Update() {
        try {
            float time = _Timer.Elapsed();

            Timestep timestep(time - _LastTime);

            _LastTime = time;

            my_Timer += timestep;
            if (my_Timer > 1.0f) {
                my_Timer = 0.0f;
                _Network.SendPacketInfo();
            }


            std::vector<std::pair<std::pair<uint32_t, bool>, asio::ip::udp::endpoint>> events = _Network.GetEvents();

            while (!events.empty()) {
                HandleEvent(events[events.size() - 1]);
                events.pop_back();
            }

            // _Network.ResendNeedAck();
            // Scenes[CurrentScene]->ForEach<TransformComponent>([&](Entity *entity, auto transform) {
            //     (void)entity;
            //     (void)transform;
            //     _Network.SendComponentOf(entity, "TransformComponent");
            // });

            Scenes[CurrentScene]->OnUpdateRuntime(timestep);
        } catch (std::exception &error) {
            EXODIA_ERROR("Unable to update the world :\n\t{0}", error.what());
        }
    }

    /**
     * The function checks if a client is new by comparing its connection with existing connections in
     * the server.
     *
     * @param connection A pair consisting of a constant string (representing the client's username)
     * and a Connection object (representing the client's connection information).
     *
     * @return a boolean value, which indicates whether the client is new or not.
     */
    bool Server::IsClientNew(std::pair<const std::string, Connection> connection) {
        bool newClient = true;
        for (User user : _Users) {
            if (user.GetConnection() == connection.second) {
                newClient = false;
            }
        }
        return newClient;
    }

    void Server::SendComponents(SceneType scene) {
        Scenes[scene]->GetWorld().ForEach<TagComponent>([&](Entity *entity, ComponentHandle<TagComponent> tag) {
            if (tag.Get().Tag.rfind("Player_") != std::string::npos) {
                _Network.SendComponentOf(entity, "TagComponent");
                _Network.SendComponentOf(entity, "TransformComponent");
                _Network.SendComponentOf(entity, "SpriteRendererComponent");
                _Network.SendComponentOf(entity, "RigidBody2DComponent");
                _Network.SendComponentOf(entity, "Animation");
                _Network.SendComponentOf(entity, "Health");
                _Network.SendComponentOf(entity, "ScriptComponent");
            }

            if (tag.Get().Tag == "Pata-pata") {
                _Network.SendComponentOf(entity, "TagComponent");
                _Network.SendComponentOf(entity, "TransformComponent");
                _Network.SendComponentOf(entity, "SpriteRendererComponent");
                _Network.SendComponentOf(entity, "RigidBody2DComponent");
                _Network.SendComponentOf(entity, "Animation");
                _Network.SendComponentOf(entity, "Health");
                _Network.SendComponentOf(entity, "ScriptComponent");
            }
        });
    }

    /**
     * The function checks for new client connections and creates player entities for them.
     *
     * @return If the `connections` map is empty, the function will return and nothing will be returned
     * explicitly.
     */
    void Server::CheckForNewClients() {
        Entity *player = nullptr;
        std::map<std::string, Connection> connections = _Network.GetConnections();

        if (connections.empty()) {
            return;
        }
        for (std::pair<const std::string, Connection> connection : connections) {
            if (IsClientNew(connection)) {
                uint32_t userID = _Users.size();
                Entity *entity = Scenes[GAME]->CreateEntity("Player_" + std::to_string(userID));

                entity->AddComponent<ScriptComponent>().Get().Bind("Player");
                player = Scenes[GAME]->GetEntityByName("Player_" + std::to_string(userID));
                _Users.push_back(User(connection.second, player));
                SendComponents(GAME);
                EXODIA_INFO("New client connected");
            }
        }
    }
}; // namespace Exodia
