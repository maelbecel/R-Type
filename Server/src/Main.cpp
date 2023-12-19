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

int main(int ac, char **av)
{
    (void)ac;
    (void)av;

    Exodia::Log::Init();

    std::cout << "Asio World !" << std::endl;

    try {
        // Server main
        Exodia::Network::IOContextManager ioContextManager;

        // Define a local endpoint to listen on
        asio::ip::udp::endpoint localEndpoint(asio::ip::address::from_string("127.0.0.1"), 8080);

        // Create a UDPSocket object for the server
        Exodia::Network::UDPSocket serverSocket(ioContextManager, localEndpoint);

        serverSocket.receive(my_callback);

        // Run the IO context to initiate asynchronous operations
        ioContextManager.run();

        return 0;

    } catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}
