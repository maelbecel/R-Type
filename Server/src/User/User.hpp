/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** User
*/

#ifndef USER_HPP_
#define USER_HPP_

#include "Exodia.hpp"

namespace Exodia {

    class User {
    
        public:

            User(Connection &connection, GameObject pawn = GameObject());
            ~User() = default;

            Connection GetConnection() const { return _Connection; }

            void SetConnection(Connection connection) { _Connection = connection; }

            GameObject GetPawn() const { return _Pawn; }

            void SetPawn(GameObject pawn) { _Pawn = pawn; }

        private:
            Connection _Connection;
            GameObject _Pawn;
    };
};

#endif /* !USER_HPP_ */
