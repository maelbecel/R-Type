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
        User(std::shared_ptr<Connection> connection);
        User(std::shared_ptr<Connection> connection, Entity *pawn);
        ~User();

        std::shared_ptr<Connection> GetConnection() const { return _Connection; }

        void SetConnection(std::shared_ptr<Connection> connection) { _Connection = connection; }

        Entity *GetPawn() const { return _Pawn; }

        void SetPawn(Entity *pawn) { _Pawn = pawn; }

      protected:
      private:
        std::shared_ptr<Connection> _Connection;
        Entity *_Pawn;
    };
};     // namespace Exodia
#endif /* !USER_HPP_ */
