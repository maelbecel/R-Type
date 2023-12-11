/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** R-Type
*/

#include "Exodia/EntryPoint.hpp"
#include "Layer/EditorLayer.hpp"
#include <iostream>

namespace Exodia {

    class ExodiaApplication : public Application {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
        public:

            ExodiaApplication(const ApplicationSpecification &spec) : Application(spec)
            {
                PushLayer(new EditorLayer());
            }

            ~ExodiaApplication() = default;
    };

    /////////////////
    // Entry Point //
    /////////////////

    Application *CreateApplication(ApplicationCommandLineArgs args)
    {
        EXODIA_PROFILE_FUNCTION();

        ApplicationSpecification spec;

        spec.Name = "Exodia Editor";
        spec.CommandLineArgs = args;

        return new ExodiaApplication(spec);
    }
};
