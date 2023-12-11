/*
** EPITECH PROJECT, 2023
** $
** File description:
** Player
*/

#ifndef PATAPATA_HPP_
    #define PATAPATA_HPP_

    // Exodia includes
    #include "Exodia.hpp"
    #include "ComponentExample.hpp"

    #include <cmath>

namespace Exodia {

    const double PI = 3.14159265358979323846;

    class PataPata : public ScriptableEntity {

        /////////////
        //  enum   //
        /////////////
        public:
            enum class State {
                ALIVE,
                DEAD
            };

        /////////////
        // Methods //
        /////////////
        public:

            void OnCreate() override
            {
                _Speed = 2.0f;
                _State = State::ALIVE;

                std::cout << "PataPata created" << std::endl;
            }

            void OnUpdate(Timestep ts) override
            {
                auto transform = GetComponent<TransformComponent>();
                auto &mytime = GetComponent<Clock>().Get().ElapsedTime;

                // Paramètres de la fonction sinus
                double amplitude = 1.0f;  // Amplitude de la sinusoïde
                double frequency = 1.0f;  // Fréquence de la sinusoïde en Hz

                if (transform && _State == State::ALIVE) {
                    auto &tc = transform.Get();
                    // Mise à jour de la position en fonction du temps et du mouvement sinusoidal
                    mytime += ts.GetSeconds();
                    tc.Translation.y = amplitude * sin(frequency * mytime * PI);
                    tc.Translation.x -= _Speed * ts;

                    // Affichage des coordonnées

                    if (transform.Get().Translation.x < -10.0f)
                        transform.Get().Translation.x = 10.0f;
                }


                if (GetComponent<Health>().Get().CurrentHealth == 0 && _State == State::ALIVE) {
                    auto animation = GetComponent<Animation>();
                    auto sprite = GetComponent<SpriteRendererComponent>();

                    animation.Get().CurrentFrame = 0;
                    animation.Get().MaxFrame = 6;
                    animation.Get().FrameTime = 1.0f;

                    // Set entity sprite
                    Ref<Texture2D> texture = Texture2D::Create("Assets/Textures/Big_Explosion.png");
                    sprite.Get().Texture = SubTexture2D::CreateFromCoords(texture, { 4.0f, 4.0f }, { 32.6f, 32.8f }, { 1.0f, 1.0f });
                    _State = State::DEAD;
                }

            }

            void OnCollisionEnter(Entity *entity) override
            {
                if (entity->GetComponent<TagComponent>().Get().Tag.rfind("Bullet", 0) == 0) {
                    EXODIA_INFO("Bullet {0} hit", entity->GetComponent<TagComponent>().Get().Tag);
                    GetComponent<Health>().Get().CurrentHealth -= 1;
                }
            }

            State GetState() const { return _State; }

        ////////////////
        // Attributes //
        ////////////////
        private:
            float _Speed;
            State _State;
    };
};

#endif /* !PATAPATA_HPP_ */

