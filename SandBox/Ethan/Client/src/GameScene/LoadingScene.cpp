/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** LoadingScene
*/

// R-Type Client includes
#include "LoadingScene.hpp"

// R-Type Games includes
#include "R-Type.hpp"
#include "Layer/GameLayer.hpp"
#include "Events/Transition.hpp"

namespace RType {

    using namespace Exodia;

    /////////////
    // Methods //
    /////////////

    void LoadingScene::OnCreate()
    {
        _Scene = CreateRef<Scene>("Intro");

        SceneSerializer serializer(_Scene);

        serializer.Deserialize("./Assets/Scene/Loading/Loading.exodia");

        // -- Scene System -- //
        _Scene->RegisterSystem(new AnimationSystem());
        _Scene->RegisterSystem(new FadeSystem());

        // -- Event Subscribe -- //
        _Scene->Subscribe<Events::FadeOutEndEvent>(new Transition());

        // -- Resizing the viewport -- //
        _Scene->OnViewportResize(Application::Get().GetWindow().GetWidth(), Application::Get().GetWindow().GetHeight());

        // -- Start the scene -- //
        _Scene->OnRuntimeStart();
    }

    void LoadingScene::OnDestroy()
    {
        _Scene->OnRuntimeStop();
    }

    void LoadingScene::OnUpdate(Timestep ts)
    {
        if (_Scene->IsRunning())
            _Scene->OnUpdateRuntime(ts);
    }

    void LoadingScene::OnEvent(Event &event)
    {
        EventDispatcher dispatcher(event);

        dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(LoadingScene::OnKeyPressedEvent));
    }

    bool LoadingScene::OnKeyPressedEvent(KeyPressedEvent &event)
    {
        int key = event.GetKeyCode();

        if (key == Key::ENTER) {
            Entity *background = _Scene->GetEntityByName("LoadingBackground");

            if (background) {
                auto script = background->GetComponent<ScriptComponent>();

                if (script && script.Get().Instance != nullptr) {
                    script.Get().Instance->OnKeyPressed(key);

                    return true;
                }
            }
        }
        return false;
    }
};
