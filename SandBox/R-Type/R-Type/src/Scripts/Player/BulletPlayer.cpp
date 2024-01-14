/*
** EPITECH PROJECT, 2023
** $
** File description:
** BulletPlayer
*/

#include "BulletPlayer.hpp"
#include "Component/Animation.hpp"
#include "Component/Health.hpp"
#include "Event/TakeDamage.hpp"

using namespace Exodia;

namespace RType {

    /////////////
    // Methods //
    /////////////

    void BulletPlayer::UpdateAnimations() {
        AnimationComponent &anim = GetComponent<AnimationComponent>();

        if (anim.CurrentFrameIndex == anim.Frames.size() - 1) {
            anim.IsPlaying = false;

            RigidBody2DComponent &body = GetComponent<RigidBody2DComponent>();

            body.Velocity.x = _Speed;

            _NeedUpdate = false;
        }
    }

    void BulletPlayer::OnUpdate(UNUSED(Timestep ts)) {
        Scene *scene = HandleEntity.GetScene();

        if (!scene)
            return;
        GameObject camera = scene->GetPrimaryCamera();

        if (!camera)
            return;
        TransformComponent &cameraTC = camera.GetComponent<TransformComponent>();
        TransformComponent &tc = GetComponent<TransformComponent>();

        UpdateAnimations();

        if (_NeedUpdate) {
            ParentComponent &parent = GetComponent<ParentComponent>();
            RigidBody2DComponent &body = GetComponent<RigidBody2DComponent>();

            GameObject parentE = scene->GetEntityByUUID(parent.Parent);

            if (parentE) {
                TransformComponent &parentTC = parentE.GetComponent<TransformComponent>();

                tc.Translation.x = parentTC.Translation.x + 0.7f;
                tc.Translation.y = parentTC.Translation.y;
            }
        }

        // -- Bullet out of screen (Destroy it)
        if (tc.Translation.x > cameraTC.Translation.x + 10.0f)
            scene->DestroyEntity(HandleEntity);
    }

    void BulletPlayer::OnCollisionEnter(Entity *entity) {
        ComponentHandle<TagComponent> tag = entity->GetComponent<TagComponent>();

        if (!tag)
            return;
        auto &tagC = tag.Get();

        // -- If Obstacle is a player ignore collision
        if (tagC.Tag.rfind("Player", 0) == 0 || tagC.Tag.rfind("BP", 0) == 0 || tagC.Tag.rfind("Module", 0) == 0)
            return;

        // -- If Entity have a life component, remove life
        // TODO: ...
        if (entity->HasComponent<Health>()) {
            Scene *scene = HandleEntity.GetScene();

            if (!scene)
                return;
            scene->GetWorldPtr()->Emit<Events::TakeDamage>({entity, 1});
        }

        // -- Destroy bullet
        if (HandleEntity.GetScene())
            HandleEntity.GetScene()->DestroyEntity(HandleEntity.GetEntity());
    }
}; // namespace RType
