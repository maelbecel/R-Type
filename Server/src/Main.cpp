/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Main
*/

#include <iostream>
#include <boost/asio.hpp>
#include "Exodia.hpp"

int main(int ac, char **av)
{
    (void)ac;
    (void)av;

    std::cout << "Asio World !" << std::endl;

    try {
        // Server main
        Exodia::IOContextManager ioContextManager;

        // Create a UDPSocket object for the server
        Exodia::UDPSocket serverSocket(ioContextManager);

        // Define a local endpoint to listen on
        boost::asio::ip::udp::endpoint localEndpoint(boost::asio::ip::address::from_string("127.0.0.1"), 8080);

        // Bind the socket to the local endpoint
        serverSocket.open(localEndpoint);

        // Start receiving data asynchronously
        serverSocket.receive();

        // Run the IO context to initiate asynchronous operations
        ioContextManager.run();

        return 0;

    } catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}
