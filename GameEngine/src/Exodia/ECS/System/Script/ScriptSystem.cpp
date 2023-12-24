/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** ScriptSystem
*/

// Exodia ECS System includes
#include "ScriptSystem.hpp"

// Exodia Debug includes
#include "Debug/Profiling.hpp"
#include "Debug/Logs.hpp"

namespace Exodia {

    /////////////
    // Methods //
    /////////////

    void ScriptSystem::Update(World *world, Timestep ts) {
        EXODIA_PROFILE_FUNCTION();

        world->ForEach<ScriptComponent>([&](UNUSED(Entity * entity), UNUSED(auto script)) {
            auto &sc = script.Get();

            if (!sc.Instance) {
                sc.Instance = sc.InstantiateScript();
                sc.Instance->HandleEntity = entity;
                sc.Instance->OnCreate();
            }

            sc.Instance->OnUpdate(ts);
        });
    }
}; // namespace Exodia
