/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** FadeEvent
*/

#ifndef FADEEVENT_HPP_
#define FADEEVENT_HPP_

// Exodia includes
#include "Exodia.hpp"

namespace RType::Events {

    struct FadeOutEndEvent {
        Exodia::Entity *Entity;
    };
}; // namespace RType::Events

#endif /* !FADEEVENT_HPP_ */
