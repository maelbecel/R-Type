/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Create pata-pata
*/

#include "CreatePataPata.hpp"

namespace Exodia {

    void CreatePataPata(std::map<SceneType, std::shared_ptr<Exodia::Scene>> _World)
    {
        Entity *patata = _World[GAME]->CreateEntity("Pata-pata");

        patata->AddComponent<Health>(1);
        // patata->AddComponent<ScriptComponent>().Get().Bind("PataPata");
        patata->AddComponent<Animation>(1.0f, 8.0f, 0.1f);
        // patata->AddComponent<Clock>();
        // patata->AddComponent<BoxCollider2DComponent>();

        auto body_patata = patata->AddComponent<RigidBody2DComponent>();
        body_patata.Get().Type = RigidBody2DComponent::BodyType::Dynamic;
        body_patata.Get().Mass = 0.0f;
        body_patata.Get().GravityScale = 0.0f;
        body_patata.Get().Velocity.x = 0.0f;
        // Set entity sprite
        auto sprite = patata->AddComponent<SpriteRendererComponent>(glm::vec4{ 0.8f, 0.2f, 0.3f, 1.0f });
        //auto sprite = patata->AddComponent<SpriteRendererComponent>();
        sprite.Get().Texture = SubTexture2D::CreateFromCoords(90123456789012678, { 0.0f, 0.0f }, { 33.3125f, 36.0f }, { 1.0f, 1.0f });

        auto transform = patata->GetComponent<TransformComponent>();
        if (!transform)
            return;
        transform.Get().Translation.x = 7.0f;
        // patata->AddComponent<CircleRendererComponent>(glm::vec4{ 1.0f, 1.0f, 0.0f, 1.0f});
        EXODIA_INFO("Pata-pata created");
    };
}