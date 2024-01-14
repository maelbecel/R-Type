/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** ExodiaEngine
*/

#include "RTypeLayer.hpp"
#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <sstream>

using namespace Exodia;

namespace RType {

    //////////////////////////////
    // Constructor & Destructor //
    //////////////////////////////

    RTypeLayer::RTypeLayer() : Layer("R-Type") {
        EXODIA_PROFILE_FUNCTION();

        _DeltaTime = 0.0f;
        _PoweredUp = false;
    }

    /////////////
    // Methods //
    /////////////

    void RTypeLayer::OnAttach() {
        EXODIA_PROFILE_FUNCTION();

        Renderer2D::SetLineWidth(4.0f);

        // Create world
        CurrentScene = GAME;

        CollisionSystem *collisionSystem = new CollisionSystem();

        Ref<Scene> scene = CreateRef<Scene>("Stage 1");

        SceneSerializer serializer(scene);

        serializer.Deserialize("./Assets/Scene/Stage_1.exodia");

        scene->RegisterSystem(new AnimationSystem());
        scene->RegisterSystem(new MovingSystem(1.5f));
        scene->RegisterSystem(new GravitySystem());
        scene->RegisterSystem(collisionSystem);
        scene->Subscribe<Exodia::Events::OnCollisionEntered>(collisionSystem);
        scene->OnViewportResize(Application::Get().GetWindow().GetWidth(), Application::Get().GetWindow().GetHeight());
        scene->Subscribe<Events::TakeDamage>(new TakeDamageSubscriber());

        // auto txt = text->AddComponent<TextRendererComponent>("\"From   the dark regions of space they\n came...Waging
        // war upon us.\n One saviour stood his ground while all\n others were crushed under the alien\n assaul t...\n\n
        // The Prototype Markl .\"");

        // Create the camera entity
        GameObject cameraEntity = scene->CreateEntity("Camera");

        CameraComponent &camera = cameraEntity.AddComponent<CameraComponent>();

        cameraEntity.GetComponent<TransformComponent>().Translation = {0.0f, 0.0f, 15.0f};

        camera.Camera.SetProjectionType(SceneCamera::ProjectionType::Perspective);
        camera.Camera.SetViewportSize(Application::Get().GetWindow().GetWidth(),
                                      Application::Get().GetWindow().GetHeight());

        // Create the player entity
        scene->LoadPrefabs((Project::GetActiveAssetDirectory() / "Prefabs/Player/Player.prefab").string(), true);

        // Create pata-pata

        // Create spawner patata
        GameObject mspawner = scene->CreateNewEntity("Spawner");
        mspawner.AddComponent<ScriptComponent>().Bind("MidSpawner");

        GameObject spawner = scene->CreateNewEntity("Spawner");
        spawner.AddComponent<ScriptComponent>().Bind("PataPataSpawner");

        // Create tabrok

        // Create Mid

        // Create Bug
        // GameObject bug = scene->CreateNewEntity("Bug");
        // bug.AddComponent<ScriptComponent>().Bind("Bug");

        // Create Module
        GameObject module = scene->CreateNewEntity("Module");
        module.AddComponent<ScriptComponent>().Bind("Module");
        // GameObject powerUp = scene->CreateNewEntity("Module");
        // powerUp.AddComponent<ScriptComponent>().Bind("PowerUp");

        // Create stars
        for (int i = 0; i < 60; i++) {
            GameObject star = scene->CreateNewEntity("Star" + std::to_string(i));

            star.AddComponent<ScriptComponent>().Bind("Star");
        }

        Scenes[CurrentScene] = scene;

        Scenes[CurrentScene]->OnRuntimeStart();
    }

    void RTypeLayer::OnDetach() { EXODIA_PROFILE_FUNCTION(); }

    void RTypeLayer::OnUpdate(Exodia::Timestep ts) {
        EXODIA_PROFILE_FUNCTION();

        Renderer2D::ResetStats();

        // Renderer Prep
        {
            EXODIA_PROFILE_SCOPE("Renderer Prep");

            Exodia::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
            Exodia::RenderCommand::Clear();
        }

        _DeltaTime += ts;

        // Update the world
        // if (_DeltaTime > 10.0 && _PoweredUp == false) {
        //     _PoweredUp = true;
        //     GameObject powerUp = Scenes[CurrentScene]->GetEntityByName("Module");
        //     Scenes[CurrentScene]->DestroyEntity(powerUp);

        //     GameObject powerUp2 = Scenes[CurrentScene]->CreateNewEntity("Module");
        //     powerUp2.GetComponent<ScriptComponent>().Bind("PowerUp");
        // }
        Scenes[CurrentScene]->OnUpdateRuntime(ts);
    }

    void RTypeLayer::OnImGUIRender() {
        EXODIA_PROFILE_FUNCTION();

#ifdef EXODIA_DEBUG
        ImGui::Begin("R-Type Statistics");
        ImGui::Text("FPS: %.1f", Application::Get().GetStatistics().FPS);
        ImGui::Text("Frame Time: %.3f ms", Application::Get().GetStatistics().FrameTime);
        ImGui::Text("Memory Usage: %ld KB", Application::Get().GetStatistics().MemoryUsage / 1024);
        ImGui::Separator();
        ImGui::Text("Renderer Statistics:");
        ImGui::Text("Draw Calls: %d", Renderer2D::GetStats().DrawCalls);
        ImGui::Text("Quad Count: %d", Renderer2D::GetStats().QuadCount);
        ImGui::Text("Vertex Count: %d", Renderer2D::GetStats().GetTotalVertexCount());
        ImGui::Text("Index Count: %d", Renderer2D::GetStats().GetTotalIndexCount());
        ImGui::Separator();
        ImGui::End();
#endif
    }

    void RTypeLayer::OnEvent(Exodia::Event &event) {
        EventDispatcher dispatcher(event);

        dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(RTypeLayer::OnKeyPressedEvent));
        dispatcher.Dispatch<KeyReleasedEvent>(BIND_EVENT_FN(RTypeLayer::OnKeyReleasedEvent));
        dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(RTypeLayer::OnWindowResizeEvent));
    }

    bool RTypeLayer::OnKeyPressedEvent(KeyPressedEvent &event) {

        int key = event.GetKeyCode();

        Scenes[CurrentScene]->OnKeyPressed(key);

        return true;
    };

    bool RTypeLayer::OnKeyReleasedEvent(KeyReleasedEvent &event) {
        int key = event.GetKeyCode();

        Scenes[CurrentScene]->OnKeyReleased(key);

        return false;
    };

    bool RTypeLayer::OnWindowResizeEvent(WindowResizeEvent &event) {
        if (Scenes[CurrentScene] != nullptr)
            Scenes[CurrentScene]->OnViewportResize(event.GetWidth(), event.GetHeight());

        return true;
    }
}; // namespace RType