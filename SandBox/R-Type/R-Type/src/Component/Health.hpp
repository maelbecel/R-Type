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
        Health(int maxHealth = 1) : CurrentHealth(maxHealth), MaxHealth(maxHealth){};

        void Serialize(YAML::Emitter &out) override {
            out << YAML::Key << "Health";
            out << YAML::BeginMap;
            {
                out << YAML::Key << "CurrentHealth" << YAML::Value << CurrentHealth;
                out << YAML::Key << "MaxHealth" << YAML::Value << MaxHealth;
            }
            out << YAML::EndMap;
        }

        void Deserialize(const YAML::Node &node) {
            try {
                auto tag = node["Health"];

                CurrentHealth = tag["CurrentHealth"].as<int>();
                MaxHealth = tag["MaxHealth"].as<int>();
            } catch (const YAML::Exception &e) {
                EXODIA_CORE_WARN("Health deserialization failed: {0}", e.what());
            }
        }

        Buffer SerializeData() override {
            try {
                uint64_t size = sizeof(int) * 2;
                Buffer buffer(size);

                std::memcpy(buffer.Data, &CurrentHealth, sizeof(int));
                std::memcpy(buffer.Data + sizeof(int), &MaxHealth, sizeof(int));

                return buffer;

            } catch (const std::exception &e) {
                EXODIA_CORE_ERROR("Error while serializing Health component: {0}", e.what());
                return Buffer();
            }
        }

        void DeserializeData(Buffer buffer) override {
            if (!buffer || buffer.Size == 0)
                return;
            try {
                uint64_t size = 0;
                Memcopy(&CurrentHealth, buffer.Data, sizeof(int));
                size += sizeof(int);
                Memcopy(&MaxHealth, buffer.Data + size, sizeof(int));
            } catch (const std::exception &e) {
                EXODIA_CORE_ERROR("Error while deserializing Health component: {0}", e.what());
            }
        }
    };
}; // namespace Exodia

#endif /* !HEALTHCOMPONENT_HPP_ */
