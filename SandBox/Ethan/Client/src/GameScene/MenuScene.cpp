/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** MenuScene
*/

// R-Type Client includes
#include "MenuScene.hpp"

// R-Type Games includes
#include "R-Type.hpp"
#include "Layer/GameLayer.hpp"

namespace RType {

    using namespace Exodia;

    /////////////
    // Methods //
    /////////////

    void MenuScene::OnCreate()
    {
        // -- Creating the scene -- //
        _Scene = CreateRef<Scene>("Menu");

        SceneSerializer serializer(_Scene);

        serializer.Deserialize("./Assets/Scene/Menu/Menu.exodia");

        // -- Scene System -- //
        _Scene->RegisterSystem(new AnimationSystem());
        _Scene->RegisterSystem(new FadeSystem());

        // -- Resizing the viewport -- //
        _Scene->OnViewportResize(Application::Get().GetWindow().GetWidth(), Application::Get().GetWindow().GetHeight());

        // -- Start the scene -- //
        _Scene->OnRuntimeStart();
    }

    void MenuScene::OnDestroy()
    {
        _Scene->OnRuntimeStop();
    }

    void MenuScene::OnUpdate(Timestep ts)
    {
        _Scene->OnUpdateRuntime(ts);
    }

    void MenuScene::OnEvent(Event &event)
    {
        EventDispatcher dispatcher(event);

        dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(MenuScene::OnKeyPressedEvent));
    }

    bool MenuScene::OnKeyPressedEvent(KeyPressedEvent &event)
    {
        Entity *menuHandler = _Scene->GetEntityByName("MenuHandler");

        if (menuHandler) {
            auto script = menuHandler->GetComponent<ScriptComponent>();

            if (script && script.Get().Instance != nullptr) {
                script.Get().Instance->OnKeyPressed(event.GetKeyCode());

                return true;
            }
        }
        return false;
    }
};
