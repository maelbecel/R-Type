/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** GameEvents
*/

#ifndef GAMEEVENTS_HPP_
    #define GAMEEVENTS_HPP_

    // Exodia includes
    #include "Exodia.hpp"

    // R-Type includes
    #include "R-Type.hpp"

    // External includes
    #include <map>

namespace RType {

    inline static std::map<RType::PlayerEvent, std::pair<int, int>> KeyBinds = {
        {PlayerEvent::UP     , {Exodia::Key::W    , Exodia::Key::UP   }},
        {PlayerEvent::DOWN   , {Exodia::Key::S    , Exodia::Key::DOWN }},
        {PlayerEvent::LEFT   , {Exodia::Key::A    , Exodia::Key::LEFT }},
        {PlayerEvent::RIGHT  , {Exodia::Key::D    , Exodia::Key::RIGHT}},
        {PlayerEvent::ATTACK1, {Exodia::Key::SPACE, Exodia::Key::Q    }},
        {PlayerEvent::ATTACK2, {Exodia::Key::E    , Exodia::Key::E    }}
    };
};

#endif /* !GAMEEVENTS_HPP_ */
