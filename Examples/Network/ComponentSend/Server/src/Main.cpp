/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Main
*/

#include <iostream>
#include <asio.hpp>
#include "Exodia.hpp"
#include "Server.hpp"

int main(void) {
    Exodia::Log::Init();

    Exodia::Project::Load("./Client/R-Type.proj");

    Exodia::RendererAPI::SetAPI(Exodia::RendererAPI::API::None);

    std::cout << "Server is waiting for infos !" << std::endl;

    try {
        Exodia::Server server(7070);

        server.Init();
        server.Run();

        return 0;
    } catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    // Exodia::Log::Init();

    // std::cout << "Server is waiting for infos !" << std::endl;

    // try {
    //     // Server main
    //     Exodia::Network::IOContextManager ioContextManager;

    //     // Define a local endpoint to listen on
    //     // asio::ip::udp::endpoint localEndpoint(asio::ip::address::from_string("127.0.0.1"), 8082);
    //     Exodia::Network::Network network(ioContextManager, 8082);
    //     network.loop();

    //     // Create a UDPSocket object for the server
    //     // Exodia::Network::UDPSocket serverSocket(ioContextManager, localEndpoint);

    //     // serverSocket.receive(my_callback);

    //     // Run the IO context to initiate asynchronous operations
    //     ioContextManager.run();

    //     return 0;

    // } catch (std::exception &e) {
    //     std::cerr << "Exception: " << e.what() << std::endl;
    // }
}
