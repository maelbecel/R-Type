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

    // External includes
    #include <yaml-cpp/yaml.h>
    #include <string>
    #include <cstring>

namespace Exodia {

    struct Component {

        static std::string GetStaticName()
        {
            return "Component";
        }

        virtual std::string GetName() const
        {
            return GetStaticName();
        }

        virtual void Serialize(YAML::Emitter &out) = 0;
        virtual void Deserialize(UNUSED const YAML::Node &node) = 0;

        virtual void DeserializeData(Buffer data)
        {
            Memcopy(this, data.Data, data.Size);
        }
    };
};

#endif /* !COMPONENT_HPP_ */
