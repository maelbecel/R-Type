/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** Connection
*/

#ifndef CONNECTION_HPP_
#define CONNECTION_HPP_

#include "Network/Packet/Packet.hpp"
#include "Network/Network.hpp"

struct NetworkInfo {
    int32_t receivedPacket = 0;
    int32_t sendPacket = 0;
    int32_t receivePacketLost = 0;
    int32_t sendPacketLost = 0;
    uint16_t ping = 0;
    float kiloByteSent = 0;
    float kiloByteReceived = 0;
    std::shared_ptr<Exodia::Network::Packet> lastPacketSent = std::make_shared<Exodia::Network::Packet>();
    std::shared_ptr<Exodia::Network::Packet> lastPacketReceived = std::make_shared<Exodia::Network::Packet>();
};

class Connection {
  public:
    Connection(asio::ip::udp::endpoint endpoint) { _endpoint = endpoint; };

    Connection(asio::ip::udp::endpoint endpoint, uint64_t worldId) {
        _endpoint = endpoint;
        _worldId = worldId;
    };

    Connection() = default;
    ~Connection() {
        _packetNeedAck.clear();
        std::cout << "Connection destroyed in destructor" << std::endl;
    };

    void ResendNeedAck(Exodia::Network::UDPSocket &socket) {
        std::vector<std::shared_ptr<Exodia::Network::Packet>> packetsDuplicate;
        for (auto packet : _packetNeedAck) {
            packetsDuplicate.push_back(std::make_shared<Exodia::Network::Packet>(*packet.second));
        }
        for (auto packet : packetsDuplicate) {
            SendPacketAck(socket, packet);
        }
    }

    void RemovePacketNeedAck(uint64_t id) {
        try {
            _packetNeedAck.erase(id);
        } catch (std::exception &e) {
            EXODIA_CORE_ERROR("Error: {0}", e.what());
        }
    }

    std::unordered_map<uint64_t, std::shared_ptr<Exodia::Network::Packet>> &GetPacketNeedAck() {
        return _packetNeedAck;
    }

    void SendPacket(Exodia::Network::UDPSocket &socket, std::shared_ptr<Exodia::Network::Packet> packet) {
        packet->GetHeader().setSize((unsigned long)packet->GetContent().size());
        packet->GetHeader().SetId(_id);
        EXODIA_CORE_TRACE("Send packet id: {0}", _id);
        std::cout << "Send packet header: " << packet->GetHeader() << std::endl;
        std::cout << packet->GetBuffer().size() << std::endl;
        socket.Send(packet, _endpoint);
        if (packet->GetHeader().GetIsImportant()) {
            _packetNeedAck[packet->GetHeader().GetId()] = std::make_shared<Exodia::Network::Packet>(packet);
        }
        _id++;
        _networkInfo.kiloByteSent += packet->GetBuffer().size() / 1024.0f;
        _networkInfo.sendPacket++;
        _networkInfo.lastPacketSent = std::make_shared<Exodia::Network::Packet>(*packet);
    }

    void SendPacketAck(Exodia::Network::UDPSocket &socket, std::shared_ptr<Exodia::Network::Packet> packet) {
        packet->GetHeader().setSize((unsigned long)packet->GetContent().size());
        EXODIA_CORE_TRACE("ReSend packet id: {0}", _id);
        std::cout << "Send ack packet header: " << packet->GetHeader() << std::endl;

        std::vector<char> buffer = packet->GetBuffer();
        socket.Send(buffer, buffer.size(), _endpoint);
        _id++;
        _networkInfo.kiloByteSent += packet->GetBuffer().size() / 1024.0f;
        _networkInfo.sendPacket++;
        _networkInfo.lastPacketSent = std::make_shared<Exodia::Network::Packet>(*packet);
    }

    NetworkInfo GetLastNetworkInfo() { return _lastNetworkInfo; }
    void SetSendPacket(int packet) {
        _lastNetworkInfo.sendPacket = _networkInfo.sendPacket;
        _networkInfo.sendPacket = packet;
    }

    void AddReceivedPacket() { _networkInfo.receivedPacket++; }

    void AddKyloByteReceived(std::shared_ptr<Exodia::Network::Packet> packet) {
        _networkInfo.kiloByteReceived += packet->GetBuffer().size() / 1024.0f;
    }

    void SetReceivedPacket(int packet) {
        _lastNetworkInfo.receivedPacket = _networkInfo.receivedPacket;
        _networkInfo.receivedPacket = packet;
    }

    void SetLastPacketSent(std::shared_ptr<Exodia::Network::Packet> packet) { _networkInfo.lastPacketSent = packet; }

    void SetLastPacketReceived(std::shared_ptr<Exodia::Network::Packet> packet) {
        _networkInfo.lastPacketReceived = std::make_shared<Exodia::Network::Packet>(*packet);
    }

    void SetWorldId(uint64_t worldId) { _worldId = worldId; }

    void SetPacketLoss(uint32_t receivedPacketLost, uint32_t sendPacketLost) {
        _lastNetworkInfo.receivePacketLost = _networkInfo.receivePacketLost;
        _lastNetworkInfo.sendPacketLost = _networkInfo.sendPacketLost;
        _networkInfo.receivePacketLost = receivedPacketLost;
        _networkInfo.sendPacketLost = sendPacketLost;
    }

    int GetSendPacket() { return _networkInfo.sendPacket; }

    int GetReceivedPacket() { return _networkInfo.receivedPacket; }

    std::shared_ptr<Exodia::Network::Packet> GetLastPacketReceived() { return _networkInfo.lastPacketReceived; }

    std::shared_ptr<Exodia::Network::Packet> GetLastPacketSent() { return _networkInfo.lastPacketSent; }

    float GetKiloByteSent() { return _networkInfo.kiloByteSent; }

    float GetKiloByteReceived() { return _networkInfo.kiloByteReceived; }

    void SetKiloByteSent(float kiloByteSent) {
        _lastNetworkInfo.kiloByteSent = _networkInfo.kiloByteSent;
        _networkInfo.kiloByteSent = kiloByteSent;
    }

    void SetKiloByteReceived(float kiloByteReceived) {
        _lastNetworkInfo.kiloByteReceived = _networkInfo.kiloByteReceived;
        _networkInfo.kiloByteReceived = kiloByteReceived;
    }

    void SetPing(uint16_t ping) {
        _lastNetworkInfo.ping = _networkInfo.ping;
        _networkInfo.ping = ping;
    }

    NetworkInfo GetNetworkInfo() { return _networkInfo; }

    int GetLastId() const { return _lastId; }

    uint64_t GetWorldId() const { return _worldId; }

    asio::ip::udp::endpoint GetEndpoint() const { return _endpoint; }

    bool operator==(const Connection &connection) const { return _endpoint == connection.GetEndpoint(); }

    bool operator!=(const Connection &connection) const { return _endpoint != connection.GetEndpoint(); }

    void SetLastId(int lastId) { _lastId = lastId; }

  protected:
  private:
    asio::ip::udp::endpoint _endpoint;
    int _lastId = -1;
    int _id = 0;
    NetworkInfo _networkInfo;
    NetworkInfo _lastNetworkInfo;
    uint64_t _worldId = 0;
    std::unordered_map<uint64_t, std::shared_ptr<Exodia::Network::Packet>> _packetNeedAck;
};

#endif /* !CONNECTION_HPP_ */
