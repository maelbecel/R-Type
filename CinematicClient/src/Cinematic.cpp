/*
** EPITECH PROJECT, 2023
** Cinemartic
** File description:
** Symetric
*/

#include "Exodia/EntryPoint.hpp"
#include "Layer/CinematicLayer.hpp"
#include "Cinematic.hpp"

namespace Exodia {

    class CinematicClient : public Application {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
      public:
        CinematicClient(const ApplicationSpecification &spec) : Application(spec) {
            PushLayer(new Cinematic::CinematicLayer());
        }

        ~CinematicClient() = default;
    };

    /////////////////
    // Entry Point //
    /////////////////

    Application *CreateApplication(ApplicationCommandLineArgs args) {
        EXODIA_PROFILE_FUNCTION();

        Cinematic::InitCinematic();

        ApplicationSpecification spec;

        spec.Name = "Cinematic";
        spec.CommandLineArgs = args;

        return new CinematicClient(spec);
    }
}; // namespace Exodia
