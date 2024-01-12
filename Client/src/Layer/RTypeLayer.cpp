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
#include <sstream>

using namespace Exodia;

namespace RType {

    //////////////////////////////
    // Constructor & Destructor //
    //////////////////////////////

    RTypeLayer::RTypeLayer() : Layer("R-Type"), _WorldNetwork(Exodia::World::CreateWorld()), _Network(nullptr){};

    /////////////
    // Methods //
    /////////////

    int RTypeLayer::GetPort() {

        ApplicationCommandLineArgs commandLine = Application::Get().GetSpecification().CommandLineArgs;

        // TODO: Temp port ./r-type_client {port} {ip} {port}
        int port = 8083; // Default port
        if (commandLine.Count > 1) {
            port = std::stoi(commandLine[1]);

            if (port < 1024 || port > 65535) {
                Application::Get().Close();
                return -1;
            }
        }
        return port;
    }

    std::string RTypeLayer::GetIp() {

        ApplicationCommandLineArgs commandLine = Application::Get().GetSpecification().CommandLineArgs;

        // TODO: Temp ip ./r-type_client {port} {ip} {port}
        std::string ip = "127.0.0.1"; // Default ip
        if (commandLine.Count > 2) {
            ip = commandLine[2];
        }
        return ip;
    }

    int RTypeLayer::GetServerPort() {
        ApplicationCommandLineArgs commandLine = Application::Get().GetSpecification().CommandLineArgs;

        // TODO: Temp port ./r-type_client {port} {ip} {port}
        int port = 8082; // Default port
        if (commandLine.Count > 3) {
            port = std::stoi(commandLine[3]);

            if (port < 1024 || port > 65535) {
                Application::Get().Close();
                return -1;
            }
        }
        return port;
    }

    void RTypeLayer::ConnectToServer(int port, std::string ip, int serverPort) {
        (void)port;
        _Network->Loop();
        _Network->SendAskConnect(ip, (short)serverPort);
    }

    void RTypeLayer::OnAttach() {
        EXODIA_PROFILE_FUNCTION();

        int port = GetPort();
        std::string ip = GetIp();
        int serverPort = GetServerPort();
        _Network = CreateScope<Network::Network>(_WorldNetwork, _IOContextManager, port);

        if (port == -1)
            return;

        // Create world
        CurrentScene = GAME;

        CollisionSystem *collisionSystem = new CollisionSystem();

        Scenes[GAME] = CreateRef<Scene>();
        Scenes[GAME]->RegisterSystem(new AnimationSystem());
        Scenes[GAME]->RegisterSystem(new MovingSystem(1.5f));
        Scenes[GAME]->RegisterSystem(collisionSystem);
        Scenes[GAME]->RegisterSystem(new ClockSystem());

        Scenes[GAME]->Subscribe<Exodia::Events::OnCollisionEntered>(collisionSystem);
        Scenes[GAME]->OnViewportResize(Application::Get().GetWindow().GetWidth(),
                                       Application::Get().GetWindow().GetHeight());

        _Network->SetWorld(Scenes[CurrentScene]->GetWorldPtr());

        // TODO: Temp code

        // Create the camera entity
        Entity *cameraEntity = Scenes[GAME]->CreateEntity("Camera");

        CameraComponent &camera = cameraEntity->AddComponent<CameraComponent>().Get();
        cameraEntity->GetComponent<TransformComponent>().Get().Translation = {0.0f, 0.0f, 15.0f};
        camera.Camera.SetProjectionType(SceneCamera::ProjectionType::Perspective);
        camera.Camera.SetViewportSize(Application::Get().GetWindow().GetWidth(),
                                      Application::Get().GetWindow().GetHeight());

        for (int i = 0; i < 60; i++) {
            Entity *star = Scenes[GAME]->CreateEntity("Star" + std::to_string(i));
            star->AddComponent<ScriptComponent>().Get().Bind("Star");
        }

        // Create the camera
        Scenes[CurrentScene]->OnRuntimeStart();

        ConnectToServer(port, ip, serverPort);
    }

    void RTypeLayer::OnDetach() {
        EXODIA_PROFILE_FUNCTION();
        _Network->SendDisconnect();
        EXODIA_CORE_ERROR("RTypeLayer::OnDetach()");
    }

    void RTypeLayer::OnUpdate(Exodia::Timestep ts) {
        EXODIA_PROFILE_FUNCTION();
        // Renderer Prep
        {
            EXODIA_PROFILE_SCOPE("Renderer Prep");

            Exodia::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
            Exodia::RenderCommand::Clear();
        }

        // Update
        if (CurrentScene == GAME) {
        };

        _packetTimer += ts;
        if (_packetTimer >= 1) {
            _Network->SendPacketInfo();
            _packetTimer = 0;
        }
        // Update the world
        Scenes[CurrentScene]->OnUpdateRuntime(ts);
    }

    void RTypeLayer::OnImGUIRender() { EXODIA_PROFILE_FUNCTION(); }

    void RTypeLayer::OnEvent(Exodia::Event &event) {
        EventDispatcher dispatcher(event);

        dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(RTypeLayer::OnKeyPressedEvent));
        dispatcher.Dispatch<KeyReleasedEvent>(BIND_EVENT_FN(RTypeLayer::OnKeyReleasedEvent));
        dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(RTypeLayer::OnWindowResizeEvent));
    }

    bool RTypeLayer::OnKeyPressedEvent(KeyPressedEvent &event) {

        int key = event.GetKeyCode();

        Scenes[CurrentScene]->GetWorld().LockMutex();
        Scenes[CurrentScene]->GetWorld().ForEach<ScriptComponent, TagComponent>(
            [&](Entity *entity, ComponentHandle<ScriptComponent> script, ComponentHandle<TagComponent> tag) {
                ScriptComponent &sc = script.Get();
                TagComponent &tc = tag.Get();

                std::ostringstream oss;
                oss << _Network->GetIdPlayer();
                std::string player = "Player_" + oss.str();

                if ((tc.Tag.compare(player) == 0) && sc.Instance != nullptr) {
                    sc.Instance->OnKeyPressed(key);

                    _Network->SendEvent(false, key, true);
                }
                (void)entity;
            });
        if (key == Key::ESCAPE) {
            NetworkInfo info = _Network->GetNetworkInfo();
            EXODIA_CORE_ERROR("PACKET info");
            EXODIA_CORE_ERROR("Send packet: {0}", info.sendPacket);
            EXODIA_CORE_ERROR("Received packet: {0}", info.receivedPacket);
            EXODIA_CORE_ERROR("KiloByte sent: {0}", info.kiloByteSent);
            EXODIA_CORE_ERROR("KiloByte received: {0}", info.kiloByteReceived);
            EXODIA_CORE_ERROR("Packet loss sent: {0}", info.sendPacketLost);
            EXODIA_CORE_ERROR("Packet loss received: {0}", info.receivePacketLost);
            EXODIA_CORE_ERROR("PING sent: {0}", info.ping);
        }
        Scenes[CurrentScene]->GetWorld().UnlockMutex();

        return true;
    };

    bool RTypeLayer::OnKeyReleasedEvent(KeyReleasedEvent &event) {
        int key = event.GetKeyCode();

        Scenes[CurrentScene]->GetWorld().LockMutex();
        Scenes[CurrentScene]->GetWorld().ForEach<ScriptComponent, TagComponent>(
            [&](Entity *entity, ComponentHandle<ScriptComponent> script, ComponentHandle<TagComponent> tag) {
                ScriptComponent &sc = script.Get();
                TagComponent &tc = tag.Get();

                std::ostringstream oss;
                oss << _Network->GetIdPlayer();
                std::string player = "Player_" + oss.str();

                if ((tc.Tag.compare(player) == 0) && sc.Instance != nullptr) {
                    sc.Instance->OnKeyReleased(key);
                    _Network->SendEvent(false, key, false);
                }

                (void)entity;
            });
        Scenes[CurrentScene]->GetWorld().UnlockMutex();

        return false;
    };

    bool RTypeLayer::OnWindowResizeEvent(WindowResizeEvent &event) {
        if (Scenes[CurrentScene] != nullptr)
            Scenes[CurrentScene]->OnViewportResize(event.GetWidth(), event.GetHeight());

        return true;
    }
}; // namespace RType
