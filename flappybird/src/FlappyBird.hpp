/*
** EPITECH PROJECT, 2023
** FlappyBird
** File description:
** FlappyBird
*/

#ifndef R_TYPE_HPP_
#define R_TYPE_HPP_

///////////////////////////////////////////////
// Main include file for FlappyBird              //
// Include this file to use the FlappyBird logic //
// And create your own FlappyBird game           //
///////////////////////////////////////////////

#include "Exodia.hpp"

#include "ECS/Component/Animation.hpp"
#include "ECS/Component/Clock.hpp"

#include "ECS/Scripts/Player.hpp"

#include "ECS/System/AnimationSystem.hpp"

#include "ECS/Event/AnimationEvent.hpp"

namespace FlappyBird {

    inline static void InitFlappyBird() {
        // -- Init the FlappyBird project ------------------------------------------
#ifdef _WIN32
        Ref<Exodia::Project> project = Exodia::Project::Load("./flappybird/src/FlappyBird.proj");
#else
        Ref<Exodia::Project> project = Exodia::Project::Load("./flappybird/src/FlappyBird.proj");
#endif

        // -- Register FlappyBird components ---------------------------------------

        project->RegisterComponent("Animation", [](Exodia::Buffer data) -> Exodia::IComponentContainer * {
            return new Exodia::ComponentContainer<FlappyBird::AnimationComponent>(data);
        });

        project->RegisterComponent("Clock", [](Exodia::Buffer data) -> Exodia::IComponentContainer * {
            return new Exodia::ComponentContainer<Exodia::Clock>(data);
        });

        // -- Register FlappyBird scripts ------------------------------------------

        project->RegisterScript("Player", []() -> Exodia::ScriptableEntity * { return new FlappyBird::Player(); });

        // -- Register FlappyBird systems ------------------------------------------
    }
}; // namespace FlappyBird

#endif /* !R_TYPE_HPP_ */
