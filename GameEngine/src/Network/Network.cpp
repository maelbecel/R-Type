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
    void Network::SendAskConnect(const std::string &ip, short port) {
        connect(ip, port);
        Exodia::Network::Header header(0x81, 1, 0);
        Exodia::Network::Packet packet;
        std::vector<char> buffer(0);

        packet.Set(header, buffer);
        _server_connection.SendPacket(_socket, packet);
    }

    /**
     * @brief Run the network
     *
     */
    void Network::Loop() {
        _socket.receive(std::bind(&Network::Splitter, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    }

    /**
     * @brief Send number of packet received and sent
     *
     * @return void
    */
    void Network::SendPacketInfo() {
        Exodia::Network::Header header(0x00, 1, 2);
        Exodia::Network::Packet packet;
        std::vector<char> buffer(2 * sizeof(int));

        packet.Set(header, buffer);

        if (_connections.size() > 0) {
           for (auto &connection : _connections) {
                int32_t received = connection.second.GetReceivedPacket();
                int32_t sent = connection.second.GetSendPacket();

                size_t offset = 0;
                offset = FillData(buffer, offset, &received, sizeof(int));
                offset = FillData(buffer, offset, &sent, sizeof(int));
                packet.Set(header, buffer);
                connection.second.SendPacket(_socket, packet);
           }
        } else {
            int32_t received = _server_connection.GetReceivedPacket();
            int32_t sent = _server_connection.GetSendPacket();

            size_t offset = 0;
            offset = FillData(buffer, offset, &received, sizeof(int));
            offset = FillData(buffer, offset, &sent, sizeof(int));
            packet.Set(header, buffer);
            _server_connection.SendPacket(_socket, packet);
        }
    }

    /**
     * @brief Receive number of packet received and sent
     *
     * @param message (Type: const std::vector<char>) The message received
     * @param size (Type: size_t) The size of the message
     * @param senderEndpoint (Type: asio::ip::udp::endpoint) The endpoint of the sender
    */
    void Network::ReceivePacketInfo(const std::vector<char> message, size_t size, asio::ip::udp::endpoint senderEndpoint, Exodia::Network::Header header) {
        (void) senderEndpoint;


        if (size != 2 * sizeof(int)) {
            EXODIA_CORE_ERROR("Network::ReceivePacketInfo() - Packet size is not correct !");
            return;
        }
        int packet_received = 0;
        int packet_sent = 0;

        std::memcpy(&packet_received, message.data(), sizeof(int));
        std::memcpy(&packet_sent, message.data() + sizeof(int), sizeof(int));
        std::cout << "Packet received: " << packet_received << " Packet sent: " << packet_sent << std::endl;
    }

    size_t Network::FillData(std::vector<char> &buffer, size_t offset, void *data, size_t size) {
        std::memcpy(buffer.data() + offset, data, size);
        return offset + size;
    }

    void Network::SendEntity(Entity *entity, std::string component_name) {
        Exodia::Network::Header header(0x0c, 1, 2);
        Exodia::Network::Packet packet;
        std::vector<char> buffer(1468, 0);

        IComponentContainer *container = entity->GetComponent(component_name);
        Buffer data = container->SerializeData();

        unsigned long size_of_string = (unsigned long)component_name.size();
        unsigned long entity_id = (unsigned long)entity->GetEntityID();

        size_t size_of_data = data.Size;
        size_t offset = 0;

        offset = FillData(buffer, offset, &entity_id, sizeof(unsigned long));           // Set id of entity
        offset = FillData(buffer, offset, &size_of_string, sizeof(unsigned int));       // Set size of name
        offset = FillData(buffer, offset, component_name.data(), component_name.size());// Set name
        offset = FillData(buffer, offset, &size_of_data, sizeof(uint32_t));             // Set size of data
        offset = FillData(buffer, offset, data.Data, size_of_data);                     // Set data
        buffer.resize(offset);

        packet.Set(header, buffer);
        if (_connections.size() > 0)
           for (auto &connection : _connections)
                connection.second.SendPacket(_socket, packet);
        else
            _server_connection.SendPacket(_socket, packet);
    }

    void Network::SendAck() {
        Exodia::Network::Header header(0x01, 1, 2);
        Exodia::Network::Packet packet;
        std::vector<char> buffer(sizeof(uint64_t));
        uint64_t command_id;

        size_t offset = 0;
        offset = FillData(buffer, offset, &command_id, sizeof(uint64_t));
        packet.Set(header, buffer);
        if (_connections.size() > 0)
           for (auto &connection : _connections)
                connection.second.SendPacket(_socket, packet);
        else
            _server_connection.SendPacket(_socket, packet);
    }

    void Network::ReceiveConnectAccept(const std::vector<char> message, size_t size, asio::ip::udp::endpoint senderEndpoint, Exodia::Network::Header header) {
        (void) size;
        (void) message;
        (void) senderEndpoint;
        std::cout << "Receive accept connect" << std::endl;
    }

    void Network::ReceiveAck(const std::vector<char> message, size_t size, asio::ip::udp::endpoint senderEndpoint, Exodia::Network::Header header) {
        (void) size;
        (void) senderEndpoint;

        uint64_t command_id = 0;
        std::vector<char> buffer(sizeof(uint64_t));
        std::memcpy(&command_id, message.data(), sizeof(uint64_t));
        std::cout << "Command id: " << command_id << std::endl;
    }

    void Network::ReceiveEntity(const std::vector<char> message, size_t size, asio::ip::udp::endpoint senderEndpoint, Exodia::Network::Header header) {
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
        EXODIA_CORE_INFO("Network::createEntity() - Component " + component_name + " added to entity " + std::to_string(id));
    }

    void Network::ReceiveConnect(const std::vector<char> message, size_t size, asio::ip::udp::endpoint senderEndpoint, Exodia::Network::Header header) {
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
        Header newHeader(0x02, 1, 2);
        packet.SetHeader(newHeader);
        std::cout << "Send accept connect" << std::endl;
        connection.SendPacket(_socket, packet);

    }

    void Network::SendAcceptConnect() {
        Exodia::Network::Header header(0x02, 1, 2);
        Exodia::Network::Packet packet;
        std::vector<char> buffer(0);

        packet.Set(header, buffer);
        if (_connections.size() > 0)
           for (auto &connection : _connections)
                connection.second.SendPacket(_socket, packet);
        else
            _server_connection.SendPacket(_socket, packet);
    }

    /**
     * @brief Send an event
     *
     * @param event (Type: uint32_t) The event to send
    */
    void Network::SendEvent(uint32_t event) {
        Exodia::Network::Header header(0x82, 1, 2);
        Exodia::Network::Packet packet;
        std::vector<char> buffer(sizeof(uint32_t));
        size_t offset = 0;

        offset = FillData(buffer, offset, &event, sizeof(uint32_t));
        packet.Set(header, buffer);
        if (_connections.size() > 0) {
           for (auto &connection : _connections)
                connection.second.SendPacket(_socket, packet);
        } else
            _server_connection.SendPacket(_socket, packet);
    }

    /**
    * @brief Receive an event
    *
    * @details This function is called when an event is received and it add it to the event queue
    *
    * @param message (Type: const std::vector<char>) The message received
    * @param size (Type: size_t) The size of the message
    * @param senderEndpoint (Type: asio::ip::udp::endpoint) The endpoint of the sender
    */
    void Network::ReceiveEvent(const std::vector<char> message, size_t size, asio::ip::udp::endpoint senderEndpoint, Exodia::Network::Header header) {
        (void) size;
        (void) message;
        float Timestamp = 0;
        uint32_t event = 0;

        if (size != sizeof(uint32_t)) {
            EXODIA_CORE_ERROR("Network::ReceiveEvent() - Packet size is not correct !");
            return;
        }
        std::memcpy(&event, message.data(), sizeof(uint32_t));

        std::cout << "Event: " << event << std::endl;

        _events.push(event);

    }

    void Network::Splitter(const std::vector<char> &message, size_t size, asio::ip::udp::endpoint senderEndpoint) {
        (void) size;
        std::vector<char> copiedBuffer(message.begin(), message.begin() + size);
        Header header = Header::fillHeader(copiedBuffer);
        std::cout << "Command: " << Network::VerbaliseCommand(header) << " Timestamp: " << header.getTimestamp() << " Id: " << header.getId() << " Size: " << header.getSize() << std::endl;

        std::vector<char> content;
        if (header.getSize() > 0)
            content = std::vector<char>(copiedBuffer.begin() + int(Header::GetSize()), copiedBuffer.end());

        if (header.getSize() != content.size()) {
            EXODIA_CORE_ERROR("Network::Splitter() - Packet size is not the one indicated got {0} instead of {1} !", copiedBuffer.size(), header.getSize());
            return;
        }

        std::unordered_map<unsigned char, std::function<void(const std::vector<char>, size_t, asio::ip::udp::endpoint senderEndpoint, Exodia::Network::Header _header)>> commands;
        commands[0x00] = std::bind(&Network::ReceivePacketInfo, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4); // Packet info for loss calculation
        commands[0x01] = std::bind(&Network::ReceiveAck, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);        // Packet Acknowledgement
        commands[0x02] = std::bind(&Network::ReceiveConnectAccept, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);     // Accept client connection
        commands[0x81] = std::bind(&Network::ReceiveConnect, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);        // Ask for connection
        commands[0x82] = std::bind(&Network::ReceiveEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);          // Send an event
        commands[0x0c] = std::bind(&Network::ReceiveEntity, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);     // Send one component of an entity
        commands[header.getCommand()](content, header.getSize(), senderEndpoint, header);
    }
};
