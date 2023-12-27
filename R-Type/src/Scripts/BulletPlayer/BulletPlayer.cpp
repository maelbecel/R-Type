/*
** EPITECH PROJECT, 2023
** $
** File description:
** BulletPlayer
*/

#include "BulletPlayer.hpp"

using namespace Exodia;

namespace RType {

    void BulletPlayer::OnCreate() {
        ComponentHandle<TransformComponent> transform = HandleEntity->GetComponent<TransformComponent>();
        ComponentHandle<ParentComponent> parent = HandleEntity->GetComponent<ParentComponent>();
        World *world = HandleEntity->GetWorld();

        if (!transform || !parent || !world)
            return;

        Entity *parent_entity = world->GetEntityByID(parent.Get().Parent);

        if (!parent_entity)
            return;

        ComponentHandle<TransformComponent> parent_transform = parent_entity->GetComponent<TransformComponent>();

        if (!parent_transform)
            return;

        TransformComponent &tc = parent_transform.Get();
        TransformComponent &bullet_tc = transform.Get();

        bullet_tc.Translation.x = tc.Translation.x + 0.7f;
        bullet_tc.Translation.y = tc.Translation.y - 0.05f;
        bullet_tc.Scale = {0.5f, 0.5f, 0.0f};

        HandleEntity->AddComponent<Animation>(0.0f, 2.0f, 1.0f);
        HandleEntity->AddComponent<BoxCollider2DComponent>();

        ComponentHandle<RigidBody2DComponent> body = HandleEntity->AddComponent<RigidBody2DComponent>();

        if (!body)
            return;

        RigidBody2DComponent &rbc = body.Get();
        rbc.Type = RigidBody2DComponent::BodyType::Dynamic;
        rbc.Mass = 0.0f;
        rbc.GravityScale = 0.0f;
        rbc.Velocity.x = 0.0f;
        rbc.Velocity.y = 0.0f;

        ComponentHandle<SpriteRendererComponent> sprite = HandleEntity->AddComponent<SpriteRendererComponent>();
        if (!sprite)
            return;
        sprite.Get().Texture =
            SubTexture2D::CreateFromCoords(18375012605620, {0.0f, 0.0f}, {17.33f, 14.0f}, {1.0f, 1.0f});

        _Speed = 25.0f;
        EXODIA_INFO("BulletPlayer created");
    }

    void BulletPlayer::OnUpdate(UNUSED(Timestep ts))  {
        ComponentHandle<TransformComponent> transform = GetComponent<TransformComponent>();
        ComponentHandle<Animation> animation = GetComponent<Animation>();
        ComponentHandle<ParentComponent> parent = GetComponent<ParentComponent>();
        World *world = HandleEntity->GetWorld();
        if (!transform || !animation || !parent || !world)
            return;

        Entity *entity = world->GetEntityByID(parent.Get().Parent);
        if (!entity) {
            EXODIA_WARN("BulletPlayer has no parent");
        }

        Entity *camera = world->GetEntityByTag("Camera");
        if (!camera)
            return;

        ComponentHandle<TransformComponent> camera_transform = camera->GetComponent<TransformComponent>();
        ComponentHandle<RigidBody2DComponent> velocity = GetComponent<RigidBody2DComponent>();
        if (!camera_transform || !velocity)
            return;

        EXODIA_TRACE("{0} {1}", animation.Get().CurrentFrame, animation.Get().MaxFrame);
        // When the shoot animation is finished, the bullet is moving
        if (animation.Get().CurrentFrame == animation.Get().MaxFrame) {
            velocity.Get().Velocity.x = _Speed;
        }

        // Remove bullet if out of screen
        if (transform.Get().Translation.x > camera_transform.Get().Translation.x + 10.0f) {
            EXODIA_INFO("Bullet {0} destroyed", HandleEntity->GetComponent<TagComponent>().Get().Tag);
            HandleEntity->GetWorld()->DestroyEntity(HandleEntity);
        }
    }
}; // namespace RType