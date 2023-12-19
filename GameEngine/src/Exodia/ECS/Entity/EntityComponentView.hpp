/*
** EPITECH PROJECT, 2023
** ECS
** File description:
** EntityComponentView
*/

#ifndef ENTITYCOMPONENTVIEW_HPP_
    #define ENTITYCOMPONENTVIEW_HPP_

    // Exodia Utils includes
    #include "Utils/CrossPlatform.hpp"

namespace Exodia {

    template<typename ...Components>
    class EntityComponentIterator;

    template<typename ...Components>
    class EntityComponentView {

        /////////////////
        // Constructor //
        /////////////////
        public:

            EntityComponentView(const EntityComponentIterator<Components ...> &first, const EntityComponentIterator<Components ...> &last) : _FirstIterator(first), _LastIterator(last)
            {
                if (_FirstIterator.Get() == nullptr || (_FirstIterator.Get()->IsPendingDestroy() && !_FirstIterator.IncludePendingDestroy()) || !_FirstIterator.Get()->template HasComponent<Components ...>())
                    ++_FirstIterator;
            }

        /////////////
        // Methods //
        /////////////
        public:

            const EntityComponentIterator<Components...> &begin() const
            {
                return _FirstIterator;
            }

            const EntityComponentIterator<Components...> &end() const
            {
                return _LastIterator;
            }

        ////////////////
        // Attributes //
        ////////////////
        private:

            EntityComponentIterator<Components ...> _FirstIterator;
            EntityComponentIterator<Components ...> _LastIterator;
    };
    };

#endif /* !ENTITYCOMPONENTVIEW_HPP_ */
