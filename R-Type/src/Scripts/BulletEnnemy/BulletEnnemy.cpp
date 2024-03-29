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

        ComponentHandle<SpriteRendererComponent> sprite = HandleEntity->AddComponent<SpriteRendererComponent>();

        sprite.Get().Texture =
            SubTexture2D::CreateFromCoords(BULLET, {8, 9.0f}, {16.6666666667f, 17.0f}, {1.0f, 1.0f}); // anim.Frames[0];
    }

    void BulletEnnemy::OnCreate() {
        EXODIA_CORE_ERROR("BulletEnnemy created");

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

        bullet_tc.Translation.x = tc.Translation.x;
        bullet_tc.Translation.y = tc.Translation.y;
        bullet_tc.Scale = {0.5f, 0.5f, 0.0f};

        HandleEntity->AddComponent<BoxCollider2DComponent>();

        // TODO: Ask to server the number of player connected, and do a rand() % nb_player
        Entity *player = world->GetEntityByTag("Player_0");

        if (!player)
            return;

        ComponentHandle<TransformComponent> player_transform = player->GetComponent<TransformComponent>();

        if (!player_transform)
            return;

        TransformComponent &player_tc = player_transform.Get();
        ComponentHandle<RigidBody2DComponent> body_bullet = HandleEntity->AddComponent<RigidBody2DComponent>();

        if (!body_bullet)
            return;

        RigidBody2DComponent &bullet_rb = body_bullet.Get();
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

        EXODIA_INFO("BulletEnnemy created");
        HandleEntity->GetWorld()->Emit<Events::OnEntityCreated>({HandleEntity});
    }

    void BulletEnnemy::UpdateAnimations() {
        ComponentHandle<TagComponent> tag = GetComponent<TagComponent>();
        if (_Animations.size() == 0)
            return;

        ComponentHandle<SpriteRendererComponent> sprite = GetComponent<SpriteRendererComponent>();
        ComponentHandle<AnimationComponent> anim = GetComponent<AnimationComponent>();

        if (!sprite)
            sprite = HandleEntity->AddComponent<SpriteRendererComponent>();

        if (!anim) {
            _Animations[0].IsPlaying = true;
            _Animations[1].IsPlaying = false;

            anim = HandleEntity->AddComponent<AnimationComponent>(_Animations[0]);

            sprite.Get().Texture = anim.Get().Frames[0];
        } else {
            if (_IsColliding && _Animations[1].IsPlaying == false) {
                ComponentHandle<RigidBody2DComponent> body = GetComponent<RigidBody2DComponent>();
                if (!body)
                    return;

                body.Get().Velocity = {0.0f, 0.0f};
                _Animations[0].IsPlaying = false;
                _Animations[1].IsPlaying = true;

                anim.Get() = _Animations[1];
                sprite.Get().Texture = anim.Get().Frames[0];
            }
            if (_IsColliding && anim.Get().CurrentFrameIndex == anim.Get().Frames.size() - 1 &&
                _Animations[1].IsPlaying == true) {
                EXODIA_INFO("Bullet {0} destroyed", HandleEntity->GetComponent<TagComponent>().Get().Tag);
                HandleEntity->GetWorld()->DestroyEntity(HandleEntity);
            }
        }
    }

    void BulletEnnemy::OnUpdate(UNUSED(Timestep ts)) {
        ComponentHandle<TransformComponent> transform = GetComponent<TransformComponent>();
        ComponentHandle<ParentComponent> parent = GetComponent<ParentComponent>();
        World *world = HandleEntity->GetWorld();

        if (!transform || !parent || !world) {
            EXODIA_ERROR("BulletEnnemy: OnUpdate: transform or parent or world is null");
            return;
        }

        Entity *camera = world->GetEntityByTag("Camera");
        if (!camera) {
            EXODIA_ERROR("No camera found");
            return;
        }

        ComponentHandle<TransformComponent> camera_transform = camera->GetComponent<TransformComponent>();
        if (!camera_transform)
            return;

        // Remove bullet if out of screen
        if (transform.Get().Translation.x < camera_transform.Get().Translation.x - 20.0f) {
            EXODIA_INFO("Bullet {0} destroyed", HandleEntity->GetComponent<TagComponent>().Get().Tag);

            world->DestroyEntity(HandleEntity);
        }

        UpdateAnimations();
    }

    void BulletEnnemy::OnCollisionEnter(Entity *entity) {
        ComponentHandle<TagComponent> tag_entity = entity->GetComponent<TagComponent>();
        if (!tag_entity)
            return;

        if (tag_entity.Get().Tag.rfind("Pata", 0) == 0 || tag_entity.Get().Tag.rfind("BE", 0) == 0) {
        } else {
            ComponentHandle<RigidBody2DComponent> body = GetComponent<RigidBody2DComponent>();
            if (!body)
                return;
            body.Get().Velocity = {0.0f, 0.0f};
            _IsColliding = true;
        }
    }
}; // namespace RType