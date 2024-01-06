/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** RigidBody2DComponent
*/

#ifndef RIGIDBODY2DCOMPONENT_HPP_
#define RIGIDBODY2DCOMPONENT_HPP_

// External includes
#include "Exodia-Debug.hpp"

// Exodia ECS includes
#include "Scene/Components/Component.hpp"

// Exodia Debug includes
#include "Exodia-Debug.hpp"

// External includes
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

// ImGui includes
#include <imgui.h>

namespace Exodia {

    struct RigidBody2DComponent : public Component {
        enum class BodyType { Static, Dynamic };

        static std::string BodyTypeToString(RigidBody2DComponent::BodyType type) {
            switch (type) {
            case RigidBody2DComponent::BodyType::Static:
                return "Static";
            case RigidBody2DComponent::BodyType::Dynamic:
                return "Dynamic";
            }

            EXODIA_CORE_ASSERT(false, "Unknown BodyType !");
            return "Static";
        }

        static RigidBody2DComponent::BodyType StringToBodyType(const std::string &type) {
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

        virtual void Serialize(YAML::Emitter &out) {
            out << YAML::Key << "RigidBody2DComponent";
            out << YAML::BeginMap;
            {
                out << YAML::Key << "BodyType" << YAML::Value << BodyTypeToString(Type);
                out << YAML::Key << "Velocity" << YAML::Value << YAML::Flow;
                { out << YAML::BeginSeq << Velocity.x << Velocity.y << YAML::EndSeq; }
                out << YAML::Key << "GravityScale" << YAML::Value << GravityScale;
                out << YAML::Key << "Mass" << YAML::Value << Mass;
            }
            out << YAML::EndMap;
        }

        virtual void Deserialize(const YAML::Node &node) {
            try {
                auto rigidBody = node["RigidBody2DComponent"];

                Type = StringToBodyType(rigidBody["BodyType"].as<std::string>());

                Velocity = glm::vec2(rigidBody["Velocity"][0].as<float>(), rigidBody["Velocity"][1].as<float>());

                GravityScale = rigidBody["GravityScale"].as<float>();
                Mass = rigidBody["Mass"].as<float>();
            } catch (YAML::BadConversion &e) {
                EXODIA_CORE_WARN("RigidBody2DComponent deserialization failed: {0}", e.what());
            }
        }

        virtual void DrawComponent() override {
            const char *bodyTypeStrings[] = {"Static", "Dynamic"};
            const char *currentBodyTypeString = bodyTypeStrings[(int)Type];

            if (ImGui::BeginCombo("Body Type", currentBodyTypeString)) {
                for (int i = 0; i < 2; i++) {
                    bool isSelected = currentBodyTypeString == bodyTypeStrings[i];

                    if (ImGui::Selectable(bodyTypeStrings[i], isSelected)) {
                        currentBodyTypeString = bodyTypeStrings[i];

                        Type = (BodyType)i;
                    }

                    if (isSelected)
                        ImGui::SetItemDefaultFocus();
                }
                ImGui::EndCombo();
            }
            ImGui::DragFloat2("Velocity", glm::value_ptr(Velocity));
            ImGui::DragFloat("Gravity Scale", &GravityScale);
            ImGui::DragFloat("Mass", &Mass);
        }

        virtual Buffer SerializeData() override {
            try {
                uint32_t size = sizeof(BodyType) + sizeof(float) * 2 + sizeof(glm::vec2);
                Buffer buffer(size);

                std::memcpy(buffer.Data, &Type, sizeof(BodyType));
                std::memcpy(buffer.Data + sizeof(BodyType), &Velocity, sizeof(glm::vec2));
                std::memcpy(buffer.Data + sizeof(BodyType) + sizeof(glm::vec2), &GravityScale, sizeof(float));
                std::memcpy(buffer.Data + sizeof(BodyType) + sizeof(glm::vec2) + sizeof(float), &Mass, sizeof(float));
                return buffer;
            } catch (const std::exception &e) {
                EXODIA_CORE_WARN("RigidBody2DComponent serialization failed: {0}", e.what());
                return Buffer();
            }
        }

        virtual void DeserializeData(Buffer buffer) override {
            if (!buffer || buffer.Size == 0)
                return;
            try {
                std::memcpy(&Type, buffer.Data, sizeof(BodyType));
                std::memcpy(&Velocity, buffer.Data + sizeof(BodyType), sizeof(glm::vec2));
                std::memcpy(&GravityScale, buffer.Data + sizeof(BodyType) + sizeof(glm::vec2), sizeof(float));
                std::memcpy(&Mass, buffer.Data + sizeof(BodyType) + sizeof(glm::vec2) + sizeof(float), sizeof(float));
            } catch (const std::exception &e) {
                EXODIA_CORE_WARN("RigidBody2DComponent deserialization failed: {0}", e.what());
            }
        }
    };
}; // namespace Exodia

#endif /* !RIGIDBODY2DCOMPONENT_HPP_ */
