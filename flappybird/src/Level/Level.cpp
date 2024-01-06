/*
** EXODIA PROJECT, 2023
** TryAGame
** File description:
** Level
*/

#include "Level.hpp"

#include "Tools/Color.hpp"
#include "Tools/Random.hpp"
#include "Tools/Collider.hpp"

#include <glm/gtc/matrix_transform.hpp>

Level::Level() : _GameOver(false), _ObstacleTarget(30.0f), _ObstacleIndex(0), _ObstacleHSV({0.0f, 0.8f, 0.8f}){};

void Level::Init() {
    _ObstacleTexture = Exodia::Texture2D::Create("Assets/Texture/Tiles/Obstacle.png");
    _Player.LoadAssets();

    _Obstacles.resize(5);

    for (int i = 0; i < 5; i++)
        CreateObstacle(i, 10.0f * i);
}

void Level::Reset() {
    _GameOver = false;
    _Player.Reset();
    _ObstacleIndex = 0;
    _ObstacleTarget = 30.0f;

    for (int i = 0; i < 5; i++)
        CreateObstacle(i, 10.0f * i);
}

void Level::OnUpdate(Exodia::Timestep ts) {
    _Player.OnUpdate(ts);

    if (Collision()) {
        _GameOver = true;
        return;
    }

    _ObstacleHSV.x += 0.1f * ts;
    if (_ObstacleHSV.x > 1.0f)
        _ObstacleHSV.x = 0.0f;

    if (_Player.GetPosition().x > _ObstacleTarget) {
        CreateObstacle(_ObstacleIndex, _ObstacleTarget + 20.0f);

        _ObstacleIndex++;
        _ObstacleIndex = _ObstacleIndex % _Obstacles.size();
        _ObstacleTarget += 10.0f;
    }
}

void Level::OnRender() {
    const glm::vec2 &playerPos = _Player.GetPosition();

    glm::vec4 color = Color::HSVtoRGB(_ObstacleHSV);

    // Background
    Exodia::Renderer2D::DrawQuad({playerPos.x, 0.0f, -0.8f}, // Position
                                 {50.0f, 50.0f},             // Size
                                 {0.3f, 0.3f, 0.3f, 1.0f}    // Color
    );

    // Floor and Ceiling
    Exodia::Renderer2D::DrawQuad({playerPos.x, 34.0f}, // Position
                                 {50.0f, 50.0f},       // Size
                                 color                 // Color
    );
    Exodia::Renderer2D::DrawQuad({playerPos.x, -34.0f}, // Position
                                 {50.0f, 50.0f},        // Size
                                 color                  // Color
    );

    // Obstacles
    for (auto &obstacle : _Obstacles) {
        Exodia::Renderer2D::DrawRotatedQuad( // Top Triangle
            obstacle.PositionTop,            // Position
            obstacle.TopScale,               // Size
            glm::radians(180.0f),            // Rotation
            _ObstacleTexture,                // Texture
            1.0f,                            // Tiling Factor
            color                            // Tint Color
        );

        Exodia::Renderer2D::DrawRotatedQuad( // Bottom Triangle
            obstacle.PositionBottom,         // Position
            obstacle.BottomScale,            // Size
            0.0f,                            // Rotation
            _ObstacleTexture,                // Texture
            1.0f,                            // Tiling Factor
            color                            // Tint Color
        );
    }

    // Entity
    _Player.OnRender();
}

void Level::OnImGuiRender() { _Player.OnImGuiRender(); }

void Level::CreateObstacle(int index, float offset) {
    Obstacle &obstacle = _Obstacles[index];

    float center = Random::Float() * 35.0f - 17.5f;
    float gap = 2.0f + Random::Float() * 5.0f;

    obstacle.PositionTop.x = offset;
    obstacle.PositionBottom.x = offset;
    obstacle.PositionTop.z = index * 0.1f - 0.5f;
    obstacle.PositionBottom.z = index * 0.1f - 0.5f + 0.05f;

    obstacle.PositionTop.y = 10.0f + ((10.0f - center) * 0.2f) + gap / 2.0f;
    obstacle.PositionBottom.y = -10.0f - ((-10.0f - center) * 0.2f) - gap / 2.0f;
}

bool Level::Collision() {
    const glm::vec2 &pos = _Player.GetPosition();

    if (glm::abs(pos.y) > 8.5f)
        return true;

    glm::vec4 playerVertices[4] = {
        {-0.5f, -0.5f, 0.0f, 1.0f}, {0.5f, -0.5f, 0.0f, 1.0f}, {0.5f, 0.5f, 0.0f, 1.0f}, {-0.5f, 0.5f, 0.0f, 1.0f}};
    glm::vec4 playerTransformedVerts[4];

    for (int i = 0; i < 4; i++)
        playerTransformedVerts[i] =
            glm::translate(glm::mat4(1.0f), {pos.x, pos.y, 0.0f}) *
            glm::rotate(glm::mat4(1.0f), glm::radians(_Player.GetRotation()), {0.0f, 0.0f, 1.0f}) *
            glm::scale(glm::mat4(1.0f), {1.0f, 1.3f, 1.0f}) * playerVertices[i];

    glm::vec4 pillarVertices[3] = {
        {-0.5f + 0.1f, -0.5f + 0.1f, 0.0f, 1.0f},
        {0.5f - 0.1f, -0.5f + 0.1f, 0.0f, 1.0f},
        {0.0f + 0.0f, 0.5f - 0.1f, 0.0f, 1.0f},
    };

    for (Obstacle &obstacle : _Obstacles) {
        glm::vec2 triangle[3];

        // Top pillars
        for (int i = 0; i < 3; i++)
            triangle[i] = glm::translate(glm::mat4(1.0f), {obstacle.PositionTop.x, obstacle.PositionTop.y, 0.0f}) *
                          glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), {0.0f, 0.0f, 1.0f}) *
                          glm::scale(glm::mat4(1.0f), {obstacle.TopScale.x, obstacle.TopScale.y, 1.0f}) *
                          pillarVertices[i];

        for (auto &vertex : playerTransformedVerts) {
            if (PointInTriangle({vertex.x, vertex.y}, triangle[0], triangle[1], triangle[2]))
                return true;
        }

        // Bottom pillars
        for (int i = 0; i < 3; i++) {
            triangle[i] =
                glm::translate(glm::mat4(1.0f), {obstacle.PositionBottom.x, obstacle.PositionBottom.y, 0.0f}) *
                glm::scale(glm::mat4(1.0f), {obstacle.BottomScale.x, obstacle.BottomScale.y, 1.0f}) * pillarVertices[i];
        }

        for (auto &vertex : playerTransformedVerts) {
            if (PointInTriangle({vertex.x, vertex.y}, triangle[0], triangle[1], triangle[2]))
                return true;
        }
    }
    return false;
}

bool Level::IsGameOver() { return _GameOver; }

Player &Level::GetPlayer() { return _Player; }
