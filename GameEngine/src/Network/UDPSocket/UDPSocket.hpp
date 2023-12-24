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
        UDPSocket(IOContextManager& ioContextManager, const asio::ip::udp::endpoint& endpoint);

        /**
         * @brief Destroy the UDPSocket object
         *
         */
        ~UDPSocket();

        /**
         * @brief Send data asynchronously
         *
         * @param message (Type: std::string &) The message to send
         * @param endpoint (Type: const asio::ip::udp::endpoint &) The endpoint to send the message to
         */
        void Send(const std::vector<char> message, size_t size, const asio::ip::udp::endpoint& endpoint);

        void Send(Exodia::Network::Packet &packet ,const asio::ip::udp::endpoint& endpoint);

        /**
         * @brief Receive data asynchronously
         *
         * @param callback (Type: void (*)(const std::string&)) The callback to call when a message is received
         */
        void Receive(const std::function<void(const std::vector<char> &, size_t, asio::ip::udp::endpoint)> &callback);

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

    protected:
        std::mutex _receive_mutex;
        asio::ip::udp::socket _socket; /*!< The UDP socket */
        asio::ip::udp::endpoint _senderEndpoint; /*!< The sender endpoint */
        std::size_t _packets_received = 0; /*!< The number of packets received */
        std::array<char, MTU> _receiveBuffer; /*!< The receive buffer */

    private:
    };
    }; // namespace Network
}; // namespace Exodia

#endif // UDP_SOCKET_HPP
