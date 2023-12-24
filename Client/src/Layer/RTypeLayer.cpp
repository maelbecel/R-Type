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

namespace Exodia {

    //////////////////////////////
    // Constructor & Destructor //
    //////////////////////////////

    RTypeLayer::RTypeLayer() : Layer("R-Type"), _CurrentScene(RType::SceneType::MENU), _WaitingCamera(35.0f, 1.778f, 0.1f, 1000.0f) {};

    /////////////
    // Methods //
    /////////////

    void RTypeLayer::OnAttach()
    {
        _Scenes.insert(std::make_pair(RType::SceneType::MENU, std::make_pair(RType::SceneState::RUNNING, CreateRef<Scene>("Menu"))));
        _Scenes.insert(std::make_pair(RType::SceneType::GAME, std::make_pair(RType::SceneState::PAUSED, nullptr)));

        _WaitingCamera.SetViewportSize(Exodia::Application::Get().GetWindow().GetWidth(), Exodia::Application::Get().GetWindow().GetHeight());

        Renderer2D::SetLineWidth(4.0f);
    }

    void RTypeLayer::OnDetach() {};

    void RTypeLayer::OnUpdate(Exodia::Timestep ts)
    {
        EXODIA_PROFILE_FUNCTION();

        // Renderer Prep
        {
            Exodia::RenderCommand::SetClearColor({ 0.0f, 0.0f, 0.0f, 1 });
            Exodia::RenderCommand::Clear();
        }

        // Render Scene
        {
            if (_CurrentScene == RType::SceneType::MENU) {};

            if (_CurrentScene == RType::SceneType::GAME) {
                if (_Scenes[RType::SceneType::GAME].first == RType::SceneState::RUNNING) {
                    _Scenes[RType::SceneType::GAME].second->OnUpdateRuntime(ts);

                    Entity *camera = _Scenes[RType::SceneType::GAME].second->GetPrimaryCamera();

                    if (!camera)
                        return;

                    Renderer2D::BeginScene(camera->GetComponent<CameraComponent>().Get().Camera, camera->GetComponent<TransformComponent>().Get().GetTransform());

                    _Scenes[RType::SceneType::GAME].second->ForEach<TransformComponent, BoxCollider2DComponent>([&](Entity *entity, auto transform, auto box) {
                        (void)entity;

                        auto &tc = transform.Get();
                        auto &bc = box.Get();

                        glm::vec3 translation = tc.Translation + glm::vec3(bc.Offset, 0.001f);
                        glm::vec3 scale       = tc.Scale       * glm::vec3(bc.Size * 2.0f, 1.0f);

                        glm::mat4 transformMatrix = glm::translate(glm::mat4(1.0f), translation) * glm::rotate(glm::mat4(1.0f), tc.Rotation.z , glm::vec3(0.0f, 0.0f, 1.0f)) * glm::scale(glm::mat4(1.0f), scale);

                        if (bc.ColliderMask & 000001)
                            Renderer2D::DrawRect(transformMatrix, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
                        if (bc.ColliderMask & 000010)
                            Renderer2D::DrawRect(transformMatrix, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
                    });

                    Renderer2D::EndScene();
                } else {
                    _WaitingCamera.OnUpdate(ts);

                    _Scenes[RType::SceneType::GAME].second->OnUpdateEditor(ts, _WaitingCamera);
                }
            }
        }
    }

    void RTypeLayer::OnEvent(Exodia::Event &event)
    {
        EventDispatcher dispatcher(event);

        dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(RTypeLayer::OnKeyPressedEvent));
        dispatcher.Dispatch<KeyReleasedEvent>(BIND_EVENT_FN(RTypeLayer::OnKeyReleasedEvent));
        dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(RTypeLayer::OnWindowResizeEvent));
    }

    bool RTypeLayer::OnKeyPressedEvent(KeyPressedEvent &event)
    {
        int key = event.GetKeyCode();

        if (_CurrentScene == RType::SceneType::MENU) {
            _CurrentScene = RType::SceneType::GAME;

            Ref<Scene> scene = CreateRef<Scene>("Stage 1");

            SceneSerializer serializer(scene);

            serializer.Deserialize("./Assets/Scene/Stage_1.exodia");

            _Scenes[RType::SceneType::GAME].second = scene;

            // TODO: .. Connect to server and create room
        } else if (_CurrentScene == RType::SceneType::GAME) {
            if (_Scenes[RType::SceneType::GAME].first == RType::SceneState::RUNNING) {
                _Scenes[RType::SceneType::GAME].second->ForEach<ScriptComponent>([&](Entity *entity, auto script) {
                    auto &sc = script.Get();

                    if (sc.Instance)
                        sc.Instance->OnKeyPressed(key);
                    (void)entity;
                });
            } else {
                if (key == Key::ENTER) {
                    _Scenes[RType::SceneType::GAME].first = RType::SceneState::RUNNING;

                    _Scenes[RType::SceneType::GAME].second->RegisterSystem(new Exodia::MovingSystem());
                    _Scenes[RType::SceneType::GAME].second->RegisterSystem(new Exodia::CollisionSystem());

                    // -- TEMP -----
                    Entity *entity = _Scenes[RType::SceneType::GAME].second->CreateEntity("Player");

                    entity->AddComponent<Health>(1);
                    entity->AddComponent<ScriptComponent>().Get().Bind("Player");
                    entity->AddComponent<Animation>(1.0f, 2.0f, 0.1f);
                    entity->GetComponent<TransformComponent>().Get().Scale.y = 0.5f;
                    entity->AddComponent<BoxCollider2DComponent>().Get().ColliderMask = 000010;

                    // Set entity sprite
                    auto sprite = entity->AddComponent<SpriteRendererComponent>();
                    sprite.Get().Texture = SubTexture2D::CreateFromCoords(12345678901234578, { 2.0f, 4.0f }, { 33.2f, 17.2f }, { 1.0f, 1.0f });

                    // Set entity rigidbody
                    auto body = entity->AddComponent<RigidBody2DComponent>();

                    body.Get().Type = RigidBody2DComponent::BodyType::Dynamic;
                    body.Get().GravityScale = 0.0f;
                    // --------

                    _Scenes[RType::SceneType::GAME].second->OnRuntimeStart();
                    _Scenes[RType::SceneType::GAME].second->OnViewportResize(Exodia::Application::Get().GetWindow().GetWidth(), Exodia::Application::Get().GetWindow().GetHeight());
                }
            }
        }
        return true;
    }

    bool RTypeLayer::OnKeyReleasedEvent(UNUSED(KeyReleasedEvent &event))
    {
        return true;
    }

    bool RTypeLayer::OnWindowResizeEvent(WindowResizeEvent &event)
    {
        int width = event.GetWidth();
        int height = event.GetHeight();

        _WaitingCamera.SetViewportSize(width, height);

        if (_CurrentScene == RType::SceneType::MENU)
            _Scenes[RType::SceneType::MENU].second->OnViewportResize(width, height);
        else if (_CurrentScene == RType::SceneType::GAME)
            _Scenes[RType::SceneType::GAME].second->OnViewportResize(width, height);

        return true;
    }
};
