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

    void MenuScene::OnCreate(){};

    void MenuScene::OnDestroy(){};

    void MenuScene::OnUpdate(UNUSED(Timestep ts)) { EXODIA_INFO("MenuScene::OnUpdate"); }

    void MenuScene::OnEvent(Event &event) {
        EventDispatcher dispatcher(event);

        dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(MenuScene::OnKeyPressedEvent));
    }

    bool MenuScene::OnKeyPressedEvent(KeyPressedEvent &event) {
        int key = event.GetKeyCode();

        (void)key;

        return false;
    }
}; // namespace RType
