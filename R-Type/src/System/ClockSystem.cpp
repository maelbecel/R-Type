/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** ClockSystem
*/

#include "ClockSystem.hpp"
#include "Component/Clock.hpp"

namespace RType {

    using namespace Exodia;

    /////////////
    // Methods //
    /////////////

    void ClockSystem::Update(World *world, Timestep ts) {

        world->LockMutex();
        world->ForEach<Clock>([&](Entity *entity, auto clock) {
            clock->ElapsedTime += ts;
        });
        world->UnlockMutex();
    }
}; // namespace RType