/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** UDPSocket
*/

#ifndef UDP_SOCKET_HPP
    #define UDP_SOCKET_HPP

#include <iostream>
#include <boost/asio.hpp>
#include "Network/IOContextManager/IOContextManager.hpp"

namespace Exodia {

#define MTU 1468

#define ERROR "\033[1;31m[ERROR]\033[0m "
#define SUCCESS "\033[1;32m[SUCCESS]\033[0m "
#define WARNING "\033[1;33m[WARNING]\033[0m "   
#define INFO "\033[1;34m[INFO]\033[0m "
#define DEBUG "\033[1;35m[DEBUG]\033[0m "

class UDPSocket {
    public:

        /**
         * @brief Construct a new UDPSocket object
         * 
         * @param ioContextManager 
         */
        UDPSocket(IOContextManager& ioContextManager)
            : socket_(ioContextManager.getIOContext()), senderEndpoint_() {
            // Construct the UDP socket using the provided IOContextManager
            socket_ = boost::asio::ip::udp::socket(ioContextManager.getIOContext());
        }

        /**
         * @brief Destroy the UDPSocket object
         * 
         */
        ~UDPSocket() {
            socket_.close();
        }

        /**
         * @brief Send data asynchronously
         * 
         * @param message 
         * @param endpoint 
         */
        void send(const std::string& message, const boost::asio::ip::udp::endpoint& endpoint) {
            socket_.async_send_to(boost::asio::buffer(message), endpoint,
                [](const boost::system::error_code& error, std::size_t /*bytes_sent*/) {
                    if (!error) {
                        std::cout << SUCCESS << "Message sent successfully" << std::endl;
                    } else {
                        std::cerr << ERROR << "Error sending message: " << error.message() << std::endl;
                    }
                });
        }

        /**
         * @brief Receive data asynchronously
         * 
         */
        void receive() {
            socket_.async_receive_from(boost::asio::buffer(receiveBuffer_), senderEndpoint_,
                [this](const boost::system::error_code& error, std::size_t bytes_received) {
                    if (!error) {
                        std::string receivedMessage(receiveBuffer_.begin(), receiveBuffer_.begin() + bytes_received);
                        std::cout << INFO << "Received message: " << receivedMessage << std::endl;
                        // Continue receiving more data
                        receive();
                    } else {
                        std::cerr << ERROR << "Error receiving message: " << error.message() << std::endl;
                    }
                });
        }

        /**
         * @brief Get the Sender Endpoint object
         * 
         * @return boost::asio::ip::udp::endpoint 
         */
        boost::asio::ip::udp::endpoint getSenderEndpoint() const {
            return senderEndpoint_;
        }

        /**
         * @brief Get the Socket object
         * 
         * @return boost::asio::ip::udp::socket& 
         */
        boost::asio::ip::udp::socket& getSocket() {
            return socket_;
        }

    private:
        boost::asio::ip::udp::socket socket_;
        boost::asio::ip::udp::endpoint senderEndpoint_;
        std::array<char, MTU> receiveBuffer_;
    };

}; // namespace Exodia

#endif // UDP_SOCKET_HPP
