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
    #include <vector>

namespace Exodia {

    namespace Network {

        class Network {
            public:

                /**
                 * @brief Construct a new Network object
                 *
                 */
                Network(short port) : _socket(_ioContextManager, asio::ip::udp::endpoint(asio::ip::address::from_string("0.0.0.0"), port)) {};

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
                }

            private:
                UDPSocket _socket;
                IOContextManager _ioContextManager;
                std::vector<asio::ip::udp::endpoint> _remote_endpoint;

        }; // class Network

    }; // namespace Network

}; // namespace Exodia
#endif /* !NETWORK_HPP_ */
