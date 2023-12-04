/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Main
*/

#include <iostream>
#include "Server.hpp"

int main(int ac, char **av)
{
    (void)ac;
    (void)av;

    std::cout << "Asio World !" << std::endl;

    try {
        boost::asio::io_context io_context;
        Server server(io_context, 4242);

        server.start();
        io_context.run();
    } catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}
