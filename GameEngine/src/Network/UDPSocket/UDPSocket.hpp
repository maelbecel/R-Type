/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** UDPSocket
*/

#ifndef UDP_SOCKET_HPP
    #define UDP_SOCKET_HPP

#include <iostream>
#include <boost/asio.hpp>
#include "Network/IOContextManager/IOContextManager.hpp"
#include "Debug/Logs.hpp"

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
        UDPSocket(IOContextManager& ioContextManager, const boost::asio::ip::udp::endpoint& endpoint)
            : _socket(ioContextManager.getIOContext()), _senderEndpoint() {
            // Construct the UDP socket using the provided IOContextManager
            boost::system::error_code error;
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
         * @param endpoint (Type: const boost::asio::ip::udp::endpoint &) The endpoint to send the message to
         */
        void send(const std::string& message, const boost::asio::ip::udp::endpoint& endpoint) {
            _socket.async_send_to(boost::asio::buffer(message), endpoint,
                [](const boost::system::error_code& error, std::size_t /*bytes_sent*/) {
                    if (error) {
                        EXODIA_CORE_ERROR("Error sending message: ", error.message());
                    }
                });
        }

        /**
         * @brief Receive data asynchronously
         *
         * @param callback (Type: void (*)(const std::string&)) The callback to call when a message is received
         */
        void receive(void (*callback)(const std::string&)) {
            _socket.async_receive_from(boost::asio::buffer(_receiveBuffer), _senderEndpoint,
                [this, callback](const boost::system::error_code& error, std::size_t bytes_received) {
                    if (!error) {
                        std::string receivedMessage(_receiveBuffer.begin(), _receiveBuffer.begin() + bytes_received);
                        callback(receivedMessage);
                    } else {
                        EXODIA_CORE_ERROR("Error receiving message: ", error.message());
                    }
                });
        }

        /**
         * @brief Get the Sender Endpoint object
         * call this function to get the sender endpoint
         *
         * @return boost::asio::ip::udp::endpoint
         */
        boost::asio::ip::udp::endpoint getSenderEndpoint() const {
            return _senderEndpoint;
        }

        /**
         * @brief Get the Socket object
         * call this function to get the socket
         *
         * @return boost::asio::ip::udp::socket&
         */
        boost::asio::ip::udp::socket& getSocket() {
            return _socket;
        }

    private:
        boost::asio::ip::udp::socket _socket; /*!< The UDP socket */
        boost::asio::ip::udp::endpoint _senderEndpoint; /*!< The sender endpoint */
        std::array<char, MTU> _receiveBuffer; /*!< The receive buffer */
    };
    }; // namespace Network
}; // namespace Exodia

#endif // UDP_SOCKET_HPP