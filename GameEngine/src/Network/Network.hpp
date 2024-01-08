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
#include <unordered_map>
#include <functional>



namespace Exodia {

    namespace Network {

        typedef enum {
            PACKET_INFO = 0x00,
            ACK = 0x01,
            CONNECT_ACCEPT = 0x02,
            CONNECT_REJECT = 0x03,
            SYSTEM_LOAD = 0x0b,
            COMPONENT_OF = 0x0c,
            GAME_EVENT = 0x0d,
            DELETE_ENTITY = 0x0e,
            DELETE_COMPONENT = 0x0f,
            IMPORTANT_EVENT = 0x10,
            CONNECT = 0x81,
            DISCONNECT = 0x82,
            EVENT = 0x8b
        } Command;

#define COMMAND_NETWORK(x)                                                                                             \
    std::bind(&x, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
#define RECEIVE_ARG                                                                                                    \
    const std::vector<char> message, size_t size, Connection &senderConnection, Exodia::Network::Header header
#define STRING_FROM_ENDPOINT(x) x.address().to_string() + ":" + std::to_string(x.port())

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
            Network(World *world, IOContextManager &context, short port)
                : _world(world),
                  _socket(context, asio::ip::udp::endpoint(asio::ip::address::from_string("0.0.0.0"), port)),
                  _ioContextManager(context) {
                Loop();
                _ioContextManager.run();
            };

            void SetWorld(World *world) { _world = world; }
            /**
             * @brief Destroy the Network object
             *
             */
            ~Network() {
                // _socket.~UDPSocket();
                _ioContextManager.stop();
            };

            /////////////
            // Methods //
            /////////////
            void Loop();

            void SendPacket(Exodia::Network::Packet &packet);
            void SendImportantPacket(Exodia::Network::Packet packet);
            void SendPacketInfo();                                                                  // 0x00
            void SendAck(uint64_t command_id);                                                      // 0x01
            void SendAcceptConnect();                                                               // 0x02
            void SendRejectConnect();                                                               // 0x03
            void SendSystemLoad(bool isImportant);                                                  // 0x0b
            void SendComponentOf(bool isImportant, Entity *entity, std::string component_name);     // 0x0c
            void SendGameEvent(bool isImportant);                                                   // 0x0d
            void SendDeleteEntity(bool isImportant, Entity *entity);                                // 0x0e
            void SendDeleteComponent(bool isImportant, Entity *entity, std::string component_name); // 0x0f
            void SendAskConnect(const std::string &ip, short port);                                 // 0x81
            void SendDisconnect();                                                                  // 0x82
            void SendEvent(bool isImportant, uint32_t event, bool isPressed);                       // 0x8b
            void Splitter(const std::vector<char> &message, size_t size, asio::ip::udp::endpoint senderEndpoint);

            void ResendNeedAck();

            /**
             * @brief Return an unordered map of pair of string and Connection
             *
             * @details The string is the ip of the connection and the Connection is the connection object
             *
             * @return std::unordered_map<std::string, Connection> Unordered map of pair of string and Connection
             */
            std::map<std::string, Connection> &GetConnections() { return _connections; }

            /**
             * @brief Return a queue of uint32_t representing the events received
             *
             * @return a copy of the queue of uint32_t representing the events received
             */
            std::vector<std::pair<std::pair<uint32_t, bool>, asio::ip::udp::endpoint>> GetEvents() {
                std::vector<std::pair<std::pair<uint32_t, bool>, asio::ip::udp::endpoint>> flushedEvents =
                    std::move(_events);
                return flushedEvents;
            }

            // Need to modify this function to have a good index
            int32_t ConnectionPlace(asio::ip::udp::endpoint endpoint) {
                int32_t i = 0;

                for (auto &connection : _connections) {
                    std::cout << connection.second.GetEndpoint() << ", " << i << std::endl;
                    if (connection.second.GetEndpoint() == endpoint)
                        return i;
                    i++;
                }
                return -1;
            }

            uint64_t GetId() { return id; }

            UDPSocket &GetSocket() { return _socket; }

            NetworkInfo GetNetworkInfo() { return _server_connection.GetLastNetworkInfo(); }

          private:
            void ReceivePacketInfo(RECEIVE_ARG);        // 0x00
            void ReceiveAck(RECEIVE_ARG);               // 0x01
            void ReceiveConnectAccept(RECEIVE_ARG);     // 0x02
            void ReceiveConnectReject(RECEIVE_ARG);     // 0x03
            void ReceiveSystemLoad(RECEIVE_ARG);        // 0x0b
            void ReceiveComponentOf(RECEIVE_ARG);       // 0x0c
            void ReceiveGameEvent(RECEIVE_ARG);         // 0x0d
            void ReceiveDeleteEntity(RECEIVE_ARG);      // 0x0e
            void ReceiveDeleteComponentOf(RECEIVE_ARG); // 0x0f
            void ReceiveConnect(RECEIVE_ARG);           // 0x81
            void ReceiveDisconnect(RECEIVE_ARG);        // 0x82
            void ReceiveEvent(RECEIVE_ARG);             // 0x8b
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

            int64_t GetIndexPacketNeedAck(Connection connection) {
                for (size_t i = 0; i < _packetNeedAck.size(); i++) {
                    if (_packetNeedAck[i].first == connection)
                        return i;
                }
                return -1;
            }

            World *GetWorld(Connection connection) {
                (void)connection;
                return _world;
            }

          private:
            uint64_t id = 0;
            World *_world;
            UDPSocket _socket;
            std::map<std::string, Connection> _connections;
            Connection _server_connection;
            IOContextManager &_ioContextManager;
            std::vector<std::pair<std::pair<uint32_t, bool>, asio::ip::udp::endpoint>> _events;
            std::vector<std::pair<Connection, std::unordered_map<uint64_t, Packet>>> _packetNeedAck;

        }; // class Network

    }; // namespace Network

};     // namespace Exodia
#endif /* !NETWORK_HPP_ */
