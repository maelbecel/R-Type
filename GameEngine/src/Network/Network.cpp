/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** Network
*/

#include "Network.hpp"
#include "Utils/Memory.hpp"

namespace Exodia::Network {

    /**
     * @brief send a packet to request connection to the server
     *
     * @param ip (Type: const std::string &) The ip of the server
     * @param port (Type: short) The port of the server
     * @return void
    */
    void Network::sendAskConnect(const std::string &ip, short port) {
        connect(ip, port);
        Exodia::Network::Header header(0x81, 1, 2);
        Exodia::Network::Packet packet;
        std::vector<char> buffer(0);

        packet.set(header, buffer);
        std::cout << "Send ask connect" << std::endl;
        _server_connection.sendPacket(_socket, packet);
    }

    /**
     * @brief Run the network
     *
     */
    void Network::loop() {
        _socket.receive(std::bind(&Network::splitter, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    }

    /**
     * @brief Send number of packet received and sent
     *
     * @return void
    */
    void Network::sendPacketInfo() {
        Exodia::Network::Header header(0x00, 1, 2);
        Exodia::Network::Packet packet;
        std::vector<char> buffer(2 * sizeof(int));

        packet.set(header, buffer);

        if (_connections.size() > 0) {
           for (auto &connection : _connections) {
                int32_t received = connection.second.getReceivedPacket();
                int32_t sent = connection.second.getSendPacket();

                size_t offset = 0;
                offset = fill_data(buffer, offset, &received, sizeof(int));
                offset = fill_data(buffer, offset, &sent, sizeof(int));
                packet.set(header, buffer);
                connection.second.sendPacket(_socket, packet);
           }
        } else {
            int32_t received = _server_connection.getReceivedPacket();
            int32_t sent = _server_connection.getSendPacket();

            size_t offset = 0;
            offset = fill_data(buffer, offset, &received, sizeof(int));
            offset = fill_data(buffer, offset, &sent, sizeof(int));
            packet.set(header, buffer);
            _server_connection.sendPacket(_socket, packet);
        }
    }

    /**
     * @brief Receive number of packet received and sent
     *
     * @param message (Type: const std::vector<char>) The message received
     * @param size (Type: size_t) The size of the message
     * @param senderEndpoint (Type: asio::ip::udp::endpoint) The endpoint of the sender
    */
    void Network::receivePacketInfo(const std::vector<char> message, size_t size, asio::ip::udp::endpoint senderEndpoint) {
        (void) senderEndpoint;


        if (size != 2 * sizeof(int)) {
            EXODIA_CORE_ERROR("Network::receivePacketInfo() - Packet size is not correct !");
            return;
        }
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

        unsigned long size_of_string = (unsigned long)component_name.size();
        unsigned long entity_id = (unsigned long)entity->GetEntityID();

        size_t size_of_data = data.Size;
        size_t offset = 0;
        offset = fill_data(buffer, offset, &entity_id, sizeof(unsigned long));           // Set if of entity
        offset = fill_data(buffer, offset, &size_of_string, sizeof(unsigned long));       // Set size of name
        offset = fill_data(buffer, offset, component_name.data(), component_name.size());// Set name
        offset = fill_data(buffer, offset, &size_of_data, sizeof(uint32_t));             // Set size of data
        offset = fill_data(buffer, offset, data.Data, size_of_data);                     // Set data

        packet.set(header, buffer);
        if (_connections.size() > 0)
           for (auto &connection : _connections)
                connection.second.sendPacket(_socket, packet);
        else
            _server_connection.sendPacket(_socket, packet);
    }

    void Network::sendAck() {
        Exodia::Network::Header header(0x01, 1, 2);
        Exodia::Network::Packet packet;
        std::vector<char> buffer(sizeof(uint64_t));
        uint64_t command_id;

        size_t offset = 0;
        offset = fill_data(buffer, offset, &command_id, sizeof(uint64_t));
        packet.set(header, buffer);
        if (_connections.size() > 0)
           for (auto &connection : _connections)
                connection.second.sendPacket(_socket, packet);
        else
            _server_connection.sendPacket(_socket, packet);
    }

    void Network::receiveConnectAccept(const std::vector<char> message, size_t size, asio::ip::udp::endpoint senderEndpoint) {
        (void) size;
        (void) message;
        (void) senderEndpoint;
        std::cout << "Receive accept connect" << std::endl;
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
        const std::string name = senderEndpoint.address().to_string() + ":" + std::to_string(senderEndpoint.port());
        auto find = _connections.find(name);
        if (find == _connections.end())
            _connections[senderEndpoint.address().to_string() + ":" + std::to_string(senderEndpoint.port())] = Connection(senderEndpoint);
        std::string connect = "Connected to " + senderEndpoint.address().to_string() + ":" + std::to_string(senderEndpoint.port());
        EXODIA_CORE_INFO(connect);

        Connection connection = _connections[senderEndpoint.address().to_string() + ":" + std::to_string(senderEndpoint.port())];
        connection.AddReceivedPacket();
        Packet packet;
        Header header(0x02, 1, 2);
        packet.setHeader(header);
        std::cout << "Send accept connect" << std::endl;
        connection.sendPacket(_socket, packet);

    }

    void Network::sendAcceptConnect() {
        Exodia::Network::Header header(0x02, 1, 2);
        Exodia::Network::Packet packet;
        std::vector<char> buffer(0);

        packet.set(header, buffer);
        if (_connections.size() > 0)
           for (auto &connection : _connections)
                connection.second.sendPacket(_socket, packet);
        else
            _server_connection.sendPacket(_socket, packet);
    }

    /**
     * @brief Send an event
     *
     * @param event (Type: uint32_t) The event to send
    */
    void Network::sendEvent(uint32_t event) {
        Exodia::Network::Header header(0x82, 1, 2);
        Exodia::Network::Packet packet;
        std::vector<char> buffer(sizeof(uint32_t));
        size_t offset = 0;

        offset = fill_data(buffer, offset, &event, sizeof(uint32_t));
        packet.set(header, buffer);
        if (_connections.size() > 0) {
           for (auto &connection : _connections)
                connection.second.sendPacket(_socket, packet);
        } else
            _server_connection.sendPacket(_socket, packet);
    }

    /**
    * @brief Receive an event
    *
    * @param message (Type: const std::vector<char>) The message received
    * @param size (Type: size_t) The size of the message
    * @param senderEndpoint (Type: asio::ip::udp::endpoint) The endpoint of the sender
    */
    void Network::receiveEvent(const std::vector<char> message, size_t size, asio::ip::udp::endpoint senderEndpoint) {
        (void) size;
        (void) message;
        uint32_t event = 0;

        if (size != sizeof(uint32_t)) {
            EXODIA_CORE_ERROR("Network::receiveEvent() - Packet size is not correct !");
            return;
        }
        std::memcpy(&event, message.data(), sizeof(uint32_t));
        std::cout << "Event: " << event << std::endl;

    }

    void Network::splitter(const std::vector<char> message, size_t size, asio::ip::udp::endpoint senderEndpoint) {
        (void) size;
        Header header = Header::fillHeader(message.data());
        std::cout << "Command: " << int(header.getCommand()) << " Timestamp: " << header.getTimestamp() << " Id: " << header.getId() << " Size: " << header.getSize() << std::endl;

        std::vector<char> content(message.begin() + int(Header::GetSize()), message.end());

        std::unordered_map<unsigned char, std::function<void(const std::vector<char>, size_t, asio::ip::udp::endpoint senderEndpoint)>> commands;
        commands[0x00] = std::bind(&Network::receivePacketInfo, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3); // Packet info for loss calculation
        commands[0x01] = std::bind(&Network::receiveAck, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);        // Packet Acknowledgement
        commands[0x02] = std::bind(&Network::receiveConnectAccept, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);     // Accept client connection
        commands[0x81] = std::bind(&Network::receiveConnect, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);        // Ask for connection
        commands[0x82] = std::bind(&Network::receiveEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);          // Send an event
        commands[0x0c] = std::bind(&Network::receiveEntity, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);     // Send one component of an entity
        commands[header.getCommand()](content, header.getSize(), senderEndpoint);
    }
};
