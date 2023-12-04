/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** ComponentExample
*/

#ifndef COMPONENTEXAMPLE_HPP_
    #define COMPONENTEXAMPLE_HPP_

    // GLM includes
    #include <glm/glm.hpp>
    #include <glm/gtc/matrix_transform.hpp>
    #define GLM_ENABLE_EXPERIMENTAL
        #include <glm/gtx/quaternion.hpp>

namespace Exodia {

    struct Transform {
        glm::vec3 Translation;
        glm::vec3 Rotation;
        glm::vec3 Scale;

        Transform(const Transform &) = default;
        Transform(const glm::vec3 &translation = glm::vec3(0.0f)) : Translation(translation), Rotation(glm::vec3(0.0f)), Scale(glm::vec3(1.0f)) {};
    };

    struct Health {
        int CurrentHealth;
        int MaxHealth;

        Health(const Health &) = default;
        Health(int maxHealth = 100) : CurrentHealth(maxHealth), MaxHealth(maxHealth) {};
    };

    struct Animation {
        float CurrentFrame;
        float MaxFrame;
        float FrameTime;
        float elapsedTime = 0.0f;

        Animation(const Animation &) = default;
        Animation(float CurrentFrame = 0.0f, float MaxFrame = 0.0f, float FrameTime = 0.0f) : CurrentFrame(CurrentFrame), MaxFrame(MaxFrame), FrameTime(FrameTime) {};
    };
};

#endif /* !COMPONENTEXAMPLE_HPP_ */
