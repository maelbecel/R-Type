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
     * @brief Run the network
     *
     * @return void
     */
    void Network::Loop() {
        _socket.Receive(
            std::bind(&Network::Splitter, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    }

    /**
     * @brief Receive number of packet received and sent
     *
     * @param message (Type: const std::vector<char>) The message received
     * @param size (Type: size_t) The size of the message
     * @param senderEndpoint (Type: asio::ip::udp::endpoint) The endpoint of the sender
     */
    void Network::ReceivePacketInfo(RECEIVE_ARG) {
        (void)senderEndpoint;

        if (size != 2 * sizeof(int)) {
            EXODIA_CORE_ERROR("Network::ReceivePacketInfo() - Packet size is not correct !");
            return;
        }
        int32_t packet_received = 0;
        int32_t packet_sent = 0;

        std::memcpy(&packet_received, message.data(), sizeof(int));
        std::memcpy(&packet_sent, message.data() + sizeof(int), sizeof(int));
        std::cout << "Packet received: " << packet_received << " Packet sent: " << packet_sent << std::endl;
    }

    /**
     * @brief Receive delete entity
     *
     * @param message (Type: const std::vector<char>) The message received
     * @param size (Type: size_t) The size of the message
     * @param senderEndpoint (Type: asio::ip::udp::endpoint) The endpoint of the sender
     *
     * @return void
     */
    void Network::ReceiveDeleteEntity(RECEIVE_ARG) {
        (void)size;
        (void)senderEndpoint;

        _world->LockMutex();
        uint64_t id = 0;
        std::memcpy(&id, message.data(), sizeof(unsigned long));

        Entity *entity = _world->GetEntityByID(id);
        _world->DestroyEntity(entity);
        _world->UnlockMutex();
        EXODIA_CORE_INFO("Network::ReceiveDeleteEntity() - Entity " + std::to_string(id) + " deleted");
    }

    /**
     * @brief This function is called when the intelocutor accept the connection
     *
     * @param message (Type: const std::vector<char>) The message received
     * @param size (Type: size_t) The size of the message
     * @param senderEndpoint (Type: asio::ip::udp::endpoint) The endpoint of the sender
     *
     * @return void
     */
    void Network::ReceiveConnectAccept(RECEIVE_ARG) {
        (void)senderEndpoint;
        std::vector<char> buffer(size, 0);
        std::memcpy(buffer.data(), message.data(), size);
        std::string id(buffer.begin(), buffer.end());
        std::cout << "Receive accept connect with id :" << id << std::endl;
        this->id = id;
        std::cout << "Receive accept connect" << std::endl;
    }

    void Network::ReceiveConnectReject(RECEIVE_ARG) {
        (void)senderEndpoint;
        (void)header;
        (void)message;
        (void)size;
        //TODO: Handle reject
    }

    void Network::ReceiveSystemLoad(RECEIVE_ARG) {
        (void)senderEndpoint;
        (void)header;
        (void)message;
        (void)size;
        //TODO: Handle system load
    }

    void Network::ReceiveGameEvent(RECEIVE_ARG) {
        (void)senderEndpoint;
        (void)header;
        (void)message;
        (void)size;
        //TODO: Handle game event
    }

    void Network::ReceiveDeleteComponentOf(RECEIVE_ARG) {
        (void)senderEndpoint;
        (void)header;
        (void)message;
        (void)size;
        //TODO: Handle delete component of
    }

    void Network::ReceiveImportantEvent(RECEIVE_ARG) {
        (void)senderEndpoint;
        (void)header;
        (void)message;
        (void)size;
        //TODO: Handle important event
    }

    void Network::ReceiveDisconnect(RECEIVE_ARG) {
        (void)senderEndpoint;
        (void)header;
        (void)message;
        (void)size;
        //TODO: Handle disconnect
    }

    /**
     * @brief This function is called when an Acknowledgement is received
     *
     * @param message (Type: const std::vector<char>) The message received
     * @param size (Type: size_t) The size of the message
     * @param senderEndpoint (Type: asio::ip::udp::endpoint) The endpoint of the sender
     *
     * @return void
     */
    void Network::ReceiveAck(RECEIVE_ARG) {
        (void)size;
        (void)senderEndpoint;

        uint64_t command_id = 0;
        std::memcpy(&command_id, message.data(), sizeof(uint64_t));
        for (auto &connection : _packetNeedAck) {
            auto find = connection.second.find(command_id);
            if (find != connection.second.end()) {
                connection.second.erase(find);
                break;
            }
        }
    }

    /**
     * @brief This function is called when an entity is received
     *
     * @param message (Type: const std::vector<char>) The message received
     * @param size (Type: size_t) The size of the message
     * @param senderEndpoint (Type: asio::ip::udp::endpoint) The endpoint of the sender
     *
     * @return void
     */
    void Network::ReceiveComponentOf(RECEIVE_ARG) {
        (void)size;
        (void)senderEndpoint;

        unsigned long id = 0;
        unsigned int size_of_string = 0;
        std::string component_name;
        uint32_t size_of_data = 0;

        std::memcpy(&id, message.data(), sizeof(unsigned long));
        std::memcpy(&size_of_string, message.data() + sizeof(unsigned long), sizeof(unsigned int));
        component_name.resize(size_of_string, 0);
        std::memcpy(component_name.data(), message.data() + sizeof(unsigned long) + sizeof(unsigned int),
                    size_of_string);
        std::memcpy(&size_of_data, message.data() + sizeof(unsigned long) + sizeof(unsigned int) + size_of_string,
                    sizeof(uint32_t));
        std::vector<char> data(size_of_data, 0);
        std::memcpy(data.data(),
                    message.data() + sizeof(unsigned long) + sizeof(unsigned int) + size_of_string + sizeof(uint32_t),
                    size_of_data);

        _world->LockMutex();
        Entity *entity = _world->CreateEntity(id);

        std::function<Exodia::IComponentContainer *(Exodia::Buffer)> func =
            Project::GetActive()->GetComponentFactory(component_name);
        if (!func) {
            _world->UnlockMutex();
            std::string error = "Network::ReceiveComponentOF() - component " + component_name + " not found !";
            EXODIA_CORE_ERROR(error);
            return;
        }

        Exodia::Buffer buffer(data.data(), size_of_data);
        IComponentContainer *container = func(buffer);
        entity->AddComponent(container);
        _world->UnlockMutex();
        EXODIA_CORE_INFO("Network::createEntity() - Component " + component_name + " added to entity " +
                         std::to_string(id));
        SendAck(header.getId());
    }

    void Network::ReceiveConnect(RECEIVE_ARG) {
        (void)size;

        // Check if already Connected
        if (_connections.find(senderEndpoint.address().to_string() + ":" + std::to_string(senderEndpoint.port())) !=
            _connections.end()) {
            EXODIA_CORE_WARN("Network::ReceiveConnect() - Already connected to " +
                             senderEndpoint.address().to_string() + ":" + std::to_string(senderEndpoint.port()));
            return;
        }

        // Adding id to the buffer
        std::vector<char> buffer(0);
        std::string id = _connections.size() > 0 ? std::to_string(_connections.size()) : "0";
        buffer = std::vector<char>(id.begin(), id.end());

        const std::string name = senderEndpoint.address().to_string() + ":" + std::to_string(senderEndpoint.port());
        auto find = _connections.find(name);
        if (find == _connections.end())
            _connections[senderEndpoint.address().to_string() + ":" + std::to_string(senderEndpoint.port())] =
                Connection(senderEndpoint);
        std::string connect =
            "Connected to " + senderEndpoint.address().to_string() + ":" + std::to_string(senderEndpoint.port());
        EXODIA_CORE_INFO(connect);

        Connection connection =
            _connections[senderEndpoint.address().to_string() + ":" + std::to_string(senderEndpoint.port())];
        connection.AddReceivedPacket();
        Packet packet(0x02);
        packet.SetContent(buffer);
        std::cout << "Send accept connect" << std::endl;
        connection.SendPacket(_socket, packet);
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
    void Network::ReceiveEvent(RECEIVE_ARG) {
        (void)size;
        (void)message;
        float Timestamp = 0;
        uint32_t event = 0;
        bool isPressed = false;

        if (size != sizeof(uint32_t) + sizeof(bool)) {
            EXODIA_CORE_ERROR("Network::ReceiveEvent() - Packet size is not correct !");
            return;
        }
        std::memcpy(&event, message.data(), sizeof(uint32_t));
        std::memcpy(&isPressed, message.data() + sizeof(uint32_t), sizeof(bool));

        std::cout << "Event: " << event << std::endl;

        std::pair<std::pair<uint32_t, bool>, asio::ip::udp::endpoint> eventPair;
        eventPair.first = std::make_pair(event, isPressed);
        eventPair.second = senderEndpoint;
        _events.push_back(eventPair);
    }

    /**
     * @brief This function is called when a packet is received
     *
     * @details This function call the right function depending on the command
     *
     * @param message (Type: const std::vector<char>) The message received
     * @param size (Type: size_t) The size of the message
     * @param senderEndpoint (Type: asio::ip::udp::endpoint) The endpoint of the sender
     *
     * @return void
     */
    void Network::Splitter(const std::vector<char> &message, size_t size, asio::ip::udp::endpoint senderEndpoint) {
        (void)size;
        std::vector<char> copiedBuffer(message.begin(), message.begin() + size);
        Header header = Header::fillHeader(copiedBuffer);
        // std::cout << "Command: " << header.VerbaliseCommand() << " Timestamp: " << header.getTimestamp() << " Id: "
        // << header.getId() << " Size: " << header.getSize() << std::endl;
        EXODIA_CORE_INFO("{0}", header.toString());

        std::vector<char> content;
        if (header.getSize() > 0)
            content = std::vector<char>(copiedBuffer.begin() + int(Header::GetSize()), copiedBuffer.end());

        if (header.getSize() != content.size()) {
            EXODIA_CORE_WARN("Network::Splitter() - Packet size is not the one indicated got {0} instead of {1} !",
                             copiedBuffer.size(), header.getSize());
            return;
        }

        // if (_connections.size() > 0) {
        //     auto find = _connections.find(senderEndpoint.address().to_string() + ":" +
        //     std::to_string(senderEndpoint.port())); if (find == _connections.end()) {
        //         EXODIA_CORE_WARN("Network::Splitter() - Connection not found !"); TODO : Check if we need to do this
        //         return;
        //     }
        //     find->second.AddReceivedPacket();
        //     if (find->second.GetLastId() >= (int)header.getId()) {
        //         EXODIA_CORE_WARN("Network::Splitter() - Packet already received !");
        //         return;
        //     }
        //     find->second.SetLastId(header.getId());
        // } else {
        //     _server_connection.AddReceivedPacket();
        //     if (_server_connection.GetLastId() >= (int)header.getId()) {
        //         EXODIA_CORE_WARN("Network::Splitter() - Packet already received !");
        //         return;
        //     }
        //     _server_connection.SetLastId(header.getId());
        // }

        std::unordered_map<unsigned char,
                           std::function<void(const std::vector<char>, size_t, asio::ip::udp::endpoint senderEndpoint,
                                              Exodia::Network::Header _header)>>
            commands;
        commands[0x00] = COMMAND_NETWORK(Network::ReceivePacketInfo); // Packet info
        commands[0x01] = COMMAND_NETWORK(Network::ReceiveAck); // Packet Acknowledgement
        commands[0x02] = COMMAND_NETWORK(Network::ReceiveConnectAccept); // Accept client connection
        commands[0x81] = COMMAND_NETWORK(Network::ReceiveConnect); // Ask for connection
        commands[0x8b] = COMMAND_NETWORK(Network::ReceiveEvent); // Send an event
        commands[0x0c] = COMMAND_NETWORK(Network::ReceiveComponentOf); // Send one component of an entity
        commands[0x0e] = COMMAND_NETWORK(Network::ReceiveDeleteEntity); // Send delete entity
        commands[header.getCommand()](content, header.getSize(), senderEndpoint, header);
    }
}; // namespace Exodia::Network
