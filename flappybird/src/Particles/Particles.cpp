/*
** EXODIA PROJECT, 2023
** TryAGame
** File description:
** Particles
*/

#include "Particles.hpp"

#include "Tools/Random.hpp"

#include <glm/gtx/compatibility.hpp>

ParticlesSystem::ParticlesSystem() : _ParticleListIndex(999) { _ParticleList.resize(1000); }

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
