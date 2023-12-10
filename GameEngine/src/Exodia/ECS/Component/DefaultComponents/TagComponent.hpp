/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** TagComponent
*/

#ifndef TAGCOMPONENT_HPP_
    #define TAGCOMPONENT_HPP_

    // External includes
    #include <yaml-cpp/yaml.h>
    #include <string>

namespace Exodia {

    struct TagComponent {
        std::string Tag;

        TagComponent(const TagComponent &) = default;
        TagComponent(const std::string &tag = std::string()) : Tag(tag) {};

        void Serialize(YAML::Emitter &out)
        {
            out << YAML::Key << "TagComponent";
            out << YAML::BeginMap;
            {
                out << YAML::Key << "Tag" << YAML::Value << Tag;
            }
            out << YAML::EndMap;
        }
    };
};

#endif /* !TAGCOMPONENT_HPP_ */
