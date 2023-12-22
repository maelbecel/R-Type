/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Create player
*/

#include "CreatePlayer.hpp"

namespace Exodia {

    void CreatePlayer(std::map<SceneType, std::shared_ptr<Exodia::Scene>> _World, int playerID)
    {
        Entity *entity = _World[GAME]->CreateEntity("Player_" + std::to_string(playerID));

        entity->AddComponent<Health>(1);
        entity->AddComponent<ScriptComponent>().Get().Bind("Player");
        entity->AddComponent<Animation>(1.0f, 2.0f, 0.1f);
        entity->GetComponent<TransformComponent>().Get().Scale.y = 0.5f;
        entity->GetComponent<TransformComponent>().Get().Translation.y = 0.4f * playerID;
        entity->AddComponent<BoxCollider2DComponent>();

        // Set entity sprite
        // auto sprite = entity->AddComponent<SpriteRendererComponent>();
        // Ref<Texture2D> texture = TextureImporter::LoadTexture2D("Assets/Textures/Player.png");
        // sprite.Get().Texture = SubTexture2D::CreateFromCoords(texture->Handle, { 2.0f, 4.0f }, { 33.2f, 17.2f }, { 1.0f, 1.0f });
        entity->AddComponent<CircleRendererComponent>(glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f});

        // Set entity rigidbody
        auto body = entity->AddComponent<RigidBody2DComponent>();

        body.Get().Type = RigidBody2DComponent::BodyType::Dynamic;
        body.Get().Mass = 0.0f;
        body.Get().GravityScale = 0.0f;
        body.Get().Velocity = glm::vec2{ 0.0f, 0.0f };
        EXODIA_INFO("Player created");
    };
};