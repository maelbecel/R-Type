/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** FadeSystem
*/

#ifndef FADESYSTEM_HPP_
#define FADESYSTEM_HPP_

// Exodia includes
#include "Exodia.hpp"

namespace RType {

    class FadeSystem : public Exodia::EntitySystem {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
      public:
        FadeSystem() = default;
        ~FadeSystem() = default;

        /////////////
        // Methods //
        /////////////
      public:
        void Update(Exodia::World *world, Exodia::Timestep ts) override;
    };
}; // namespace RType

#endif /* !FADESYSTEM_HPP_ */
