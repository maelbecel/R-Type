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

    // Exodia ECS includes
    #include "ECS/Interface/Component.hpp"

namespace Exodia {

    struct CameraComponent : public Component {

        static std::string GetStaticName()
        {
            return "CameraComponent";
        }

        std::string GetName() const override
        {
            return GetStaticName();
        }

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
    };
};

#endif /* !CAMERACOMPONENT_HPP_ */
