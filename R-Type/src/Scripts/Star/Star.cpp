/*
** EPITECH PROJECT, 2023
** $
** File description:
** Star
*/

#include "Star.hpp"

using namespace Exodia;

namespace RType {

    void Star::OnCreate() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> sizeDist(0.01f, 0.09f);
        std::uniform_int_distribution<int> intensityDist(1, 255);
        std::uniform_int_distribution<int> stateDist(0, 1);
        std::uniform_real_distribution<float> colorDist(0.9f, 1.0f);
        std::uniform_int_distribution<int> velocityDist(-8, -1);

        World *world = HandleEntity->GetWorld();
        if (!world)
            return;

        Entity *camera = world->GetEntityByTag("Camera");
        if (!camera)
            return;

        ComponentHandle<TransformComponent> camera_tc = camera->GetComponent<TransformComponent>();

        if (!camera_tc)
            return;

        _Size = sizeDist(gen);
        _Intensity = intensityDist(gen) / 255.0f;
        _State = stateDist(gen) ? State::GROWING : State::SHRINKING;

        HandleEntity->AddComponent<CircleRendererComponent>(glm::vec4{0.9f, 0.9f, colorDist(gen), 0.9f});
        HandleEntity->AddComponent<Clock>();

        ComponentHandle<TransformComponent> transform = GetComponent<TransformComponent>();
        if (!transform)
            return;

        TransformComponent &tc = transform.Get();
        float max_height = 20.0f;
        int height = 40;

        tc.Translation.x = (float)(10 + std::uniform_int_distribution<int>(0, 19)(gen)) + camera_tc.Get().Translation.x;
        tc.Translation.y = max_height - (float)(std::uniform_int_distribution<int>(0, height)(gen));
        tc.Scale.x = _Size;
        tc.Scale.y = _Size;

        ComponentHandle<RigidBody2DComponent> body = HandleEntity->AddComponent<RigidBody2DComponent>();
        if (!body)
            return;

        body.Get().Type = RigidBody2DComponent::BodyType::Dynamic;
        body.Get().Mass = 0.0f;
        body.Get().GravityScale = 0.0f;
        body.Get().Velocity.x = (float)velocityDist(gen);
    }

    void Star::OnUpdate(Timestep ts) {
        ComponentHandle<Clock> clock = GetComponent<Clock>();
        ComponentHandle<TransformComponent> transform = GetComponent<TransformComponent>();
        ComponentHandle<CircleRendererComponent> circle = GetComponent<CircleRendererComponent>();
        World *world = HandleEntity->GetWorld();
        if (!transform || !circle || !clock || !world) {
            EXODIA_WARN("No transform, circle, clock or world");
            return;
        }

        float &mytime = clock.Get().ElapsedTime;
        Entity *camera = world->GetEntityByTag("Camera");
        if (!camera) {
            EXODIA_WARN("No camera");
            return;
        }

        ComponentHandle<TransformComponent> camera_tc = camera->GetComponent<TransformComponent>();
        if (!camera_tc) {
            EXODIA_WARN("Camera has no TransformComponent");
            return;
        }

        mytime += ts.GetMilliseconds();

        CircleRendererComponent &cc = circle.Get();

        float seconds = ts.GetSeconds();

        _Intensity += (_State == State::GROWING) ? seconds * 0.1f : seconds * 0.1f * -1.0f;

        if (_Intensity <= 0.01f)
            _State = State::GROWING;
        else if (_Intensity >= 0.99f)
            _State = State::SHRINKING;
        cc.Color.a = _Intensity;

        if (transform.Get().Translation.x < camera_tc.Get().Translation.x - 12) {
            std::mt19937 gen(std::random_device{}());
            std::uniform_int_distribution<int> xDist(10, 19);
            std::uniform_int_distribution<int> yDist(-5, 5);

            transform.Get().Translation.x = (float)(xDist(gen)) + camera_tc.Get().Translation.x;
            transform.Get().Translation.y = (float)(yDist(gen));
        }
    }
}; // namespace RType