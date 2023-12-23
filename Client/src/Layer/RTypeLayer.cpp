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

                // TODO: Update Scripts...
            } else {
                if (key == Key::ENTER) {
                    _Scenes[RType::SceneType::GAME].first = RType::SceneState::RUNNING;

                    _Scenes[RType::SceneType::GAME].second->RegisterSystem(new Exodia::MovingSystem());

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
