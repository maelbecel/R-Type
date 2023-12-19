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
    #include "Utils/TypeIndex.hpp"

namespace Exodia {

    class Entity;

    template<typename Component>
    class ComponentHandle;

    namespace Events {
        struct OnEntityCreated {
            Exodia::Entity *Entity;
        };

        struct OnEntityDestroyed {
            Exodia::Entity *Entity;
        };

        template<typename Component>
        struct OnComponentAdded {
            Exodia::Entity                    *Entity;
            Exodia::ComponentHandle<Component> AddedComponent;
        };

        struct OnComponentAddedNoTemplate {
            Exodia::Entity *Entity;
            TypeIndex       ComponentType;
        };

        template<typename Component>
        struct OnComponentRemoved {
            Exodia::Entity                    *Entity;
            Exodia::ComponentHandle<Component> RemovedComponent;
        };

        struct OnComponentRemovedNoTemplate {
            Exodia::Entity *Entity;
            TypeIndex       ComponentType;
        };

        struct OnCollisionEntered {
            Exodia::Entity *EntityA;
            Exodia::Entity *EntityB;
        };
    };
};

#endif /* !EVENTS_HPP_ */
