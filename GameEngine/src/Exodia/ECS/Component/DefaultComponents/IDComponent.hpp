/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** IDComponent
*/

#ifndef IDCOMPONENT_HPP_
    #define IDCOMPONENT_HPP_

    // Exodia UUID includes
    #include "Core/ID/UUID.hpp"

    // Exodia ECS includes
    #include "ECS/Interface/Component.hpp"

namespace Exodia {

    struct IDComponent : public Component {
        static std::string GetStaticName()
        {
            return "IDComponent";
        }

        std::string GetName() const override
        {
            return GetStaticName();
        }

        UUID ID;

        IDComponent(const IDComponent &) = default;
        IDComponent(const UUID &uuid = UUID()) : ID(uuid) {};

        virtual void Serialize(UNUSED YAML::Emitter &out)
        {
            return;
        }
    };
};

#endif /* !IDCOMPONENT_HPP_ */
