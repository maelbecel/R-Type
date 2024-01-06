/*
** EPITECH PROJECT, 2023
** FlappyBird
** File description:
** FlappyBird
*/

#include "Exodia/EntryPoint.hpp"
#include "Layer/GameLayer.hpp"

namespace Exodia {

    class FlappyBirdClient : public Application {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
      public:
        FlappyBirdClient(const ApplicationSpecification &spec) : Application(spec) {
            PushLayer(new FlappyBird::GameLayer());
        }

        ~FlappyBirdClient() = default;
    };

    /////////////////
    // Entry Point //
    /////////////////

    Application *CreateApplication(ApplicationCommandLineArgs args) {
        EXODIA_PROFILE_FUNCTION();

        // FlappyBird::InitFlappyBird();

        ApplicationSpecification spec;

        spec.Name = "FlappyBird";
        spec.CommandLineArgs = args;

        return new FlappyBirdClient(spec);
    }
}; // namespace Exodia
