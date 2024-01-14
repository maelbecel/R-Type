/*
** EPITECH PROJECT, 2023
** $
** File description:
** Player
*/

#ifndef PATASPAWNER_HPP_
#define PATASPAWNER_HPP_

// Exodia includes
#include "Component/Animation.hpp"
#include "Component/Clock.hpp"
#include "Component/Health.hpp"
#include "Scripts/Enemies/BulletEnemy.hpp"

#include <cmath>
#include <random>

using namespace Exodia;

namespace RType {

    class PataPataSpawner : public ScriptableEntity {

        /////////////
        // Methods //
        /////////////
      public:
        void OnCreate() override {}
        void OnUpdate(UNUSED(Timestep ts)) override {
            uint32_t nbPataPata = 0;
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

                    if (sc.Name.rfind("PataPata", 0) == 0)
                        nbPataPata++;
                },
                false);

            timer += ts;

            if (nbPataPata < 5 && timer > 0.5f) {
                scene->LoadPrefabs((Project::GetActiveAssetDirectory() / "Prefabs/Mobs/Pata-Pata.prefab").string(),
                                   true);

                timer = 0.0f;
                EXODIA_TRACE("Pata-Pata spawned");
            }
        }
    };
}; // namespace RType

#endif /* !PATASPAWNER_HPP_ */
