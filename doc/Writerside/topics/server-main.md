# Main

The main part of the server is very simple.

We start by initialize the logger.

```c++
Exodia::Log::Init();
```

Then we set up the renderer API.

```c++
Exodia::RendererAPI::SetAPI(Exodia::RendererAPI::API::None);
```

And we can finally initialize the R-Type.

```c++
RType::InitRType();
```

Then we can start the server on the port 8082.

```c++
Exodia::Server server(8082);
server.Init();
server.Run();
```