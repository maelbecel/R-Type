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

#include "Exodia.hpp"

#include "src/Component/Animation.hpp"
#include "src/Component/Clock.hpp"
#include "src/Component/Health.hpp"

#include "src/Scripts/BulletPlayer/BulletPlayer.hpp"
#include "src/Scripts/BulletEnnemy/BulletEnnemy.hpp"
#include "src/Scripts/Player/Player.hpp"
#include "src/Scripts/Pata-pata/Pata-pata.hpp"

#include "src/System/AnimationSystem.hpp"

#include "src/Event/EntityEventSubscriber.hpp"

#include "src/Entity/CreateBackground.hpp"
#include "src/Entity/CreateStars.hpp"

namespace RType {

    inline static void InitRType() {
        // -- Init the R-Type project ------------------------------------------
#ifdef _WIN32
        Ref<Exodia::Project> project = Exodia::Project::Load("../Client/R-Type.proj");
#else
        Ref<Exodia::Project> project = Exodia::Project::Load("./Client/R-Type.proj");
#endif

        // -- Register R-Type components ---------------------------------------

        project->RegisterComponent("Health", [](Exodia::Buffer data) -> Exodia::IComponentContainer * {
            return new Exodia::ComponentContainer<Exodia::Health>(data);
        });

        project->RegisterComponent("Animation", [](Exodia::Buffer data) -> Exodia::IComponentContainer * {
            return new Exodia::ComponentContainer<Exodia::Animation>(data);
        });

        project->RegisterComponent("Clock", [](Exodia::Buffer data) -> Exodia::IComponentContainer * {
            return new Exodia::ComponentContainer<Exodia::Clock>(data);
        });

        // -- Register R-Type scripts ------------------------------------------

        project->RegisterScript("Star", []() -> Exodia::ScriptableEntity * { return new RType::Star(); });

        project->RegisterScript("PataPata", []() -> Exodia::ScriptableEntity * { return new PataPata(); });

        project->RegisterScript("BulletPlayer",
                                []() -> Exodia::ScriptableEntity * { return new RType::BulletPlayer(); });

        project->RegisterScript("BulletEnnemy",
                                []() -> Exodia::ScriptableEntity * { return new RType::BulletEnnemy(); });

        project->RegisterScript("Player", []() -> Exodia::ScriptableEntity * { return new RType::Player(); });
    }
}; // namespace RType

#endif /* !R_TYPE_HPP_ */
