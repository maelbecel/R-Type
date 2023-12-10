/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** RigidBody2DComponent
*/

#ifndef RIGIDBODY2DCOMPONENT_HPP_
    #define RIGIDBODY2DCOMPONENT_HPP_

    // External includes
    #include "Utils/Assert.hpp"

    // Exodia ECS includes
    #include "ECS/Interface/Component.hpp"

    // External includes
    #include <glm/glm.hpp>

namespace Exodia {

    struct RigidBody2DComponent : public Component {
        static std::string GetStaticName()
        {
            return "RigidBody2DComponent";
        }

        std::string GetName() const override
        {
            return GetStaticName();
        }

        enum class BodyType {
            Static,
            Dynamic
        };

        static std::string BodyTypeToString(RigidBody2DComponent::BodyType type)
        {
            switch (type) {
                case RigidBody2DComponent::BodyType::Static:
                    return "Static";
                case RigidBody2DComponent::BodyType::Dynamic:
                    return "Dynamic";
            }

            EXODIA_CORE_ASSERT(false, "Unknown BodyType !");
            return "Static";
        }

        static RigidBody2DComponent::BodyType StringToBodyType(const std::string &type)
        {
            if (type == "Static")
                return RigidBody2DComponent::BodyType::Static;
            if (type == "Dynamic")
                return RigidBody2DComponent::BodyType::Dynamic;

            EXODIA_CORE_ASSERT(false, "Unknown BodyType !");
            return RigidBody2DComponent::BodyType::Static;
        }

        BodyType Type;
        glm::vec2 Velocity;
        float GravityScale;
        float Mass;

        virtual void Serialize(YAML::Emitter &out)
        {
            out << YAML::Key << "RigidBody2DComponent";
            out << YAML::BeginMap;
            {
                out << YAML::Key << "Type"         << YAML::Value << BodyTypeToString(Type);
                out << YAML::Key << "Velocity"     << YAML::Value << YAML::Flow;
                {
                    out << YAML::BeginSeq << Velocity.x << Velocity.y << YAML::EndSeq;
                }
                out << YAML::Key << "GravityScale" << YAML::Value << GravityScale;
                out << YAML::Key << "Mass"         << YAML::Value << Mass;
            }
            out << YAML::EndMap;
        }
    };
};

#endif /* !RIGIDBODY2DCOMPONENT_HPP_ */
