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
                    Exodia::Network::Header header(0x00, 1, 2);
                    Exodia::Network::Packet packet;
                    std::vector<char> buffer(2 * sizeof(int));
                    int packet_received = 0;
                    int packet_sent = 0;

                    size_t offset = 0;
                    offset = fill_data(buffer, offset, &packet_received, sizeof(int));
                    offset = fill_data(buffer, offset, &packet_sent, sizeof(int));
                    packet.set(header, buffer);
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

                size_t fill_data(std::vector<char> &buffer, size_t offset, void *data, size_t size) {
                    std::memcpy(buffer.data() + offset, data, size);
                    return offset + size;
                }

                void sendEntity(Entity *entity, std::string component_name) {
                    Exodia::Network::Header header(0x0c, 1, 2);
                    Exodia::Network::Packet packet;
                    std::vector<char> buffer(1468, 0);

                    IComponentContainer *container = entity->GetComponent(component_name);
                    std::cout << "Container: " << container << std::endl;

                    std::string component = component_name;
                    unsigned int size_of_string = component.size();
                    unsigned long id = entity->GetEntityID();

                    uint32_t size_of_data = sizeof(container);
                    std::vector<char> data(size_of_data, 0);
                    std::memcpy(data.data(), &container, size_of_data);

                    size_t offset = 0;
                    offset = fill_data(buffer, offset, &id, sizeof(unsigned long)); //Set if of entity
                    offset = fill_data(buffer, offset, &size_of_string, sizeof(unsigned int)); //Set size of name
                    offset = fill_data(buffer, offset, component.data(), component.size()); // Set name
                    offset = fill_data(buffer, offset, &size_of_data, sizeof(uint32_t)); // Set size of data
                    offset = fill_data(buffer, offset, data.data(), size_of_data); // Set data

                    packet.set(header, buffer);
                    _socket.send(packet.getBuffer(), packet.get_size(), _remote_endpoint[0]);
                }

                void createEntity(const std::vector<char> message, size_t size) {
                    (void) size;
                    unsigned long id = 0;
                    unsigned int size_of_string = 0;
                    std::string component_name;
                    uint32_t size_of_data = 0;

                    std::memcpy(&id, message.data(), sizeof(unsigned long));
                    std::memcpy(&size_of_string, message.data() + sizeof(unsigned long), sizeof(unsigned int));
                    component_name.resize(size_of_string, 0);
                    std::memcpy(component_name.data(), message.data() + sizeof(unsigned long) + sizeof(unsigned int), size_of_string);
                    std::memcpy(&size_of_data, message.data() + sizeof(unsigned long) + sizeof(unsigned int) + size_of_string, sizeof(uint32_t));
                    std::vector<char> data(size_of_data, 0);
                    std::memcpy(data.data(), message.data() + sizeof(unsigned long) + sizeof(unsigned int) + size_of_string + sizeof(uint32_t), size_of_data);

                    std::cout << "Id: " << id << " Size of string: " << size_of_string << " component_name: " << component_name << " Size of data: " << size_of_data << std::endl;
                    Entity *entity = _world->CreateEntity(id);

                    std::function<Exodia::IComponentContainer *(Exodia::Buffer)> func = Project::GetActive()->GetComponentFactory(component_name);
                    // auto func = Project::GetActive()->GetComponentFactory(component_name);
                    if (!func) {
                        std::string error = "Network::createEntity() - component " + component_name + " not found !";
                        EXODIA_CORE_ERROR(error);
                        return;
                    }
                    Exodia::Buffer buffer(data.data(), size_of_data);
                    IComponentContainer *container = func(buffer);
                    entity->AddComponent(container);
                    std::cout << entity->GetComponent<TransformComponent>()->Translation.x << std::endl;
                    std::cout << "Entity created" << std::endl;
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
