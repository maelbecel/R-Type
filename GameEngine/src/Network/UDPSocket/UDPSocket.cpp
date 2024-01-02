/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** UDPSocket
*/

#include "UDPSocket.hpp"

namespace Exodia {

    namespace Network {

        UDPSocket::UDPSocket(IOContextManager &ioContextManager, const asio::ip::udp::endpoint &endpoint)
            : _receiveStrand(ioContextManager.getIOContext()), _socket(ioContextManager.getIOContext()),
              _senderEndpoint() {
            // Construct the UDP socket using the provided IOContextManager
            asio::error_code error;
            if (_socket.is_open())
                EXODIA_CORE_ERROR("Socket already open");
            _socket.open(endpoint.protocol(), error);
            if (!error) {
                _socket.bind(endpoint, error);
                if (!error) {
                    EXODIA_CORE_INFO("Socket opened successfully on port {0}", endpoint.port());
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

        /**
         * @brief Send data to the given endpoint
         *
         * @param message (Type: std::vector<char>) The message to send
         * @param size (Type: size_t) The size of the message
         * @param endpoint (Type: asio::ip::udp::endpoint) The endpoint to send the message to
         *
         * @return void
         */
        void UDPSocket::Send(const std::vector<char> message, size_t size, const asio::ip::udp::endpoint &endpoint) {
            // Send data asynchronously
            _socket.async_send_to(asio::buffer(message, size), endpoint,
                                  [this](const asio::error_code &error, std::size_t bytes_transferred) {
                                      if (error) {
                                          EXODIA_CORE_ERROR("Error sending data: ", error.message());
                                      }
                                  });
        }

        /**
         * @brief Send data to the given endpoint
         *
         * @param packet (Type: Exodia::Network::Packet) The packet to send
         * @param endpoint (Type: asio::ip::udp::endpoint) The endpoint to send the packet to
         *
         * @return void
         */
        void UDPSocket::Send(Exodia::Network::Packet &packet, const asio::ip::udp::endpoint &endpoint) {
            _senderEndpoint = endpoint;
            std::vector<char> message = packet.GetBuffer();
            size_t size = message.size();

            _socket.async_send_to(asio::buffer(message, size), endpoint,
                                  [this](const asio::error_code &error, std::size_t bytes_transferred) {
                                      if (error) {
                                          EXODIA_CORE_ERROR(
                                              "Error sending data on {0}:{1}: ", _senderEndpoint.address().to_string(),
                                              _senderEndpoint.port(), error.message());
                                      }
                                  });
        }

        void UDPSocket::Receive(
            const std::function<void(const std::vector<char> &, size_t, asio::ip::udp::endpoint)> &callback) {
            _receiveStrand.post([this, callback]() {
                _socket.async_receive_from(asio::buffer(_receiveBuffer), _senderEndpoint,
                                           [this, callback](const asio::error_code &error, std::size_t bytes_received) {
                                               if (!error) {
                                                   std::vector<char> receivedMessage(
                                                       _receiveBuffer.begin(), _receiveBuffer.begin() + bytes_received);
                                                   callback(receivedMessage, receivedMessage.size(), _senderEndpoint);
                                               } else {
                                                   EXODIA_CORE_ERROR("Error receiving message: ", error.message());
                                               }

                                               Receive(callback); // Initiating the next receive operation
                                           });
            });
        }

    } // namespace Network
} // namespace Exodia
