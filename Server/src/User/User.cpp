/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** User
*/

#include "User.hpp"

namespace Exodia {

    User::User(std::shared_ptr<Connection> connection) {
        _Connection = connection;
        _Pawn = nullptr;
    }

    User::User(std::shared_ptr<Connection> connection, Entity *pawn) {
        _Connection = connection;
        _Pawn = pawn;
    }

    User::~User() {}
} // namespace Exodia
