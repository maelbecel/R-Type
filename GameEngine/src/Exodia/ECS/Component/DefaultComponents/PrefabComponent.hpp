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
        static std::string GetStaticName()
        {
            return "ChildrenComponent";
        }

        std::string GetName() const override
        {
            return GetStaticName();
        }

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

        virtual void Serialize(YAML::Emitter &out)
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

        virtual void Deserialize(const YAML::Node &node)
        {
            try {
                auto children = node["ChildrenComponent"];

                for (auto child : children["Children"])
                    Children.push_back(child.as<uint64_t>());
            } catch (YAML::BadConversion &e) {
                EXODIA_CORE_WARN("ChildrenComponent deserialization failed: {0}", e.what());
            }
        }
    };

    struct ParentComponent : public Component {
        static std::string GetStaticName()
        {
            return "ParentComponent";
        }

        std::string GetName() const override
        {
            return GetStaticName();
        }

        UUID Parent;

        ParentComponent(const ParentComponent &) = default;
        ParentComponent(const UUID &parent = UUID(0)) : Parent(parent) {};

        virtual void Serialize(YAML::Emitter &out)
        {
            out << YAML::Key << "ParentComponent";
            out << YAML::BeginMap;
            {
                out << YAML::Key << "Parent" << YAML::Value << (uint64_t)Parent;
            }
            out << YAML::EndMap;
        }

        virtual void Deserialize(const YAML::Node &node)
        {
            try {
                auto parent = node["ParentComponent"];

                Parent = parent["Parent"].as<uint64_t>();
            } catch (YAML::BadConversion &e) {
                EXODIA_CORE_WARN("ParentComponent deserialization failed: {0}", e.what());
            }
        }
    };
};

#endif /* !PREFABCOMPONENT_HPP_ */
