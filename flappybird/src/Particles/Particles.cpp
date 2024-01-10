/*
** EXODIA PROJECT, 2023
** TryAGame
** File description:
** Particles
*/

#include "Particles.hpp"

#include "../Tools/Random.hpp"

#include <glm/gtx/compatibility.hpp>

namespace FlappyBird {

    /**
     * The above function is a constructor for the ParticlesSystem class that initializes the
     * _ParticleListIndex to 999 and resizes the _ParticleList vector to 1000.
     */
    ParticlesSystem::ParticlesSystem() : _ParticleListIndex(999) { _ParticleList.resize(1000); }

    /**
     * The function emits a particle with specified properties and updates the particle list index.
     * 
     * @param props The "props" parameter is of type ParticleProps, which is a struct or class that
     * contains various properties of a particle. These properties include:
     */
    void ParticlesSystem::Emit(const ParticleProps &props) {
        Particle &particle = _ParticleList[_ParticleListIndex];

        // Active
        particle.Active = true;

        // Position
        particle.Position = props.Position;

        // Rotation
        particle.Rotation = Random::Float() * 2.0f * glm::pi<float>();

        // Velocity
        particle.Velocity = props.Velocity;
        particle.Velocity.x += props.VelocityVariation.x * (Random::Float() - 0.5f);
        particle.Velocity.y += props.VelocityVariation.y * (Random::Float() - 0.5f);

        // Color
        particle.ColorBegin = props.ColorBegin;
        particle.ColorEnd = props.ColorEnd;

        // Size
        particle.SizeBegin = props.SizeBegin + props.SizeVariation * (Random::Float() - 0.5f);
        particle.SizeEnd = props.SizeEnd;

        // Life
        particle.LifeTime = props.LifeTime;
        particle.LifeRemaining = props.LifeTime;

        _ParticleListIndex--;
        _ParticleListIndex = _ParticleListIndex % _ParticleList.size();
    }

    /**
     * The function updates the position, rotation, and remaining life of each active particle in a
     * particle system.
     * 
     * @param ts The parameter "ts" is of type "Exodia::Timestep" and is used to represent the time
     * elapsed since the last update. It is likely a custom data type defined in the Exodia namespace
     * specifically for handling time-related calculations.
     */
    void ParticlesSystem::OnUpdate(Exodia::Timestep ts) {
        for (Particle &particle : _ParticleList) {
            if (!particle.Active)
                continue;

            if (particle.LifeRemaining <= 0.0f) {
                particle.Active = false;
                continue;
            }

            particle.LifeRemaining -= ts;
            particle.Position += particle.Velocity * (float)ts;
            particle.Rotation += 0.01f * ts;
        }
    }

    /**
     * The function iterates through a list of particles and renders them with their respective
     * position, size, rotation, and color.
     */
    void ParticlesSystem::OnRender() {
        for (Particle &particle : _ParticleList) {
            if (!particle.Active)
                continue;

            float life = particle.LifeRemaining / particle.LifeTime;

            glm::vec4 color = glm::lerp(particle.ColorEnd, particle.ColorBegin, life);

            color.a = color.a * life;

            float size = glm::lerp(particle.SizeEnd, particle.SizeBegin, life);

            Exodia::Renderer2D::DrawRotatedQuad(particle.Position, // Position
                                                {size, size},      // Size
                                                particle.Rotation, // Rotation
                                                color              // Color
            );
        }
    }

} // namespace FlappyBird