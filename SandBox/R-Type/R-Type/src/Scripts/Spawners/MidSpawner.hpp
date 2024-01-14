/*
** EPITECH PROJECT, 2023
** $
** File description:
** Player
*/

#ifndef MIDSPAWNER_HPP_
#define MIDSPAWNER_HPP_

// Exodia includes
#include "Component/Animation.hpp"
#include "Component/Clock.hpp"
#include "Component/Health.hpp"
#include "Scripts/Enemies/BulletEnemy.hpp"

#include <cmath>
#include <random>

using namespace Exodia;

namespace RType {

    class MidSpawner : public ScriptableEntity {

        /////////////
        // Methods //
        /////////////
      public:
        void OnCreate() override {}
        void OnUpdate(UNUSED(Timestep ts)) override {
            uint32_t nbMid = 0;
            Scene *scene = HandleEntity.GetScene();
            static float timer = 0.0f;

            if (!scene) {
                EXODIA_ERROR("Scene is null");
                return;
            }

            scene->GetWorldPtr()->ForEach<ScriptComponent>(
                [&](Entity *entity, ComponentHandle<ScriptComponent> script) {
                    (void)entity;

                    auto &sc = script.Get();

                    if (sc.Name.rfind("Mid", 0) == 0)
                        nbMid++;
                },
                false);

            timer += ts;

            if (nbMid < 5 && timer > 0.5f) {
                scene->LoadPrefabs((Project::GetActiveAssetDirectory() / "Prefabs/Mobs/Mid.prefab").string(), true);

                timer = 0.0f;
                EXODIA_TRACE("Mid spawned");
            }
        }
    };
}; // namespace RType

#endif /* !MIDSPAWNER_HPP_ */
