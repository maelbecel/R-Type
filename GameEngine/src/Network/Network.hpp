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
    #include "Packet/Packet.hpp"
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
                    stopIOContextThread();
                };

                /**
                 * @brief Connect to a remote endpoint
                 *
                 */
                void connect(const std::string &ip, short port) {
                    _remote_endpoint.push_back(asio::ip::udp::endpoint(asio::ip::address::from_string(ip), port));
                }

                /**
                 * @brief Run the network
                 *
                 */
                void loop() {
                    _socket.receive(std::bind(&Network::splitter, this, std::placeholders::_1, std::placeholders::_2));
                }

                void sendPacketInfo() {
                    float time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
                    Exodia::Network::Header header(0x00, time, 1, 2);
                    Exodia::Network::Packet packet;
                    std::vector<char> buffer(2 * sizeof(int));
                    int packet_received = 0;
                    int packet_sent = 0;

                    std::memcpy(buffer.data(), &packet_received, sizeof(int));
                    std::memcpy(buffer.data() + sizeof(int), &packet_sent, sizeof(int));
                    packet.setHeader(header);
                    packet.setContent(buffer);
                    _socket.send(packet.getBuffer(), packet.get_size(), _remote_endpoint[0]);
                }

                void receivePacketInfo(const std::vector<char> message, size_t size) {
                    (void) size;
                    int packet_received = 0;
                    int packet_sent = 0;

                    std::memcpy(&packet_received, message.data(), sizeof(int));
                    std::memcpy(&packet_sent, message.data() + sizeof(int), sizeof(int));
                    std::cout << "Packet received: " << packet_received << " Packet sent: " << packet_sent << std::endl;
                }

                void sendEntity() {
                    float time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
                    Exodia::Network::Header header(0x0c, time, 1, 2);
                    Exodia::Network::Packet packet;
                    std::vector<char> buffer(1468, 0);

                    std::string component = "Test";
                    unsigned int size_of_string = component.size();
                    unsigned long id = 1;

                    std::memcpy(buffer.data(), &id, sizeof(unsigned long));
                    std::memcpy(buffer.data() + sizeof(unsigned long), &size_of_string, sizeof(unsigned int));
                    std::memcpy(buffer.data() + sizeof(unsigned int) + sizeof(unsigned long), component.c_str(), component.size());

                    packet.setHeader(header);
                    packet.setContent(buffer);
                    std::vector<char> test = packet.getBuffer();
                    for (int i = 0; i < 30; i++)
                        std::cout << test[i] << std::endl;
                    _socket.send(packet.getBuffer(), packet.get_size(), _remote_endpoint[0]);
                }
                void createEntity(const std::vector<char> message, size_t size) {
                    (void) size;
                    unsigned long id = 0;
                    unsigned int size_of_string = 0;

                    std::memcpy(&id, message.data(), sizeof(unsigned long));
                    std::memcpy(&size_of_string, message.data() + sizeof(unsigned long), sizeof(unsigned int));
                    std::string component(size_of_string, 0);
                    std::memcpy(component.data(), message.data() + sizeof(unsigned long) + sizeof(unsigned int), size_of_string);

                    std::cout << "Id: " << id << " Size of string: " << size_of_string << " Component: " << component << std::endl;
                    // _world->CreateNewEntity
                }

                void splitter(const std::vector<char> message, size_t size) {
                    (void) size;
                    Header header = Header::fillHeader(message.data());
                    std::cout << "Command: " << int(header.getCommand()) << " Timestamp: " << header.getTimestamp() << " Id: " << header.getId() << " Size: " << header.getSize() << std::endl;

                    std::vector<char> content(message.begin() + int(Header::get_size()), message.end());

                    std::unordered_map<char, std::function<void(const std::vector<char>, size_t)>> commands;
                    commands[0x00] = std::bind(&Network::receivePacketInfo, this, std::placeholders::_1, std::placeholders::_2);
                    commands[0x01] = std::bind(&Network::receivePacketInfo, this, std::placeholders::_1, std::placeholders::_2);
                    commands[0x0c] = std::bind(&Network::createEntity, this, std::placeholders::_1, std::placeholders::_2);



                    commands[header.getCommand()](content, header.getSize());
                }

                void startIOContextThread() {
                    _ioContextThread = std::thread([this]() {
                        _ioContextManager.run();
                    });
                }

                void stopIOContextThread() {
                    _ioContextThread.join();
                }

                std::vector<asio::ip::udp::endpoint> getRemoteEndpoint() const {
                    return _remote_endpoint;
                }

            private:
                World *_world;
                UDPSocket _socket;
                std::vector<asio::ip::udp::endpoint> _remote_endpoint;

                // IOContext
                IOContextManager &_ioContextManager;
                std::thread _ioContextThread;

        }; // class Network

    }; // namespace Network

}; // namespace Exodia
#endif /* !NETWORK_HPP_ */
