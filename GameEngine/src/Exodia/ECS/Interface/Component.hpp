/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Component
*/

#ifndef COMPONENT_HPP_
    #define COMPONENT_HPP_

    // Exodia Utils includes
    #include "Utils/Memory.hpp"

    // External includes
    #include <yaml-cpp/yaml.h>
    #include <string>

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
    };
};

#endif /* !COMPONENT_HPP_ */
