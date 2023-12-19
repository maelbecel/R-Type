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
                    Loop();
                    _ioContextManager.run();
                };

                /**
                 * @brief Destroy the Network object
                 *
                 */
                ~Network()
                {
                };

                /**
                 * @brief Connect to a remote endpoint
                 *
                 */

                void Loop();
                void ReceivePacketInfo(const std::vector<char> message, size_t size, asio::ip::udp::endpoint senderEndpoint, Exodia::Network::Header header);   // 0x00
                void ReceiveAck(const std::vector<char> message, size_t size, asio::ip::udp::endpoint senderEndpoint, Exodia::Network::Header header);          // 0x01
                void ReceiveConnectAccept(const std::vector<char> message, size_t size, asio::ip::udp::endpoint senderEndpoint, Exodia::Network::Header header);// 0x02
                void ReceiveEntity(const std::vector<char> message, size_t size, asio::ip::udp::endpoint senderEndpoint, Exodia::Network::Header header);       // 0x0c
                void ReceiveConnect(const std::vector<char> message, size_t size, asio::ip::udp::endpoint senderEndpoint, Exodia::Network::Header header);      // 0x81
                void ReceiveEvent(const std::vector<char> message, size_t size, asio::ip::udp::endpoint senderEndpoint, Exodia::Network::Header header);        // 0x82
                void SendPacketInfo();      // 0x00
                void SendAck();             // 0x01
                void SendAcceptConnect();   // 0x02
                void SendEntity(Entity *entity, std::string component_name); // 0x0c
                void SendAskConnect(const std::string &ip, short port);      // 0x81
                void SendEvent(u_int32_t event);                                   // 0x82
                void Splitter(const std::vector<char> message, size_t size, asio::ip::udp::endpoint senderEndpoint);
                std::unordered_map<std::string, Connection> &GetConnections() {
                    return _connections;
                }

            private:
                void connect(const std::string &ip, short port) {
                    _server_connection = Connection(asio::ip::udp::endpoint(asio::ip::address::from_string(ip), port));
                }
                size_t FillData(std::vector<char> &buffer, size_t offset, void *data, size_t size);

            private:
                World *_world;
                UDPSocket _socket;
                std::unordered_map<std::string, Connection> _connections;
                Connection _server_connection;

                // IOContext
                IOContextManager &_ioContextManager;

                std::map<float, uint32_t> _events;

        }; // class Network

    }; // namespace Network

}; // namespace Exodia
#endif /* !NETWORK_HPP_ */
