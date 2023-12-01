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
        int CurrentFrame;
        int MaxFrame;
        float FrameTime;
        float CurrentTime;

        Animation(const Animation &) = default;
        Animation(int maxFrame = 0, float frameTime = 0.0f) : CurrentFrame(0), MaxFrame(maxFrame), FrameTime(frameTime), CurrentTime(0.0f) {};
    };
};

#endif /* !COMPONENTEXAMPLE_HPP_ */
