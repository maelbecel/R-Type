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
                // set random seed to 4

                _Speed = random() % 8 + 1;
                _size = 0.01f + static_cast<float>(random() % 8) / 100.0f;
                _intensity = random() % 255 + 1;
                _State = random() % 2 ? State::GROWING : State::SHRINKING;

                GetComponent<TransformComponent>().Get().Scale.x = _size;
                GetComponent<TransformComponent>().Get().Scale.y = _size;
                auto transform = GetComponent<TransformComponent>();
                auto &tc = transform.Get();
				tc.Translation.x = 10 + random() % 20;
				tc.Translation.y = 5 - random() % 10;
            }

            void OnUpdate(Timestep ts) override
            {
                auto &mytime = GetComponent<Clock>().Get().ElapsedTime;
                mytime += ts.GetMilliseconds();

                auto transform = GetComponent<TransformComponent>();
                if (transform) {
                    auto &tc = transform.Get();
                    tc.Translation.x -= _Speed * ts;
                }

                auto circle = GetComponent<CircleRendererComponent>();
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

				if (GetComponent<TransformComponent>().Get().Translation.x < -10) {
				    GetComponent<TransformComponent>().Get().Translation.x = 10 + random() % 10;
					GetComponent<TransformComponent>().Get().Translation.y = 5 - random() % 10;
				}

            }

        ////////////////
        // Attributes //
        ////////////////
        private:
            float _Speed;
            float _intensity;
            State _State;
            float _size;
            float getIntensity() const { return _intensity; }
    };
};

#endif /* !STAR_HPP_ */

