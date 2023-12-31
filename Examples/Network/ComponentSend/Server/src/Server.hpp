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
        void HandleCommand(const std::string &command);
        void Init();
        void Run();
        void Update();
        void Stop() { _running = false; };

      public:
        inline static std::shared_ptr<Exodia::Scene> _World;

      private:
        // WARNING: This is a temporary solution
        Exodia::World *_worldNetwork = Exodia::World::CreateWorld();

        // Network is used to manage the network with the clients
        Network::IOContextManager _ioContextManager;
        Network::Network _network;

        // Timestep is used to manage the time
        Timer _Timer;
        float _lastTime;

        bool _running = true;

        std::thread _inputThread;
    };
} // namespace Exodia

#endif /* !SERVER_HPP_ */
