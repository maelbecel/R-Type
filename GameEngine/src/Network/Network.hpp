/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** Network
*/

#ifndef NETWORK_HPP_
    #define NETWORK_HPP_

    #include "IOContextManager/IOContextManager.hpp"
    #include "UDPSocket/UDPSocket.hpp"
    #include "Header/Header.hpp"
    #include <vector>

namespace Exodia {

    namespace Network {

        class Network {
            public:

                /**
                 * @brief Construct a new Network object
                 *
                 */
                Network(IOContextManager &context,short port) : _socket(context, asio::ip::udp::endpoint(asio::ip::address::from_string("0.0.0.0"), port)) {};

                /**
                 * @brief Destroy the Network object
                 *
                 */
                ~Network() = default;

                /**
                 * @brief Connect to a remote endpoint
                 *
                 */
                void connect(const std::string &ip, short port) {
                    _remote_endpoint.push_back(asio::ip::udp::endpoint(asio::ip::address::from_string(ip), port));
                }

                /**
                 * @brief Run the network
                 *
                 */
                void loop() {
                    _ioContextManager.run();
                    _socket.receive(std::bind(&Network::splitter, this, std::placeholders::_1, std::placeholders::_2));
                }

                void splitter(const std::vector<char> message, size_t size) {
                    std::cout << "Size: " << size << std::endl;
                    for (size_t i = 0; i < size; i++)
                        std::cout << int(message.data()[i]) << std::endl;
                    Header header = Header::fillHeader(message.data());
                    std::cout << "Command: " << int(header.getCommand()) << " Timestamp: " << header.getTimestamp() << " Id: " << header.getId() << " Size: " << header.getSize() << std::endl;
                }

            private:

            private:
                UDPSocket _socket;
                IOContextManager _ioContextManager;
                std::vector<asio::ip::udp::endpoint> _remote_endpoint;

        }; // class Network

    }; // namespace Network

}; // namespace Exodia
#endif /* !NETWORK_HPP_ */
