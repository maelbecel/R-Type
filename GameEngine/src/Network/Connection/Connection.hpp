/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** Connection
*/

#ifndef CONNECTION_HPP_
#define CONNECTION_HPP_

#include "Network/Packet/Packet.hpp"

class Connection {
    public:
        Connection(asio::ip::udp::endpoint endpoint)
        {
            _endpoint = endpoint;
            _sendPacket = 0;
            _receivedPacket = 0;
        };

        Connection() = default;

        ~Connection()
        {
        };


        void SendPacket(Exodia::Network::UDPSocket &socket, Exodia::Network::Packet &packet) {
            std::cout << "Send packet to " << _endpoint.address().to_string() << ":" << _endpoint.port() << std::endl;
            std::cout << "Header: command: " << int(packet.GetHeader().getCommand()) << " id: " << packet.GetHeader().getId() << " size: " << packet.GetHeader().getSize() << std::endl;
            Exodia::Network::Header header = packet.GetHeader();
            header.SetId(_sendPacket);
            header.setSize(packet.GetSize());
            socket.send(packet.GetBuffer(), packet.GetSize(), _endpoint);
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
    protected:
    private:
        asio::ip::udp::endpoint _endpoint;
        int _sendPacket;
        int _receivedPacket;

};

#endif /* !CONNECTION_HPP_ */
