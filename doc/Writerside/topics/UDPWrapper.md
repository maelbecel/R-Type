# UDPWrapper

The **`UDPSocket`** class encapsulates UDP socket functionality for network communication within the R-Type game.

### Purpose
- Provides asynchronous sending and receiving of messages using Asio library for networking.
- Manages opening, binding, and closing of UDP sockets.
- Enables flexible handling of data transmission between game clients.

### Usage
```cpp
class UDPSocket {
public:
    // Constructor
    UDPSocket(IOContextManager& ioContextManager, const asio::ip::udp::endpoint& endpoint);

    // Methods
    void Send(const std::vector<char> message, size_t size, const asio::ip::udp::endpoint& endpoint);
    template <typename Callback>
    void Receive(Callback callback);
    asio::ip::udp::endpoint getSenderEndpoint() const;
    asio::ip::udp::socket& getSocket();

private:
    asio::ip::udp::socket _socket; /*!< The UDP socket */
    asio::ip::udp::endpoint _senderEndpoint; /*!< The sender endpoint */
    std::array<char, MTU> _receiveBuffer; /*!< The receive buffer */
};
```

### Features
- **Asynchronous Communication:** Utilizes Asio's asynchronous methods, enabling non-blocking communication for sending and receiving messages.
- **Error Handling & Logging:** Provides robust error handling mechanisms and logging functionalities to monitor network operations.
- **Configurable Buffer Size:** Supports a configurable Maximum Transmission Unit (MTU) for the receive buffer (default: 1468 bytes).
- **Data Integrity:** Ensures correct sizing of received messages and offers a callback mechanism for seamless handling of received data.

### Dependencies

The **`UDPSocket`** class offers versatile functionality for managing UDP communication, providing essential features for seamless networking in the R-Type game.