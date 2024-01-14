/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Create background
*/

#include "CreateBackground.hpp"

namespace Exodia {

    void CreateBackground(std::map<SceneType, std::shared_ptr<Exodia::Scene>> _World) {
        // Create background
        GameObject background = _World[GAME]->CreateEntity("Background");

        background.AddComponent<CircleRendererComponent>(glm::vec4{0.0f, 0.0f, 0.005f, 1.0f});
        background.AddComponent<MusicComponent>(UUID(124013371145915), 0.6f, true);

        background.GetComponent<TransformComponent>().Scale.y = 100.0f;
        background.GetComponent<TransformComponent>().Scale.x = 100.0f;
        background.GetComponent<TransformComponent>().Translation.z = -0.5f;

        auto &body_bg = background.AddComponent<RigidBody2DComponent>();

        body_bg.Type = RigidBody2DComponent::BodyType::Dynamic;
        body_bg.Mass = 0.0f;
        body_bg.GravityScale = 0.0f;
        body_bg.Velocity = glm::vec2{1.5f, 0.0f};

        EXODIA_INFO("Background created");
    };
}; // namespace Exodia