/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ParticleComponent
*/

#ifndef PARTICLECOMPONENT_HPP_
#define PARTICLECOMPONENT_HPP_

// Exodia ECS includes
#include "Scene/Components/Component.hpp"

// External includes
#include <glm/glm.hpp>

namespace Exodia {

    struct ParticleComponent : public Component {
        float LifeTime;
        float LifeRemaining;
        glm::vec4 ColorBegin;
        glm::vec4 ColorEnd;
        float SizeBegin;
        float SizeEnd;

        ParticleComponent(ParticleComponent const &) = default;
        ParticleComponent() = default;
        ParticleComponent(float lifeTime, const glm::vec4 &colorBegin, const glm::vec4 &colorEnd, float sizeBegin,
                          float sizeEnd)
            : LifeTime(lifeTime), LifeRemaining(lifeTime), ColorBegin(colorBegin), ColorEnd(colorEnd),
              SizeBegin(sizeBegin), SizeEnd(sizeEnd){};
    };
}; // namespace Exodia

#endif /* !PARTICLECOMPONENT_HPP_ */
