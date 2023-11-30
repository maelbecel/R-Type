/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Components
*/

#ifndef COMPONENTS_HPP_
    #define COMPONENTS_HPP_

    // Exodia Core
    #include "Core/ID/UUID.hpp"

    // Exodia Renderer
    #include "Renderer/Texture/SubTexture2D.hpp"

    // Exodia Scene
    #include "Scene/Camera/SceneCamera.hpp"

    // Exodia Script
    #include "Script/ScriptableEntity.hpp"

    // GLM includes
    #include <glm/glm.hpp>
    #include <glm/gtc/matrix_transform.hpp>
    #define GLM_ENABLE_EXPERIMENTAL
        #include <glm/gtx/quaternion.hpp>

    // External includes
    #include <string>

namespace Exodia {

    struct IDComponent {
        UUID ID;

        IDComponent(const IDComponent &) = default;
        IDComponent(const UUID &uuid = UUID()) : ID(uuid) {};
    };

    struct TagComponent {
        std::string Tag;

        TagComponent(const TagComponent &) = default;
        TagComponent(const std::string &tag = std::string()) : Tag(tag) {};
    };

    struct TransformComponent {
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
    };

    struct SpriteRendererComponent {
        glm::vec4         Color;
        Ref<SubTexture2D> Texture;
        float             TilingFactor;

        SpriteRendererComponent(const SpriteRendererComponent &) = default;
        SpriteRendererComponent(const glm::vec4 &color = glm::vec4(1.0f)) : Color(color), TilingFactor(1.0f) {};
    };

    struct CircleRendererComponent {
        glm::vec4      Color;
        float          Thickness;
        float          Fade;

        CircleRendererComponent(const CircleRendererComponent &) = default;
        CircleRendererComponent(const glm::vec4 &color = glm::vec4(1.0f)) : Color(color), Thickness(1.0f), Fade(0.005f) {};
    };

    struct CameraComponent {
        SceneCamera Camera;
        bool        Primary;
        bool        FixedAspectRatio;

        CameraComponent(const CameraComponent &) = default;
        CameraComponent() : Primary(true), FixedAspectRatio(false) {};
    };

    struct ScriptComponent {
        ScriptableEntity *Instance = nullptr;

        ScriptableEntity *(*InstantiateScript)();
        void              (*DestroyScript)(ScriptComponent *);

        template<typename ScriptClass>
        void Bind()
        {
            InstantiateScript = []() {
                return static_cast<ScriptableEntity *>(new ScriptClass());
            };

            DestroyScript = [](ScriptComponent *script) {
                if (script->Instance != nullptr) {
                    delete script->Instance;
                    script->Instance = nullptr;
                }
            };
        }
    };

    struct BoxCollider2DComponent {
        glm::vec2 Offset;
        glm::vec2 Size;

        BoxCollider2DComponent(const BoxCollider2DComponent &) = default;
        BoxCollider2DComponent() : Offset(glm::vec2(0.0f)), Size(glm::vec2(0.5f)) {};
    };

    struct CircleCollider2DComponent {
        glm::vec2 Offset;
        float     Radius;

        CircleCollider2DComponent(const CircleCollider2DComponent &) = default;
        CircleCollider2DComponent() : Offset(glm::vec2(0.0f)), Radius(0.5f) {};
    };

    struct RigidBody2DComponent {
        enum class BodyType {
            Static,
            Dynamic
        };

        BodyType Type;
        glm::vec2 Velocity;
        float GravityScale;
        float Mass;

        RigidBody2DComponent(const RigidBody2DComponent &) = default;
        RigidBody2DComponent() : Type(BodyType::Static), Velocity(glm::vec2(0.0f)), GravityScale(1.0f), Mass(1.0f) {};
    };
};

#endif /* !COMPONENTS_HPP_ */
