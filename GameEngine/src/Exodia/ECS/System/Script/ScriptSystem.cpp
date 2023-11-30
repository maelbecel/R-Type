/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** ScriptSystem
*/

#include "ScriptSystem.hpp"

namespace Exodia {

    /////////////
    // Methods //
    /////////////

    void ScriptSystem::Update(World *world, Timestep ts)
    {
        world->ForEach<ScriptComponent>([&](Entity *entity, ComponentHandle<ScriptComponent> script) {
            auto &sc = script.Get();
        
            if (!sc.Instance) {
                sc.Instance = sc.InstantiateScript();
                sc.Instance->HandleEntity = *entity;
                sc.Instance->OnCreate();
            }

            sc.Instance->OnUpdate(ts);
        });
    }
};
