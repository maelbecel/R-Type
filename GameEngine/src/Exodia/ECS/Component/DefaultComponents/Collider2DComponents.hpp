/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Collider2DComponents
*/

#ifndef COLLIDER2DCOMPONENTS_HPP_
    #define COLLIDER2DCOMPONENTS_HPP_

    // Exodia ECS includes
    #include "ECS/Interface/Component.hpp"

    // External includes
    #include <glm/glm.hpp>

namespace Exodia {

    struct BoxCollider2DComponent : public Component {
        static std::string GetStaticName()
        {
            return "BoxCollider2DComponent";
        }

        std::string GetName() const override
        {
            return GetStaticName();
        }

        glm::vec2 Offset;
        glm::vec2 Size;
        uint32_t  ColliderMask;

        BoxCollider2DComponent(const BoxCollider2DComponent &) = default;
        BoxCollider2DComponent() : Offset(glm::vec2(0.0f)), Size(glm::vec2(0.5f)), ColliderMask(0xFFFFFFFF) {};

        virtual void Serialize(YAML::Emitter &out)
        {
            out << YAML::Key << "BoxCollider2DComponent";
            out << YAML::BeginMap;
            {
                out << YAML::Key << "Offset" << YAML::Value << YAML::Flow;
                {
                    out << YAML::BeginSeq << Offset.x << Offset.y << YAML::EndSeq;
                }
                out << YAML::Key << "Size"   << YAML::Value << YAML::Flow;
                {
                    out << YAML::BeginSeq << Size.x << Size.y << YAML::EndSeq;
                }
                out << YAML::Key << "Mask"   << YAML::Value << ColliderMask;
            }
            out << YAML::EndMap;
        }
    };

    struct CircleCollider2DComponent : public Component {
        static std::string GetStaticName()
        {
            return "CircleCollider2DComponent";
        }

        std::string GetName() const override
        {
            return GetStaticName();
        }

        glm::vec2 Offset;
        float     Radius;
        uint32_t  ColliderMask;

        CircleCollider2DComponent(const CircleCollider2DComponent &) = default;
        CircleCollider2DComponent() : Offset(glm::vec2(0.0f)), Radius(0.5f), ColliderMask(0xFFFFFFFF) {};

        virtual void Serialize(YAML::Emitter &out) override
        {
            out << YAML::Key << "CircleCollider2DComponent";
            out << YAML::BeginMap;
            {
                out << YAML::Key << "Offset" << YAML::Value << YAML::Flow;
                {
                    out << YAML::BeginSeq << Offset.x << Offset.y << YAML::EndSeq;
                }
                out << YAML::Key << "Radius" << YAML::Value << Radius;
                out << YAML::Key << "Mask"   << YAML::Value << ColliderMask;
            }
            out << YAML::EndMap;
        }
    };
};

#endif /* !COLLIDER2DCOMPONENTS_HPP_ */