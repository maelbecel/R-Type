/*
** EPITECH PROJECT, 2023
** ECS
** File description:
** EntityView
*/

#ifndef ENTITYVIEW_HPP_
    #define ENTITYVIEW_HPP_

    // Exodia ECS Entity includes
    #include "Entity/EntityIterator.hpp"

    // Exodia Utils includes
    #include "Utils/CrossPlatform.hpp"

namespace Exodia {

    class EXODIA_API EntityView {

        /////////////////
        // Constructor //
        /////////////////
        public:

            EntityView(const EntityIterator &first, const EntityIterator &last);

        /////////////
        // Methods //
        /////////////
        public:

            const EntityIterator &begin() const;

            const EntityIterator &end() const;

        ////////////////
        // Attributes //
        ////////////////
        private:

            EntityIterator _FirstIterator;
            EntityIterator _LastIterator;
    };
};

#endif /* !ENTITYVIEW_HPP_ */
