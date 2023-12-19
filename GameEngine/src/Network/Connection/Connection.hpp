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
            _send_packet = 0;
            _received_packet = 0;
        };

        Connection() = default;

        ~Connection()
        {
        };


        void sendPacket(Exodia::Network::UDPSocket &socket, Exodia::Network::Packet &packet) {
            std::cout << "Send packet to " << _endpoint.address().to_string() << ":" << _endpoint.port() << std::endl;
            std::cout << "Header: command: " << int(packet.GetHeader().getCommand()) << " id: " << packet.GetHeader().getId() << " size: " << packet.GetHeader().getSize() << std::endl;
            Exodia::Network::Header header = packet.GetHeader();
            header.SetId(_send_packet);
            header.setSize(packet.GetSize());
            socket.send(packet.GetBuffer(), packet.GetSize(), _endpoint);
            _send_packet++;
        }

        void setSendPacket(int packet) {
            _send_packet = packet;
        }

        void AddReceivedPacket() {
            _received_packet++;
        }

        void setReceivedPacket(int packet) {
            _received_packet = packet;
        }

        int getSendPacket() {
            return _send_packet;
        }

        int getReceivedPacket() {
            return _received_packet;
        }

        asio::ip::udp::endpoint getEndpoint() const {
            return _endpoint;
        }

        bool operator==(const Connection &connection) const {
            return _endpoint == connection.getEndpoint();
        }

        bool operator!=(const Connection &connection) const {
            return _endpoint != connection.getEndpoint();
        }
    protected:
    private:
        asio::ip::udp::endpoint _endpoint;
        int _send_packet;
        int _received_packet;

};

#endif /* !CONNECTION_HPP_ */
