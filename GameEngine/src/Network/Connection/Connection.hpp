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

    Connection() = default;

    ~Connection(){};

    void SendPacket(Exodia::Network::UDPSocket &socket, Exodia::Network::Packet &packet) {
        packet.GetHeader()->SetId(_sendPacket);
        for (int i = 0; i < 2; i++)
            socket.send(packet, _endpoint);
        _sendPacket++;
    }

    void SetSendPacket(int packet) { _sendPacket = packet; }

    void AddReceivedPacket() { _receivedPacket++; }

    void SetReceivedPacket(int packet) { _receivedPacket = packet; }

    int GetSendPacket() { return _sendPacket; }

    int GetReceivedPacket() { return _receivedPacket; }

    asio::ip::udp::endpoint GetEndpoint() const { return _endpoint; }

    bool operator==(const Connection &connection) const { return _endpoint == connection.GetEndpoint(); }

    bool operator!=(const Connection &connection) const { return _endpoint != connection.GetEndpoint(); }

  protected:
  private:
    asio::ip::udp::endpoint _endpoint;
    int _sendPacket;
    int _receivedPacket;
};

#endif /* !CONNECTION_HPP_ */
