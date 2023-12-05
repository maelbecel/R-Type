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

namespace Exodia {

#define MTU 1468

class UDPSocket {
    public:

        /**
         * @brief Construct a new UDPSocket object
         *
         * @param ioContextManager
         */
        UDPSocket(IOContextManager& ioContextManager)
            : _socket(ioContextManager.getIOContext()), _senderEndpoint() {
            // Construct the UDP socket using the provided IOContextManager
            _socket = boost::asio::ip::udp::socket(ioContextManager.getIOContext());
        }

        /**
         * @brief Destroy the UDPSocket object
         *
         */
        ~UDPSocket() {
            _socket.close();
        }

        /**
         * @brief Send data asynchronously
         *
         * @param message
         * @param endpoint
         */
        void send(const std::string& message, const boost::asio::ip::udp::endpoint& endpoint) {
            _socket.async_send_to(boost::asio::buffer(message), endpoint,
                [](const boost::system::error_code& error, std::size_t /*bytes_sent*/) {
                    if (!error) {
                        EXODIA_CORE_INFO("Message sent successfully");
                    } else {
                        EXODIA_CORE_ERROR("Error sending message: ", error.message());
                    }
                });
        }

        /**
         * @brief Receive data asynchronously
         *
         */
        void receive() {
            _socket.async_receive_from(boost::asio::buffer(_receiveBuffer), _senderEndpoint,
                [this](const boost::system::error_code& error, std::size_t bytes_received) {
                    if (!error) {
                        std::string receivedMessage(_receiveBuffer.begin(), _receiveBuffer.begin() + bytes_received);
                        EXODIA_CORE_INFO("Received message: ", receivedMessage);
                        receive();
                    } else {
                        EXODIA_CORE_ERROR("Error receiving message: ", error.message());
                    }
                });
        }

        /**
         * @brief Open the UDP socket
         *
         * @param endpoint The endpoint to bind the socket to
         */
        void open(const boost::asio::ip::udp::endpoint& endpoint) {
            boost::system::error_code error;
            _socket.open(endpoint.protocol(), error);
            if (!error) {
                _socket.bind(endpoint, error);
                if (!error) {
                    EXODIA_CORE_INFO("Socket opened successfully");
                } else {
                    EXODIA_CORE_ERROR("Error binding socket: ", error.message());
                }
            } else {
                EXODIA_CORE_ERROR("Error opening socket: ", error.message());
            }
        }

        /**
         * @brief Get the Sender Endpoint object
         *
         * @return boost::asio::ip::udp::endpoint
         */
        boost::asio::ip::udp::endpoint getSenderEndpoint() const {
            return _senderEndpoint;
        }

        /**
         * @brief Get the Socket object
         *
         * @return boost::asio::ip::udp::socket&
         */
        boost::asio::ip::udp::socket& getSocket() {
            return _socket;
        }

    private:
        boost::asio::ip::udp::socket _socket;
        boost::asio::ip::udp::endpoint _senderEndpoint;
        std::array<char, MTU> _receiveBuffer;
    };

}; // namespace Exodia

#endif // UDP_SOCKET_HPP
