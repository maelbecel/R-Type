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
};

class Connection {
  public:
    Connection(asio::ip::udp::endpoint endpoint) { _endpoint = endpoint; };

    Connection(asio::ip::udp::endpoint endpoint, uint64_t worldId) {
        _endpoint = endpoint;
        _worldId = worldId;
    };

    Connection() = default;
    ~Connection() = default;

    void SendPacket(Exodia::Network::UDPSocket &socket, Exodia::Network::Packet &packet) {
        packet.GetHeader()->setSize((unsigned long)packet.GetContent().size());
        packet.GetHeader()->SetId(_id);
        std::cout << "Send packet id: " << _id << " to " << _endpoint << std::endl;
        for (int i = 0; i < 2; i++)
            socket.Send(packet, _endpoint);
        _id++;
        _networkInfo.kiloByteSent += packet.GetBuffer().size() / 1024.0f;
        _networkInfo.sendPacket++;
    }

    NetworkInfo GetLastNetworkInfo() { return _lastNetworkInfo; }
    void SetSendPacket(int packet) {
        _lastNetworkInfo.sendPacket = _networkInfo.sendPacket;
        _networkInfo.sendPacket = packet;
    }

    void AddReceivedPacket() { _networkInfo.receivedPacket++; }

    void AddKyloByteReceived(Exodia::Network::Packet packet) {
        _networkInfo.kiloByteReceived += packet.GetBuffer().size() / 1024.0f;
    }

    void SetReceivedPacket(int packet) {
        _lastNetworkInfo.receivedPacket = _networkInfo.receivedPacket;
        _networkInfo.receivedPacket = packet;
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
};

#endif /* !CONNECTION_HPP_ */
