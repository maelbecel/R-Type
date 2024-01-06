/*
** EXODIA PROJECT, 2023
** TryAGame
** File description:
** Player
*/

#include "Player.hpp"
#include "imgui.h"

#include <glm/gtc/matrix_transform.hpp>

Player::Player() : _Position({ -10.0f, 0.0f}), _Velocity({ 5.0f, 0.0f }), _Time(0.0f), _EnginePower(0.5f), _Gravity(0.4f), _SmokeEmitInterval(0.4f), _SmokeNextEmitTime(0.4f)
{
    // Smoke Particles
    _SmokeParticle.Position = {  0.0f, 0.0f };
    _SmokeParticle.Velocity = { -2.0f, 0.0f };
    _SmokeParticle.VelocityVariation = { 4.0f, 2.0f };
    _SmokeParticle.SizeBegin = 0.35f;
    _SmokeParticle.SizeEnd = 0.0f;
    _SmokeParticle.SizeVariation = 0.15f;
    _SmokeParticle.ColorBegin = { 0.8f, 0.8f, 0.8f, 1.0f };
    _SmokeParticle.ColorEnd = { 0.6f, 0.6f, 0.6f, 1.0f };
    _SmokeParticle.LifeTime = 4.0f;

    // Engine Particles
    _EngineParticle.Position = {  0.0f, 0.0f };
    _EngineParticle.Velocity = { -2.0f, 0.0f };
    _EngineParticle.VelocityVariation = { 3.0f, 1.0f };
    _EngineParticle.SizeBegin = 0.5f;
    _EngineParticle.SizeEnd = 0.0f;
    _EngineParticle.SizeVariation = 0.3f;
    _EngineParticle.ColorBegin = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f };
    _EngineParticle.ColorEnd = { 254 / 255.0f, 212 / 255.0f, 123 / 255.0f, 1.0f };
    _EngineParticle.LifeTime = 1.0f;
}

void Player::LoadAssets()
{
    _Texture = Exodia::Texture2D::Create("./Assets/Texture/Characters/SpaceShip.png");
}

void Player::Reset()
{
    _Position = { -10.0f, 0.0f };
    _Velocity = { 5.0f, 0.0f };
}

void Player::OnUpdate(Exodia::Timestep ts)
{
    _Time += ts;

    if (Exodia::Input::IsKeyPressed(EXODIA_KEY_SPACE)) {
        _Velocity.y += _EnginePower;

        if (_Velocity.y > 0.0f)
            _Velocity.y += _EnginePower * 2.0f;

        // Engine Particles
        glm::vec2 emissionPoint = { 0.0f, -0.6f };
        float rotation = glm::radians(GetRotation());
        glm::vec2 rotated = glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f }) * glm::vec4(emissionPoint, 0.0f, 1.0f);

        _EngineParticle.Position = _Position + glm::vec2(rotated.x, rotated.y);
        _EngineParticle.Velocity.y = -_Velocity.y * 0.2f - 0.2f;
        _ParticleSystem.Emit(_EngineParticle);
    } else {
        _Velocity.y -= _Gravity;
    }

    _Velocity.y = glm::clamp(_Velocity.y, -20.0f, 20.0f);
    _Position += _Velocity * (float)ts;

    // Smoke Particles
    if (_Time > _SmokeNextEmitTime) {
        _SmokeParticle.Position = _Position;

        _ParticleSystem.Emit(_SmokeParticle);

        _SmokeNextEmitTime += _SmokeEmitInterval;
    }
    _ParticleSystem.OnUpdate(ts);
}

void Player::OnRender()
{
    _ParticleSystem.OnRender();

    Exodia::Renderer2D::DrawRotatedQuad(
        { _Position.x, _Position.y, 0.5f }, // Position
        { 1.0f, 1.3f },                     // Size
        glm::radians(GetRotation()),        // Rotation
        _Texture                            // Texture
    );
}

void Player::OnImGuiRender()
{
    ImGui::DragFloat("Engine Power", &_EnginePower, 0.1f);
    ImGui::DragFloat("Gravity", &_Gravity, 0.1f);
}

const glm::vec2 &Player::GetPosition()
{
    return _Position;
}

float Player::GetRotation()
{
    return _Velocity.y * 4.0f - 90.0f;
}

uint32_t Player::GetScore()
{
    return (uint32_t)(_Position.x + 10.0f) / 10.0f;
}
