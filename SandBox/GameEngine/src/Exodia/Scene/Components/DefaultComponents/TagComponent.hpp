/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** TagComponent
*/

#ifndef TAGCOMPONENT_HPP_
#define TAGCOMPONENT_HPP_

// Exodia ECS includes
#include "Scene/Components/Component.hpp"

// Exodia Debug includes
#include "Exodia-Debug.hpp"

namespace Exodia {

    struct TagComponent : public Component {
        std::string Tag;

        TagComponent(const TagComponent &other) : Tag(other.Tag){};
        TagComponent(const std::string &tag = std::string()) : Tag(tag){};

        TagComponent &operator=(const TagComponent &other) {
            Tag = other.Tag;

            return *this;
        }

        virtual void Serialize(YAML::Emitter &out) {
            out << YAML::Key << "TagComponent";
            out << YAML::BeginMap;
            { out << YAML::Key << "Tag" << YAML::Value << Tag; }
            out << YAML::EndMap;
        }

        virtual void Deserialize(const YAML::Node &node) {
            try {
                auto tag = node["TagComponent"];

                Tag = tag["Tag"].as<std::string>();
            } catch (const YAML::Exception &e) {
                EXODIA_CORE_WARN("TagComponent deserialization failed: {0}", e.what());
            }
        }

        virtual Buffer SerializeData() {
            try {
                Buffer buffer(sizeof(char) * Tag.size());

                std::memcpy(buffer.Data, Tag.data(), sizeof(char) * Tag.size());

                return buffer;
            } catch (const std::exception &e) {
                EXODIA_CORE_WARN("TagComponent serialization failed: {0}", e.what());
                return Buffer();
            }
        }

        virtual void DeserializeData(Buffer buffer) {
            if (!buffer || buffer.Size == 0)
                return;

            try {
                for (uint32_t i = 0; i < buffer.Size; i++)
                    Tag.push_back((char)buffer.Data[i]);
            } catch (const std::exception &e) {
                EXODIA_CORE_WARN("TagComponent deserialization failed: {0}", e.what());
            }
        }
    };
}; // namespace Exodia

#endif /* !TAGCOMPONENT_HPP_ */
