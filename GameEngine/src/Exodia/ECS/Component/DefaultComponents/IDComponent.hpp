/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** IDComponent
*/

#ifndef IDCOMPONENT_HPP_
    #define IDCOMPONENT_HPP_

    // Exodia UUID includes
    #include "Core/ID/UUID.hpp"

    // External includes
    #include <yaml-cpp/yaml.h>

namespace Exodia {

    struct IDComponent {
        UUID ID;

        IDComponent(const IDComponent &) = default;
        IDComponent(const UUID &uuid = UUID()) : ID(uuid) {};

        void Serialize(YAML::Emitter &out)
        {
            out << YAML::Key << "IDComponent";
            out << YAML::BeginMap;
            {
                out << YAML::Key << "ID" << YAML::Value << (uint64_t)ID;
            }
            out << YAML::EndMap;
        }
    };
};

#endif /* !IDCOMPONENT_HPP_ */
