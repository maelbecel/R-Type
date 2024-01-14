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
        GameObject ship = _Scene->GetEntityByName("SpaceShip");

        if (!ship)
            return;
        score = (ship.GetComponent<TransformComponent>().Translation.x) / 20.0f;

        GameObject spike_haut = _Scene->GetEntityByName("spike_haut");
        GameObject spike_bas = _Scene->GetEntityByName("spike_bas");

        if (spike_haut && spike_bas) {
            float rand = Random::Float() * 8.0f - 4.0f;
            float diff = 8.5f;
            glm::vec4 color = {Random::Float(), Random::Float(), Random::Float(), 1};

            auto &ts_h = spike_haut.GetComponent<TransformComponent>();

            if (ts_h.Translation.x < ship.GetComponent<TransformComponent>().Translation.x - 15.0f) {
                ts_h.Translation.x += 40.0f;
                ts_h.Translation.y = rand + diff;

                auto &sp_h = spike_haut.GetComponent<SpriteRendererComponent>();
                sp_h.Color = color;
            }

            auto &ts_b = spike_bas.GetComponent<TransformComponent>();

            if (ts_b.Translation.x < ship.GetComponent<TransformComponent>().Translation.x - 15.0f) {
                ts_b.Translation.x += 40.0f;
                ts_b.Translation.y = rand - diff - 3.0f;
                auto &sp_b = spike_bas.GetComponent<SpriteRendererComponent>();
                sp_b.Color = color;
            }
        }

        GameObject spike_haut2 = _Scene->GetEntityByName("spike_haut2");
        GameObject spike_bas2 = _Scene->GetEntityByName("spike_bas2");

        if (spike_haut2 && spike_bas2) {
            float rand2 = Random::Float() * 8.0f - 4.0f;
            float diff2 = 8.5f;
            glm::vec4 color = {Random::Float(), Random::Float(), Random::Float(), 1};

            auto &ts_h2 = spike_haut2.GetComponent<TransformComponent>();

            if (ts_h2.Translation.x < ship.GetComponent<TransformComponent>().Translation.x - 15.0f) {
                ts_h2.Translation.x += 40.0f;
                ts_h2.Translation.y = rand2 + diff2;
                auto &sp_h2 = spike_haut2.GetComponent<SpriteRendererComponent>();
                sp_h2.Color = color;
            }

            auto &ts_b2 = spike_bas2.GetComponent<TransformComponent>();

            if (ts_b2.Translation.x < ship.GetComponent<TransformComponent>().Translation.x - 15.0f) {
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

        _Scene->LoadPrefabs("Assets/Prefabs/FlappyBird.prefab");
        _Scene->LoadPrefabs("Assets/Prefabs/Camera.prefab");
        _Scene->LoadPrefabs("Assets/Prefabs/spike_bas2.prefab");
        _Scene->LoadPrefabs("Assets/Prefabs/spike_bas.prefab");
        _Scene->LoadPrefabs("Assets/Prefabs/spike_haut.prefab");
        _Scene->LoadPrefabs("Assets/Prefabs/spike_haut2.prefab");

        GameObject spike_haut = _Scene->GetEntityByName("spike_haut");
        GameObject spike_bas = _Scene->GetEntityByName("spike_bas");

        if (spike_haut && spike_bas) {
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

        GameObject spike_haut2 = _Scene->GetEntityByName("spike_haut2");
        GameObject spike_bas2 = _Scene->GetEntityByName("spike_bas2");

        if (spike_haut2 && spike_bas2) {
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
        _Scene->OnKeyPressed(keyCode);
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
}; // namespace FlappyBird
