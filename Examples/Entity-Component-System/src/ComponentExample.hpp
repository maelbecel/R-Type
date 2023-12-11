/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** ComponentExample
*/

#ifndef COMPONENTEXAMPLE_HPP_
    #define COMPONENTEXAMPLE_HPP_

    // Exodia includes
    #include "Exodia.hpp"

    // GLM includes
    #include <glm/gtc/matrix_transform.hpp>
    #define GLM_ENABLE_EXPERIMENTAL
        #include <glm/gtx/quaternion.hpp>

namespace Exodia {

    struct Transform : public Component {
        static std::string GetStaticName()
        {
            return "Transform";
        }

        std::string GetName() const override
        {
            return GetStaticName();
        }

        glm::vec3 Translation;
        glm::vec3 Rotation;
        glm::vec3 Scale;

        Transform(const Transform &) = default;
        Transform(const glm::vec3 &translation = glm::vec3(0.0f)) : Translation(translation), Rotation(glm::vec3(0.0f)), Scale(glm::vec3(1.0f)) {};

        virtual void Serialize(YAML::Emitter &out)
        {
            out << YAML::Key << "Transform";
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
    };

    struct Health : public Component {
        static std::string GetStaticName()
        {
            return "Health";
        }

        std::string GetName() const override
        {
            return GetStaticName();
        }

        int CurrentHealth;
        int MaxHealth;

        Health(const Health &) = default;
        Health(int maxHealth = 100) : CurrentHealth(maxHealth), MaxHealth(maxHealth) {};

        virtual void Serialize(YAML::Emitter &out)
        {
            out << YAML::Key << "Health";
            out << YAML::BeginMap;
            {
                out << YAML::Key << "CurrentHealth" << YAML::Value << CurrentHealth;
                out << YAML::Key << "MaxHealth"     << YAML::Value << MaxHealth;
            }
            out << YAML::EndMap;
        }
    };
};

#endif /* !COMPONENTEXAMPLE_HPP_ */
