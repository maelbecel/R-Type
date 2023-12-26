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

    // -- R-Type Settings includes ---------------------------------------------

    #include "Settings/Config.hpp"

    // -- R-Type Components includes -------------------------------------------

    #include "Components/Animation.hpp"

    // -- R-Type Events includes -----------------------------------------------

    #include "Events/AnimationEvent.hpp"

    // -- R-Type Systems includes ----------------------------------------------

    #include "Systems/AnimationSystem.hpp"

namespace RType {

    inline static void EntryPoint()
    {
        // -- Init the R-Type Project ------------------------------------------
        Ref<Exodia::Project> project = Exodia::Project::Load("Assets/R-Type.proj");

        // -- Register R-Type Components ---------------------------------------
        project->RegisterComponent("AnimationComponent", [](Exodia::Buffer data) -> Exodia::IComponentContainer * {
            return new Exodia::ComponentContainer<AnimationComponent>(data);
        });

        // -- Register R-Type Scripts ------------------------------------------

        // -- Register R-Type Systems ------------------------------------------
    }
};

#endif /* !R_TYPE_HPP_ */
