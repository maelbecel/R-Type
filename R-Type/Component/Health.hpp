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
    struct Health: public Component {
        static std::string GetStaticName()
        {
            return "Health";
        }

        virtual std::string GetName() const
        {
            return GetStaticName();
        }

        int CurrentHealth;
        int MaxHealth;

        Health(const Health &) = default;
        Health(int maxHealth = 100) : CurrentHealth(maxHealth), MaxHealth(maxHealth) {};

        virtual void Serialize(UNUSED YAML::Emitter &out) override {};
    };
};

#endif /* !HEALTHCOMPONENT_HPP_ */
