/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** User
*/

#include "User.hpp"

namespace Exodia {

    User::User(Connection &connection)
    {
        _Connection = connection;
        _Pawn = nullptr;
    }

    User::User(Connection &connection, Entity *pawn)
    {
        _Connection = connection;
        _Pawn = pawn;
    }

    User::~User()
    {
    }
}

