/*
** EPITECH PROJECT, 2023
** $
** File description:
** BulletEnnemy
*/

#include "BulletEnnemy.hpp"

using namespace Exodia;

namespace RType {

    void BulletEnnemy::CreateAnimations() {
        AnimationComponent anim;
        AnimationComponent destroy;

        std::vector<Ref<SubTexture2D>> framesIdle;
        std::vector<Ref<SubTexture2D>> framesDestroy;

        for (int i = 0; i < 4; i++)
            framesIdle.push_back(
                SubTexture2D::CreateFromCoords(BULLET, {8 + i, 9.0f}, {16.6666666667f, 17.0f}, {1.0f, 1.0f}));

        anim.Frames = framesIdle;
        anim.IsPlaying = true;
        anim.Repeat = true;
        anim.FrameRate = TimeBetweenAnimations;

        for (int i = 0; i < 5; i++)
            framesDestroy.push_back(
                SubTexture2D::CreateFromCoords(BULLET, {7 + i, 8.0f}, {16.6666666667f, 17.0f}, {1.0f, 1.0f}));

        destroy.Frames = framesDestroy;
        destroy.IsPlaying = false;
        destroy.Repeat = false;
        destroy.FrameRate = TimeBetweenAnimations;

        _Animations.push_back(anim);
        _Animations.push_back(destroy);

        SpriteRendererComponent &sprite = HandleEntity.AddComponent<SpriteRendererComponent>();

        sprite.Texture = anim.Frames[0];
    }

    void BulletEnnemy::OnCreate() {
        TransformComponent &bullet_tc = GetComponent<TransformComponent>();
        ParentComponent &parent = GetComponent<ParentComponent>();
        Scene *scene = HandleEntity.GetScene();

        if (!scene)
            return;
        GameObject parent_entity = scene->GetEntityByUUID(parent.Parent);

        TransformComponent &tc = parent_entity.GetComponent<TransformComponent>();

        bullet_tc.Translation.x = tc.Translation.x;
        bullet_tc.Translation.y = tc.Translation.y;
        bullet_tc.Scale = {0.5f, 0.5f, 0.0f};

        HandleEntity.AddComponent<BoxCollider2DComponent>();

        // TODO: Ask to server the number of player connected, and do a rand() % nb_player
        GameObject player = scene->GetEntityByName("Player_0");

        if (!player.GetEntity())
            return;
        TransformComponent &player_tc = player.GetComponent<TransformComponent>();
        RigidBody2DComponent &bullet_rb = HandleEntity.AddComponent<RigidBody2DComponent>();

        bullet_rb.Type = RigidBody2DComponent::BodyType::Dynamic;
        bullet_rb.Mass = 0.0f;
        bullet_rb.GravityScale = 0.0f;

        float delta_x = player_tc.Translation.x - tc.Translation.x;
        float delta_y = player_tc.Translation.y - tc.Translation.y;

        // Calcul of the velocity magnitude
        float velocity_magnitude = std::sqrt(delta_x * delta_x + delta_y * delta_y);

        // Calcul of the velocity vector
        if (velocity_magnitude > 0.0f) {
            bullet_rb.Velocity.x = (delta_x / velocity_magnitude) * _Speed;
            bullet_rb.Velocity.y = (delta_y / velocity_magnitude) * _Speed;
        }

        CreateAnimations();

        HandleEntity.GetScene()->GetWorldPtr()->Emit<Events::OnEntityCreated>({HandleEntity.GetEntity()});
    }

    void BulletEnnemy::UpdateAnimations() {
        if (_Animations.size() == 0)
            return;
        SpriteRendererComponent &sprite = GetComponent<SpriteRendererComponent>();
        ComponentHandle<AnimationComponent> anim = HandleEntity.GetEntity()->GetComponent<AnimationComponent>();

        if (!anim) {
            _Animations[0].IsPlaying = true;
            _Animations[1].IsPlaying = false;

            anim = HandleEntity.GetEntity()->AddComponent<AnimationComponent>(_Animations[0]);

            sprite.Texture = anim.Get().Frames[0];
        } else {
            if (_IsColliding && _Animations[1].IsPlaying == false) {
                RigidBody2DComponent &body = GetComponent<RigidBody2DComponent>();

                body.Velocity = {0.0f, 0.0f};

                _Animations[0].IsPlaying = false;
                _Animations[1].IsPlaying = true;

                anim.Get() = _Animations[1];
                sprite.Texture = anim.Get().Frames[0];
            }

            if (_IsColliding && anim.Get().CurrentFrameIndex == anim.Get().Frames.size() - 1 &&
                _Animations[1].IsPlaying == true)
                HandleEntity.GetScene()->DestroyEntity(HandleEntity);
        }
    }

    void BulletEnnemy::OnUpdate(UNUSED(Timestep ts)) {
        TransformComponent &transform = GetComponent<TransformComponent>();
        ParentComponent &parent = GetComponent<ParentComponent>();

        Scene *scene = HandleEntity.GetScene();

        if (!scene)
            return;

        GameObject camera = scene->GetEntityByName("Camera");

        if (!camera.GetEntity()) {
            EXODIA_ERROR("No camera found");

            return;
        }

        TransformComponent &camera_transform = camera.GetComponent<TransformComponent>();

        // Remove bullet if out of screen
        if (transform.Translation.x < camera_transform.Translation.x - 20.0f)
            scene->DestroyEntity(HandleEntity);
        UpdateAnimations();
    }

    void BulletEnnemy::OnCollisionEnter(Entity *entity) {
        ParentComponent &parent = GetComponent<ParentComponent>();
        ComponentHandle<IDComponent> entity_id = entity->GetComponent<IDComponent>();

        if (!entity_id)
            return;
        if (parent.Parent == entity_id.Get().ID)
            return;
        _IsColliding = true;
    }
}; // namespace RType