/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** PrefabComponent
*/

#ifndef PREFABCOMPONENT_HPP_
#define PREFABCOMPONENT_HPP_

// Exodia UUID includes
#include "Core/ID/UUID.hpp"

// Exodia Debug includes
#include "Debug/Logs.hpp"

// Exodia ECS includes
#include "ECS/Interface/Component.hpp"

namespace Exodia {

    struct ChildrenComponent : public Component {
        std::vector<UUID> Children;

        ChildrenComponent(const ChildrenComponent &) = default;
        ChildrenComponent() : Children(std::vector<UUID>()){};

        void AddChild(const UUID &child) { Children.push_back(child); }

        void RemoveChild(const UUID &child) {
            Children.erase(std::remove(Children.begin(), Children.end(), child), Children.end());
        }

        bool HasChild(const UUID &child) {
            return std::find(Children.begin(), Children.end(), child) != Children.end();
        }

        virtual void Serialize(YAML::Emitter &out) {
            out << YAML::Key << "ChildrenComponent";
            out << YAML::BeginMap;
            {
                out << YAML::Key << "Children" << YAML::Value << YAML::BeginSeq;
                {
                    for (auto &child : Children)
                        out << (uint64_t)child;
                }
                out << YAML::EndSeq;
            }
            out << YAML::EndMap;
        }

        virtual void Deserialize(const YAML::Node &node) {
            try {
                auto children = node["ChildrenComponent"];

                for (auto child : children["Children"])
                    Children.push_back(child.as<uint64_t>());
            } catch (YAML::BadConversion &e) {
                EXODIA_CORE_WARN("ChildrenComponent deserialization failed: {0}", e.what());
            }
        }

        Buffer SerializeData() override {
            try {
                uint32_t size = sizeof(uint64_t) * (uint32_t)Children.size();
                Buffer buffer(size);

                for (uint32_t i = 0; i < (uint64_t)Children.size(); i++)
                    std::memcpy(buffer.Data + sizeof(uint64_t) * i, &Children[i], sizeof(uint64_t));
            } catch (std::exception &e) {
                EXODIA_CORE_WARN("ChildrenComponent serialization failed: {0}", e.what());
            }

            return Buffer();
        }

        void DeserializeData(Buffer data) override {
            try {
                for (uint32_t i = 0; i < (data.Size / sizeof(uint64_t)); i++) {
                    uint64_t child = 0;

                    std::memcpy(&child, data.Data + sizeof(uint64_t) * i, sizeof(uint64_t));

                    Children.push_back(child);
                }
            } catch (std::exception &e) {
                EXODIA_CORE_WARN("ChildrenComponent deserialization failed: {0}", e.what());
            }
        }

        // TODO: Add a display to the component
    };

    struct ParentComponent : public Component {
        UUID Parent;

        ParentComponent(const ParentComponent &) = default;
        ParentComponent(const UUID &parent = UUID(0)) : Parent(parent){};

        virtual void Serialize(YAML::Emitter &out) {
            out << YAML::Key << "ParentComponent";
            out << YAML::BeginMap;
            { out << YAML::Key << "Parent" << YAML::Value << (uint64_t)Parent; }
            out << YAML::EndMap;
        }

        virtual void Deserialize(const YAML::Node &node) {
            try {
                auto parent = node["ParentComponent"];

                Parent = parent["Parent"].as<uint64_t>();
            } catch (YAML::BadConversion &e) {
                EXODIA_CORE_WARN("ParentComponent deserialization failed: {0}", e.what());
            }
        }

        Buffer SerializeData() override {
            try {
                uint32_t size = sizeof(uint64_t);
                Buffer buffer(size);

                std::memcpy(buffer.Data, &Parent, sizeof(uint64_t));
            } catch (std::exception &e) {
                EXODIA_CORE_WARN("ParentComponent serialization failed: {0}", e.what());
            }

            return Buffer();
        }

        void DeserializeData(Buffer data) override {
            try {
                uint64_t parent = 0;

                std::memcpy(&parent, data.Data, sizeof(uint64_t));

                Parent = parent;
            } catch (std::exception &e) {
                EXODIA_CORE_WARN("ParentComponent deserialization failed: {0}", e.what());
            }
        }

        // TODO: Add a display to the component
    };
}; // namespace Exodia

#endif /* !PREFABCOMPONENT_HPP_ */
