/*
** EPITECH PROJECT, 2023
** $
** File description:
** Player
*/

#ifndef STAR_HPP_
    #define STAR_HPP_

    // Exodia includes
    #include "Exodia.hpp"
    #include <random>

namespace Exodia {

    class Star : public ScriptableEntity {

        /////////////
        // Methods //
        /////////////
        public:

            enum class State {
                GROWING = 0,
                SHRINKING,
            };

            void OnCreate() override
            {
                auto camera = HandleEntity->GetWorld()->GetEntityByTag("Camera")->GetComponent<TransformComponent>();

                float max_height = 20.0f;
                int height = 40;

                _size = 0.01f + static_cast<float>(random() % 8) / 100.0f;
                _intensity = random() % 255 + 1;
                _State = random() % 2 ? State::GROWING : State::SHRINKING;

                auto transform = GetComponent<TransformComponent>();
                auto &tc = transform.Get();
				tc.Translation.x = (10 + random() % 20) + camera.Get().Translation.x;
				tc.Translation.y = max_height - random() % height;
                tc.Scale.x = _size;
                tc.Scale.y = _size;
            }

            void OnUpdate(Timestep ts) override
            {
                auto &mytime = GetComponent<Clock>().Get().ElapsedTime;
                auto transform = GetComponent<TransformComponent>();
                auto circle = GetComponent<CircleRendererComponent>();
                auto camera = HandleEntity->GetWorld()->GetEntityByTag("Camera")->GetComponent<TransformComponent>();


                mytime += ts.GetMilliseconds();

                if (circle) {
                    auto &cc = circle.Get();
                    _intensity += (_State == State::GROWING) ? ts.GetSeconds() * 0.1 : ts.GetSeconds() * 0.1 * -1;
                    if (_intensity <= 0.01f) {
                        _State = State::GROWING;
                    } else if (_intensity >= 0.99f) {
                        _State = State::SHRINKING;
                    }
                    cc.Color.a = getIntensity();
                }

				if (transform.Get().Translation.x <  camera.Get().Translation.x - 10) {
				    transform.Get().Translation.x = (10 + random() % 10) + camera.Get().Translation.x;
					transform.Get().Translation.y = 5 - random() % 10;
				}
            }

        ////////////////
        // Attributes //
        ////////////////
        private:
            float _intensity;
            State _State;
            float _size;
            float getIntensity() const { return _intensity; }
    };
};

#endif /* !STAR_HPP_ */

