/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** R-Type
*/

#include "Exodia/EntryPoint.hpp"
#include "Layer/RTypeLayer.hpp"
#include <iostream>


void my_callback(const std::string &message)
{
    (void)message;
    std::cout << "Message received: " << message << std::endl;
}

namespace Exodia {

    class RType : public Application {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
        public:

            RType(const ApplicationSpecification &spec) : Application(spec)
            {
                PushLayer(new RTypeLayer());
            }

            ~RType() = default;
    };

    /////////////////
    // Entry Point //
    /////////////////

    Application *CreateApplication(ApplicationCommandLineArgs args)
    {
        EXODIA_PROFILE_FUNCTION();

        Exodia::Network::IOContextManager ioContextManager;
        Exodia::World *world = Exodia::World::CreateWorld();
        Exodia::Network::Network network(world, ioContextManager, 8083);
    
        network.connect("0.0.0.0", 8082);
        
        Exodia::Entity *entity = world->CreateEntity();
        entity->AddComponent<Exodia::TransformComponent>();
        entity->GetComponent<Exodia::TransformComponent>()->Translation = glm::vec3(1, 2, 3);
        entity->GetComponent<Exodia::TransformComponent>()->Rotation = glm::vec3(4, 5, 6);

        while (true)
        {
            std::cout << "Sending entity" << std::endl;
            network.sendEntity(entity, "TransformComponent");
            sleep(10);
        }

        ApplicationSpecification spec;

        spec.Name = "Application Example";
        spec.CommandLineArgs = args;

        return new RType(spec);
    }
};
