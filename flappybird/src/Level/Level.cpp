/*
** EXODIA PROJECT, 2023
** TryAGame
** File description:
** Level
*/

#include "Level.hpp"
#include "Tools/Random.hpp"

/*#include "Tools/Color.hpp"
#include "Tools/Collider.hpp"

#include <glm/gtc/matrix_transform.hpp>*/

using namespace Exodia;

namespace FlappyBird {

    //////////////////////////////
    // Constructor & Destructor //
    //////////////////////////////

    Level::Level() : _Scene(nullptr), _GameOver(false), _EditorCamera(30.0f, 1.778f, 0.1f, 1000.0f){};

    /////////////
    // Methods //
    /////////////

    void Level::OnUpdate(Timestep ts) {
        _mytime += ts;
        if (_Scene == nullptr)
            return;

        if (_Scene->GetEntityByName("SpaceShip").GetComponent<TransformComponent>().Translation.y < -10.0f) {
            _GameOver = true;
            return;
        }

        auto spike_haut = _Scene->GetEntityByName("spike_haut");
        auto spike_bas = _Scene->GetEntityByName("spike_bas");

        if (spike_haut != nullptr && spike_bas != nullptr) {

            float rand = Random::Float() * 7.0f - 4.0f;
            float diff = 7.0f;
            glm::vec4 color = {Random::Float(), Random::Float(), Random::Float(), 1};

            auto &ts_h = spike_haut.GetComponent<TransformComponent>();

            if (ts_h.Translation.x <
                _Scene->GetEntityByName("SpaceShip").GetComponent<TransformComponent>().Translation.x - 15.0f) {
                ts_h.Translation.x += 40.0f;
                ts_h.Translation.y = rand + diff;
                auto &sp_h = spike_haut.GetComponent<SpriteRendererComponent>();
                sp_h.Color = color;
            }


            auto &ts_b = spike_bas.GetComponent<TransformComponent>();

            if (ts_b.Translation.x <
                _Scene->GetEntityByName("SpaceShip").GetComponent<TransformComponent>().Translation.x - 15.0f) {
                ts_b.Translation.x += 40.0f;
                ts_b.Translation.y = rand - diff - 3.0f;
                auto &sp_b = spike_bas.GetComponent<SpriteRendererComponent>();
                sp_b.Color = color;
            }

        }

        auto spike_haut2 = _Scene->GetEntityByName("spike_haut2");
        auto spike_bas2 = _Scene->GetEntityByName("spike_bas2");

        if (spike_haut2 != nullptr && spike_bas2 != nullptr) {

            float rand2 = Random::Float() * 8.0f - 4.0f;
            float diff2 = 7.0f;
            glm::vec4 color = {Random::Float(), Random::Float(), Random::Float(), 1};

            auto &ts_h2 = spike_haut2.GetComponent<TransformComponent>();

            if (ts_h2.Translation.x <
                _Scene->GetEntityByName("SpaceShip").GetComponent<TransformComponent>().Translation.x - 15.0f) {
                ts_h2.Translation.x += 40.0f;
                ts_h2.Translation.y = rand2 + diff2;
                auto &sp_h2 = spike_haut2.GetComponent<SpriteRendererComponent>();
                sp_h2.Color = color;
            }


            auto &ts_b2 = spike_bas2.GetComponent<TransformComponent>();

            if (ts_b2.Translation.x <
                _Scene->GetEntityByName("SpaceShip").GetComponent<TransformComponent>().Translation.x - 15.0f) {
                ts_b2.Translation.x += 40.0f;
                ts_b2.Translation.y = rand2 - diff2 - 3.0f;
                auto &sp_b2 = spike_bas2.GetComponent<SpriteRendererComponent>();
                sp_b2.Color = color;
            }

        }

        _Scene->OnUpdateRuntime(ts);
    }

    void Level::OnRender(Timestep ts) {
        if (_Scene == nullptr)
            return;
        _EditorCamera.OnUpdate(ts);
        _Scene->OnUpdateEditor(ts, _EditorCamera);
    }

    void Level::Reset() {
        _GameOver = false;

        if (_Scene != nullptr) {
            _Scene->OnRuntimeStop();
            _Scene->OnRuntimeStart();
        }
    }

    void Level::Init() {
        _Scene = CreateRef<Scene>();

        PrefabsImporter::LoadPrefabs("Assets/Prefabs/FlappyBird.prefab", _Scene);
        PrefabsImporter::LoadPrefabs("Assets/Prefabs/obstacle.prefab", _Scene);

        auto spike_haut = _Scene->GetEntityByName("spike_haut");
        auto spike_bas = _Scene->GetEntityByName("spike_bas");

        if (spike_haut != nullptr && spike_bas != nullptr) {

            float rand = Random::Float() * 7.0f - 4.0f;
            float diff = 7.0f;
            glm::vec4 color = {Random::Float(), Random::Float(), Random::Float(), 1};

            auto &ts_h = spike_haut.GetComponent<TransformComponent>();
            ts_h.Translation.y = rand + diff;
            auto &sp_h = spike_haut.GetComponent<SpriteRendererComponent>();
            sp_h.Color = color;

            auto &ts_b = spike_bas.GetComponent<TransformComponent>();
            ts_b.Translation.y = rand - diff - 3.0f;
            auto &sp_b = spike_bas.GetComponent<SpriteRendererComponent>();
            sp_b.Color = color;

        }

        auto spike_haut2 = _Scene->GetEntityByName("spike_haut2");
        auto spike_bas2 = _Scene->GetEntityByName("spike_bas2");

        if (spike_haut2 != nullptr && spike_bas2 != nullptr) {

            float rand2 = Random::Float() * 8.0f - 4.0f;
            float diff2 = 7.0f;
            glm::vec4 color = {Random::Float(), Random::Float(), Random::Float(), 1};

            auto &ts_h2 = spike_haut2.GetComponent<TransformComponent>();

            ts_h2.Translation.y = rand2 + diff2;
            auto &sp_h2 = spike_haut2.GetComponent<SpriteRendererComponent>();
            sp_h2.Color = color;



            auto &ts_b2 = spike_bas2.GetComponent<TransformComponent>();
            ts_b2.Translation.y = rand2 - diff2 - 3.0f;
            auto &sp_b2 = spike_bas2.GetComponent<SpriteRendererComponent>();
            sp_b2.Color = color;

        }

        _Scene->OnViewportResize(Application::Get().GetWindow().GetWidth(), Application::Get().GetWindow().GetHeight());
    }

    void Level::Play() {
        if (_Scene == nullptr)
            return;
        _Scene->RegisterSystem(new ParticleSystem());
        _Scene->RegisterSystem(new GravitySystem());
        _Scene->RegisterSystem(new MovingSystem());

        // TODO: Flappy Collision System

        _Scene->OnRuntimeStart();
    }

    void Level::OnKeyPressed(int keyCode) {
        if (_Scene == nullptr)
            return;
        _Scene->OnKeyPressedEvent(keyCode);
    }

    ///////////////////////
    // Getters & Setters //
    ///////////////////////

    bool Level::IsGameOver() { return _GameOver; }

    // Level::Level() : _GameOver(false), _ObstacleTarget(30.0f), _ObstacleIndex(0), _ObstacleHSV({0.0f, 0.8f, 0.8f}){};

    /*void Level::Init() {
        AnimationComponent anim;

        std::vector<Ref<SubTexture2D>> frames;

        frames.push_back(SubTexture2D::CreateFromCoords(PLAYER, {0.0f, 0.0f}, {32.0f, 32.0f}, {1.0f, 1.0f}));

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
                    glm::scale(glm::mat4(1.0f), {obstacle.BottomScale.x, obstacle.BottomScale.y, 1.0f}) *
                    pillarVertices[i];
            }

            for (auto &vertex : playerTransformedVerts) {
                if (PointInTriangle({vertex.x, vertex.y}, triangle[0], triangle[1], triangle[2]))
                    return true;
            }
        }
        return false;
    }

    bool Level::IsGameOver() { return _GameOver; }

    Player &Level::GetPlayer() { return _Player; }*/

} // namespace FlappyBird