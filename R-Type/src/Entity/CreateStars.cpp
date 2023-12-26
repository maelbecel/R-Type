/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Create stars
*/

#include "CreateStars.hpp"
#include "SceneType.hpp"
#include <random>

namespace Exodia {

    void CreateStars(std::map<SceneType, std::shared_ptr<Exodia::Scene>> world) {
        std::random_device rd;
        std::mt19937 gen(rd());

        std::uniform_real_distribution<float> colorDist(0.9f, 1.0f);
        std::uniform_int_distribution<int> velocityDist(-8, -1);

        for (int i = 0; i < 60; i++) {
            Entity *star = world[GAME]->CreateEntity("Star" + std::to_string(i));

            star->AddComponent<ScriptComponent>().Get().Bind("Star");
            star->GetComponent<TransformComponent>().Get().Scale.y = 0.1f;
            star->GetComponent<TransformComponent>().Get().Scale.x = 0.1f;
            star->AddComponent<Clock>();
            star->AddComponent<CircleRendererComponent>(glm::vec4{0.9f, 0.9f, colorDist(gen), 0.9f});

            auto body = star->AddComponent<RigidBody2DComponent>();

            body.Get().Type = RigidBody2DComponent::BodyType::Dynamic;
            body.Get().Mass = 0.0f;
            body.Get().GravityScale = 0.0f;
            body.Get().Velocity.x = (float)velocityDist(gen);
        }
    };
}; // namespace Exodia
