# RTypeLayer

The R-Type layer is the layer that will contain the game. It inherits from the `Layer` class.

```mermaid
graph LR
RTypeLayer --> Exodia::Layer
```

## R-TypeLayer

```c++
    RTypeLayer::RTypeLayer() : Layer("R-Type"), _WorldNetwork(Exodia::World::CreateWorld()), _Network(nullptr){};
```

It constructs the R-Type layer.


## OnAttach

```c++
    void OnAttach() override;
```

This function is called when the layer is attached to the application.

It will start by create a network.

```c++
        int port = GetPort();
        std::string ip = GetIp();
        int serverPort = GetServerPort();
        _Network = CreateScope<Network::Network>(_WorldNetwork, _IOContextManager, port);
```

Then we will initialize the game scene.

```c++
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
```

Then we add to the scene a camera.

```c++
        Entity *cameraEntity = Scenes[GAME]->CreateEntity("Camera");

        CameraComponent &camera = cameraEntity->AddComponent<CameraComponent>().Get();
        cameraEntity->GetComponent<TransformComponent>().Get().Translation = {0.0f, 0.0f, 15.0f};
        camera.Camera.SetProjectionType(SceneCamera::ProjectionType::Perspective);
        camera.Camera.SetViewportSize(Application::Get().GetWindow().GetWidth(),
                                      Application::Get().GetWindow().GetHeight());
```

We add stars in background.

```c++
        for (int i = 0; i < 60; i++) {
            Entity *star = Scenes[GAME]->CreateEntity("Star" + std::to_string(i));
            star->AddComponent<ScriptComponent>().Get().Bind("Star");
        }
```

We can finally run the scene and connect to the server.

```c++
        Scenes[CurrentScene]->OnRuntimeStart();
        ConnectToServer(port, ip, serverPort);
```

## OnDetach

```c++
    void OnDetach() override;
```

This function is called when the layer is detached from the application.

It will stop the network.

```c++
        _Network->SendDisconnect();
```

## OnUpdate

```c++
    void OnUpdate(Exodia::TimeStep ts) override;
```

This function is called when the layer is updated.

We start by clearing the screen.

```c++
            Exodia::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
            Exodia::RenderCommand::Clear();
```

Then we send every second an info packet.

```c++
        if (_packetTimer >= 1) {
            _Network->SendPacketInfo();
            _packetTimer = 0;
        }
```

Then we update the scene.

```c++
        Scenes[CurrentScene]->OnUpdateRuntime(ts);
```

## OnImGuiRender

```c++
    void OnImGuiRender() override;
```

This function is called when the layer is rendered.

## OnEvent

```c++
    void OnEvent(Exodia::Event &event) override;
```

This function is called when the layer receive an event.

We will dispatch the event to the scene.

```c++
        Exodia::EventDispatcher dispatcher(event);
        dispatcher.Dispatch<Exodia::KeyPressedEvent>(EXODIA_BIND_EVENT_FN(RTypeLayer::OnKeyPressedEvent));
        dispatcher.Dispatch<Exodia::KeyReleasedEvent>(EXODIA_BIND_EVENT_FN(RTypeLayer::OnKeyReleasedEvent));
        dispatcher.Dispatch<Exodia::WindowResizeEvent>(EXODIA_BIND_EVENT_FN(RTypeLayer::OnWindowResizeEvent));
```

## OnKeyReleasedEvent

```c++
    bool OnKeyReleasedEvent(Exodia::KeyReleasedEvent &event);
```

This function is called when a key is released.

It sends the event to the network.

```c++
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
```

## OnKeyPressedEvent

```c++
    bool OnKeyPressedEvent(Exodia::KeyPressedEvent &event);
```

This function is called when a key is pressed.

We start by sending the event to the network.

```c++
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
```

Then if the key is `Key::Escape` we dump the network info.

```c++
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
```

## OnWindowResizeEvent

```c++
    bool OnWindowResizeEvent(Exodia::WindowResizeEvent &event);
```

This function is called when the window is resized.

We update the camera.

```c++
        Scenes[CurrentScene]->OnViewportResize(event.GetWidth(), event.GetHeight());
```

## GetPort

```c++
    uint16_t GetPort() const;
```

This function is uses to get the port from the command line command.

It will set the port at `8083` by default.

```c++
        ApplicationCommandLineArgs commandLine = Application::Get().GetSpecification().CommandLineArgs;

        int port = 8083; // Default port
        if (commandLine.Count > 1) {
            port = std::stoi(commandLine[1]);

            if (port < 1024 || port > 65535) {
                Application::Get().Close();
                return -1;
            }
        }
        return port;
```

## GetIp

```c++
    const std::string &GetIp() const;
```

This function is uses to get the ip from the command line command.

It will set the ip at `127.0.0.1` by default.

```c++
        ApplicationCommandLineArgs commandLine = Application::Get().GetSpecification().CommandLineArgs;

        std::string ip = "127.0.0.1"; // Default ip
        if (commandLine.Count > 2) {
            ip = commandLine[2];
        }
        return ip;
```

## GetServerPort

```c++
    uint16_t GetServerPort() const;
```

This function is uses to get the server port from the command line command.

It will set the server port at `8082` by default.

```c++
        ApplicationCommandLineArgs commandLine = Application::Get().GetSpecification().CommandLineArgs;

        int serverPort = 8082; // Default server port
        if (commandLine.Count > 3) {
            serverPort = std::stoi(commandLine[3]);

            if (serverPort < 1024 || serverPort > 65535) {
                Application::Get().Close();
                return -1;
            }
        }
        return serverPort;
```

## ConnectToServer

```c++
        void ConnectToServer(int port, std::string ip, int serverPort);
```

This function is uses to connect to the server.

```c++
        _Network->Loop();
        _Network->SendAskConnect(ip, (short)serverPort);
```

