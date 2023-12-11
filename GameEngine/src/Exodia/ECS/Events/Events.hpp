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
        struct EXODIA_API OnEntityCreated {
            Exodia::Entity *Entity;
        };

        struct EXODIA_API OnEntityDestroyed {
            Exodia::Entity *Entity;
        };

        template<typename Component>
        struct EXODIA_API OnComponentAdded {
            Exodia::Entity                    *Entity;
            Exodia::ComponentHandle<Component> AddedComponent;
        };

        struct EXODIA_API OnComponentAddedNoTemplate {
            Exodia::Entity *Entity;
            TypeIndex       ComponentType;
        };

        template<typename Component>
        struct EXODIA_API OnComponentRemoved {
            Exodia::Entity                    *Entity;
            Exodia::ComponentHandle<Component> RemovedComponent;
        };

        struct EXODIA_API OnComponentRemovedNoTemplate {
            Exodia::Entity *Entity;
            TypeIndex       ComponentType;
        };

        struct EXODIA_API OnCollisionEntered {
            Exodia::Entity *EntityA;
            Exodia::Entity *EntityB;
        };
    };
};

#endif /* !EVENTS_HPP_ */
