/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** UDPSocket
*/

#include "UDPSocket.hpp"

namespace Exodia {

    namespace Network {

        UDPSocket::UDPSocket(IOContextManager& ioContextManager, const asio::ip::udp::endpoint& endpoint) : _socket(ioContextManager.getIOContext()), _senderEndpoint() {
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
        }

        UDPSocket::~UDPSocket() {
            // Close the socket
            _socket.close();
        }
        
        void UDPSocket::send(const std::vector<char> message, size_t size, const asio::ip::udp::endpoint& endpoint) {
            // Send data asynchronously
            _socket.async_send_to(asio::buffer(message, size), endpoint, [this](const asio::error_code& error, std::size_t bytes_transferred) {
                if (error) {
                    EXODIA_CORE_ERROR("Error sending data: ", error.message());
                } else {
                    EXODIA_CORE_INFO("Data sent successfully");
                }
            });
        }

        void UDPSocket::send(Exodia::Network::Packet &packet ,const asio::ip::udp::endpoint& endpoint) {
            _senderEndpoint = endpoint;
            std::vector<char> message = packet.GetBuffer();
            size_t size = message.size();

            _socket.async_send_to(asio::buffer(message, size), endpoint, [this](const asio::error_code& error, std::size_t bytes_transferred) {
                if (error) {
                    EXODIA_CORE_ERROR("Error sending data: ", error.message());
                } else {
                    EXODIA_CORE_INFO("Data sent successfully");
                }
            });
        }

        void UDPSocket::receive(const std::function<void(const std::vector<char>&, size_t, asio::ip::udp::endpoint)>& callback) {

        _socket.async_receive_from(asio::buffer(_receiveBuffer), _senderEndpoint,
            [this, callback](const asio::error_code& error, std::size_t bytes_received) {
                _receive_mutex.lock();
                std::vector<char> receivedMessage(_receiveBuffer.begin(), _receiveBuffer.begin() + bytes_received);
                if (!error) {

                    // Call the callback with the received data
                    callback(receivedMessage, receivedMessage.size(), _senderEndpoint);

                    // Call receive again to listen for more messages
                    _receive_mutex.unlock();
                    receive(callback);
                } else {
                    _receive_mutex.unlock();
                    EXODIA_CORE_ERROR("Error receiving message: ", error.message());
                }
            });
        }
    }
}
