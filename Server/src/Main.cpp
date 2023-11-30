/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Main
*/

#include <iostream>
#include <boost/asio.hpp>

int main(int ac, char **av)
{
    (void)ac;
    (void)av;

    std::cout << "Asio World !" << std::endl;

    try {
        boost::asio::io_context io_context;

        // Création du socket accepteur
        boost::asio::ip::tcp::acceptor acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 8080));

        std::cout << "Server started. Listening on port 8080...\n";

        while (true) {
            boost::asio::ip::tcp::socket socket(io_context);

            // En attente et acceptation d'une nouvelle connexion
            acceptor.accept(socket);

            std::cout << "New connection established: " << socket.remote_endpoint() << std::endl;

            // Lecture et renvoi des données reçues
            char data[1024];
            size_t len = socket.read_some(boost::asio::buffer(data, sizeof(data)));

            boost::asio::write(socket, boost::asio::buffer(data, len), boost::asio::transfer_all());

            socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
        }
    } catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}
