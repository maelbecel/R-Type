/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Create background
*/

#include "Entity/CreateBackground.hpp"

namespace Exodia {

    void CreateBackground(std::map<SceneType, std::shared_ptr<Exodia::Scene>> _World) {
        // Create background
        Entity *background = _World[GAME]->CreateEntity("Background");

        background->AddComponent<IDComponent>();
        background->AddComponent<CircleRendererComponent>(glm::vec4{ 0.0f, 0.0f, 0.005f, 1.0f });
        background->GetComponent<TransformComponent>().Get().Scale.y = 100.0f;
        background->GetComponent<TransformComponent>().Get().Scale.x = 100.0f;
        background->GetComponent<TransformComponent>().Get().Translation.z = -0.5f;

        auto body_bg = background->AddComponent<RigidBody2DComponent>();
        body_bg.Get().Type = RigidBody2DComponent::BodyType::Dynamic;
        body_bg.Get().Mass = 0.0f;
        body_bg.Get().GravityScale = 0.0f;
        body_bg.Get().Velocity = glm::vec2{ 1.5f, 0.0f };
        EXODIA_INFO("Background created");
    };
};