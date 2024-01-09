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
            EXODIA_INFO("ClockSystem: ElapsedTime: {0} from entity {1}", clock->ElapsedTime, entity->GetComponent<TagComponent>().Get().Tag);
        });
        world->UnlockMutex();
    }
}; // namespace RType