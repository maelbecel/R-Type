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

    // External includes
    #include <yaml-cpp/yaml.h>

namespace Exodia {

    struct ChildrenComponent {
        std::vector<UUID> Children;

        ChildrenComponent(const ChildrenComponent &) = default;
        ChildrenComponent() : Children(std::vector<UUID>()) {};

        void AddChild(const UUID &child)
        {
            Children.push_back(child);
        }

        void RemoveChild(const UUID &child)
        {
            Children.erase(std::remove(Children.begin(), Children.end(), child), Children.end());
        }

        void HasChild(const UUID &child)
        {
            std::find(Children.begin(), Children.end(), child) != Children.end();
        }

        void Serialize(YAML::Emitter &out)
        {
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
    };

    struct ParentComponent {
        UUID Parent;

        ParentComponent(const ParentComponent &) = default;
        ParentComponent(const UUID &parent = UUID(0)) : Parent(parent) {};

        void Serialize(YAML::Emitter &out)
        {
            out << YAML::Key << "ParentComponent";
            out << YAML::BeginMap;
            {
                out << YAML::Key << "Parent" << YAML::Value << (uint64_t)Parent;
            }
            out << YAML::EndMap;
        }
    };
};

#endif /* !PREFABCOMPONENT_HPP_ */
