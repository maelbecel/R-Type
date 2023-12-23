/*
** EPITECH PROJECT, 2023
** ECS
** File description:
** IComponentContainer
*/

#ifndef ICOMPONENTCONTAINER_HPP_
#define ICOMPONENTCONTAINER_HPP_

// Exodia Core includes
#include "Core/Buffer/Buffer.hpp"

// Exodia Utils includes
#include "Utils/CrossPlatform.hpp"
#include "Utils/Memory.hpp"
#include "Utils/TypeIndex.hpp"

// External includes
#include <yaml-cpp/yaml.h>

namespace Exodia
{

    class World;
    class Entity;

    struct IComponentContainer
    {

        ////////////////
        // Destructor //
        ////////////////
      public:
        virtual ~IComponentContainer() = default;

        /////////////
        // Methods //
        /////////////
      public:
        virtual TypeIndex GetTypeIndexOfComponent() = 0;

        virtual void Serialize( YAML::Emitter &out )       = 0;
        virtual void Deserialize( const YAML::Node &node ) = 0;

        virtual void Destroy( World *world )   = 0;
        virtual void Removed( Entity *entity ) = 0;

        virtual void   OnImGuiRender() = 0;
        virtual Buffer SerializeData() = 0;
    };
}; // namespace Exodia

#endif /* !ICOMPONENTCONTAINER_HPP_ */
