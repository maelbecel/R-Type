/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** MenuHander
*/

#include "MenuHandler.hpp"

namespace RType {

    using namespace Exodia;

    /////////////
    // Methods //
    /////////////

    void MenuHandler::OnKeyPressed(int keycode) {
        if (keycode == Key::UP) {
            //...
        } else if (keycode == Key::DOWN) {
            //...
        } else if (keycode == Key::LEFT) {
            //...
        } else if (keycode == Key::RIGHT) {
            //...
        } else if (keycode == Key::ENTER) {
            //...
        } else if (keycode == Key::ESCAPE) {
            if (_CurrentPages == 0)
                Application::Get().Close();
            else
                _CurrentPages = 0;
        }
    }
}; // namespace RType
