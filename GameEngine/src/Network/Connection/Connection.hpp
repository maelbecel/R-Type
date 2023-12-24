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
        Connection(asio::ip::udp::endpoint endpoint)
        {
            _endpoint = endpoint;
            _sendPacket = 0;
            _receivedPacket = 0;
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

        void SetSendPacket(int packet) {
            _sendPacket = packet;
        }

        void AddReceivedPacket() {
            _receivedPacket++;
        }

        void SetReceivedPacket(int packet) {
            _receivedPacket = packet;
        }

        int GetSendPacket() {
            return _sendPacket;
        }

        int GetReceivedPacket() {
            return _receivedPacket;
        }

        asio::ip::udp::endpoint GetEndpoint() const {
            return _endpoint;
        }

        bool operator==(const Connection &connection) const {
            return _endpoint == connection.GetEndpoint();
        }

        bool operator!=(const Connection &connection) const {
            return _endpoint != connection.GetEndpoint();
        }

        int GetLastId() const {
            return _lastId;
        }

        void SetLastId(int lastId) {
            _lastId = lastId;
        }
    protected:
    private:
        asio::ip::udp::endpoint _endpoint;
        int _lastId = -1;
        int _sendPacket;
        int _receivedPacket;

};

#endif /* !CONNECTION_HPP_ */
