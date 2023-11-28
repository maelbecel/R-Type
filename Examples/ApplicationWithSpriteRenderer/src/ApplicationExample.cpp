/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** ApplicationExample
*/

#include "Exodia/EntryPoint.hpp"
#include "DefaultLayer.hpp"

namespace Exodia {

    // -- Application ----------------------------------------------------------

    class ApplicationExample : public Application {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
        public:

            ApplicationExample(const ApplicationSpecification &spec) : Application(spec)
            {
                PushLayer(new DefaultLayer());
            }

            ~ApplicationExample() = default;
    };

    // -- Entry Point ----------------------------------------------------------

    Application *CreateApplication(ApplicationCommandLineArgs args)
    {
        EXODIA_PROFILE_FUNCTION();

        ApplicationSpecification spec;

        spec.Name = "Application Example";
        spec.CommandLineArgs = args;

        return new ApplicationExample(spec);
    }
};
