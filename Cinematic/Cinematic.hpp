/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** R-Type
*/

#ifndef CINEMATIC_HPP_
#define CINEMATIC_HPP_

#include "Exodia.hpp"
#include "Scripts/Train.hpp"
#include "Scripts/FollowingCamera.hpp"
#include "Components/Animation.hpp"
#include "System/AnimationSystem.hpp"

namespace Cinematic {

    inline static void InitCinematic() {
        // -- Init the Cinematic project ------------------------------------------
#ifdef _WIN32
        Ref<Exodia::Project> project = Exodia::Project::Load("../CinematicClient/Cinematic.proj");
#else
        Ref<Exodia::Project> project = Exodia::Project::Load("./CinematicClient/Cinematic.proj");
#endif

        project->RegisterComponent("Animation", [](Exodia::Buffer data) -> Exodia::IComponentContainer * {
            return new Exodia::ComponentContainer<Cinematic::AnimationComponent>(data);
        });

        project->RegisterScript("Train", []() -> Exodia::ScriptableEntity * { return new Cinematic::Train(); });
        project->RegisterScript("FollowingCamera",
                                []() -> Exodia::ScriptableEntity * { return new Cinematic::FollowingCamera(); });
    }
}; // namespace Cinematic

#endif /* !CINEMATIC_HPP_ */