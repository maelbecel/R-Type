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
        // Methods //
        /////////////
        public:

            void OnCreate() override
            {
                _Speed = 2.0f;

                std::cout << "PataPata created" << std::endl;
            }

            void OnUpdate(Timestep ts) override
            {
                auto transform = GetComponent<TransformComponent>();
                auto &mytime = GetComponent<Clock>().Get().ElapsedTime;

                // Paramètres de la fonction sinus
                double amplitude = 1.0f;  // Amplitude de la sinusoïde
                double frequency = 1.0f;  // Fréquence de la sinusoïde en Hz

                if (transform) {
                    auto &tc = transform.Get();
                    // Mise à jour de la position en fonction du temps et du mouvement sinusoidal
                    mytime += ts.GetSeconds();
                    tc.Translation.y = amplitude * sin(frequency * mytime * PI);
                    tc.Translation.x -= _Speed * ts;

                    // Affichage des coordonnées
                    std::cout << "Temps : " << mytime << " s\tPosition Y : " << tc.Translation.y << std::endl;

                }
            }

        ////////////////
        // Attributes //
        ////////////////
        private:
            float _Speed;
    };
};

#endif /* !PATAPATA_HPP_ */

