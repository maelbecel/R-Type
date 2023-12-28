/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** R-Type
*/

#ifndef R_TYPE_HPP_
    #define R_TYPE_HPP_

    ///////////////////////////////////////////////
    // Main include file for R-Type              //
    // Include this file to use the R-Type logic //
    // And create your own R-Type game           //
    ///////////////////////////////////////////////

    // -- Game Engine includes -------------------------------------------------

    #include "Exodia.hpp"

    // -- R-Type Components includes -------------------------------------------

    #include "Components/Animation.hpp"
    #include "Components/Fade.hpp"

    // -- R-Type Events includes -----------------------------------------------

    #include "Events/AnimationEvent.hpp"
    #include "Events/FadeEvent.hpp"
    #include "Events/PlayerEvents.hpp"

    // -- R-Type Systems includes ----------------------------------------------

    #include "Systems/AnimationSystem.hpp"
    #include "Systems/FadeSystem.hpp"

    // -- R-Type Scripts includes ----------------------------------------------

    #include "Scripts/Mars.hpp"

namespace RType {

    inline static void EntryPoint()
    {
        // -- Init the R-Type Project ------------------------------------------
        Ref<Exodia::Project> project = Exodia::Project::Load("Assets/R-Type.proj");

        // -- Register R-Type Components ---------------------------------------
        project->RegisterComponent("AnimationComponent", [](Exodia::Buffer data) -> Exodia::IComponentContainer * {
            return new Exodia::ComponentContainer<AnimationComponent>(data);
        });
        project->RegisterComponent("FadeComponent", [](Exodia::Buffer data) -> Exodia::IComponentContainer * {
            return new Exodia::ComponentContainer<FadeComponent>(data);
        });

        // -- Register R-Type Scripts ------------------------------------------
        project->RegisterScript("Mars", []() -> Exodia::ScriptableEntity * {
            return new Mars();
        });

        // -- Register R-Type Systems ------------------------------------------
    }
};

#endif /* !R_TYPE_HPP_ */
