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
#include "User/User.hpp"
#include <optional>

namespace Exodia {

    class Server {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
      public:
        Server(short port);
        ~Server();

        /////////////
        // Methods //
        /////////////
      public:
        void HandleCommand(const std::string &command);
        void Init();
        void Run();
        void Update();
        void Stop();

      private:
        void InitScene(SceneType scene, std::optional<std::vector<Exodia::EntitySystem *>> systems);
        void InitScenes();
        void InitEntities();
        void WaitForClient();
        void HandleEvent(std::pair<std::pair<uint32_t, bool>, asio::ip::udp::endpoint> event);
        bool IsClientNew(std::pair<const std::string, std::shared_ptr<Connection>> connection);
        void SendComponents(SceneType scene);

        ////////////////
        // Attributes //
        ////////////////
      public:
        inline static std::map<SceneType, Ref<Scene>> Scenes;
        inline static SceneType CurrentScene = SceneType::GAME;
        uint64_t count = 0;

      private:
        // TODO: WARNING: This is a temporary solution
        World *_WorldNetwork;

        // Network is used to manage the network with the clients
        Network::IOContextManager _IOContextManager;
        Network::Network _Network;

        // Timestep is used to manage the time
        Timer _Timer;
        float _LastTime;
        float my_Timer;

        bool _Running;

        std::thread _InputThread;

        void CheckForNewClients();
        void CheckConnectedClients();
        std::vector<Exodia::User> _Users;
    };
}; // namespace Exodia

#endif /* !SERVER_HPP_ */
