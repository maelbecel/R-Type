/*
** EPITECH PROJECT, 2023
** $
** File description:
** BulletEnnemy
*/

#include "BulletEnnemy.hpp"

using namespace Exodia;

namespace RType {

    void BulletEnnemy::OnCreate() {
        EXODIA_INFO("BulletEnnemy created");

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

        HandleEntity->AddComponent<Animation>(8.0f, 12.0f, 0.0795f);
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
        bullet_rb.Velocity.x = player_tc.Translation.x - tc.Translation.x;
        bullet_rb.Velocity.y = player_tc.Translation.y - tc.Translation.y;

        // Ref<Texture2D> texture = TextureImporter::LoadTexture2D("Assets/Textures/Explosion.png");
        // auto sprite = bullet->AddComponent<SpriteRendererComponent>();
        // if (!texture || !sprite)
        //     return;
        // sprite.Get().Texture = SubTexture2D::CreateFromCoords(texture->Handle, { 8.0f, 4.0f },
        // { 16.6666666667f, 17.0f }, { 1.0f, 1.0f });
        HandleEntity->AddComponent<CircleRendererComponent>(glm::vec4{0.0f, 1.0f, 0.0f, 1.0f});

        std::cout << "Bullet created" << std::endl;
    }

    void BulletEnnemy::OnUpdate(UNUSED(Timestep ts))  {
        ComponentHandle<TransformComponent> transform = GetComponent<TransformComponent>();
        ComponentHandle<ParentComponent> parent = GetComponent<ParentComponent>();
        World *world = HandleEntity->GetWorld();

        if (!transform || !parent || !world)
            return;

        Entity *camera = world->GetEntityByTag("Camera");
        if (!camera)
            return;

        ComponentHandle<TransformComponent> camera_transform = camera->GetComponent<TransformComponent>();
        if (!camera_transform)
            return;

        Entity *entity = world->GetEntityByID(parent.Get().Parent);

        if (!entity) {
            EXODIA_WARN("BulletPlayer has no parent");
        }

        // Remove bullet if out of screen
        if (transform.Get().Translation.x > camera_transform.Get().Translation.x + 20.0f) {
            EXODIA_INFO("Bullet {0} destroyed", HandleEntity->GetComponent<TagComponent>().Get().Tag);
            world->DestroyEntity(HandleEntity);
        }
    }
}; // namespace RType