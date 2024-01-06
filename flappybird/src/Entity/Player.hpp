/*
** EXODIA PROJECT, 2023
** TryAGame
** File description:
** Player
*/

#ifndef PLAYER_HPP_
    #define PLAYER_HPP_

    #include "Particles/Particles.hpp"

class Player {

    // Constructor / Destructor (default)
    public:
        Player();
        ~Player() = default;

    // Methods
    public:
        void LoadAssets();
        void Reset();

        void OnUpdate(Exodia::Timestep ts);
        void OnRender();
        void OnImGuiRender();

    // Getter
    public:
        const glm::vec2 &GetPosition();
        float GetRotation();
        uint32_t GetScore();

    // Attributes
    private:
        glm::vec2 _Position;
        glm::vec2 _Velocity;

        float _Time;

        float _EnginePower;
        float _Gravity;

        float _SmokeEmitInterval;
        float _SmokeNextEmitTime;

        ParticleProps _SmokeParticle;
        ParticleProps _EngineParticle;

        ParticlesSystem _ParticleSystem;

        Ref<Exodia::Texture2D> _Texture;
};

#endif /* !PLAYER_HPP_ */
