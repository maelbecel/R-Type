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
     * @brief Send packet wheter we are the server or the client
     *
     * @param packet (Type: Packet) The packet to send
     *
     * @return void
     */
    void Network::SendPacket(Packet packet) {
        if (_connections.size() > 0) {
            for (auto &connection : _connections)
                connection.second.SendPacket(_socket, packet);
        } else
            _server_connection.SendPacket(_socket, packet);
    }

    /**
     * @brief Send an important packet wheter we are the server or the client so it will be resend if not ack
     *
     * @param packet (Type: Packet) The packet to send
     *
     * @return void
     */
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
        Buffer buffer(0);

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
        Buffer buffer(2 * sizeof(int));

        if (_connections.size() > 0) {
            for (auto &connection : _connections) {
                int32_t received = connection.second.GetReceivedPacket();
                int32_t sent = connection.second.GetSendPacket();

                buffer.Write(&received, sizeof(int));
                buffer.Write(&sent, sizeof(int));
                packet.SetContent(buffer);
                connection.second.SetReceivedPacket(0);
                connection.second.SetSendPacket(0);
                connection.second.SendPacket(_socket, packet);
            }
        } else {
            int32_t received = _server_connection.GetReceivedPacket();
            int32_t sent = _server_connection.GetSendPacket();

            buffer.Write(&received, sizeof(int));
            buffer.Write(&sent, sizeof(int));
            packet.SetContent(buffer);
            _server_connection.SetReceivedPacket(0);
            _server_connection.SetSendPacket(0);
            _server_connection.SendPacket(_socket, packet);
        }
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
        Buffer buffer(1468, 0);

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

        buffer.Write(&entity_id, sizeof(unsigned long));            // Set id of entity
        buffer.Write(&size_of_string, sizeof(unsigned int));        // Set size of name
        buffer.Write(component_name.data(), component_name.size()); // Set name
        buffer.Write(&size_of_data, sizeof(uint32_t));              // Set size of data
        buffer.Write(data.Data, size_of_data);                      // Set data
        buffer.Resize(buffer.Offset);

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
        Buffer buffer(sizeof(unsigned long));
        unsigned long entity_id = (unsigned long)entity->GetEntityID();

        buffer.Write(&entity_id, sizeof(unsigned long));
        packet.SetContent(buffer);
        SendImportantPacket(packet);
    }

    /**
     * @brief Send Acknowledgement
     *
     * @return void
     */
    void Network::SendAck(uint64_t command_id) {
        Exodia::Network::Packet packet(0x01);
        Buffer buffer(sizeof(uint64_t));

        buffer.Write(&command_id, sizeof(uint64_t));
        packet.SetContent(buffer);
        SendPacket(packet);
    }

    void Network::SendAcceptConnect() {
        Exodia::Network::Packet packet(0x02);
        Buffer buffer(0);

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
        Buffer buffer(sizeof(uint32_t) + sizeof(bool));

        buffer.Write(&event, sizeof(uint32_t));
        buffer.Write(&isPressed, sizeof(bool));
        packet.SetContent(buffer);
        SendPacket(packet);
    }

    void Network::SendRejectConnect() {
        Exodia::Network::Packet packet(0x03);
        Buffer buffer(0);

        packet.SetContent(buffer);
        SendPacket(packet);
    }

    void Network::SendSystemLoad() {
        // TODO: Send system load
    }

    void Network::SendGameEvent() {
        // TODO: Send game event
    }

    void Network::SendDeleteComponent(Entity *entity, std::string component_name) {
        Exodia::Network::Packet packet(0x0f);
        Buffer buffer(1468, 0);

        if (entity == nullptr) {
            EXODIA_CORE_ERROR("Network::SendComponentOf() - Entity is null !");
            return;
        }
        std::function<Exodia::IComponentContainer *(Exodia::Buffer)> func =
            Project::GetActive()->GetComponentFactory(component_name);
        if (!func) {
            std::string error = "Network::ReceiveComponentOF() - component " + component_name + " not found !";
            EXODIA_CORE_ERROR(error);
            return;
        }
        unsigned long size_of_string = (unsigned long)component_name.size();
        unsigned long entity_id = (unsigned long)entity->GetEntityID();

        buffer.Write(&entity_id, sizeof(unsigned long));            // Set id of entity
        buffer.Write(&size_of_string, sizeof(unsigned int));        // Set size of name
        buffer.Write(component_name.data(), component_name.size()); // Set name
        buffer.Resize(buffer.Offset);

        packet.SetContent(buffer);
        SendImportantPacket(packet);
    }

    void Network::SendImportantEvent(uint32_t event, bool isPressed) {
        Exodia::Network::Packet packet(0x8b);
        Buffer buffer(sizeof(uint32_t) + sizeof(bool));

        buffer.Write(&event, sizeof(uint32_t));
        buffer.Write(&isPressed, sizeof(bool));
        packet.SetContent(buffer);
        SendImportantPacket(packet);
    }

    void Network::SendDisconnect() {
        Exodia::Network::Packet packet(0x82);
        Buffer buffer(0);

        packet.SetContent(buffer);
        SendPacket(packet);
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
