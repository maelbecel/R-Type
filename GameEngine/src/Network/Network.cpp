/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** Network
*/

#include "Network.hpp"

namespace Exodia::Network {
    void Network::sendAskConnect() {
        Exodia::Network::Header header(0x81, 1, 2);
        Exodia::Network::Packet packet;
        std::vector<char> buffer(0);

        packet.set(header, buffer);
        _socket.send(packet.getBuffer(), packet.get_size(), _remote_endpoint[0]);
    }

    /**
     * @brief Run the network
     *
     */
    void Network::loop() {
        _socket.receive(std::bind(&Network::splitter, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    }

    void Network::sendPacketInfo() {
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

    void Network::receivePacketInfo(const std::vector<char> message, size_t size, asio::ip::udp::endpoint senderEndpoint) {
        (void) size;
        (void) senderEndpoint;

        int packet_received = 0;
        int packet_sent = 0;

        std::memcpy(&packet_received, message.data(), sizeof(int));
        std::memcpy(&packet_sent, message.data() + sizeof(int), sizeof(int));
        std::cout << "Packet received: " << packet_received << " Packet sent: " << packet_sent << std::endl;
    }

    size_t Network::fill_data(std::vector<char> &buffer, size_t offset, void *data, size_t size) {
        std::memcpy(buffer.data() + offset, data, size);
        return offset + size;
    }

    void Network::sendEntity(Entity *entity, std::string component_name) {
        Exodia::Network::Header header(0x0c, 1, 2);
        Exodia::Network::Packet packet;
        std::vector<char> buffer(1468, 0);

        IComponentContainer *container = entity->GetComponent(component_name);
        Buffer data = container->SerializeData();
        unsigned int size_of_string = component_name.size();
        unsigned long entity_id = entity->GetEntityID();

        size_t size_of_data = data.Size;
        size_t offset = 0;
        offset = fill_data(buffer, offset, &entity_id, sizeof(unsigned long));           // Set if of entity
        offset = fill_data(buffer, offset, &size_of_string, sizeof(unsigned int));       // Set size of name
        offset = fill_data(buffer, offset, component_name.data(), component_name.size());// Set name
        offset = fill_data(buffer, offset, &size_of_data, sizeof(uint32_t));             // Set size of data
        offset = fill_data(buffer, offset, data.Data, size_of_data);                     // Set data

        packet.set(header, buffer);
        _socket.send(packet.getBuffer(), packet.get_size(), _remote_endpoint[0]);
    }

    void Network::sendAck() {
        Exodia::Network::Header header(0x01, 1, 2);
        Exodia::Network::Packet packet;
        std::vector<char> buffer(sizeof(uint64_t));
        uint64_t command_id;

        size_t offset = 0;
        offset = fill_data(buffer, offset, &command_id, sizeof(uint64_t));
        packet.set(header, buffer);
        _socket.send(packet.getBuffer(), packet.get_size(), _remote_endpoint[0]);
    }

    void Network::receiveAck(const std::vector<char> message, size_t size, asio::ip::udp::endpoint senderEndpoint) {
        (void) size;
        (void) senderEndpoint;

        uint64_t command_id = 0;
        std::vector<char> buffer(sizeof(uint64_t));
        std::memcpy(&command_id, message.data(), sizeof(uint64_t));
        std::cout << "Command id: " << command_id << std::endl;
    }

    void Network::receiveEntity(const std::vector<char> message, size_t size, asio::ip::udp::endpoint senderEndpoint) {
        (void) size;
        (void) senderEndpoint;

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

        Entity *entity = _world->CreateEntity(id);

        std::function<Exodia::IComponentContainer *(Exodia::Buffer)> func = Project::GetActive()->GetComponentFactory(component_name);
        if (!func) {
            std::string error = "Network::createEntity() - component " + component_name + " not found !";
            EXODIA_CORE_ERROR(error);
            return;
        }
        Exodia::Buffer buffer(data.data(), size_of_data);
        IComponentContainer *container = func(buffer);
        entity->AddComponent(container);
    }

    void Network::receiveConnect(const std::vector<char> message, size_t size, asio::ip::udp::endpoint senderEndpoint) {
        (void) size;
        (void) message;
        auto find = std::find(_remote_endpoint.begin(), _remote_endpoint.end(), senderEndpoint);
        if (find == _remote_endpoint.end())
            _remote_endpoint.push_back(senderEndpoint);
        std::string connect = "Connected to " + senderEndpoint.address().to_string() + ":" + std::to_string(senderEndpoint.port());
        EXODIA_CORE_INFO(connect);
    }

    void Network::sendAcceptConnect() {
        Exodia::Network::Header header(0x02, 1, 2);
        Exodia::Network::Packet packet;
        std::vector<char> buffer(0);

        packet.set(header, buffer);
        _socket.send(packet.getBuffer(), packet.get_size(), _remote_endpoint[0]);
    }

    void Network::splitter(const std::vector<char> message, size_t size, asio::ip::udp::endpoint senderEndpoint) {
        (void) size;
        Header header = Header::fillHeader(message.data());
        std::cout << "Command: " << int(header.getCommand()) << " Timestamp: " << header.getTimestamp() << " Id: " << header.getId() << " Size: " << header.getSize() << std::endl;

        std::vector<char> content(message.begin() + int(Header::get_size()), message.end());

        std::unordered_map<char, std::function<void(const std::vector<char>, size_t, asio::ip::udp::endpoint senderEndpoint)>> commands;
        commands[0x00] = std::bind(&Network::receivePacketInfo, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3); // Packet info for loss calculation
        commands[0x01] = std::bind(&Network::receiveAck, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);        // Packet Acknowledgement
        commands[0x02] = std::bind(&Network::receiveEntity, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);     // Accept client connection
        commands[0x81] = std::bind(&Network::receiveConnect, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);        // Ask for connection
        commands[0x0c] = std::bind(&Network::receiveEntity, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);     // Send one component of an entity
        commands[header.getCommand()](content, header.getSize(), senderEndpoint);
    }

    void Network::startIOContextThread() {
        _ioContextThread = std::thread([this]() {
            _ioContextManager.run();
        });
    }

    void Network::stopIOContextThread() {
        _ioContextThread.join();
    }
};
