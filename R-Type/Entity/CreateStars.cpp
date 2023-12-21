/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Create stars
*/

#include "Entity/CreateStars.hpp"

namespace Exodia {

    void CreateStars(std::map<SceneType, std::shared_ptr<Exodia::Scene>> _World)
    {
        for(int i = 0; i < 60; i++) {
            Entity *star = _World[GAME]->CreateEntity("Star" + std::to_string(i));

            star->AddComponent<ScriptComponent>().Get().Bind<Star>();
            star->GetComponent<TransformComponent>().Get().Scale.y = 0.1f;
            star->GetComponent<TransformComponent>().Get().Scale.x = 0.1f;
            star->AddComponent<Clock>();
			star->AddComponent<CircleRendererComponent>(glm::vec4{ 0.9f, 0.9f, 0.9f + static_cast<float>(random() % 100) / 10000.0f, 0.9f });

            auto body = star->AddComponent<RigidBody2DComponent>();

            body.Get().Type = RigidBody2DComponent::BodyType::Dynamic;
            body.Get().Mass = 0.0f;
            body.Get().GravityScale = 0.0f;
            body.Get().Velocity.x = (random() % 10 + 1) * -1;
            EXODIA_INFO("Star {0} created", i);
        }
    };
};