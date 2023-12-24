/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** ComponentExample
*/

#ifndef HEALTHCOMPONENT_HPP_
#define HEALTHCOMPONENT_HPP_

#include "Exodia.hpp"

namespace Exodia {

    /**
     * @brief Health component.
     *
     * @param CurrentHealth Current health of the entity.
     * @param MaxHealth Max health of the entity.
     */
    struct Health : public Component {
        int CurrentHealth;
        int MaxHealth;

        Health(const Health &) = default;
        Health(int maxHealth = 100) : CurrentHealth(maxHealth), MaxHealth(maxHealth){};
    };
}; // namespace Exodia

#endif /* !HEALTHCOMPONENT_HPP_ */
