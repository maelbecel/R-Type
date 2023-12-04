/*
** EPITECH PROJECT, 2023
** ECS
** File description:
** IComponentContainer
*/

#ifndef ICOMPONENTCONTAINER_HPP_
    #define ICOMPONENTCONTAINER_HPP_

    // Exodia Utils includes
    #include "Utils/CrossPlatform.hpp"
    #include "Utils/Memory.hpp"

namespace Exodia {

    class World;
    class Entity;

    struct EXODIA_API IComponentContainer {

        ////////////////
        // Destructor //
        ////////////////
        public:
            virtual ~IComponentContainer() = default;

        /////////////
        // Methods //
        /////////////
        public:
            virtual void Destroy(World * world) = 0;
            virtual void Removed(Entity *entity) = 0;
    };
};

#endif /* !ICOMPONENTCONTAINER_HPP_ */
