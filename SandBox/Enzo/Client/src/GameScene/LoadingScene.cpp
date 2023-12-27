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

namespace RType {

    using namespace Exodia;

    /////////////
    // Methods //
    /////////////

    void LoadingScene::OnCreate()
    {
        _Scene = CreateRef<Scene>("Intro");

        SceneSerializer serializer(_Scene);

        serializer.Deserialize("./Assets/Scene/Loading.exodia");

        // -- Scene System -- //
        _Scene->RegisterSystem(new AnimationSystem());
        _Scene->RegisterSystem(new FadeSystem());

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
            // -- Stop the scene -- //
            // -- Go to the next scene -- //

            _Scene->OnRuntimeStop();
            return true;
        }
        return false;
    }
};
