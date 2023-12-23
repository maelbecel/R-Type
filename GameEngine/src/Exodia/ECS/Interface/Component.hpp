/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Component
*/

#ifndef COMPONENT_HPP_
#define COMPONENT_HPP_

// Exodia Core includes
#include "Core/Buffer/Buffer.hpp"

// Exodia Utils includes
#include "Utils/Memory.hpp"

// External includes
#include <cstring>
#include <string>
#include <yaml-cpp/yaml.h>

namespace Exodia
{

    class Entity;

    struct Component
    {

        virtual void DeserializeData( Buffer data ) { Memcopy( &data, this, sizeof( *this ) ); }

        virtual void Serialize( UNUSED( YAML::Emitter &out ) ){};
        virtual void Deserialize( UNUSED( const YAML::Node &node ) ){};

        virtual void DrawComponent(){};

        virtual Buffer SerializeData() { return Buffer( this, sizeof( *this ) ); }
    };
}; // namespace Exodia

#endif /* !COMPONENT_HPP_ */
