/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Main
*/

#include <iostream>
#include <asio.hpp>

int main(int ac, char **av)
{
    (void)ac;
    (void)av;

    std::cout << "Asio World !" << std::endl;

    try {
        asio::io_context io_context;

        // Création du socket accepteur
        asio::ip::tcp::acceptor acceptor(io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 8080));

        std::cout << "Server started. Listening on port 8080...\n";

        while (true) {
            asio::ip::tcp::socket socket(io_context);

            // En attente et acceptation d'une nouvelle connexion
            acceptor.accept(socket);

            std::cout << "New connection established: " << socket.remote_endpoint() << std::endl;

            // Lecture et renvoi des données reçues
            char data[1024];
            size_t len = socket.read_some(asio::buffer(data, sizeof(data)));

            asio::write(socket, asio::buffer(data, len), asio::transfer_all());

            socket.shutdown(asio::ip::tcp::socket::shutdown_both);
        }
    } catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}
