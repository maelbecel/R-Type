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

namespace Exodia
{

    class SceneHierarchy
    {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
      public:
        SceneHierarchy( const Ref<Scene> &context = nullptr );
        ~SceneHierarchy() = default;

        /////////////
        // Methods //
        /////////////
      public:
        void OnImGuiRender();

      private:
        void DrawSceneHierarchy();
        void DrawProperties();
        void DrawEntityNode( Entity *entity );
        void DrawComponents( Entity *entity );

        ///////////////////////
        // Getters & Setters //
        ///////////////////////
      public:
        void SetContext( Ref<Scene> context );
        void SetSelectedEntity( Entity *entity );

        Entity *GetSelectedEntity() const;

        ////////////////
        // Attributes //
        ////////////////
      private:
        Ref<Scene> _Context;
        Entity    *_SelectedEntity;
    };
}; // namespace Exodia

#endif /* !SCENEHIERARCHY_HPP_ */
