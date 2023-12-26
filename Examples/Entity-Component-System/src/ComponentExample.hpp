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
        glm::vec3 Translation;
        glm::vec3 Rotation;
        glm::vec3 Scale;

        Transform(const Transform &) = default;
        Transform(const glm::vec3 &translation = glm::vec3(0.0f))
            : Translation(translation), Rotation(glm::vec3(0.0f)), Scale(glm::vec3(1.0f)){};
    };

    struct Health : public Component {
        int CurrentHealth;
        int MaxHealth;

        Health(const Health &) = default;
        Health(int maxHealth = 100) : CurrentHealth(maxHealth), MaxHealth(maxHealth){};
    };
}; // namespace Exodia

#endif /* !COMPONENTEXAMPLE_HPP_ */
