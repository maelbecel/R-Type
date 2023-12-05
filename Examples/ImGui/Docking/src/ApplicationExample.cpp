/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** ApplicationExample
*/

#include "Exodia/EntryPoint.hpp"
#include "DockerLayer.hpp"

namespace Exodia {

    // -- Application ----------------------------------------------------------

    class ApplicationExample : public Application {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
        public:

            ApplicationExample(const ApplicationSpecification &spec) : Application(spec)
            {
                PushLayer(new DockerLayer());
            }

            ~ApplicationExample() = default;
    };

    // -- Entry Point ----------------------------------------------------------

    Application *CreateApplication(ApplicationCommandLineArgs args)
    {
        EXODIA_PROFILE_FUNCTION();

        ApplicationSpecification spec;

        spec.Name = "Docking Space";
        spec.CommandLineArgs = args;

        return new ApplicationExample(spec);
    }
};
