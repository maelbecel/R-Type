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

// Exodia Debug includes
#include "Debug/Logs.hpp"

// External includes
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

// ImGui includes
#include <imgui.h>

namespace Exodia {

    struct BoxCollider2DComponent : public Component {
        glm::vec2 Offset;
        glm::vec2 Size;
        uint32_t ColliderMask;

        BoxCollider2DComponent(const BoxCollider2DComponent &) = default;
        BoxCollider2DComponent() : Offset(glm::vec2(0.0f)), Size(glm::vec2(0.5f)), ColliderMask(0xFFFFFFFF){};

        virtual void Serialize(YAML::Emitter &out) {
            out << YAML::Key << "BoxCollider2DComponent";
            out << YAML::BeginMap;
            {
                out << YAML::Key << "Offset" << YAML::Value << YAML::Flow;
                { out << YAML::BeginSeq << Offset.x << Offset.y << YAML::EndSeq; }
                out << YAML::Key << "Size" << YAML::Value << YAML::Flow;
                { out << YAML::BeginSeq << Size.x << Size.y << YAML::EndSeq; }
                out << YAML::Key << "Mask" << YAML::Value << ColliderMask;
            }
            out << YAML::EndMap;
        }

        virtual void Deserialize(const YAML::Node &node) {
            try {
                auto box = node["BoxCollider2DComponent"];

                Offset = glm::vec2(box["Offset"][0].as<float>(), box["Offset"][1].as<float>());
                Size = glm::vec2(box["Size"][0].as<float>(), box["Size"][1].as<float>());

                ColliderMask = box["Mask"].as<uint32_t>();
            } catch (YAML::BadConversion &e) {
                EXODIA_CORE_WARN("BoxCollider2DComponent deserialization failed: {0}", e.what());
            }
        }

        Buffer SerializeData() override {
            try {
                uint32_t size = sizeof(glm::vec2) * 2 + sizeof(uint32_t);
                Buffer data(size);

                std::memcpy(data.Data, &Offset, sizeof(glm::vec2));
                std::memcpy(data.Data + sizeof(glm::vec2), &Size, sizeof(glm::vec2));
                std::memcpy(data.Data + sizeof(glm::vec2) * 2, &ColliderMask, sizeof(uint32_t));

                return data;
            } catch (const std::exception &error) {
                EXODIA_CORE_WARN("BoxCollider2DComponent serialization failed:\n\t{0}", error.what());
            }

            return Buffer();
        }

        void DeserializeData(Buffer data) override {
            if (!data || data.Size == 0)
                return;

            try {
                std::memcpy(&Offset, data.Data, sizeof(glm::vec2));
                std::memcpy(&Size, data.Data + sizeof(glm::vec2), sizeof(glm::vec2));
                std::memcpy(&ColliderMask, data.Data + sizeof(glm::vec2) * 2, sizeof(uint32_t));
            } catch (const std::exception &error) {
                EXODIA_CORE_WARN("BoxCollider2DComponent deserialization failed:\n\t{0}", error.what());
            }
        }

        virtual void DrawComponent() override {
            ImGui::DragFloat2("Offset", glm::value_ptr(Offset));
            ImGui::DragFloat2("Size", glm::value_ptr(Size));

            // TODO: Add display for mask (binary)
        }
    };

    struct CircleCollider2DComponent : public Component {
        glm::vec2 Offset;
        float Radius;
        uint32_t ColliderMask;

        CircleCollider2DComponent(const CircleCollider2DComponent &) = default;
        CircleCollider2DComponent() : Offset(glm::vec2(0.0f)), Radius(0.5f), ColliderMask(0xFFFFFFFF){};

        virtual void Serialize(YAML::Emitter &out) {
            out << YAML::Key << "CircleCollider2DComponent";
            out << YAML::BeginMap;
            {
                out << YAML::Key << "Offset" << YAML::Value << YAML::Flow;
                { out << YAML::BeginSeq << Offset.x << Offset.y << YAML::EndSeq; }
                out << YAML::Key << "Radius" << YAML::Value << Radius;
                out << YAML::Key << "Mask" << YAML::Value << ColliderMask;
            }
            out << YAML::EndMap;
        }

        virtual void Deserialize(const YAML::Node &node) {
            try {
                auto circle = node["CircleCollider2DComponent"];

                Offset = glm::vec2(circle["Offset"][0].as<float>(), circle["Offset"][1].as<float>());

                Radius = circle["Radius"].as<float>();

                ColliderMask = circle["Mask"].as<uint32_t>();
            } catch (YAML::BadConversion &e) {
                EXODIA_CORE_WARN("CircleCollider2DComponent deserialization failed: {0}", e.what());
            }
        }

        Buffer SerializeData() override {
            try {
                uint32_t size = sizeof(glm::vec2) + sizeof(float) + sizeof(uint32_t);
                Buffer data(size);

                std::memcpy(data.Data, &Offset, sizeof(glm::vec2));
                std::memcpy(data.Data + sizeof(glm::vec2), &Radius, sizeof(float));
                std::memcpy(data.Data + sizeof(glm::vec2) + sizeof(float), &ColliderMask, sizeof(uint32_t));

                return data;
            } catch (const std::exception &error) {
                EXODIA_CORE_WARN("CircleCollider2DComponent serialization failed:\n\t{0}", error.what());
            }

            return Buffer();
        }

        void DeserializeData(Buffer data) override {
            if (!data || data.Size == 0)
                return;

            try {
                std::memcpy(&Offset, data.Data, sizeof(glm::vec2));
                std::memcpy(&Radius, data.Data + sizeof(glm::vec2), sizeof(float));
                std::memcpy(&ColliderMask, data.Data + sizeof(glm::vec2) + sizeof(float), sizeof(uint32_t));
            } catch (const std::exception &error) {
                EXODIA_CORE_WARN("CircleCollider2DComponent deserialization failed:\n\t{0}", error.what());
            }
        }

        virtual void DrawComponent() override {
            ImGui::DragFloat2("Offset", glm::value_ptr(Offset));
            ImGui::DragFloat("Radius", &Radius);

            // TODO: Add display for mask (binary)
        }
    };
}; // namespace Exodia

#endif /* !COLLIDER2DCOMPONENTS_HPP_ */
