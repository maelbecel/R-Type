/*
** EPITECH PROJECT, 2023
** ECS
** File description:
** EntityComponentIterator
*/

#ifndef ENTITYCOMPONENTITERATOR_HPP_
    #define ENTITYCOMPONENTITERATOR_HPP_

    // Exodia Utils includes
    #include "Utils/CrossPlatform.hpp"

namespace Exodia {

    class World;

    template<typename ...Components>
    class EXODIA_API EntityComponentIterator {

        /////////////////
        // Constructor //
        /////////////////
        public:

            EntityComponentIterator(World *world, size_t index, bool isEnd, bool includePendingDestroy);

        ///////////////////////
        // Getters & Setters //
        ///////////////////////
        public:

            size_t GetIndex() const
            {
                return _Index;
            }

            bool IsEnd() const;

            bool IncludePendingDestroy() const
            {
                return _IncludePendingDestroy;
            }

            World *GetWorld() const
            {
                return _World;
            }

            Entity *Get() const;

        ///////////////
        // Operators //
        ///////////////
        public:

            Entity *operator*() const
            {
                return Get();
            }

            EntityComponentIterator<Components ...> &operator++();

        /////////////////
        // Comparators //
        /////////////////
        public:

            bool operator==(const EntityComponentIterator<Components ...> &other) const
            {
                return _World == other._World && IsEnd() == other.IsEnd() && _Index == other._Index;
            }

            bool operator!=(const EntityComponentIterator<Components ...> &other) const
            {
                return !(*this == other);
            }

        ////////////////
        // Attributes //
        ////////////////
        private:

            World *_World;
            size_t _Index;
            bool   _IsEnd;
            bool   _IncludePendingDestroy;
    };
};

#endif /* !ENTITYCOMPONENTITERATOR_HPP_ */
