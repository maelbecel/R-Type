/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Main
*/

#include <iostream>
#include <asio.hpp>
#include "Exodia.hpp"

void my_callback(const std::string &message)
{
    (void)message;
    std::cout << "Message received: " << message << std::endl;
}

int main(void)
{
    Exodia::Log::Init();

    std::cout << "Client have been launched!" << std::endl;

    try {
        // Server main
                 // Server main
        Exodia::Network::IOContextManager ioContextManager;

        // Define a local endpoint to listen on
        asio::ip::udp::endpoint localEndpoint(asio::ip::address::from_string("127.0.0.1"), 8083);
        asio::ip::udp::endpoint serverEndpoint(asio::ip::address::from_string("127.0.0.1"), 8082);

        // Create a UDPSocket object for the server
        Exodia::Network::UDPSocket serverSocket(ioContextManager, localEndpoint);

        // serverSocket.receive(my_callback);
        Exodia::Network::Header header(1, 1, 2);
        Exodia::Network::Packet packet;

        std::cout << "Header" << header << std::endl;
        packet.SetHeader(header);

        std::vector<char> buffer(1468, 1);
        int packet_received = 8;
        int packet_sent = 12;
        std::memcpy(buffer.data(), &packet_received, sizeof(int));
        std::memcpy(buffer.data() + sizeof(int), &packet_sent, sizeof(int));

        packet.SetContent(buffer);

        serverSocket.Send(packet.GetBuffer(), 1468, serverEndpoint);
        // Run the IO context to initiate asynchronous operations
        ioContextManager.run();

        return 0;

    } catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}