/*
** EPITECH PROJECT, 2023
** FlappyBird
** File description:
** FlappyBird
*/

// Exodia Entry Point
#include "Exodia/EntryPoint.hpp"

// Game Layer
#include "Layer/GameLayer.hpp"

using namespace Exodia;

namespace FlappyBird {

    class FlappyBirdClient : public Application {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
      public:

            FlappyBirdClient(const ApplicationSpecification &spec) : Application(spec)
            {
                PushLayer(new GameLayer());
            }

            ~FlappyBirdClient() = default;
    };
}; // namespace FlappyBird

/////////////////
// Entry Point //
/////////////////

namespace Exodia {
    Application *CreateApplication(ApplicationCommandLineArgs args) {
        EXODIA_PROFILE_FUNCTION();

        ApplicationSpecification spec;

        spec.Name = "FlappyBird";
        spec.CommandLineArgs = args;

        return new FlappyBird::FlappyBirdClient(spec);
    }
}; // namespace Exodia
