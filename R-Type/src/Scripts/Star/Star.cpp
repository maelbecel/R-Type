/*
** EPITECH PROJECT, 2023
** $
** File description:
** Star
*/

#include "Star.hpp"

using namespace Exodia;

namespace RType {

    void Star::OnCreate()
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> sizeDist(0.01f, 0.09f);
        std::uniform_int_distribution<int> intensityDist(1, 255);
        std::uniform_int_distribution<int> stateDist(0, 1);
        std::uniform_real_distribution<float> colorDist(0.9f, 1.0f);
        std::uniform_int_distribution<int> velocityDist(-8, -1);

        Scene *scene = HandleEntity.GetScene();

        if (!scene)
            return;

        GameObject camera = scene->GetEntityByName("Camera");
        TransformComponent &cameraTc = camera.GetComponent<TransformComponent>();

        _Size      = sizeDist(gen);
        _Intensity = intensityDist(gen) / 255.0f;
        _State     = stateDist(gen) ? State::GROWING : State::SHRINKING;

        HandleEntity.AddComponent<CircleRendererComponent>(glm::vec4{0.9f, 0.9f, colorDist(gen), 0.9f});
        HandleEntity.AddComponent<Clock>();

        TransformComponent &tc = GetComponent<TransformComponent>();

        float max_height = 20.0f;
        int height       = 40;

        tc.Translation.x = (float)(10 + std::uniform_int_distribution<int>(0, 19)(gen)) + cameraTc.Translation.x;
        tc.Translation.y = max_height - (float)(std::uniform_int_distribution<int>(0, height)(gen));
        tc.Scale.x       = _Size;
        tc.Scale.y       = _Size;

        RigidBody2DComponent &body = HandleEntity.AddComponent<RigidBody2DComponent>();

        body.Type = RigidBody2DComponent::BodyType::Dynamic;
        body.Mass = 0.0f;
        body.GravityScale = 0.0f;
        body.Velocity.x = (float)velocityDist(gen);
    }

    void Star::OnUpdate(Timestep ts)
    {
        Clock                   &clock     = GetComponent<Clock>();
        TransformComponent      &transform = GetComponent<TransformComponent>();
        CircleRendererComponent &cc        = GetComponent<CircleRendererComponent>();

        Scene *scene = HandleEntity.GetScene();

        if (!scene) {
            EXODIA_WARN("No scene");

            return;
        }
        float &mytime = clock.ElapsedTime;

        GameObject camera = scene->GetEntityByName("Camera");
        TransformComponent &camera_tc = camera.GetComponent<TransformComponent>();

        mytime += ts.GetMilliseconds();

        float seconds = ts.GetSeconds();

        _Intensity += (_State == State::GROWING) ? seconds * 0.1f : seconds * 0.1f * -1.0f;

        if (_Intensity <= 0.01f)
            _State = State::GROWING;
        else if (_Intensity >= 0.99f)
            _State = State::SHRINKING;
        cc.Color.a = _Intensity;

        if (transform.Translation.x < camera_tc.Translation.x - 12) {
            std::mt19937 gen(std::random_device{}());
            std::uniform_int_distribution<int> xDist(10, 19);
            std::uniform_int_distribution<int> yDist(-5, 5);

            transform.Translation.x = (float)(xDist(gen)) + camera_tc.Translation.x;
            transform.Translation.y = (float)(yDist(gen));
        }
    }
}; // namespace RType