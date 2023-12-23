# UDPSocket

The UDPSocket class is used to manage the UDP socket.

## Constructor

```c++
UDPSocket(IOContextManager& ioContextManager, const asio::ip::udp::endpoint& endpoint)
```

It creates a UDP socket.

The constructor takes the following parameters:

| Name             | Type                    | Description            |
|------------------|-------------------------|------------------------|
| ioContextManager | IOContextManager&       | The IO context manager |
| endpoint         | asio::ip::udp::endpoint | The endpoint           |

Here is an example of how to use it:

```c++
IOContextManager ioContextManager;
asio::ip::udp::endpoint endpoint(asio::ip::make_address("10.10.10.10"), 1234);
Exodia::Network::UDPSocket socket(ioContextManager, endpoint);
```

## send

```c++
void send(const std::vector<char> message, size_t size, const asio::ip::udp::endpoint& endpoint) {
```

It sends a message to a server.

The method takes the following parameters:

| Name     | Type                    | Description            |
|----------|-------------------------|------------------------|
| message  | std::vector<char>       | The message            |
| size     | size_t                  | The size of the message|
| endpoint | asio::ip::udp::endpoint | The endpoint           |

Here is an example of how to use it:

```c++
std::vector<char> message;
size_t size = 0;
asio::ip::udp::endpoint endpoint(asio::ip::make_address("10.10.10.10"), 1234);
socket.send(message, size, endpoint);
```

## receive

```c++
template <typename Callback>
void receive(Callback callback)
```

It receives a message from a server.

The method takes the following parameters:

| Name     | Type    | Description            |
|----------|---------|------------------------|
| callback | Callback| The callback           |

Here is an example of how to use it:

```c++
socket.receive([](std::vector<char> message, size_t size, asio::ip::udp::endpoint endpoint) {
    std::cout << "Message received" << std::endl;
});
```

## getSenderEndpoint

```c++
asio::ip::udp::endpoint getSenderEndpoint() const
```

It returns the sender endpoint.

Here is an example of how to use it:

```c++
asio::ip::udp::endpoint endpoint = socket.getSenderEndpoint();
```

## getSocket

```c++
asio::ip::udp::socket& getSocket()
```

It returns the socket.

Here is an example of how to use it:

```c++
asio::ip::udp::socket& socket = socket.getSocket();
```
