/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** Network
*/

#ifndef NETWORK_HPP_
    #define NETWORK_HPP_

    #include "IOContextManager/IOContextManager.hpp"
    #include "UDPSocket/UDPSocket.hpp"
    #include "Header/Header.hpp"
    #include "Connection/Connection.hpp"
    #include "Packet/Packet.hpp"
    #include "ECS/ECS.hpp"
    #include <vector>
    #include <chrono>

namespace Exodia {

    namespace Network {

        class Network {
            public:

                /**
                 * @brief Construct a new Network object
                 *
                 */
                Network(World *world, IOContextManager &context,short port) : _world(world), _socket(context, asio::ip::udp::endpoint(asio::ip::address::from_string("0.0.0.0"), port)), _ioContextManager(context)
                {
                    startIOContextThread();
                };

                /**
                 * @brief Destroy the Network object
                 *
                 */
                ~Network()
                {
                    EXODIA_CORE_WARN("Network destroyed");
                    stopIOContextThread();
                };

                /**
                 * @brief Connect to a remote endpoint
                 *
                 */

                void loop();
                void receivePacketInfo(const std::vector<char> message, size_t size, asio::ip::udp::endpoint senderEndpoint);   // 0x00
                void receiveAck(const std::vector<char> message, size_t size, asio::ip::udp::endpoint senderEndpoint);          // 0x01
                void receiveConnectAccept(const std::vector<char> message, size_t size, asio::ip::udp::endpoint senderEndpoint);// 0x02
                void receiveEntity(const std::vector<char> message, size_t size, asio::ip::udp::endpoint senderEndpoint);       // 0x0c
                void receiveConnect(const std::vector<char> message, size_t size, asio::ip::udp::endpoint senderEndpoint);      // 0x81
                void sendPacketInfo();      // 0x00
                void sendAck();             // 0x01
                void sendAcceptConnect();   // 0x02
                void sendEntity(Entity *entity, std::string component_name); // 0x0c
                void sendAskConnect(const std::string &ip, short port);      // 0x81
                size_t fill_data(std::vector<char> &buffer, size_t offset, void *data, size_t size);
                void splitter(const std::vector<char> message, size_t size, asio::ip::udp::endpoint senderEndpoint);
                void startIOContextThread();
                void stopIOContextThread();

            private:
                void connect(const std::string &ip, short port) {
                    _server_connection = Connection(asio::ip::udp::endpoint(asio::ip::address::from_string(ip), port));
                }

            private:
                World *_world;
                UDPSocket _socket;
                std::unordered_map<std::string, Connection> _connections;
                Connection _server_connection;

                // IOContext
                IOContextManager &_ioContextManager;
                std::thread _ioContextThread;

        }; // class Network

    }; // namespace Network

}; // namespace Exodia
#endif /* !NETWORK_HPP_ */
