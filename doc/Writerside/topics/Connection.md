# Connection

The connection module contains functions for connecting to a server.

## Connection

```c++
Connection();
Connection(asio::ip::udp::endpoint endpoint);
```

It creates a connection.

The method takes the following parameters:

| Name     | Type                     | Description          |
|----------|--------------------------|----------------------|
| endpoint | asio::ip::udp::endpoint  | The endpoint         |

Here is an example of how to use it:

```c++
asio::ip::udp::endpoint endpoint(asio::ip::make_address("10.10.10.10"), 1234);
Exodia::Connection connection(endpoint);
```

## sendPacket

```c++
void sendPacket(Exodia::Network::UDPSocket &socket, Exodia::Network::Packet &packet)
```

It sends a packet to a server.

The method takes the following parameters:

| Name   | Type                        | Description          |
|--------|-----------------------------|----------------------|
| socket | Exodia::Network::UDPSocket& | The socket           |
| packet | Exodia::Network::Packet&    | The packet           |

Here is an example of how to use it:

```c++
Exodia::Network::UDPSocket socket;
Exodia::Network::Packet packet;
connection->sendPacket(socket, packet);
```

## setSendPacket

```c++
void setSendPacket(int packet)
```

It sets the packet to send.

The method takes the following parameters:

| Name   | Type | Description          |
|--------|------|----------------------|
| packet | int  | The packet           |

Here is an example of how to use it:

```c++
connection->setSendPacket(0);
```

## AddReceivePacket

```c++
void AddReceivePAcket()
```

It adds a packet to receive.

Here is an example of how to use it:

```c++
connection->AddReceivePacket();
```

## setReceivePacket

```c++
void setReceivePacket(int packet)
```

It sets the packet to receive.

The method takes the following parameters:

| Name   | Type | Description          |
|--------|------|----------------------|
| packet | int  | The packet           |

Here is an example of how to use it:

```c++
connection->setReceivePacket(0);
```

## getSendPacket

```c++
int getSendPacket()
```

It returns the packet to send.

Here is an example of how to use it:

```c++
std::cout << connection->getSendPacket() << std::endl;
```

## getReceivePacket

```c++
int getReceivePacket()
```

It returns the packet to receive.

Here is an example of how to use it:

```c++
std::cout << connection->getReceivePacket() << std::endl;
```

## getEndpoint

```c++
asio::ip::udp::endpoint getEndpoint() const
```

It returns the endpoint.

Here is an example of how to use it:

```c++
std::cout << connection->getEndpoint() << std::endl;
```