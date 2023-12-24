/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** Server
*/

#ifndef SERVER_HPP_
    #define SERVER_HPP_

    #include "Exodia.hpp"
    #include "SceneType.hpp"

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
            void RegisterComponent(std::string name, std::function<IComponentContainer *(Buffer)> factory);

        protected:

        public:
            inline static std::map<SceneType, std::shared_ptr<Exodia::Scene>> _World;
            inline static SceneType _currentScene;

        private:
            // WARNING: This is a temporary solution
            Exodia::World *_worldNetwork = Exodia::World::CreateWorld();
            std::unordered_map<std::string, std::function<IComponentContainer *(Buffer)>> _ComponentFactory;

            // Network is used to manage the network with the clients
            Network::IOContextManager _ioContextManager;
            Network::Network _network;

            // Timestep is used to manage the time
            Timer _Timer;
            float _lastTime;

            bool _running = true;

            std::thread _inputThread;
    };
}

#endif /* !SERVER_HPP_ */
