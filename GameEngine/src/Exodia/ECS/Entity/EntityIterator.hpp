/*
** EPITECH PROJECT, 2023
** ECS
** File description:
** EntityIterator
*/

#ifndef ENTITYITERATOR_HPP_
#define ENTITYITERATOR_HPP_

// Exodia Utils includes
#include "Utils/CrossPlatform.hpp"

// External includes
#include <cstddef>

namespace Exodia {

    class World;
    class Entity;

    class EntityIterator {

        /////////////////
        // Constructor //
        /////////////////
      public:
        EntityIterator(World *world, size_t index, bool isEnd, bool includePendingDestroy);

        ///////////////////////
        // Getters & Setters //
        ///////////////////////
      public:
        size_t GetIndex() const;

        bool IsEnd() const;

        bool IncludePendingDestroy() const;

        World *GetWorld() const;

        Entity *Get() const;

        ///////////////
        // Operators //
        ///////////////
      public:
        Entity *operator*() const;

        EntityIterator &operator++();

        ////////////////
        // Comparator //
        ////////////////
      public:
        bool operator==(const EntityIterator &other) const;
        bool operator!=(const EntityIterator &other) const;

        ////////////////
        // Attributes //
        ////////////////
      private:
        Exodia::World *_World;
        size_t _Index;
        bool _IsEnd;
        bool _IncludePendingDestroy;
    };
}; // namespace Exodia

#endif /* !ENTITYITERATOR_HPP_ */
