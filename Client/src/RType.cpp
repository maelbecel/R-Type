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

#ifdef _WIN32
        Project::Load("../Client/R-Type.proj");
#else
        Project::Load("Client/R-Type.proj");
#endif

        ApplicationSpecification spec;

        spec.Name = "Application Example";
        spec.CommandLineArgs = args;

        return new RType(spec);
    }
};
