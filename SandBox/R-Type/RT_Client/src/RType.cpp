/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** R-Type
*/

#include "Exodia/EntryPoint.hpp"
#include "Layer/RTypeLayer.hpp"
#include "R-Type.hpp"

namespace Exodia {

    class RTypeClient : public Application {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
      public:
        RTypeClient(const ApplicationSpecification &spec) : Application(spec) { PushLayer(new RType::RTypeLayer()); }

        ~RTypeClient() = default;
    };

    /////////////////
    // Entry Point //
    /////////////////

    Application *CreateApplication(ApplicationCommandLineArgs args) {
        EXODIA_PROFILE_FUNCTION();

        try {
            RType::InitRType();
        } catch (std::exception &error) {
            return nullptr;
        }

        ApplicationSpecification spec;

        spec.Name = "Application Example";
        spec.CommandLineArgs = args;

        return new RTypeClient(spec);
    }
}; // namespace Exodia
