/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** R-Type
*/

#include "Exodia/EntryPoint.hpp"
#include "Layer/GameLayer.hpp"
#include "R-Type.hpp"

namespace RType {

    class RTypeApplication : public Exodia::Application {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
      public:
        RTypeApplication(const Exodia::ApplicationSpecification &spec) : Application(spec) {
            Ref<Exodia::Layer> gameLayer = GameLayer::New();

            PushLayer(gameLayer.get());
        }

        ~RTypeApplication() = default;
    };
}; // namespace RType

/////////////////
// Entry Point //
/////////////////

Exodia::Application *Exodia::CreateApplication(ApplicationCommandLineArgs args) {
    Exodia::ApplicationSpecification spec;

    spec.Name = "R-Type";
    spec.CommandLineArgs = args;

    return new RType::RTypeApplication(spec);
}
