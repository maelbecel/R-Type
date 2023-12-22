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

    #include "src/Scripts/BulletPlayer.hpp"
    #include "src/Scripts/Player/Player.hpp"
    #include "src/Scripts/Pata-pata.hpp"

    #include "src/System/AnimationSystem.hpp"

    #include "src/Event/EntityEventSubscriber.hpp"

    #include "src/Entity/CreatePataPata.hpp"
    #include "src/Entity/CreatePlayer.hpp"
    #include "src/Entity/CreateBackground.hpp"
    #include "src/Entity/CreateStars.hpp"

namespace RType {

    inline static void InitRType()
    {
#ifdef _WIN32
        Ref<Exodia::Project> project = Exodia::Project::Load("../Client/R-Type.proj");
#else
        Ref<Exodia::Project> project = Exodia::Project::Load("./Client/R-Type.proj");
#endif
        project->RegisterComponent("Health", [](Exodia::Buffer data) -> Exodia::IComponentContainer * {
            return new Exodia::ComponentContainer<Exodia::Health>(data);
        });

        project->RegisterComponent("Animation", [](Exodia::Buffer data) -> Exodia::IComponentContainer * {
            return new Exodia::ComponentContainer<Exodia::Animation>(data);
        });

        project->RegisterComponent("Clock", [](Exodia::Buffer data) -> Exodia::IComponentContainer * {
            return new Exodia::ComponentContainer<Exodia::Clock>(data);
        });

        // TODO: Register Scripts
    }
};

#endif /* !R_TYPE_HPP_ */
