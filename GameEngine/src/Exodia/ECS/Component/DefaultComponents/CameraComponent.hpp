/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** CameraComponent
*/

#ifndef CAMERACOMPONENT_HPP_
    #define CAMERACOMPONENT_HPP_

    // Exodia Scene includes
    #include "Scene/Camera/SceneCamera.hpp"

    // Exodia Debug includes
    #include "Debug/Logs.hpp"

    // Exodia ECS includes
    #include "ECS/Interface/Component.hpp"

    // ImGui includes
    #include <imgui.h>

namespace Exodia {

    struct CameraComponent : public Component {
        SceneCamera Camera;
        bool        Primary;
        bool        FixedAspectRatio;

        CameraComponent(const CameraComponent &) = default;
        CameraComponent() : Primary(true), FixedAspectRatio(false) {};

        virtual void Serialize(YAML::Emitter &out)
        {
            out << YAML::Key << "CameraComponent";
            out << YAML::BeginMap;
            {
                out << YAML::Key << "Camera"            << YAML::Value;
                out << YAML::BeginMap;
                {
                    out << YAML::Key << "ProjectionType"   << YAML::Value << (int)Camera.GetProjectionType();
                    out << YAML::Key << "PerspectiveFOV"   << YAML::Value << Camera.GetPerspectiveVerticalFOV();
                    out << YAML::Key << "PerspectiveNear"  << YAML::Value << Camera.GetPerspectiveNearClip();
                    out << YAML::Key << "PerspectiveFar"   << YAML::Value << Camera.GetPerspectiveFarClip();
                    out << YAML::Key << "OrthographicSize" << YAML::Value << Camera.GetOrthographicSize();
                    out << YAML::Key << "OrthographicNear" << YAML::Value << Camera.GetOrthographicNearClip();
                    out << YAML::Key << "OrthographicFar"  << YAML::Value << Camera.GetOrthographicFarClip();
                }
                out << YAML::EndMap;
                out << YAML::Key << "Primary"           << YAML::Value << Primary;
                out << YAML::Key << "FixedAspectRatio"  << YAML::Value << FixedAspectRatio;
            }
            out << YAML::EndMap;
        }

        virtual void Deserialize(const YAML::Node &node)
        {
            try {
                auto camera = node["CameraComponent"];

                Primary          = camera["Primary"].as<bool>();
                FixedAspectRatio = camera["FixedAspectRatio"].as<bool>();

                auto cameraProps = camera["Camera"];

                if (!cameraProps) {
                    EXODIA_CORE_WARN("CameraComponent has invalid data !");

                    return;
                }

                Camera.SetProjectionType((SceneCamera::ProjectionType)cameraProps["ProjectionType"].as<int>());
                Camera.SetPerspectiveVerticalFOV(cameraProps["PerspectiveFOV"].as<float>());
                Camera.SetPerspectiveNearClip(cameraProps["PerspectiveNear"].as<float>());
                Camera.SetPerspectiveFarClip(cameraProps["PerspectiveFar"].as<float>());
                Camera.SetOrthographicSize(cameraProps["OrthographicSize"].as<float>());
                Camera.SetOrthographicNearClip(cameraProps["OrthographicNear"].as<float>());
                Camera.SetOrthographicFarClip(cameraProps["OrthographicFar"].as<float>());
            } catch (YAML::BadConversion &e) {
                EXODIA_CORE_WARN("CameraComponent deserialization failed: {0}", e.what());
            }
        }

        Buffer SerializeData() override
        {
            try {
                uint32_t size = sizeof(SceneCamera::ProjectionType) + sizeof(float) * 6 + sizeof(bool) * 2;
                Buffer   data(size);

                std::memcpy(data.Data, &Camera.GetProjectionType(), sizeof(SceneCamera::ProjectionType));
                std::memcpy(data.Data + sizeof(SceneCamera::ProjectionType), &Camera.GetPerspectiveVerticalFOV(), sizeof(float));
                std::memcpy(data.Data + sizeof(SceneCamera::ProjectionType) + sizeof(float), &Camera.GetPerspectiveNearClip(), sizeof(float));
                std::memcpy(data.Data + sizeof(SceneCamera::ProjectionType) + sizeof(float) * 2, &Camera.GetPerspectiveFarClip(), sizeof(float));
                std::memcpy(data.Data + sizeof(SceneCamera::ProjectionType) + sizeof(float) * 3, &Camera.GetOrthographicSize(), sizeof(float));
                std::memcpy(data.Data + sizeof(SceneCamera::ProjectionType) + sizeof(float) * 4, &Camera.GetOrthographicNearClip(), sizeof(float));
                std::memcpy(data.Data + sizeof(SceneCamera::ProjectionType) + sizeof(float) * 5, &Camera.GetOrthographicFarClip(), sizeof(float));
                std::memcpy(data.Data + sizeof(SceneCamera::ProjectionType) + sizeof(float) * 6, &Primary, sizeof(bool));
                std::memcpy(data.Data + sizeof(SceneCamera::ProjectionType) + sizeof(float) * 6 + sizeof(bool), &FixedAspectRatio, sizeof(bool));

                return data;
            } catch (const std::exception &error) {
                EXODIA_CORE_WARN("CameraComponent serialization failed:\n\t{0}", error.what());
            }

            return Buffer();
        }

        void DeserializeData(Buffer buffer) override
        {
            try {
                std::memcpy(&Camera.GetProjectionType(), buffer.Data, sizeof(SceneCamera::ProjectionType));
                std::memcpy(&Camera.GetPerspectiveVerticalFOV(), buffer.Data + sizeof(SceneCamera::ProjectionType), sizeof(float));
                std::memcpy(&Camera.GetPerspectiveNearClip(), buffer.Data + sizeof(SceneCamera::ProjectionType) + sizeof(float), sizeof(float));
                std::memcpy(&Camera.GetPerspectiveFarClip(), buffer.Data + sizeof(SceneCamera::ProjectionType) + sizeof(float) * 2, sizeof(float));
                std::memcpy(&Camera.GetOrthographicSize(), buffer.Data + sizeof(SceneCamera::ProjectionType) + sizeof(float) * 3, sizeof(float));
                std::memcpy(&Camera.GetOrthographicNearClip(), buffer.Data + sizeof(SceneCamera::ProjectionType) + sizeof(float) * 4, sizeof(float));
                std::memcpy(&Camera.GetOrthographicFarClip(), buffer.Data + sizeof(SceneCamera::ProjectionType) + sizeof(float) * 5, sizeof(float));
                std::memcpy(&Primary, buffer.Data + sizeof(SceneCamera::ProjectionType) + sizeof(float) * 6, sizeof(bool));
                std::memcpy(&FixedAspectRatio, buffer.Data + sizeof(SceneCamera::ProjectionType) + sizeof(float) * 6 + sizeof(bool), sizeof(bool));
            } catch (const std::exception &error) {
                EXODIA_CORE_WARN("CameraComponent deserialization failed:\n\t{0}", error.what());
            }
        }

        virtual void DrawComponent() override
        {
            ImGui::Checkbox("Primary", &Primary);

            const char *projectionTypeString[]      = { "Perspective", "Orthographic" };
            const char *currentProjectionTypeString = projectionTypeString[(int)Camera.GetProjectionType()];

            if (ImGui::BeginCombo("Projection", currentProjectionTypeString)) {
                for (int i = 0; i < 2; i++) {
                    bool isSelected = (currentProjectionTypeString == projectionTypeString[i]);

                    if (ImGui::Selectable(projectionTypeString[i], isSelected)) {
                        currentProjectionTypeString = projectionTypeString[i];

                        Camera.SetProjectionType((SceneCamera::ProjectionType)i);
                    }

                    if (isSelected)
                        ImGui::SetItemDefaultFocus();
                }
                ImGui::EndCombo();
            }

            if (Camera.GetProjectionType() == SceneCamera::ProjectionType::Perspective) {
                float fov      = glm::degrees(Camera.GetPerspectiveVerticalFOV());
                float nearClip = Camera.GetPerspectiveNearClip();
                float farClip  = Camera.GetPerspectiveFarClip();

                if (ImGui::DragFloat("Vertical FOV", &fov))
                    Camera.SetPerspectiveVerticalFOV(glm::radians(fov));
                if (ImGui::DragFloat("Near", &nearClip))
                    Camera.SetPerspectiveNearClip(nearClip);
                if (ImGui::DragFloat("Far", &farClip))
                    Camera.SetPerspectiveFarClip(farClip);
            } else if (Camera.GetProjectionType() == SceneCamera::ProjectionType::Orthographic) {
                float size     = Camera.GetOrthographicSize();
                float nearClip = Camera.GetOrthographicNearClip();
                float farClip  = Camera.GetOrthographicFarClip();

                if (ImGui::DragFloat("Size", &size))
                    Camera.SetOrthographicSize(size);
                if (ImGui::DragFloat("Near", &nearClip))
                    Camera.SetOrthographicNearClip(nearClip);
                if (ImGui::DragFloat("Far", &farClip))
                    Camera.SetOrthographicFarClip(farClip);

                ImGui::Checkbox("Fixed Aspect Ratio", &FixedAspectRatio);
            }
        }
    };
};

#endif /* !CAMERACOMPONENT_HPP_ */
