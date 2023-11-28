/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** R-Type
*/

#include "Exodia/EntryPoint.hpp"
#include "Layer/RTypeLayer.hpp"
#include <iostream>

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

        ApplicationSpecification spec;

        spec.Name = "R-Type";
        spec.CommandLineArgs = args;

        return new RType(spec);
    }
};
