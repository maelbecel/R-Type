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

#include "src/Scripts/Player/PlayerController.hpp"
#include "src/Scripts/Player/BulletPlayer.hpp"
#include "src/Scripts/Player/Player.hpp"
#include "src/Scripts/Player/Module.hpp"
#include "src/Scripts/Player/PowerUp.hpp"

#include "src/Scripts/Enemies/PataPata/Pata-pata.hpp"
#include "src/Scripts/Enemies/BulletEnemy.hpp"

#include "src/Scripts/Star/Star.hpp"
#include "src/Scripts/Tabrok/Tabrok.hpp"
#include "src/Scripts/Mid/Mid.hpp"
#include "src/Scripts/Bug/Bug.hpp"
#include "src/Scripts/Spawners/PataPataSpawner.hpp"

#include "src/System/AnimationSystem.hpp"

#include "src/Event/TakeDamage.hpp"

#include "src/Entity/CreateBackground.hpp"

namespace RType {

    inline static void InitRType(Ref<Exodia::Project> project = nullptr) {
        // -- Init the R-Type project ------------------------------------------
        if (!project) {
        #ifdef _WIN32
            project = Exodia::Project::Load("../Assets/R-Type.proj");
        #else
            project = Exodia::Project::Load("./Assets/R-Type.proj");
        #endif
        }

        // -- Register R-Type components ---------------------------------------

        project->RegisterComponent("Health", [](Exodia::Buffer data) -> Exodia::IComponentContainer * {
            return new Exodia::ComponentContainer<Exodia::Health>(data);
        });

        project->RegisterComponent("Animation", [](Exodia::Buffer data) -> Exodia::IComponentContainer * {
            return new Exodia::ComponentContainer<RType::AnimationComponent>(data);
        });

        project->RegisterComponent("Clock", [](Exodia::Buffer data) -> Exodia::IComponentContainer * {
            return new Exodia::ComponentContainer<Exodia::Clock>(data);
        });

        // -- Register R-Type scripts ------------------------------------------

        project->RegisterScript("PlayerController",
                                []() -> Exodia::ScriptableEntity * { return new RType::PlayerController(); });

        project->RegisterScript("Star", []() -> Exodia::ScriptableEntity * { return new RType::Star(); });

        project->RegisterScript("PataPata", []() -> Exodia::ScriptableEntity * { return new PataPata(); });

        project->RegisterScript("BulletPlayer",
                                []() -> Exodia::ScriptableEntity * { return new RType::BulletPlayer(); });

        project->RegisterScript("BulletEnemy", []() -> Exodia::ScriptableEntity * { return new RType::BulletEnemy(); });

        project->RegisterScript("Player", []() -> Exodia::ScriptableEntity * { return new RType::Player(); });

        project->RegisterScript("Tabrok", []() -> Exodia::ScriptableEntity * { return new RType::Tabrok(); });

        project->RegisterScript("Mid", []() -> Exodia::ScriptableEntity * { return new RType::Mid(); });

        project->RegisterScript("Bug", []() -> Exodia::ScriptableEntity * { return new RType::Bug(); });

        project->RegisterScript("Module", []() -> Exodia::ScriptableEntity * { return new RType::Module(); });

        project->RegisterScript("PowerUp", []() -> Exodia::ScriptableEntity * { return new RType::PowerUp(); });

        project->RegisterScript("PataPataSpawner",
                                []() -> Exodia::ScriptableEntity * { return new RType::PataPataSpawner(); });
        // -- Register R-Type systems ------------------------------------------

        project->RegisterSystem("AnimationSystem", []() -> Exodia::EntitySystem * { return new AnimationSystem(); });
    }
}; // namespace RType

#endif /* !R_TYPE_HPP_ */
