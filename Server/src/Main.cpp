/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Main
*/

#include "R-Type.hpp"
#include "Server.hpp"

int main(void) {
    Exodia::Log::Init();
    Exodia::RendererAPI::SetAPI(Exodia::RendererAPI::API::None);

    try {
        RType::InitRType();
    } catch (std::exception &error) {
        EXODIA_ERROR("Exception :\n\t{0}", error.what());

        return 84;
    }

    try {
        Exodia::Server server(8082);

        server.Init();
        server.Run();
    } catch (std::exception &error) {
        EXODIA_ERROR("Exception :\n\t{0}", error.what());

        return 84;
    }
    return 0;
}
