/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** Server
*/

#include "Server.hpp"
#include "R-Type.hpp"

namespace Exodia {

    Server::Server(short port): _network(_world, _ioContextManager, port)
    {
        std::cout << "Server is launching !" << std::endl;

        _inputThread = std::thread([&] {
            while (this->_running) {
                if (std::cin.peek() != EOF) {
                    std::string inputCommand;
                    std::getline(std::cin, inputCommand);
                    HandleCommand(inputCommand);
                }
            }
        });
    }

    Server::~Server()
    {
        std::cout << "Server is closing !" << std::endl;
        _inputThread.join();
    }

    void Server::HandleCommand(const std::string &command)
    {
        std::cout << "Command received: " << command << std::endl;
        if (command == "stop") {
            this->_running = false;
            this->Stop();
        }
        if (command == "update") {
            this->Update();
        }
        if (command == "dump") {
            std::cout << "Clients: " << std::endl;
            if (_network.getRemoteEndpoint().empty())
                std::cout << "No client connected" << std::endl;
            else
                for (auto &client : _network.getRemoteEndpoint()) {
                    std::cout << client.address().to_string() << ":" << client.port() << std::endl;
                }
            std::cout << "Entities: " << std::endl;
            auto entities = _world->AllEntities();
            std::size_t i = 0;
            for (auto entity : entities) {
                (void)entity;
                i++;
            }
            std::cout << "Total: " << i << std::endl;
        }
    }

    void Server::Init()
    {
        std::cout << "Server is initializing !" << std::endl;
        try {
            // Register the systems
            _world->RegisterSystem(new AnimationSystem());      // Animation system
            _world->RegisterSystem(new ScriptSystem());         // Script system
            _world->RegisterSystem(new MovingSystem(1.5f));     // Moving system

            CollisionSystem *collisionSystem = new CollisionSystem();
            _world->RegisterSystem(collisionSystem);
            _world->Subscribe<Events::OnCollisionEntered>(collisionSystem);

            // Create the entities
            CreatePlayer(_world);
            CreatePataPata(_world);
            CreateBackground(_world);
            CreateStars(_world);

        } catch (std::exception &e) {
            std::cerr << "Exception: " << e.what() << std::endl;
        }
        std::cout << "Server is initialized !" << std::endl;
    }

    void Server::Run()
    {
        std::cout << "Server is running !" << std::endl;
        try {
            while(_running) {
                //this->Update();
                sleep(1);
            }
        } catch (std::exception &e) {
            std::cerr << "Exception: " << e.what() << std::endl;
        }
        std::cout << "Server is stopped !" << std::endl;
    }

    void Server::Update()
    {
        float time = _Timer.Elapsed();

        Timestep timestep(time - _lastTime);

        _lastTime = time;

        this->_world->Update(timestep);
    }


}; // namespace Exodia