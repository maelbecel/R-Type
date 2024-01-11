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
    void Network::SendPacket(std::shared_ptr<Packet> packet) {
        if (_networkType == NetworkType::SERVER) {
            for (auto &connection : _connections)
                connection.second->SendPacket(_socket, packet);
        } else {
            _server_connection->SendPacket(_socket, packet);
        }
    }

    /**
     * @brief Send an important packet wheter we are the server or the client so it will be resend if not ack
     *
     * @param packet (Type: Packet) The packet to send
     *
     * @return void
     */

    /**
     * @brief send a packet to request connection to the server
     *
     * @param ip (Type: const std::string &) The ip of the server
     * @param port (Type: short) The port of the server
     * @return void
     */
    void Network::SendAskConnect(const std::string &ip, short port) {
        connect(ip, port);
        std::shared_ptr<Exodia::Network::Packet> packet = std::make_shared<Exodia::Network::Packet>(CONNECT, true);
        Buffer buffer(0);

        packet->SetContent(buffer);
        _server_connection->SendPacket(_socket, packet);
    }

    /**
     * @brief Send number of packet received and sent
     *
     * @return void
     */
    void Network::SendPacketInfo() {
        std::shared_ptr<Exodia::Network::Packet> packet = std::make_shared<Exodia::Network::Packet>(PACKET_INFO, false);
        Buffer buffer(2 * sizeof(int));

        if (_networkType == NetworkType::SERVER) {
            for (auto &connection : _connections) {
                int32_t received = connection.second->GetReceivedPacket();
                int32_t sent = connection.second->GetSendPacket();

                buffer.Write(&received, sizeof(int));
                buffer.Write(&sent, sizeof(int));
                packet->SetContent(buffer);
                connection.second->SetReceivedPacket(0);
                connection.second->SetSendPacket(0);
                connection.second->SendPacket(_socket, packet);
            }
        } else {
            int32_t received = _server_connection->GetReceivedPacket();
            int32_t sent = _server_connection->GetSendPacket();

            buffer.Write(&received, sizeof(int));
            buffer.Write(&sent, sizeof(int));
            packet->SetContent(buffer);
            _server_connection->SetReceivedPacket(0);
            _server_connection->SetSendPacket(0);
            _server_connection->SendPacket(_socket, packet);
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
    void Network::SendComponentOf(bool isImportant, Entity *entity, std::string component_name) {
        std::shared_ptr<Exodia::Network::Packet> packet =
            std::make_shared<Exodia::Network::Packet>(COMPONENT_OF, isImportant);
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

        packet->SetContent(buffer);
        SendPacket(packet);
        if (component_name == "BoxCollider2DComponent" || component_name == "ScriptComponent" ||
            component_name == "ParentComponent") {
            //     EXODIA_CORE_WARN("=============================================== {0}", component_name);
            SendPacket(packet);
        }
    }

    /**
     * @brief Send delete entity
     *
     * @param entity (Type: Entity *) The entity to delete
     *
     * @return void
     */
    void Network::SendDeleteEntity(bool isImportant, Entity *entity) {
        if (entity == nullptr) {
            EXODIA_CORE_ERROR("Network::() - Entity is null !");
            return;
        }
        std::shared_ptr<Exodia::Network::Packet> packet =
            std::make_shared<Exodia::Network::Packet>(DELETE_ENTITY, isImportant);
        Buffer buffer(sizeof(unsigned long));
        unsigned long entity_id = (unsigned long)entity->GetEntityID();

        buffer.Write(&entity_id, sizeof(unsigned long));
        packet->SetContent(buffer);
        SendPacket(packet);
    }

    /**
     * @brief Send Acknowledgement
     *
     * @return void
     */
    void Network::SendAck(uint64_t command_id) {
        std::shared_ptr<Exodia::Network::Packet> packet = std::make_shared<Exodia::Network::Packet>(ACK);
        Buffer buffer(sizeof(uint64_t));

        buffer.Write(&command_id, sizeof(uint64_t));
        packet->SetContent(buffer);
        SendPacket(packet);
    }

    void Network::SendAcceptConnect() {
        std::shared_ptr<Exodia::Network::Packet> packet = std::make_shared<Exodia::Network::Packet>(CONNECT_ACCEPT);
        Buffer buffer(0);

        packet->SetContent(buffer);
        SendPacket(packet);
    }

    /**
     * @brief Send an event
     *
     * @param event (Type: uint32_t) The event to send
     */
    void Network::SendEvent(bool isImportant, uint32_t event, bool isPressed) {
        std::shared_ptr<Exodia::Network::Packet> packet = std::make_shared<Exodia::Network::Packet>(EVENT, isImportant);
        Buffer buffer(sizeof(uint32_t) + sizeof(bool));

        buffer.Write(&event, sizeof(uint32_t));
        buffer.Write(&isPressed, sizeof(bool));
        packet->SetContent(buffer);
        SendPacket(packet);
    }

    void Network::SendRejectConnect() {
        std::shared_ptr<Exodia::Network::Packet> packet = std::make_shared<Exodia::Network::Packet>(CONNECT_REJECT);
        Buffer buffer(0);

        packet->SetContent(buffer);
        SendPacket(packet);
    }

    void Network::SendSystemLoad(bool isImportant) {
        (void)isImportant;
        // TODO: Send system load
    }

    void Network::SendGameEvent(bool isImportant) {
        (void)isImportant;
        // TODO: Send game event
    }

    void Network::SendDeleteComponent(bool isImportant, Entity *entity, std::string component_name) {
        std::shared_ptr<Exodia::Network::Packet> packet =
            std::make_shared<Exodia::Network::Packet>(DELETE_COMPONENT, isImportant);
        Buffer buffer(1468, 0);

        if (entity == nullptr) {
            EXODIA_CORE_ERROR("Network::SendDeleteComponentOf() - Entity is null !");
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

        packet->SetContent(buffer);
        SendPacket(packet);
    }

    void Network::SendDisconnect() {
        std::shared_ptr<Exodia::Network::Packet> packet = std::make_shared<Exodia::Network::Packet>(DISCONNECT);
        Buffer buffer(0);

        packet->SetContent(buffer);
        SendPacket(packet);
    }

    void Network::ResendNeedAck() {
        if (_networkType == NetworkType::SERVER) {
            for (auto &connection : _connections)
                connection.second->ResendNeedAck(_socket);
        } else
            _server_connection->ResendNeedAck(_socket);
    }
}; // namespace Exodia::Network
