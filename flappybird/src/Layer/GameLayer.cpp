/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** ExodiaEngine
*/

#include "GameLayer.hpp"
#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <sstream>

using namespace Exodia;

namespace FlappyBird {

    //////////////////////////////
    // Constructor & Destructor //
    //////////////////////////////

    GameLayer::GameLayer() : Layer("R-Type"){};

    /////////////
    // Methods //
    /////////////

    void GameLayer::OnAttach() {
        EXODIA_PROFILE_FUNCTION();

        // Create world
        CurrentScene = GameState::Menu;

        CollisionSystem *collisionSystem = new CollisionSystem();

        Scenes[CurrentScene] = CreateRef<Scene>();
        // Scenes[CurrentScene]->RegisterSystem(new AnimationSystem());
        Scenes[CurrentScene]->RegisterSystem(new MovingSystem(1.5f));
        Scenes[CurrentScene]->RegisterSystem(collisionSystem);
        Scenes[CurrentScene]->Subscribe<Exodia::Events::OnCollisionEntered>(collisionSystem);
        Scenes[CurrentScene]->OnViewportResize(Application::Get().GetWindow().GetWidth(),
                                                  Application::Get().GetWindow().GetHeight());

        // Create the camera entity
        GameObject cameraEntity = Scenes[CurrentScene]->CreateEntity("Camera");

        CameraComponent &camera = cameraEntity.AddComponent<CameraComponent>();

        cameraEntity.GetComponent<TransformComponent>().Translation = {0.0f, 0.0f, 15.0f};

        camera.Camera.SetProjectionType(SceneCamera::ProjectionType::Perspective);
        camera.Camera.SetViewportSize(Application::Get().GetWindow().GetWidth(),
                                      Application::Get().GetWindow().GetHeight());

        /*RType::EntityEventSubscriber *subscribe = new RType::EntityEventSubscriber(*_Network);

        Scenes[GAME]->Subscribe<Events::OnEntityCreated>(subscribe);
        Scenes[GAME]->Subscribe<Events::OnEntityDestroyed>(subscribe);*/

        /* Removing rigid body for static camera
        auto body_camera = cameraEntity->AddComponent<RigidBody2DComponent>();
        body_camera.Get().Type = RigidBody2DComponent::BodyType::Dynamic;
        body_camera.Get().Mass = 0.0f;
        body_camera.Get().GravityScale = 0.0f;
        body_camera.Get().Velocity = glm::vec2{ 1.5f, 0.0f };
        */

        // Create the entities
        // TODO: Ask server for playerID
        int playerID = 0;
        GameObject entity = Scenes[CurrentScene]->CreateEntity("Player_" + std::to_string(playerID));
        entity.AddComponent<ScriptComponent>().Bind("Player");

        // Create pata-pata
        // Entity *patata = Scenes[GAME]->CreateEntity("Pata-pata");
        // patata->AddComponent<ScriptComponent>().Get().Bind("PataPata");

        // Create stars
        // CreateStars(Scenes);
        // for (int i = 0; i < 60; i++) {
        //     GameObject star = Scenes[CurrentScene]->CreateEntity("Star" + std::to_string(i));

        //     star.AddComponent<ScriptComponent>().Bind("Star");
        // }

        // Create the camera
        Scenes[CurrentScene]->OnRuntimeStart();
    }

    void GameLayer::OnDetach() { EXODIA_PROFILE_FUNCTION(); }

    void GameLayer::OnUpdate(Exodia::Timestep ts) {
        EXODIA_PROFILE_FUNCTION();
        // Renderer Prep
        {
            EXODIA_PROFILE_SCOPE("Renderer Prep");

            Exodia::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
            Exodia::RenderCommand::Clear();
        }

        // Update
        if (CurrentScene == GameState::Menu) {
        };

        // Update the world
        Scenes[CurrentScene]->OnUpdateRuntime(ts);
    }

    void GameLayer::OnImGUIRender() { EXODIA_PROFILE_FUNCTION(); }

    void GameLayer::OnEvent(Exodia::Event &event) {
        EventDispatcher dispatcher(event);

        dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(GameLayer::OnKeyPressedEvent));
        dispatcher.Dispatch<KeyReleasedEvent>(BIND_EVENT_FN(GameLayer::OnKeyReleasedEvent));
        dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(GameLayer::OnWindowResizeEvent));
    }

    bool GameLayer::OnKeyPressedEvent(KeyPressedEvent &event) {

        int key = event.GetKeyCode();
        (void)key;

        return true;
    };

    bool GameLayer::OnKeyReleasedEvent(KeyReleasedEvent &event) {
        int key = event.GetKeyCode();
        (void)key;
        return false;
    };

    bool GameLayer::OnWindowResizeEvent(WindowResizeEvent &event) {
        if (Scenes[CurrentScene] != nullptr)
            Scenes[CurrentScene]->OnViewportResize(event.GetWidth(), event.GetHeight());

        return true;
    }
}; // namespace FlappyBird
