/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** ScriptableEntity
*/

#ifndef SCRIPTABLEENTITY_HPP_
    #define SCRIPTABLEENTITY_HPP_

    // Exodia ECS includes
    #include "ECS.hpp"

    // Exodia Utils
    #include "Utils/CrossPlatform.hpp"

namespace Exodia {

    class Entity;

    class EXODIA_API ScriptableEntity {

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
            virtual void OnCreate() {};

            /**
             * @brief Called when the scriptable entity is destroyed.
             */
            virtual void OnDestroy() {};

            /**
             * @brief Called when the scriptable entity is updated.
             *
             * @param ts The timestep.
             */
            virtual void OnUpdate(UNUSED Timestep ts) {};

        ///////////////////////
        // Getters & Setters //
        ///////////////////////
        public:

            template<typename Component>
            ComponentHandle<Component> GetComponent()
            {
                return HandleEntity->GetComponent<Component>();
            }

        ////////////////
        // Attributes //
        ////////////////
        public:
            Entity *HandleEntity; /* !< The entity that owns the scriptable entity. */
    };
};

#endif /* !SCRIPTABLEENTITY_HPP_ */
