/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** ScriptableEntity
*/

#ifndef SCRIPTABLEENTITY_HPP_
#define SCRIPTABLEENTITY_HPP_

// Exodia ECS includes
#include "Scene/GameObject/GameObject.hpp"
#include "Exodia-Utils.hpp"

namespace Exodia {

    class ScriptableEntity {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
      public:
        virtual ~ScriptableEntity() = default;

        /////////////
        // Methods //
        /////////////
      public:
        /**
         * @brief Called when the scriptable entity is created.
         */
        virtual void OnCreate(){};

        /**
         * @brief Called when the scriptable entity is destroyed.
         */
        virtual void OnDestroy(){};

        /**
         * @brief Called when the scriptable entity is updated.
         *
         * @param ts The timestep.
         */
        virtual void OnUpdate(UNUSED(Timestep ts)){};

        /**
         * @brief Called when the handle entity is entered in collision with another entity.
         *
         * @param other The other entity.
         */
        virtual void OnCollisionEnter(UNUSED(Entity *other)){};

        virtual void OnHoveredEnter(){};

        virtual void OnKeyPressed(UNUSED(int keycode)){};

        virtual void OnKeyReleased(UNUSED(int keycode)){};

        virtual void OnHoveredExit(){};

        virtual void OnClick(){};

        ///////////////////////
        // Getters & Setters //
        ///////////////////////
      public:
        template <typename Component> Component &GetComponent() { return HandleEntity.GetComponent<Component>(); }

        ////////////////
        // Attributes //
        ////////////////
      public:
        GameObject HandleEntity; /* !< The entity that owns the scriptable entity. */
    };
}; // namespace Exodia

#endif /* !SCRIPTABLEENTITY_HPP_ */
