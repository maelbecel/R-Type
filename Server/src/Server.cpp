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
    }

    Server::~Server()
    {
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
                std::cout << "In server loop" << std::endl;
                auto entities = _world->AllEntities();
                for (auto entity : entities) {
                    std::cout << entity->GetEntityID() << std::endl;
                }
                this->Update();
                sleep(10);
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

        this->_world->(timestep);
    }


}; // namespace Exodia