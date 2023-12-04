/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Server
*/

#include "Server.hpp"
#include <cstddef>
#include <iostream>
#include <memory>

Server::Server(boost::asio::io_context& io_context, short port)
    : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)) {}

void Server::start() {
    doAccept();
}

void Server::doAccept() {
    acceptor_.async_accept([this](boost::system::error_code ec, tcp::socket socket) {
        if (!ec) {
            std::string message = "Welcome to the server !\n";
            boost::asio::write(socket, boost::asio::buffer(message));
            auto newSocket = std::make_shared<tcp::socket>(std::move(socket));
            sockets_.insert(newSocket);
            std::cout << "New client connected" << std::endl;
            //write to client that he is connected
            boost::asio::write(*newSocket, boost::asio::buffer("Welcome to the server !\n"));
            doRead(newSocket);
        }
        doAccept();
    });
}

void Server::doRead(std::shared_ptr<tcp::socket> socket) {
    auto buffer = std::make_shared<boost::asio::streambuf>();

    boost::asio::async_read_until(*socket, *buffer, '\n',
        [this, socket, buffer](boost::system::error_code ec, std::size_t length) {
            std::cout << "Read " << length << " bytes" << std::endl;
            if (!ec) {
                std::cout << "Read: " << &buffer << std::endl;
                std::istream is(buffer.get());
                std::string message;
                std::getline(is, message);

                broadcast(message, socket);
                doRead(socket);
            } else {
                sockets_.erase(socket);
            }
        });
}

void Server::broadcast(const std::string& message, std::shared_ptr<tcp::socket> sender) {
    std::cout << "Broadcasting: " << message << std::endl;
    for (auto& socket : sockets_) {
        if (socket != sender) {
            std::cout << "Send to client: " << message << std::endl;
            boost::asio::write(*socket, boost::asio::buffer(message));
        }
    }
}