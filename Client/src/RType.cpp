/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** R-Type
*/

#include "Exodia/EntryPoint.hpp"
#include "Layer/RTypeLayer.hpp"
#include <iostream>

namespace Exodia {

    class RType : public Application {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
        public:

            RType(const ApplicationSpecification &spec) : Application(spec)
            {
                PushLayer(new RTypeLayer());
            }

            ~RType() = default;
    };

    /////////////////
    // Entry Point //
    /////////////////

    Application *CreateApplication(ApplicationCommandLineArgs args)
    {
        (void)args;
        Exodia::Network::IOContextManager ioContextManager;

        // Create a UDPSocket object for the server
        Exodia::Network::UDPSocket serverSocket(ioContextManager);

        // Define a local endpoint to listen on
        boost::asio::ip::udp::endpoint localEndpoint(boost::asio::ip::address::from_string("127.0.0.1"), 8081);

        // Bind the socket to the local endpoint
        serverSocket.getSocket().open(localEndpoint.protocol());
        serverSocket.getSocket().bind(localEndpoint);

        // Start receiving data asynchronously
        serverSocket.receive();

        // the other server is in the same machine but on port 8080
        boost::asio::ip::udp::endpoint remoteEndpoint(boost::asio::ip::address::from_string("127.0.0.1"), 8080);

        serverSocket.send("Hello World 9999", remoteEndpoint);
        // Run the IO context to initiate asynchronous operations
        ioContextManager.run();

        return 0;
    }
};
