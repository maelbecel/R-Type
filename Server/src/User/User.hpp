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
        User(Connection &connection);
        User(Connection &connection, Entity *pawn);
        ~User();

        Connection GetConnection() const { return _Connection; }

        void SetConnection(Connection connection) { _Connection = connection; }

        Entity *GetPawn() const { return _Pawn; }

        void SetPawn(Entity *pawn) { _Pawn = pawn; }

      protected:
      private:
        Connection _Connection;
        Entity *_Pawn;
    };
};     // namespace Exodia
#endif /* !USER_HPP_ */
