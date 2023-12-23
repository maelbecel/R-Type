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

    // Exodia Debug includes
    #include "Debug/Logs.hpp"

namespace Exodia {

    struct TagComponent : public Component {
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

        virtual void Deserialize(const YAML::Node &node)
        {
            try {
                auto tag = node["TagComponent"];

                Tag = tag["Tag"].as<std::string>();
            } catch (const YAML::Exception &e) {
                EXODIA_CORE_WARN("TagComponent deserialization failed: {0}", e.what());
            }
        }

        virtual Buffer SerializeData()
        {
            try {
                Buffer buffer(sizeof(Tag));
                std::memcpy(buffer.Data, Tag.data(), sizeof(Tag));
                return buffer;
            } catch (const std::exception &e) {
                EXODIA_CORE_WARN("TagComponent serialization failed: {0}", e.what());
                return Buffer();
            }
        }

        virtual void DeserializeData(Buffer buffer)
        {
            try {
                if (buffer.Size <= 0) {
                    Tag = "";
                    return;
                }
                std::memcpy(Tag.data(), buffer.Data, sizeof(Tag));
            } catch (const std::exception &e) {
                EXODIA_CORE_WARN("TagComponent deserialization failed: {0}", e.what());
            }
        }
    };
};

#endif /* !TAGCOMPONENT_HPP_ */
