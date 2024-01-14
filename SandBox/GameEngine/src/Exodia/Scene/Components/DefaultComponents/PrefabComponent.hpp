/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** PrefabComponent
*/

#ifndef PREFABCOMPONENT_HPP_
#define PREFABCOMPONENT_HPP_

// Exodia UUID includes
#include "Exodia-Utils.hpp"

// Exodia Debug includes
#include "Exodia-Debug.hpp"

// Exodia ECS includes
#include "Scene/Components/Component.hpp"
#include "Scene/Serializer/SceneSerializer.hpp"

namespace Exodia {

    class GameObject;
    class Scene;

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

                return buffer;
            } catch (std::exception &e) {
                EXODIA_CORE_WARN("ParentComponent serialization failed: {0}", e.what());
            }

            return Buffer();
        }

        void DeserializeData(Buffer data) override {
            if (!data || data.Size == 0)
                return;
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

    struct ChildrenComponent : public Component {
        std::vector<UUID> Children;

        ChildrenComponent(const ChildrenComponent &) = default;
        ChildrenComponent() : Children(std::vector<UUID>()){};

        void AddChild(const UUID &child) { Children.push_back(child); }

        GameObject AddChild(const YAML::detail::iterator_value &node, Scene *scene) {
            GameObject newGameObject = scene->CreateNewEntityWithUUID(UUID());

            try {
                for (YAML::detail::iterator_value component : node) {
                    std::string componentType = component.first.as<std::string>();

                    if (componentType == "Entity" || componentType == "IDComponent" ||
                        componentType == "ParentComponent")
                        continue;
                    if (componentType == "ChildrenComponent") {
                        auto children = component.second["Children"];

                        for (auto child : children) {
                            auto &cc = newGameObject.AddComponent<ChildrenComponent>();

                            GameObject childObject = cc.AddChild(child, scene);

                            childObject.GetComponent<ParentComponent>().Parent =
                                newGameObject.GetComponent<IDComponent>().ID;
                        }
                        continue;
                    }

                    SceneSerializer::DeserializeComponent(componentType, node, newGameObject);
                }

                AddChild(newGameObject.GetComponent<IDComponent>().ID);
            } catch (YAML::BadConversion &e) {
                EXODIA_CORE_WARN("ChildrenComponent deserialization failed:\n\t{0}", e.what());
            }
            return newGameObject;
        }

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
                return buffer;
            } catch (std::exception &e) {
                EXODIA_CORE_WARN("ChildrenComponent serialization failed: {0}", e.what());
            }

            return Buffer();
        }

        void DeserializeData(Buffer data) override {
            if (!data || data.Size == 0)
                return;

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
}; // namespace Exodia

#endif /* !PREFABCOMPONENT_HPP_ */
