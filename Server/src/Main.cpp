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

int main(int ac, char **av)
{
    (void)ac;
    (void)av;

    Exodia::Log::Init();

    Exodia::Project::Load("./Client/R-Type.proj");

    std::cout << "Server is waiting for infos !" << std::endl;

    try {
        Exodia::Server server(8082);
        server.Init();
        server.Run();
        return 0;

    } catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}
