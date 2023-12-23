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
    #include <queue>

namespace Exodia {

    namespace Network {

        class Network {
            public:

                //////////////////////////////
                // Constructor & Destructor //
                //////////////////////////////
                /**
                 * @brief Construct a new Network object
                 *
                 * @param world (Type: World *) The world that the network can edit
                 * @param context (Type: IOContextManager &) The context manager of the game
                 * @param port (Type: short) The port to listen on
                 *
                 * @return void
                 */
                Network(World *world, IOContextManager &context, short port) : _world(world), _socket(context, asio::ip::udp::endpoint(asio::ip::address::from_string("0.0.0.0"), port)), _ioContextManager(context)
                {
                    Loop();
                    _ioContextManager.run();
                };

                void SetWorld(World *world) {
                    _world = world;
                }
                /**
                 * @brief Destroy the Network object
                 *
                 */
                ~Network()
                {
                };

                /////////////
                // Methods //
                /////////////
                void Loop();
                void ReceivePacketInfo(const std::vector<char> message, size_t size, asio::ip::udp::endpoint senderEndpoint, Exodia::Network::Header header);   // 0x00
                void ReceiveAck(const std::vector<char> message, size_t size, asio::ip::udp::endpoint senderEndpoint, Exodia::Network::Header header);          // 0x01
                void ReceiveConnectAccept(const std::vector<char> message, size_t size, asio::ip::udp::endpoint senderEndpoint, Exodia::Network::Header header);// 0x02
                void ReceiveComponentOf(const std::vector<char> message, size_t size, asio::ip::udp::endpoint senderEndpoint, Exodia::Network::Header header);  // 0x0c
                void ReceiveDeleteEntity(const std::vector<char> message, size_t size, asio::ip::udp::endpoint senderEndpoint, Exodia::Network::Header header);        // 0x0e
                void ReceiveConnect(const std::vector<char> message, size_t size, asio::ip::udp::endpoint senderEndpoint, Exodia::Network::Header header);      // 0x81
                void ReceiveEvent(const std::vector<char> message, size_t size, asio::ip::udp::endpoint senderEndpoint, Exodia::Network::Header header);        // 0x82

                void SendPacketInfo();      // 0x00
                void SendAck();             // 0x01
                void SendAcceptConnect();   // 0x02
                void SendComponentOf(Entity *entity, std::string component_name);  // 0x0c
                void SendDeleteEntity(Entity *entity);                             // 0x0e
                void SendAskConnect(const std::string &ip, short port);            // 0x81
                void SendEvent(uint32_t event, bool isPressed);                    // 0x82
                void Splitter(const std::vector<char> &message, size_t size, asio::ip::udp::endpoint senderEndpoint);

                /**
                 * @brief Return an unordered map of pair of string and Connection
                 *
                 * @details The string is the ip of the connection and the Connection is the connection object
                 *
                 * @return std::unordered_map<std::string, Connection> Unordered map of pair of string and Connection
                */
                std::unordered_map<std::string, Connection> &GetConnections() {
                    return _connections;
                }

                /**
                 * @brief Return a queue of uint32_t representing the events received
                 *
                 * @return a copy of the queue of uint32_t representing the events received
                */
                std::queue<std::pair<std::pair<uint32_t, bool>, asio::ip::udp::endpoint>> GetEvents() {
                    std::queue<std::pair<std::pair<uint32_t, bool>, asio::ip::udp::endpoint>> flushedEvents = std::move(_events);
                    return flushedEvents;
                }

                //Need to modify this function to have a good index
                uint32_t ConnectionPlace(asio::ip::udp::endpoint endpoint)
                {
                    uint32_t i = 0;

                    for (auto &connection : _connections) {
                        if (connection.second.GetEndpoint() == endpoint)
                            return i;
                        i++;
                    }
                    return 0;
                }

                UDPSocket &GetSocket() {
                    return _socket;
                }

            std::string id = "0";

            private:
                /**
                 * @brief Use to connect to a user with the ip and port given
                 *
                 * @param ip (Type: std::string) The ip of the user to connect to
                 * @param port (Type: short) The port of the user to connect to
                 *
                 * @return void
                */
                void connect(const std::string &ip, short port) {
                    _server_connection = Connection(asio::ip::udp::endpoint(asio::ip::address::from_string(ip), port));
                }
                size_t FillData(std::vector<char> &buffer, size_t offset, void *data, size_t size);

            private:
                World *_world;
                UDPSocket _socket;
                std::unordered_map<std::string, Connection> _connections;
                Connection _server_connection;
                IOContextManager &_ioContextManager;
                std::queue<std::pair<std::pair<uint32_t, bool>, asio::ip::udp::endpoint>> _events;

        }; // class Network

    }; // namespace Network

}; // namespace Exodia
#endif /* !NETWORK_HPP_ */
