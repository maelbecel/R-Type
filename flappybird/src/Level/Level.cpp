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

    /**
     * The Level constructor initializes the member variables _Scene, _GameOver, and _EditorCamera.
     */
    Level::Level() : _Scene(nullptr), _GameOver(false), _EditorCamera(30.0f, 1.778f, 0.1f, 1000.0f){};

    /////////////
    // Methods //
    /////////////

    /**
     * The function updates the game level by moving spikes and updating the score based on the
     * position of the spaceship.
     *
     * @param ts The parameter "ts" in the above code represents the timestep, which is the amount of
     * time that has passed since the last update. It is used to update the game logic and perform
     * calculations based on the elapsed time.
     *
     * @return In this code, nothing is being returned. The return statement is used to exit the
     * function early if certain conditions are met, but it does not return any value.
     */
    void Level::OnUpdate(Timestep ts) {
        _mytime += ts;
        if (_Scene == nullptr)
            return;

        Exodia::GameObject ship = nullptr;
        ship = _Scene->GetEntityByName("SpaceShip");
        if (ship == nullptr)
            return;

        score = (ship.GetComponent<TransformComponent>().Translation.x) / 20.0f;

        auto spike_haut = _Scene->GetEntityByName("spike_haut");
        auto spike_bas = _Scene->GetEntityByName("spike_bas");

        if (spike_haut != nullptr && spike_bas != nullptr) {

            float rand = Random::Float() * 8.0f - 4.0f;
            float diff = 8.5f;
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
            float diff2 = 8.5f;
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

    /**
     * The function `OnRender` updates the editor camera and calls the `OnUpdateEditor` function of the
     * scene with the given timestep and editor camera.
     *
     * @param ts The parameter "ts" is of type "Timestep". It is likely a time step value that
     * represents the elapsed time since the last frame. It is used to update the editor camera and the
     * scene in the OnUpdateEditor function.
     *
     * @return If the `_Scene` is `nullptr`, then the function will return and no further code will be
     * executed.
     */
    void Level::OnRender(Timestep ts) {
        if (_Scene == nullptr)
            return;
        _EditorCamera.OnUpdate(ts);
        _Scene->OnUpdateEditor(ts, _EditorCamera);
    }

    /**
     * The Reset function resets the level by setting the _GameOver flag to false, stopping the runtime
     * of the scene, destroying all entities, initializing the level, and starting the runtime of the
     * scene again.
     */
    void Level::Reset() {
        _GameOver = false;

        if (_Scene != nullptr) {
            _Scene->OnRuntimeStop();
            _Scene->DestroyAllEntities();
            this->Init();
            _Scene->OnRuntimeStart();
        }
    }

    /**
     * The function initializes the level by loading prefabs, setting the position and color of spike
     * entities, and resizing the viewport.
     */
    void Level::Init() {
        _Scene = CreateRef<Scene>();

        PrefabsImporter::LoadPrefabs("Assets/Prefabs/FlappyBird.prefab", _Scene);
        PrefabsImporter::LoadPrefabs("Assets/Prefabs/Camera.prefab", _Scene);
        PrefabsImporter::LoadPrefabs("Assets/Prefabs/obstacle.prefab", _Scene);

        auto spike_haut = _Scene->GetEntityByName("spike_haut");
        auto spike_bas = _Scene->GetEntityByName("spike_bas");

        if (spike_haut != nullptr && spike_bas != nullptr) {

            float rand = Random::Float() * 8.0f - 4.0f;
            float diff = 8.5f;
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
            float diff2 = 8.5f;
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

    /**
     * The Play function sets up and initializes various systems and event subscriptions for a game
     * level.
     *
     * @return In the given code, if `_Scene` is `nullptr`, the function will return without executing
     * the rest of the code.
     */
    void Level::Play() {
        if (_Scene == nullptr)
            return;

        auto colision = new CollisionSystem();

        _Scene->RegisterSystem(new ParticleSystem());
        _Scene->RegisterSystem(new GravitySystem());
        _Scene->RegisterSystem(new MovingSystem());
        _Scene->RegisterSystem(colision);

        _Scene->Subscribe<Events::OnCollisionEntered>(colision);
        _Scene->Subscribe<Events::OnEntityDestroyed>(this);

        // TODO: Flappy Collision System

        _Scene->OnRuntimeStart();
    }

    /**
     * The function OnKeyPressed in the Level class checks if the scene is not null and then calls the
     * OnKeyPressedEvent function of the scene with the provided keyCode.
     *
     * @param keyCode The keyCode parameter represents the code of the key that was pressed on the
     * keyboard. It is an integer value that uniquely identifies each key on the keyboard.
     *
     * @return nothing (void).
     */
    void Level::OnKeyPressed(int keyCode) {
        if (_Scene == nullptr)
            return;
        _Scene->OnKeyPressedEvent(keyCode);
    }

    ///////////////////////
    // Getters & Setters //
    ///////////////////////

    /**
     * The function returns a boolean value indicating whether the game is over or not.
     *
     * @return The IsGameOver() function returns the value of the _GameOver variable.
     */
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