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

    // Exodia Debug includes
    #include "Debug/Logs.hpp"

    // GLM includes
    #include <glm/glm.hpp>
    #include <glm/gtc/matrix_transform.hpp>
    #define GLM_ENABLE_EXPERIMENTAL
        #include <glm/gtx/quaternion.hpp>

    // Exodia ImGui includes
    #include "ImGui/ImGuiToolsUI.hpp"

namespace Exodia {

    struct TransformComponent : public Component {
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

        virtual void Serialize(YAML::Emitter &out) override
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

        virtual void Deserialize(const YAML::Node &node) override
        {
            try {
                auto transform = node["TransformComponent"];

                Translation = glm::vec3(transform["Translation"][0].as<float>(), transform["Translation"][1].as<float>(), transform["Translation"][2].as<float>());
                Rotation    = glm::vec3(transform["Rotation"][0].as<float>()   , transform["Rotation"][1].as<float>()   , transform["Rotation"][2].as<float>());
                Scale       = glm::vec3(transform["Scale"][0].as<float>()      , transform["Scale"][1].as<float>()      , transform["Scale"][2].as<float>());
            } catch (YAML::BadConversion &e) {
                EXODIA_CORE_WARN("TransformComponent deserialization failed: {0}", e.what());
            }
        }

        virtual void DrawComponent() override
        {
            glm::vec3 rotation = glm::degrees(Rotation);

            DrawVec3Control("Translation", Translation);
            DrawVec3Control("Rotation"   , rotation);
            DrawVec3Control("Scale"      , Scale, 1.0f);

            Rotation = glm::radians(rotation);
        }
    };
};

#endif /* !TRANSFORMCOMPONENT_HPP_ */
