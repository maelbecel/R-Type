/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** PlayrEvents
*/

#ifndef PLAYER_EVENTS_HPP
    #define PLAYER_EVENTS_HPP

    // External includes
    #include <string>

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
};

#endif /* !PLAYER_EVENTS_HPP */
