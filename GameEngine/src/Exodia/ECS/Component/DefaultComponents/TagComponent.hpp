/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** TagComponent
*/

#ifndef TAGCOMPONENT_HPP_
    #define TAGCOMPONENT_HPP_

    // Exodia ECS includes
    #include "ECS/Interface/Component.hpp"

namespace Exodia {

    struct TagComponent : public Component {
        static std::string GetStaticName()
        {
            return "TagComponent";
        }

        std::string GetName() const override
        {
            return GetStaticName();
        }

        std::string Tag;

        TagComponent(const TagComponent &) = default;
        TagComponent(const std::string &tag = std::string()) : Tag(tag) {};

        virtual void Serialize(YAML::Emitter &out)
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
