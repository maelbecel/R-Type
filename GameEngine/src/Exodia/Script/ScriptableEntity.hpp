/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** ScriptableEntity
*/

#ifndef SCRIPTABLEENTITY_HPP_
    #define SCRIPTABLEENTITY_HPP_

    // Exodia ECS includes
    #include "Exodia/ECS/ECS.hpp"

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
        protected:

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
            ComponentHandle<Component> &GetComponent()
            {
                return _Entity.GetComponent<Component>();
            }

        ////////////////
        // Attributes //
        ////////////////
        private:
            Entity _Entity; /* !< The entity that owns the scriptable entity. */
    };
};

#endif /* !SCRIPTABLEENTITY_HPP_ */
