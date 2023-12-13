/*
** EPITECH PROJECT, 2023
** ECS
** File description:
** IComponentContainer
*/

#ifndef ICOMPONENTCONTAINER_HPP_
    #define ICOMPONENTCONTAINER_HPP_

    // Exodia Utils includes
    #include "Utils/CrossPlatform.hpp"
    #include "Utils/Memory.hpp"
    #include "Utils/TypeIndex.hpp"

    // External includes
    #include <yaml-cpp/yaml.h>

namespace Exodia {

    class World;
    class Entity;

    struct EXODIA_API IComponentContainer {

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

            virtual void Serialize(YAML::Emitter &out) = 0;
            virtual void Deserialize(const YAML::Node &node) = 0;

            virtual void Destroy(World *world) = 0;
            virtual void Removed(Entity *entity) = 0;
    };
};

#endif /* !ICOMPONENTCONTAINER_HPP_ */
