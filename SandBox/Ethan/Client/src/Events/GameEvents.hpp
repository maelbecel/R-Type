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

    // External includes
    #include <map>

namespace RType {

    enum PlayerEvent {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        ATTACK1,
        ATTACK2,
        UNKNOWN
    };

    inline static std::string PlayerEventToString(PlayerEvent event)
    {
        switch (event) {
            case UP:
                return "UP";
            case DOWN:
                return "DOWN";
            case LEFT:
                return "LEFT";
            case RIGHT:
                return "RIGHT";
            case ATTACK1:
                return "ATTACK1";
            case ATTACK2:
                return "ATTACK2";
            default:
                break;
        }
        return "UNKNOWN";
    }

    inline static PlayerEvent StringToPlayerEvent(const std::string &event)
    {
        if (event == "UP")
            return UP;
        if (event == "DOWN")
            return DOWN;
        if (event == "LEFT")
            return LEFT;
        if (event == "RIGHT")
            return RIGHT;
        if (event == "ATTACK1")
            return ATTACK1;
        if (event == "ATTACK2")
            return ATTACK2;
        return UNKNOWN;
    }

    inline static std::map<PlayerEvent, std::pair<int, int>> KeyBinds = {
        {UP     , {Exodia::Key::W    , Exodia::Key::UP   }},
        {DOWN   , {Exodia::Key::S    , Exodia::Key::DOWN }},
        {LEFT   , {Exodia::Key::A    , Exodia::Key::LEFT }},
        {RIGHT  , {Exodia::Key::D    , Exodia::Key::RIGHT}},
        {ATTACK1, {Exodia::Key::SPACE, Exodia::Key::Q    }},
        {ATTACK2, {Exodia::Key::E    , Exodia::Key::E    }}
    };
};

#endif /* !GAMEEVENTS_HPP_ */
