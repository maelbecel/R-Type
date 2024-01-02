/*
** EPITECH PROJECT, 2023
** $
** File description:
** ClockSystem
*/

// R-Type includes
#include "ClockSystem.hpp"
#include "Components/Clock.hpp"

namespace RType {

    using namespace Exodia;

    /////////////
    // Methods //
    /////////////

    void ClockSystem::Update(Exodia::World *world, Exodia::Timestep ts)
    {
        world->ForEach<ClockComponent>([&](Entity *entity, ComponentHandle<ClockComponent> clock) {
            ClockComponent &cc = clock.Get(); // cc = Clock Component

            if (!cc.Active)
                return;

            cc.Time += ts;

            (void)entity;
        });
    }
};
