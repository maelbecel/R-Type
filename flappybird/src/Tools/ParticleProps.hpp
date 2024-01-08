/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ParticleProps
*/

#ifndef PARTICLEPROPS_HPP_
    #define PARTICLEPROPS_HPP_

    #include <glm/glm.hpp>

namespace FlappyBird {

    struct ParticleProps {
        glm::vec2 Position;
        glm::vec2 Velocity;
        glm::vec2 VelocityVariation;
        glm::vec4 ColorBegin;
        glm::vec4 ColorEnd;
        float SizeBegin;
        float SizeEnd;
        float SizeVariation;
        float LifeTime = 1.0f;
        int NumberOfParticles = 100;
    };
};

#endif /* !PARTICLEPROPS_HPP_ */
