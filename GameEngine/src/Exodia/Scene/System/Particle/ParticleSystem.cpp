/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ParticleSystem
*/

#include "ParticleSystem.hpp"
#include <glm/gtx/compatibility.hpp>

namespace Exodia {

    /////////////
    // Methods //
    /////////////

    void ParticleSystem::Update(World *world, Timestep ts)
    {
        world->ForEach<TransformComponent, RigidBody2DComponent, ParticleComponent, SpriteRendererComponent>([&](Entity *entity, auto transform, auto rigidBody, auto particle, auto sprite) {
            auto &tc = transform.Get();
            auto &rb = rigidBody.Get();            
            auto &pc = particle.Get();
            auto &sc = sprite.Get();

            if (pc.LifeRemaining <= 0.0f) {
                world->DestroyEntity(entity);

                return;
            }
            float life = pc.LifeRemaining / pc.LifeTime;
            float size = glm::lerp(pc.SizeEnd, pc.SizeBegin, life);
            glm::vec4 color = glm::lerp(pc.ColorEnd, pc.ColorBegin, life);

            pc.LifeRemaining -= ts;
            sc.Color.a        = color.a * life;
            tc.Rotation.z    += 0.01f * ts;
            tc.Scale          = glm::vec3(size);
        });
    }
};
