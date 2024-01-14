/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** IDComponent
*/

#ifndef IDCOMPONENT_HPP_
#define IDCOMPONENT_HPP_

// Exodia UUID includes
#include "Exodia-Utils.hpp"
#include "Exodia-Debug.hpp"

// Exodia ECS includes
#include "Scene/Components/Component.hpp"

namespace Exodia {

    struct IDComponent : public Component {
        UUID ID;

        IDComponent(const IDComponent &) = default;
        IDComponent(const UUID &uuid = UUID()) : ID(uuid){};

        void DeserializeData(Buffer data) override {
            if (!data || data.Size == 0)
                return;
            try {
                uint64_t id = 0;

                std::memcpy(&id, data.Data, sizeof(uint64_t));

                ID = id;
            } catch (std::exception &error) {
                EXODIA_CORE_WARN("IDComponent deserialization failed:\n\t{0}", error.what());
            }
        }

        Buffer SerializeData() {
            try {
                Buffer buffer(sizeof(uint64_t));

                std::memcpy(buffer.Data, &ID, sizeof(uint64_t));

                return buffer;
            } catch (std::exception &error) {
                EXODIA_CORE_WARN("IDComponent serialization failed:\n\t{0}", error.what());
            }
            return Buffer();
        }
    };
}; // namespace Exodia

#endif /* !IDCOMPONENT_HPP_ */
