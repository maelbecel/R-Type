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

        SpriteRendererComponent &sprite = HandleEntity.AddComponent<SpriteRendererComponent>();

        sprite.Texture = anim.Frames[0];
    }

    void BulletPlayer::OnCreate()
    {
        TransformComponent &bullet_tc = GetComponent<TransformComponent>();
        ParentComponent    &parent    = GetComponent<ParentComponent>();
        Scene *scene = HandleEntity.GetScene();

        if (!scene)
            return;

        GameObject parent_entity = scene->GetEntityByUUID(parent.Parent);

        if (parent_entity.GetEntity()) {
            TransformComponent &tc = parent_entity.GetComponent<TransformComponent>();

            bullet_tc.Translation.x = tc.Translation.x + 0.7f;
            bullet_tc.Translation.y = tc.Translation.y - 0.05f;
        }

        bullet_tc.Scale = { 0.5f, 0.5f, 0.0f };

        HandleEntity.AddComponent<BoxCollider2DComponent>();

        RigidBody2DComponent &rbc = HandleEntity.AddComponent<RigidBody2DComponent>();

        rbc.Type = RigidBody2DComponent::BodyType::Dynamic;
        rbc.Mass = 0.0f;
        rbc.GravityScale = 0.0f;
        rbc.Velocity.x = _Speed;
        rbc.Velocity.y = 0.0f;

        CreateAnimations();

        HandleEntity.GetScene()->GetWorldPtr()->Emit<Exodia::Events::OnEntityCreated>({ HandleEntity.GetEntity() });
    }

    void BulletPlayer::UpdateAnimations()
    {
        if (_Animations.size() == 0)
            return;

        SpriteRendererComponent &sprite = GetComponent<SpriteRendererComponent>();
        ComponentHandle<AnimationComponent> anim = HandleEntity.GetEntity()->GetComponent<AnimationComponent>();

        if (!anim) {
            _Animations[0].IsPlaying = true;

            anim = HandleEntity.GetEntity()->AddComponent<AnimationComponent>(_Animations[0]);

            sprite.Texture = anim.Get().Frames[0];
        } else {
            if (_Animations[0].IsPlaying && anim.Get().CurrentFrameIndex == anim.Get().Frames.size() - 1) {
                _Animations[0].IsPlaying = false;
                anim.Get() = _Animations[0];

                RigidBody2DComponent &body = GetComponent<RigidBody2DComponent>();

                body.Velocity.x = _Speed;
                _NeedUpdate = false;
            }
        }
    }

    void BulletPlayer::OnUpdate(UNUSED(Timestep ts))
    {
        TransformComponent &transform = GetComponent<TransformComponent>();
        ParentComponent    &parent    = GetComponent<ParentComponent>();
        Scene *scene = HandleEntity.GetScene();

        if (!scene)
            return;
        
        GameObject parent_entity = scene->GetEntityByUUID(parent.Parent);
        GameObject camera        = scene->GetPrimaryCamera();

        if (!camera.GetEntity())
            return;
        TransformComponent &camera_transform = camera.GetComponent<TransformComponent>();

        if (_NeedUpdate && parent_entity)
            transform.Translation.y = parent_entity.GetComponent<TransformComponent>().Translation.y;

        UpdateAnimations();

        // Remove bullet if out of screen
        if (transform.Translation.x > camera_transform.Translation.x + 10.0f)
            scene->DestroyEntity(HandleEntity);
    }

    void BulletPlayer::OnCollisionEnter(Entity *entity)
    {
        ParentComponent &parent = GetComponent<ParentComponent>();
        ComponentHandle<IDComponent> entity_id = entity->GetComponent<IDComponent>();

        if (!entity_id)
            return;
        if (parent.Parent == entity_id.Get().ID)
            return;

        if (HandleEntity.GetScene())
            HandleEntity.GetScene()->DestroyEntity(HandleEntity);
    }
};
