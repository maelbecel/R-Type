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

class Connection {
  public:
    Connection(asio::ip::udp::endpoint endpoint) {
        _endpoint = endpoint;
        _sendPacket = 0;
        _receivedPacket = 0;
    };

    Connection(asio::ip::udp::endpoint endpoint, uint64_t worldId) {
        _endpoint = endpoint;
        _sendPacket = 0;
        _receivedPacket = 0;
        _worldId = worldId;
    };

    Connection() = default;
    ~Connection() = default;

    void SendPacket(Exodia::Network::UDPSocket &socket, Exodia::Network::Packet &packet) {
        packet.GetHeader()->setSize((unsigned long)packet.GetContent().size());
        packet.GetHeader()->SetId(_sendPacket);
        std::cout << "Sending packet to " << _endpoint << std::endl;
        for (int i = 0; i < 2; i++)
            socket.Send(packet, _endpoint);
        _sendPacket++;
    }

    void SetSendPacket(int packet) { _sendPacket = packet; }

    void AddReceivedPacket() { _receivedPacket++; }

    void SetReceivedPacket(int packet) { _receivedPacket = packet; }

    void SetWorldId(uint64_t worldId) { _worldId = worldId; }

    int GetSendPacket() { return _sendPacket; }

    int GetReceivedPacket() { return _receivedPacket; }

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
    int _sendPacket;
    int _receivedPacket;
    uint64_t _worldId = 0;
};

#endif /* !CONNECTION_HPP_ */
