/*
** EPITECH PROJECT, 2023
** $
** File description:
** BulletPlayer
*/

#include "BulletPlayer.hpp"

using namespace Exodia;

namespace RType {

    void BulletPlayer::CreateAnimations() {
        AnimationComponent anim;

        std::vector<Ref<SubTexture2D>> framesIdle;

        for (int i = 0; i < 3; i++)
            framesIdle.push_back(SubTexture2D::CreateFromCoords(BULLET, {i, 0.0f}, {17.33f, 14.0f}, {1.0f, 1.0f}));

        anim.Frames = framesIdle;
        anim.IsPlaying = false;
        anim.Repeat = false;
        anim.FrameRate = TimeBetweenAnimations;

        _Animations.push_back(anim);
    }

    void BulletPlayer::OnCreate() {
        ComponentHandle<TransformComponent> transform = HandleEntity->GetComponent<TransformComponent>();
        ComponentHandle<ParentComponent> parent = HandleEntity->GetComponent<ParentComponent>();
        World *world = HandleEntity->GetWorld();

        if (!transform || !parent || !world)
            return;

        Entity *parent_entity = world->GetEntityByID(parent.Get().Parent);
        TransformComponent &bullet_tc = transform.Get();

        if (parent_entity) {
            ComponentHandle<TransformComponent> parent_transform = parent_entity->GetComponent<TransformComponent>();

            if (parent_transform) {
                TransformComponent &tc = parent_transform.Get();

                bullet_tc.Translation.x = tc.Translation.x + 0.7f;
                bullet_tc.Translation.y = tc.Translation.y - 0.05f;
            }
        }

        bullet_tc.Scale = {0.5f, 0.5f, 0.0f};

        HandleEntity->AddComponent<BoxCollider2DComponent>();

        ComponentHandle<RigidBody2DComponent> body = HandleEntity->AddComponent<RigidBody2DComponent>();

        if (!body) {
            RigidBody2DComponent &rbc = body.Get();

            rbc.Type = RigidBody2DComponent::BodyType::Dynamic;
            rbc.Mass = 0.0f;
            rbc.GravityScale = 0.0f;
            rbc.Velocity.x = 0.0f;
            rbc.Velocity.y = 0.0f;
        }

        CreateAnimations();

        HandleEntity->GetWorld()->Emit<Exodia::Events::OnEntityCreated>({HandleEntity});
    }

    void BulletPlayer::UpdateAnimations() {
        if (_Animations.size() == 0)
            return;

        ComponentHandle<SpriteRendererComponent> sprite = GetComponent<SpriteRendererComponent>();
        ComponentHandle<AnimationComponent> anim = GetComponent<AnimationComponent>();

        if (!sprite)
            sprite = HandleEntity->AddComponent<SpriteRendererComponent>();

        if (!anim) {
            _Animations[0].IsPlaying = true;

            anim = HandleEntity->AddComponent<AnimationComponent>(_Animations[0]);

            sprite.Get().Texture = anim.Get().Frames[0];
        } else {
            if (_Animations[0].IsPlaying && anim.Get().CurrentFrameIndex == anim.Get().Frames.size() - 1) {
                _Animations[0].IsPlaying = false;
                anim.Get() = _Animations[0];

                ComponentHandle<RigidBody2DComponent> body = GetComponent<RigidBody2DComponent>();
                if (!body)
                    return;

                body.Get().Velocity.x = _Speed;
                _NeedUpdate = false;
            }
        }
    }

    void BulletPlayer::OnUpdate(UNUSED(Timestep ts)) {
        ComponentHandle<TransformComponent> transform = GetComponent<TransformComponent>();
        ComponentHandle<ParentComponent> parent = GetComponent<ParentComponent>();
        World *world = HandleEntity->GetWorld();
        if (!transform || !parent || !world)
            return;

        Entity *parent_entity = world->GetEntityByID(parent.Get().Parent);
        // if (!parent_entity) {
        //     EXODIA_WARN("BulletPlayer has no parent");
        // }

        Entity *camera = world->GetEntityByTag("Camera");
        if (!camera)
            return;

        ComponentHandle<TransformComponent> camera_transform = camera->GetComponent<TransformComponent>();
        if (!camera_transform)
            return;

        if (_NeedUpdate && parent_entity)
            transform.Get().Translation.y = parent_entity->GetComponent<TransformComponent>().Get().Translation.y;

        UpdateAnimations();

        // Remove bullet if out of screen
        if (transform.Get().Translation.x > camera_transform.Get().Translation.x + 10.0f) {
            EXODIA_INFO("Bullet {0} destroyed", HandleEntity->GetComponent<TagComponent>().Get().Tag);
            world->DestroyEntity(HandleEntity);
        }
    }

    void BulletPlayer::OnCollisionEnter(Entity *entity) {
        ComponentHandle<ParentComponent> parent = GetComponent<ParentComponent>();
        ComponentHandle<IDComponent> entity_id = entity->GetComponent<IDComponent>();
        if (!parent || !entity_id)
            return;
        if (parent.Get().Parent == entity_id.Get().ID)
            return;

        HandleEntity->GetWorld()->DestroyEntity(HandleEntity);
    }
}; // namespace RType