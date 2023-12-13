/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** TransformComponent
*/

#ifndef TRANSFORMCOMPONENT_HPP_
    #define TRANSFORMCOMPONENT_HPP_

    // Exodia ECS includes
    #include "ECS/Interface/Component.hpp"

    // GLM includes
    #include <glm/glm.hpp>
    #include <glm/gtc/matrix_transform.hpp>
    #define GLM_ENABLE_EXPERIMENTAL
        #include <glm/gtx/quaternion.hpp>

namespace Exodia {

    struct TransformComponent : public Component {
        static std::string GetStaticName()
        {
            return "TransformComponent";
        }

        std::string GetName() const override
        {
            return GetStaticName();
        }

        glm::vec3 Translation;
        glm::vec3 Rotation;
        glm::vec3 Scale;

        TransformComponent(const TransformComponent &) = default;
        TransformComponent(const glm::vec3 &translation = glm::vec3(0.0f)) : Translation(translation), Rotation(glm::vec3(0.0f)), Scale(glm::vec3(1.0f)) {};

        glm::mat4 GetTransform() const
        {
            glm::mat4 translation = glm::translate(glm::mat4(1.0f), Translation);
            glm::mat4 rotation    = glm::toMat4(glm::quat(Rotation));
            glm::mat4 scale       = glm::scale(glm::mat4(1.0f), Scale);

            return translation * rotation * scale;
        }

        virtual void Serialize(YAML::Emitter &out)
        {
            out << YAML::Key << "TransformComponent";
            out << YAML::BeginMap;
            {
                out << YAML::Key << "Translation" << YAML::Value << YAML::Flow;
                {
                    out << YAML::BeginSeq << Translation.x << Translation.y << Translation.z << YAML::EndSeq;
                }
                out << YAML::Key << "Rotation"    << YAML::Value << YAML::Flow;
                {
                    out << YAML::BeginSeq << Rotation.x << Rotation.y << Rotation.z << YAML::EndSeq;
                }
                out << YAML::Key << "Scale"       << YAML::Value << YAML::Flow;
                {
                    out << YAML::BeginSeq << Scale.x << Scale.y << Scale.z << YAML::EndSeq;
                }
            }
            out << YAML::EndMap;
        }

        virtual Buffer SerializeData()
        {
            return Buffer(this, sizeof(*this));
        }
    };
};

#endif /* !TRANSFORMCOMPONENT_HPP_ */
