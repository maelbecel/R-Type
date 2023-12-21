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
                void ReceiveConnect(const std::vector<char> message, size_t size, asio::ip::udp::endpoint senderEndpoint, Exodia::Network::Header header);      // 0x81
                void ReceiveEvent(const std::vector<char> message, size_t size, asio::ip::udp::endpoint senderEndpoint, Exodia::Network::Header header);        // 0x82
                void SendPacketInfo();      // 0x00
                void SendAck();             // 0x01
                void SendAcceptConnect();   // 0x02
                void SendComponentOf(Entity *entity, std::string component_name);  // 0x0c
                void SendAskConnect(const std::string &ip, short port);            // 0x81
                void SendEvent(u_int32_t event);                                   // 0x82
                void Splitter(const std::vector<char> &message, size_t size, asio::ip::udp::endpoint senderEndpoint);

                /**
                 * @brief Return string representation of a command
                 *
                 * @param header (Type: Exodia::Network::Header) The header of the command
                 *
                 * @return std::string String representation of the command
                */
                static std::string VerbaliseCommand(Exodia::Network::Header header)
                {
                    std::string command;
                    std::unordered_map<char, std::string> commands;
                    commands[0x00] = "Packet info";
                    commands[0x01] = "Acknowledgement";
                    commands[0x02] = "Accept client connection";
                    commands[0x81] = "Ask for connection";
                    commands[0x82] = "New Event";
                    commands[0x0c] = "Create component";
                    command = commands[header.getCommand()];
                    if (command.empty())
                        command = "Unknown command";
                    return command;
                }

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
                std::queue<uint32_t> flushEvents() {
                    std::queue<uint32_t> flushedEvents = std::move(_events);
                    return flushedEvents;
                }

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
                std::queue<uint32_t> _events;

        }; // class Network

    }; // namespace Network

}; // namespace Exodia
#endif /* !NETWORK_HPP_ */
