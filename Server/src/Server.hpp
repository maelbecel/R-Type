/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Server
*/

#ifndef SERVER_HPP
    #define SERVER_HPP

    #include <iostream>
    #include <boost/asio.hpp>
    #include <set>
    #include <memory>

using boost::asio::ip::tcp;

class Server {
    public:
        Server(boost::asio::io_context &io_context, short port);

        void start();

    private:
        void doAccept();

        void doRead(std::shared_ptr<tcp::socket> socket);

        void broadcast(const std::string& message, std::shared_ptr<tcp::socket> sender);

        tcp::acceptor acceptor_;
        std::set<std::shared_ptr<tcp::socket>> sockets_;
};

#endif /* SERVER_HPP */
