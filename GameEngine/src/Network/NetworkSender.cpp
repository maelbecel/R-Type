/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** Network
*/

#include "Network.hpp"
#include "Utils/Memory.hpp"

namespace Exodia::Network {


    void Network::SendPacket(Packet packet) {
        if (_connections.size() > 0) {
            for (auto &connection : _connections)
                connection.second.SendPacket(_socket, packet);
        } else
            _server_connection.SendPacket(_socket, packet);
    }

    void Network::SendImportantPacket(Packet packet) {
        if (_connections.size() > 0) { // If we are the server
            for (auto &connection : _connections) {
                connection.second.SendPacket(_socket, packet);
                int64_t find = GetIndexPacketNeedAck(connection.second);
                if (find == -1) {
                    _packetNeedAck.push_back(std::make_pair(connection.second, std::unordered_map<uint64_t, Packet>()));
                    find = _packetNeedAck.size() - 1; // Update the value of find to the new index
                }
                _packetNeedAck[find].second[packet.GetHeader()->GetId()] = packet;
            }
        } else { // If we are the client
            _server_connection.SendPacket(_socket, packet);
            int64_t find = GetIndexPacketNeedAck(_server_connection);
            if (find == -1) {
                _packetNeedAck.push_back(std::make_pair(_server_connection, std::unordered_map<uint64_t, Packet>()));
                find = _packetNeedAck.size() - 1; // Update the value of find to the new index
            }
            _packetNeedAck[find].second[packet.GetHeader()->GetId()] = packet;
        }
    }

    /**
     * @brief send a packet to request connection to the server
     *
     * @param ip (Type: const std::string &) The ip of the server
     * @param port (Type: short) The port of the server
     * @return void
     */
    void Network::SendAskConnect(const std::string &ip, short port) {
        connect(ip, port);
        Packet packet(0x81);
        std::vector<char> buffer(0);

        packet.SetContent(buffer);
        _server_connection.SendPacket(_socket, packet);
    }

    /**
     * @brief Send number of packet received and sent
     *
     * @return void
     */
    void Network::SendPacketInfo() {
        Exodia::Network::Packet packet(0x00);
        std::vector<char> buffer(2 * sizeof(int));

        packet.SetContent(buffer);

        if (_connections.size() > 0) {
            for (auto &connection : _connections) {
                int32_t received = connection.second.GetReceivedPacket();
                int32_t sent = connection.second.GetSendPacket();

                size_t offset = 0;
                offset = FillData(buffer, offset, &received, sizeof(int));
                offset = FillData(buffer, offset, &sent, sizeof(int));
                packet.SetContent(buffer);
                connection.second.SendPacket(_socket, packet);
            }
        } else {
            int32_t received = _server_connection.GetReceivedPacket();
            int32_t sent = _server_connection.GetSendPacket();

            size_t offset = 0;
            offset = FillData(buffer, offset, &received, sizeof(int));
            offset = FillData(buffer, offset, &sent, sizeof(int));
            packet.SetContent(buffer);
            _server_connection.SendPacket(_socket, packet);
        }
    }

    /**
     * @brief Fill a buffer with data and return the offset after filling
     *
     * @param buffer (Type: std::vector<char> &) The buffer to fill
     * @param offset (Type: size_t) The offset to start filling the buffer
     * @param data (Type: void *) The data to put in the buffer
     * @param size (Type: size_t) The size of the data
     *
     * @return size_t The offset after filling the buffer
     */
    size_t Network::FillData(std::vector<char> &buffer, size_t offset, void *data, size_t size) {
        std::memcpy(buffer.data() + offset, data, size);
        return offset + size;
    }

    /**
     * @brief Send an entity
     *
     * @param entity (Type: Entity *) The entity to send
     * @param component_name (Type: std::string) The name of the component to send
     *
     * @return void
     */
    void Network::SendComponentOf(Entity *entity, std::string component_name) {
        Exodia::Network::Packet packet(0x0c);
        std::vector<char> buffer(1468, 0);

        if (entity == nullptr) {
            EXODIA_CORE_ERROR("Network::SendComponentOf() - Entity is null !");
            return;
        }
        if (entity->GetComponent(component_name) == nullptr) {
            EXODIA_CORE_ERROR("Network::SendComponentOf() - Component " + component_name + " not found !");
            return;
        }

        IComponentContainer *container = entity->GetComponent(component_name);
        Buffer data = container->SerializeData();

        unsigned long size_of_string = (unsigned long)component_name.size();
        unsigned long entity_id = (unsigned long)entity->GetEntityID();

        size_t size_of_data = data.Size;
        size_t offset = 0;

        offset = FillData(buffer, offset, &entity_id, sizeof(unsigned long));            // Set id of entity
        offset = FillData(buffer, offset, &size_of_string, sizeof(unsigned int));        // Set size of name
        offset = FillData(buffer, offset, component_name.data(), component_name.size()); // Set name
        offset = FillData(buffer, offset, &size_of_data, sizeof(uint32_t));              // Set size of data
        offset = FillData(buffer, offset, data.Data, size_of_data);                      // Set data
        buffer.resize(offset);

        packet.SetContent(buffer);
        SendImportantPacket(packet);
    }

    /**
     * @brief Send delete entity
     *
     * @param entity (Type: Entity *) The entity to delete
     *
     * @return void
     */
    void Network::SendDeleteEntity(Entity *entity) {
        if (entity == nullptr) {
            EXODIA_CORE_ERROR("Network::SendDeleteEntity() - Entity is null !");
            return;
        }
        Exodia::Network::Packet packet(0x0e);
        std::vector<char> buffer(sizeof(unsigned long));
        unsigned long entity_id = (unsigned long)entity->GetEntityID();

        uint64_t offset = 0;
        offset = FillData(buffer, offset, &entity_id, sizeof(unsigned long));
        packet.SetContent(buffer);
        SendPacket(packet);
    }

    /**
     * @brief Send Acknowledgement
     *
     * @return void
     */
    void Network::SendAck(uint64_t command_id) {
        Exodia::Network::Packet packet(0x01);
        std::vector<char> buffer(sizeof(uint64_t));

        size_t offset = 0;
        offset = FillData(buffer, offset, &command_id, sizeof(uint64_t));
        packet.SetContent(buffer);
        SendPacket(packet);
    }

    void Network::SendAcceptConnect() {
        Exodia::Network::Packet packet(0x02);
        std::vector<char> buffer(0);

        packet.SetContent(buffer);
        SendPacket(packet);
    }

    /**
     * @brief Send an event
     *
     * @param event (Type: uint32_t) The event to send
     */
    void Network::SendEvent(uint32_t event, bool isPressed) {
        Exodia::Network::Packet packet(0x8b);
        std::vector<char> buffer(sizeof(uint32_t) + sizeof(bool));
        size_t offset = 0;

        offset = FillData(buffer, offset, &event, sizeof(uint32_t));
        offset = FillData(buffer, offset, &isPressed, sizeof(bool));
        packet.SetContent(buffer);
        SendPacket(packet);
    }

    void Network::SendRejectConnect()
    {
        Exodia::Network::Packet packet(0x03);
        std::vector<char> buffer(0);

        packet.SetContent(buffer);
        SendPacket(packet);
    }

    void Network::SendSystemLoad()
    {
        //TODO: Send system load
    }

    void Network::SendGameEvent()
    {
        //TODO: Send game event
    }

    void Network::SendDeleteComponent(Entity *entity, std::string component_name)
    {
        (void)entity;
        (void)component_name;
        //TODO: Send delete component
    }

    void Network::SendImportantEvent(uint32_t event, bool isPressed)
    {
        (void)event;
        (void)isPressed;
        //TODO: Send important event
    }

    void Network::SendDisconnect()
    {
        //TODO: Send disconnect
    }

    void Network::ResendNeedAck() {
        for (auto &connection : _packetNeedAck) {
            for (auto &packet : connection.second) {
                std::cout << "Resending packet " << std::endl;
                connection.first.SendPacket(_socket, packet.second);
            }
        }
    }
}; // namespace Exodia::Network
