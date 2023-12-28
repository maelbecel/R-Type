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
        std::mt19937 gen(std::random_device{}());
        std::uniform_real_distribution<float> sizeDist(0.01f, 0.09f);
        std::uniform_int_distribution<int> intensityDist(1, 255);
        std::uniform_int_distribution<int> stateDist(0, 1);

        World *world = HandleEntity->GetWorld();

        if (!world)
            return;

        Entity *cam = world->GetEntityByTag("Camera");

        if (!cam)
            return;

        auto camera = cam->GetComponent<TransformComponent>();

        if (!camera)
            return;

        float max_height = 20.0f;
        int height = 40;

        _size = sizeDist(gen);
        _intensity = intensityDist(gen) / 255.0f;
        _State = stateDist(gen) ? State::GROWING : State::SHRINKING;

        auto transform = GetComponent<TransformComponent>();

        if (!transform)
            return;

        auto &tc = transform.Get();

        tc.Translation.x =
            (float)(10 + std::uniform_int_distribution<int>(0, 19)(gen)) + camera.Get().Translation.x;
        tc.Translation.y = max_height - (float)(std::uniform_int_distribution<int>(0, height)(gen));
        tc.Scale.x = _size;
        tc.Scale.y = _size;
    }

    void Star::OnUpdate(Timestep ts)  {

        auto clock = GetComponent<Clock>();
        auto transform = GetComponent<TransformComponent>();
        auto circle = GetComponent<CircleRendererComponent>();
        World *world = HandleEntity->GetWorld();

        if (!transform || !circle || !clock || !world) {
            EXODIA_WARN("No transform, circle, clock or world");
            return;
        }

        auto &mytime = clock.Get().ElapsedTime;
        auto cam = world->GetEntityByTag("Camera");

        if (!cam) {
            EXODIA_WARN("No camera");
            return;
        }

        auto camera = cam->GetComponent<TransformComponent>();

        if (!camera) {
            EXODIA_WARN("Camera has no TransformComponent");
            return;
        }

        mytime += ts.GetMilliseconds();

        if (circle) {
            auto &cc = circle.Get();

            _intensity +=
                (_State == State::GROWING) ? (float)(ts.GetSeconds() * 0.1) : (float)(ts.GetSeconds() * 0.1 * -1);

            if (_intensity <= 0.01f)
                _State = State::GROWING;
            else if (_intensity >= 0.99f)
                _State = State::SHRINKING;
            cc.Color.a = _intensity;
        }

        if (transform.Get().Translation.x < camera.Get().Translation.x - 12) {
            std::mt19937 gen(std::random_device{}());
            std::uniform_int_distribution<int> xDist(10, 19);
            std::uniform_int_distribution<int> yDist(-5, 5);

            transform.Get().Translation.x = (float)(xDist(gen)) + camera.Get().Translation.x;
            transform.Get().Translation.y = (float)(yDist(gen));
        }
    }
}; // namespace RType