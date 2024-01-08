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

    void MenuScene::OnCreate() {
        // -- Creating the scene -- //
        _Scene = CreateRef<Scene>("Menu");

        SceneSerializer serializer(_Scene);

        serializer.Deserialize("./Assets/Scene/Menu/Menu.exodia");

        // -- Scene System -- //
        _Scene->RegisterSystem(new AnimationSystem());
        _Scene->RegisterSystem(new FadeSystem());
        _Scene->RegisterSystem(new ParticleSystem());
        _Scene->RegisterSystem(new MovingSystem());

        // -- Resizing the viewport -- //
        _Scene->OnViewportResize(Application::Get().GetWindow().GetWidth(), Application::Get().GetWindow().GetHeight());

        // -- Start the scene -- //
        _Scene->OnRuntimeStart();

        // -- Add Fade in transition to all entities -- //
        GiveFadeEffect();
    }

    void MenuScene::OnDestroy() { _Scene->OnRuntimeStop(); }

    void MenuScene::OnUpdate(Timestep ts) { _Scene->OnUpdateRuntime(ts); }

    void MenuScene::OnEvent(Event &event) {
        EventDispatcher dispatcher(event);

        dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(MenuScene::OnKeyPressedEvent));
    }

    void MenuScene::GiveFadeEffect(bool in) {
        for (Entity *entity : _Scene->GetWorldPtr()->AllEntities()) {
            auto fade = entity->GetComponent<FadeComponent>();

            if (!fade)
                fade = entity->AddComponent<FadeComponent>();
            auto &fc = fade.Get(); // fc = Fade Component

            fc.Opacity = 0.0f;
            fc.FadeInSpeed = 0.4f;
            fc.FadeOutSpeed = 0.4f;
            fc.ShouldFadeIn = in;
            fc.ShouldFadeOut = !in;
            fc.Repeat = false;
        }
    }

    bool MenuScene::OnKeyPressedEvent(KeyPressedEvent &event) {
        /*GameObject menuHandler = _Scene->GetEntityByName("MenuHandler");

        if (menuHandler.GetEntity()) {
            auto &script = menuHandler.GetComponent<ScriptComponent>();

            if (script.Instance != nullptr) {
                script.Instance->OnKeyPressed(event.GetKeyCode());

                return true;
            }
        }
        return false;*/

        _Scene->GetWorldPtr()->ForEach<ScriptComponent>([&](Entity *entity, auto script) {
            auto &sc = script.Get(); // sc = Script Component

            if (sc.Instance != nullptr)
                sc.Instance->OnKeyPressed(event.GetKeyCode());

            (void)entity;
        });

        return true;
    }
}; // namespace RType
