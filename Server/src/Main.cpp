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

#ifdef _WIN32
    Exodia::Project::Load("../Client/R-Type.proj");
#else
    Exodia::Project::Load("./Client/R-Type.proj");
#endif

    Exodia::RendererAPI::SetGraphical(false);

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
