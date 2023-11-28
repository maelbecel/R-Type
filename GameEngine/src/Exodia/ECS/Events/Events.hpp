/*
** EPITECH PROJECT, 2023
** ECS
** File description:
** Events
*/

#ifndef EVENTS_HPP_
    #define EVENTS_HPP_

    // Exodia Utils includes
    #include "Utils/CrossPlatform.hpp"

namespace Exodia {

    class Entity;

    template<typename Component>
    class ComponentHandle;

    namespace Events {
        struct EXODIA_API OnEntityCreated
        {
            Exodia::Entity *Entity;
        };

        struct EXODIA_API OnEntityDestroyed
        {
            Exodia::Entity *Entity;
        };

        template<typename Component>
        struct EXODIA_API OnComponentAdded
        {
            Exodia::Entity                      *Entity;
            Exodia::ComponentHandle<Component> AddedComponent;
        };

        template<typename Component>
        struct EXODIA_API OnComponentRemoved
        {
            Exodia::Entity                    *Entity;
            Exodia::ComponentHandle<Component> RemovedComponent;
        };
    };
};

#endif /* !EVENTS_HPP_ */
