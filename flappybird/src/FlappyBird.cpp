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
        FlappyBirdClient(const ApplicationSpecification &spec) : Application(spec) { PushLayer(new GameLayer()); }

        ~FlappyBirdClient() = default;
    };
}; // namespace FlappyBird

/////////////////
// Entry Point //
/////////////////

namespace Exodia {
    /**
     * The function creates and returns a new instance of the FlappyBirdClient application with the
     * given command line arguments.
     *
     * @param args The "args" parameter is of type "ApplicationCommandLineArgs" and it represents the
     * command line arguments passed to the application. These arguments can be used to configure or
     * customize the behavior of the application at runtime.
     *
     * @return a pointer to a new instance of the FlappyBirdClient class, which is derived from the
     * Application class.
     */
    Application *CreateApplication(ApplicationCommandLineArgs args) {
        EXODIA_PROFILE_FUNCTION();

        ApplicationSpecification spec;

        spec.Name = "FlappyBird";
        spec.CommandLineArgs = args;

        return new FlappyBird::FlappyBirdClient(spec);
    }
}; // namespace Exodia
