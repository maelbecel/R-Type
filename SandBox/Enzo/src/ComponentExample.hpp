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

    /**
     * @brief Transform component.
     *
     * @param Translation Translation of the entity.
     * @param Rotation Rotation of the entity.
     * @param Scale Scale of the entity.
     */
    struct Transform {
        glm::vec3 Translation;
        glm::vec3 Rotation;
        glm::vec3 Scale;

        Transform(const Transform &) = default;
        Transform(const glm::vec3 &translation = glm::vec3(0.0f)) : Translation(translation), Rotation(glm::vec3(0.0f)), Scale(glm::vec3(1.0f)) {};
    };

    /**
     * @brief Health component.
     *
     * @param CurrentHealth Current health of the entity.
     * @param MaxHealth Max health of the entity.
     */
    struct Health {
        int CurrentHealth;
        int MaxHealth;

        Health(const Health &) = default;
        Health(int maxHealth = 100) : CurrentHealth(maxHealth), MaxHealth(maxHealth) {};
    };

    /**
     * @brief Animation component.
     *
     * @param CurrentFrame Current frame of the animation.
     * @param MaxFrame Max frame of the animation.
     * @param FrameTime Time between each frame.
     */
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
