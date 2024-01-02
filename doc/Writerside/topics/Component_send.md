# ComponentSend

The component send example of the Network. It contains the classes that will be used to send components.

It shows you how to send components using the Network.

## Client

The client is the one who recieves the components.

### Create the client

The client is created as default, by loading the project and adding a player.

```c++
Project::Load("./Client/R-Type.proj");

Entity *entity = _World->CreateEntity("Player");
entity->AddComponent<TransformComponent>(glm::vec3(1.0f, 0.0f, 0.0f));
entity->AddComponent<SpriteRendererComponent>(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
```

### Add the component receiver

In the  `onAttach` method of the layer, add the component receiver.

```c++
_Network.Loop();
_Network.SendAskConnect("0.0.0.0", 7070);
```

For example here he will connect in localhost on the port 7070.

And that's it ! You can now recieve components.

## Server

The server is the one who sends the components.

### Create the server

The server is created as default, by loading the project.

```c++
Exodia::Log::Init();

Exodia::Project::Load("./Client/R-Type.proj");

Exodia::RendererAPI::SetAPI(Exodia::RendererAPI::API::None);
```

### Add the component sender

In the main of the server, add the component sender.

```c++
Exodia::Server server(7070);

server.Init();
server.Run();
```

For example here he will create a server on the port 7070.

When the server is running, he will update himself, and here you can send components.

### Send components

In the `onUpdate` method of the layer, send the components by updating components that are in the world.

```c++
_World->OnUpdateRuntime(timestep);
```
