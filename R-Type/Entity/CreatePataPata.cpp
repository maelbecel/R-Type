/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Create pata-pata
*/

#include "Entity/CreatePataPata.hpp"

namespace Exodia {

    void CreatePataPata(World *_World) {
        Entity *patata = _World->CreateEntity("Pata-pata");

        auto sprite = patata->AddComponent<SpriteRendererComponent>();
        patata->AddComponent<Health>(1);
        patata->AddComponent<ScriptComponent>().Get().Bind<PataPata>();
        patata->AddComponent<Animation>(1.0f, 8.0f, 0.075f);
        patata->AddComponent<Clock>();
        patata->AddComponent<BoxCollider2DComponent>();

        auto body_patata = patata->AddComponent<RigidBody2DComponent>();

        body_patata.Get().Type = RigidBody2DComponent::BodyType::Dynamic;
        body_patata.Get().Mass = 0.0f;
        body_patata.Get().GravityScale = 0.0f;
        body_patata.Get().Velocity.x = -2.0f;
        // Set entity sprite
        Ref<Texture2D> texture = TextureImporter::LoadTexture2D("Assets/Textures/Pata-Pata.png");
        sprite.Get().Texture = SubTexture2D::CreateFromCoords(texture, { 0.0f, 0.0f }, { 33.3125f, 36.0f }, { 1.0f, 1.0f });
    };
}