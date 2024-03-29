/*
** EPITECH PROJECT, 2023
** ECS
** File description:
** Events
*/

#ifndef EVENTS_HPP_
#define EVENTS_HPP_

// Exodia Utils includes
#include "Utils/TypeIndex.hpp"

// External includes
#include <string>

namespace Exodia {

    class Entity;

    template <typename Component> class ComponentHandle;

    namespace Events {
        struct OnEntityCreated {
            Exodia::Entity *Entity;
        };

        struct OnEntityDestroyed {
            Exodia::Entity *Entity;
        };

        template <typename Component> struct OnComponentAdded {
            Exodia::Entity *Entity;
            Exodia::ComponentHandle<Component> AddedComponent;
        };

        struct OnComponentAddedNoTemplate {
            Exodia::Entity *Entity;
            std::string ComponentType;
        };

        template <typename Component> struct OnComponentRemoved {
            Exodia::Entity *Entity;
            Exodia::ComponentHandle<Component> RemovedComponent;
        };

        struct OnComponentRemovedNoTemplate {
            Exodia::Entity *Entity;
            std::string ComponentType;
        };

        struct OnCollisionEntered {
            Exodia::Entity *EntityA;
            Exodia::Entity *EntityB;
        };

        struct OnHoveredEnter {
            Exodia::Entity *Entity;
        };

        struct OnHoveredExit {
            Exodia::Entity *Entity;
        };

        struct OnClick {
            Exodia::Entity *Entity;
        };
    }; // namespace Events
};     // namespace Exodia

#endif /* !EVENTS_HPP_ */
