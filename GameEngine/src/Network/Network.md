# Network

The Network module contains classes and functions for networking.
He is divided in 5 parts:

- [**Connection**](Connection.md) : The connection part of the Network module. It contains the classes that will be used to create connections.
- [**Header**](Header.md) : The header part of the Network module. It contains the classes that will be used to create headers.
- [**IOContextManager**](IOContextManager.md) : The IOContextManager part of the Network module. It contains the classes that will be used to create IOContextManagers.
- [**Packet**](Packet.md) : The packet part of the Network module. It contains the classes that will be used to create packets.
- [**UDPSocket**](UDPSocket.md) : The UDPSocket part of the Network module. It contains the classes that will be used to create UDPSockets.

The Network class is the main class of the Network module. It contains the methods that will be used to initialize the Network module.

### Constructor

```c++
Network(World *world, IOContextManager &context, short port);
```

It initializes the Network module.

The constructor takes the following parameters:

| Name    | Type              | Description          |
|---------|-------------------|----------------------|
| world   | World*            | The world            |
| context | IOContextManager& | The IOContextManager |
| port    | short             | The port             |

Here is an example of how to use it:

```c++
Exodia::IOContextManager context;
Exodia::World world;
Exodia::Network network(&world, context, 8080);
```

## loop

The loop function launches the async_receive of the _socket

Here is an example of how to use it:

```c++
void loop();
```

It runs the Network module.

Here is an example of how to use it:

```c++
network.loop();
```

## receivePacketInfo

```c++
void receivePacketInfo(const std::vector<char> message, size_t size, asio::ip::udp::endpoint senderEndpoint);
```

It allows the network to receive packets information.

The method takes the following parameters:

| Name           | Type                        | Description             |
|----------------|-----------------------------|-------------------------|
| message        | const std::vector<char>     | The message             |
| size           | size_t                      | The size of the message |
| senderEndpoint | asio::ip::udp::endpoint     | The sender endpoint     |

Here is an example of how to use it:

```c++
std::vector<char> message;
size_t size;
asio::ip::udp::endpoint senderEndpoint;
network.receivePacketInfo(message, size, senderEndpoint);
```

## receiveAck

```c++
void receiveAck(const std::vector<char> message, size_t size, asio::ip::udp::endpoint senderEndpoint);
```

It allows the network to receive acks. Ack is the short for acknowledgment.

The method takes the following parameters:

| Name           | Type                        | Description             |
|----------------|-----------------------------|-------------------------|
| message        | const std::vector<char>     | The message             |
| size           | size_t                      | The size of the message |
| senderEndpoint | asio::ip::udp::endpoint     | The sender endpoint     |

Here is an example of how to use it:

```c++
std::vector<char> message;
size_t size;
asio::ip::udp::endpoint senderEndpoint;
network.receiveAck(message, size, senderEndpoint);
```

## receiveConnectAccept

```c++
void receiveConnectAccept(const std::vector<char> message, size_t size, asio::ip::udp::endpoint senderEndpoint);
```

It allows the network to receive connect accepts.

The method takes the following parameters:

| Name           | Type                        | Description             |
|----------------|-----------------------------|-------------------------|
| message        | const std::vector<char>     | The message             |
| size           | size_t                      | The size of the message |
| senderEndpoint | asio::ip::udp::endpoint     | The sender endpoint     |

Here is an example of how to use it:

```c++
std::vector<char> message;
size_t size;
asio::ip::udp::endpoint senderEndpoint;
network.receiveConnectAccept(message, size, senderEndpoint);
```

## receiveEntity

```c++
void recieveEntity(const std::vector<char> message, size_t size, asio::ip::udp::endpoint senderEndpoint);
```

It allows the network to receive entities.

The method takes the following parameters:

| Name           | Type                        | Description             |
|----------------|-----------------------------|-------------------------|
| message        | const std::vector<char>     | The message             |
| size           | size_t                      | The size of the message |
| senderEndpoint | asio::ip::udp::endpoint     | The sender endpoint     |

Here is an example of how to use it:

```c++
std::vector<char> message;
size_t size;
asio::ip::udp::endpoint senderEndpoint;
network.recieveEntity(message, size, senderEndpoint);
```

## receiveConnect

```c++
void receiveConnect(const std::vector<char> message, size_t size, asio::ip::udp::endpoint senderEndpoint);
```

It allows the network to receive connects.

The method takes the following parameters:

| Name           | Type                        | Description             |
|----------------|-----------------------------|-------------------------|
| message        | const std::vector<char>     | The message             |
| size           | size_t                      | The size of the message |
| senderEndpoint | asio::ip::udp::endpoint     | The sender endpoint     |

Here is an example of how to use it:

```c++
std::vector<char> message;
size_t size;
asio::ip::udp::endpoint senderEndpoint;
network.receiveConnect(message, size, senderEndpoint);
```

## receiveEvent

```c++
void receiveEvent(const std::vector<char> message, size_t size, asio::ip::udp::endpoint senderEndpoint);
```

It allows the network to receive events.
    
The method takes the following parameters:

| Name           | Type                        | Description             |
|----------------|-----------------------------|-------------------------|
| message        | const std::vector<char>     | The message             |
| size           | size_t                      | The size of the message |
| senderEndpoint | asio::ip::udp::endpoint     | The sender endpoint     |

Here is an example of how to use it:

```c++
std::vector<char> message;
size_t size;
asio::ip::udp::endpoint senderEndpoint;
network.receiveEvent(message, size, senderEndpoint);
```

## sendPacketInfo

```c++
void sendPacketInfo()
```

It allows the network to send packets information.

Here is an example of how to use it:

```c++
network.sendPacketInfo();
```

## sendAck

```c++
void sendAck()
```

It allows the network to send acks. Ack is the short for acknowledgment.

Here is an example of how to use it:

```c++
network.sendAck();
```

## sendAcceptConnect

```c++
void sendAcceptConnect()
```

It allows the network to send accept connects.

Here is an example of how to use it:

```c++
network.sendAcceptConnect();
```

## SendComponentOf

```c++
void SendComponentOf(Entity *entity, std::string component_name);
```

It allows the network to send entities.

The method takes the following parameters:

| Name           | Type                        | Description             |
|----------------|-----------------------------|-------------------------|
| entity         | Entity*                     | The entity              |
| component_name | std::string                 | The component name      |

Here is an example of how to use it:

```c++
Entity entity;
std::string component_name = "TransformComponent";
network.SendComponentOf(&entity, component_name);
```

## sendAskConnect

```c++
void sendAskConnect(const std::string &ip, short port)
```

It allows the network to send ask connects.

The method takes the following parameters:

| Name | Type         | Description             |
|------|--------------|-------------------------|
| ip   | std::string  | The ip                  |
| port | short        | The port                |

Here is an example of how to use it:

```c++
std::string ip = "10.10.10.10";
short port = 8080;
network.sendAskConnect(ip, port);
```

## sendEvent

```c++
void sendEvent(u_int32_t event)
```

It allows the network to send events.

The method takes the following parameters:

| Name  | Type         | Description             |
|-------|--------------|-------------------------|
| event | u_int32_t    | The event               |

Here is an example of how to use it:

```c++
u_int32_t event = 1;
network.sendEvent(event);
```

## fill_data

```c++
size_t fill_data(std::vector<char> &buffer, size_t offset, void *data, size_t size);
```

It fills the data.

The method takes the following parameters:

| Name   | Type               | Description             |
|--------|--------------------|-------------------------|
| buffer | std::vector<char>& | The buffer              |
| offset | size_t             | The offset              |
| data   | void*              | The data                |
| size   | size_t             | The size of the data    |

Here is an example of how to use it:

```c++
std::vector<char> buffer;
size_t offset;
void *data;
size_t size;
network.fill_data(buffer, offset, data, size);
```

## splitter

```c++
void splitter(const std::vector<char> message, size_t size, asio::ip::udp::endpoint senderEndpoint);
```

It splits the message.

The method takes the following parameters:

| Name           | Type                        | Description             |
|----------------|-----------------------------|-------------------------|
| message        | const std::vector<char>     | The message             |
| size           | size_t                      | The size of the message |
| senderEndpoint | asio::ip::udp::endpoint     | The sender endpoint     |

Here is an example of how to use it:

```c++
std::vector<char> message;
size_t size;
asio::ip::udp::endpoint senderEndpoint;
network.splitter(message, size, senderEndpoint);
```

## getConnections

```c++
std::unordered_map<std::string, Connection> &getConnections()
```

It returns the connections.

Here is an example of how to use it:

```c++
std::unordered_map<std::string, Connection> connections = network.getConnections();
```
