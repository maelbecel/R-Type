/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** SceneHierarchy
*/

#ifndef SCENEHIERARCHY_HPP_
    #define SCENEHIERARCHY_HPP_

    // Exodia includes
    #include "Exodia.hpp"

namespace Exodia {

    class SceneHierarchy {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
        public:

            SceneHierarchy()  = default;
            ~SceneHierarchy() = default;

        /////////////
        // Methods //
        /////////////
        public:

            void OnImGuiRender();
        
        ///////////////////////
        // Getters & Setters //
        ///////////////////////
        public:
            
            void SetContext(Ref<Scene> context);            
            void SetSelectedEntity(Entity entity);

            Entity GetSelectedEntity() const;

        ////////////////
        // Attributes //
        ////////////////
        private:
            Ref<Scene> _Context;
            Entity     _SelectedEntity;
    };
};

#endif /* !SCENEHIERARCHY_HPP_ */
