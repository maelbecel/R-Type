/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** Server
*/

#ifndef SERVER_HPP_
    #define SERVER_HPP_

    #include "Exodia.hpp"

namespace Exodia {

    class Server {
        public:
            Server(short port);
            ~Server();
            void Init();
            void Run();
            void Update();
            void Stop() { _running = false; };

        protected:
        private:
            // World is used to manage the entities
            World *_world = World::CreateWorld();

            // Network is used to manage the network with the clients
            Network::IOContextManager _ioContextManager;
            Network::Network _network;

            // Timestep is used to manage the time
            Timer _Timer; 
            float _lastTime;

            bool _running = true;
    };
}

#endif /* !SERVER_HPP_ */
