/*
** EPITECH PROJECT, 2023
** $
** File description:
** SuperBullet
*/

#include "SuperBullet.hpp"
#include "Component/Animation.hpp"
#include "Component/Health.hpp"
#include "Event/TakeDamage.hpp"

using namespace Exodia;

namespace RType {

    /////////////
    // Methods //
    /////////////
    void SuperBullet::UpdateAnimations() {
        AnimationComponent &anim = GetComponent<AnimationComponent>();

        anim.IsPlaying = true;
        anim.Repeat = true;
    }

    void SuperBullet::OnUpdate(UNUSED(Timestep ts)) {
        Scene *scene = HandleEntity.GetScene();
        Health &health = GetComponent<Health>();
        if (!scene)
            return;

        if (health.CurrentHealth <= 0) {
            scene->DestroyEntity(HandleEntity);
            EXODIA_INFO("SuperBullet destroyed");
            return;
        }
        GameObject camera = scene->GetPrimaryCamera();

        if (!camera)
            return;

        TransformComponent &cameraTC = camera.GetComponent<TransformComponent>();
        TransformComponent &tc = GetComponent<TransformComponent>();

        UpdateAnimations();

        // -- Bullet out of screen (Destroy it)
        if (tc.Translation.x > cameraTC.Translation.x + 12.0f) {
            scene->DestroyEntity(HandleEntity);
            EXODIA_INFO("SuperBullet destroyed");
        }
    }

    void SuperBullet::OnCollisionEnter(Entity *entity) {
        ComponentHandle<TagComponent> tag = entity->GetComponent<TagComponent>();
        Health &health = GetComponent<Health>();

        if (!tag)
            return;
        auto &tagC = tag.Get();

        // -- If Obstacle is a player ignore collision
        if (tagC.Tag.rfind("Pata", 0) == 0) {
            if (entity->HasComponent<Health>()) {
                Scene *scene = HandleEntity.GetScene();

                if (!scene)
                    return;
                scene->GetWorldPtr()->Emit<Events::TakeDamage>({entity, 1});
            }
            EXODIA_INFO("Bullet health: {0}", health.CurrentHealth);
            // -- Destroy bullet
            health.CurrentHealth--;
        }
    }
}; // namespace RType