/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ParticleSystem
*/

#ifndef PARTICLESYSTEM_HPP_
    #define PARTICLESYSTEM_HPP_

    // Exodia ECS Interface includes
    #include "Exodia-ECS.hpp"

    // Exodia Scene includes
    #include "Scene/Components/Components.hpp"

namespace Exodia {

    class ParticleSystem : public EntitySystem {

        /////////////
        // Methods //
        /////////////
        public:

            virtual void Update(World *world, Timestep ts) override;
    };
};

#endif /* !PARTICLESYSTEM_HPP_ */
