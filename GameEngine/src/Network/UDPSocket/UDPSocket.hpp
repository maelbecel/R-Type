/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** UDPSocket
*/

#ifndef UDP_SOCKET_HPP
    #define UDP_SOCKET_HPP

#include <iostream>
#include <asio.hpp>
#include "Network/IOContextManager/IOContextManager.hpp"
#include "Network/Header/Header.hpp"
#include "Network/Packet/Packet.hpp"
#include "Debug/Logs.hpp"
#include <thread>
#include <mutex>
#include <queue>

namespace Exodia {

    namespace Network {

    #define MTU 1468

class UDPSocket {
    public:

        /**
         * @brief Construct a new UDPSocket object
         * Construct a new UDPSocket object using the provided IOContextManager
         *
         * @param ioContextManager (Type: IOContextManager &) The IOContextManager to use
         */
        UDPSocket(IOContextManager& ioContextManager, const asio::ip::udp::endpoint& endpoint)
            : _socket(ioContextManager.getIOContext()), _senderEndpoint() {
            // Construct the UDP socket using the provided IOContextManager
            asio::error_code error;
            if (_socket.is_open())
                EXODIA_CORE_ERROR("Socket already open");
            _socket.open(endpoint.protocol(), error);
            if (!error) {
                _socket.bind(endpoint, error);
                if (!error) {
                    EXODIA_CORE_INFO("Socket opened successfully");
                } else {
                    EXODIA_CORE_ERROR("Error binding socket: ", error.message());
                    throw std::runtime_error("Error binding socket");
                }
            } else {
                EXODIA_CORE_ERROR("Error opening socket: ", error.message());
                throw std::runtime_error("Error opening socket");
            }
            _send_message_thread = std::thread(&UDPSocket::send_thread, this);
        }

        /**
         * @brief Destroy the UDPSocket object
         *
         */
        ~UDPSocket() {
            if (_socket.is_open())
                _socket.close();
        }

        /**
         * @brief Send data asynchronously
         *
         * @param message (Type: std::string &) The message to send
         * @param endpoint (Type: const asio::ip::udp::endpoint &) The endpoint to send the message to
         */
        void send(const std::vector<char> message, size_t size, const asio::ip::udp::endpoint& endpoint) {
            (void)size;
            _socket.async_send_to(asio::buffer(message), endpoint,
                [](const asio::error_code& error, std::size_t bytes_sents) {
                    if (error) {
                        EXODIA_CORE_ERROR("Error sending message: ", error.message());
                    } else {
                        std::cout << "Sent " << bytes_sents << " bytes" << std::endl;
                    }
                });
        }

        void send(Exodia::Network::Packet &packet ,const asio::ip::udp::endpoint& endpoint) {
            _senderEndpoint = endpoint;
            std::vector<char> message = packet.GetBuffer();
            std::vector<char> dup_message = message;

            _mutex.lock();
            _messages.push(dup_message);
            _mutex.unlock();
        }

        void send_thread()
        {
            while (true) {
                if (!_messages.empty()) {
                    _mutex.lock();
                    std::vector<char> message = _messages.front();
                    _messages.pop();
                    _mutex.unlock();
                    _socket.send_to(asio::buffer(message), _senderEndpoint);
                }
            }
        }
        

        /**
         * @brief Receive data asynchronously
         *
         * @param callback (Type: void (*)(const std::string&)) The callback to call when a message is received
         */
        template <typename Callback>
        void receive(Callback callback) {
            _socket.async_receive_from(asio::buffer(_receiveBuffer), _senderEndpoint,
                [this, callback](const asio::error_code& error, std::size_t bytes_received) {
                    if (!error) {

                        std::vector<char> new_datas(_receiveBuffer.begin(), _receiveBuffer.begin() + bytes_received);
                        asio::ip::udp::endpoint senderEndpoint = getSenderEndpoint();
                        // Ensure correct sizing of receivedMessage
                        std::unique_ptr<std::vector<char>> receivedMessage = std::make_unique<std::vector<char>>(bytes_received);
                        // Use std::memcpy to copy the received data
                        std::cout << "Received " << new_datas.size() << " and " << bytes_received << std::endl;
                        if (new_datas.size() != bytes_received)
                            EXODIA_CORE_ERROR("Error in bytes received");
                        std::memcpy(receivedMessage->data(), new_datas.data(),  new_datas.size());


                        // Call the callback with the received data
                        callback(*receivedMessage.get(),  new_datas.size(), senderEndpoint);

                        // Call receive again to listen for more messages
                        receive(callback);
                    } else {
                        EXODIA_CORE_ERROR("Error receiving message: ", error.message());
                    }
                });
        }

        /**
         * @brief Get the Sender Endpoint object
         * call this function to get the sender endpoint
         *
         * @return asio::ip::udp::endpoint
         */
        asio::ip::udp::endpoint getSenderEndpoint() const {
            return _senderEndpoint;
        }

        /**
         * @brief Get the Socket object
         * call this function to get the socket
         *
         * @return asio::ip::udp::socket&
         */
        asio::ip::udp::socket& getSocket() {
            return _socket;
        }

    private:
        asio::ip::udp::socket _socket; /*!< The UDP socket */
        asio::ip::udp::endpoint _senderEndpoint; /*!< The sender endpoint */
        std::array<char, 4096> _receiveBuffer; /*!< The receive buffer */

        //thread safe
        std::mutex _mutex;
        std::queue<std::vector<char>> _messages;
        std::thread _send_message_thread;

    };
    }; // namespace Network
}; // namespace Exodia

#endif // UDP_SOCKET_HPP
