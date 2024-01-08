/*
** EPITECH PROJECT, 2023
** TryAGame
** File description:
** Particles
*/

#ifndef PARTICLES_HPP_
#define PARTICLES_HPP_

#include "Exodia.hpp"

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
  };

  struct Particle {
      glm::vec2 Position;
      glm::vec2 Velocity;
      glm::vec4 ColorBegin;
      glm::vec4 ColorEnd;
      float Rotation = 0.0f;
      float SizeBegin;
      float SizeEnd;
      float LifeTime = 1.0f;
      float LifeRemaining = 0.0f;
      bool Active = false;
  };

  class ParticlesSystem {

      // Constructor & Destructor (default)
    public:
      ParticlesSystem();
      ~ParticlesSystem() = default;

      // Methods
    public:
      void Emit(const ParticleProps &props);
      void OnUpdate(Exodia::Timestep ts);
      void OnRender();

      // Attributes
    private:
      std::vector<Particle> _ParticleList;
      uint32_t _ParticleListIndex;
  };
}

#endif /* !PARTICLES_HPP_ */
