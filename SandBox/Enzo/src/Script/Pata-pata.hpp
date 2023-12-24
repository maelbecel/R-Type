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

namespace Exodia {

    class PataPata : public ScriptableEntity {

        /////////////
        // Methods //
        /////////////
      public:
        void OnCreate() override {
            _Speed = 5.0f;

            std::cout << "PataPata created" << std::endl;
        }

        void OnUpdate(UNUSED(Timestep ts)) override {
            auto transform = GetComponent<TransformComponent>();

            if (transform) {
                // auto &tc = transform.Get();

                //  // Amplitude du mouvement sinusoidal
                // float amplitude = 1.0f;

                // // Fréquence du mouvement sinusoidal (plus la fréquence est élevée, plus le mouvement est rapide)
                // float frequency = 1.0f;

                // // Mise à jour de la position en fonction du temps et du mouvement sinusoidal
                // tc.Translation.y += amplitude * sin(frequency * ts.GetSeconds());
            }
        }

        ////////////////
        // Attributes //
        ////////////////
      private:
        float _Speed;
    };
}; // namespace Exodia

#endif /* !PATAPATA_HPP_ */
