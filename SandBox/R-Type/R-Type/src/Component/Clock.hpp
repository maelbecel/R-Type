/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** ComponentExample
*/

#ifndef CLOCKCOMPONENT_HPP_
#define CLOCKCOMPONENT_HPP_

#include "Exodia.hpp"

namespace Exodia {
    /**
     * @brief Clock component.
     *
     * @param ElapsedTime Elapsed time of the entity.
     */
    struct Clock : public Component {
        float ElapsedTime;

        Clock(const Clock &) = default;
        Clock(float ElapsedTime = 0.0f) : ElapsedTime(ElapsedTime){};

        void Serialize(YAML::Emitter &out) override {
            out << YAML::Key << "Clock";
            out << YAML::BeginMap;
            { out << YAML::Key << "ElapsedTime" << YAML::Value << ElapsedTime; }
            out << YAML::EndMap;
        }

        void Deserialize(const YAML::Node &node) override {
            try {
                auto sprite = node["Clock"];

                ElapsedTime = sprite["ElapsedTime"].as<float>();
            } catch (YAML::BadConversion &error) {
                EXODIA_CORE_WARN("Clock has invalid data !\n\t{0}", error.what());
            }
        }

        virtual Buffer SerializeData() override {
            try {
                Buffer buffer(sizeof(float));

                std::memcpy(buffer.Data, &ElapsedTime, sizeof(float));

                return buffer;
            } catch (const std::exception &e) {
                EXODIA_CORE_WARN("ClockComponent serialization failed: {0}", e.what());
                return Buffer();
            }
        }

        virtual void DeserializeData(Buffer buffer) override {
            if (!buffer || buffer.Size == 0)
                return;

            try {
                std::memcpy(&ElapsedTime, buffer.Data, sizeof(float));
            } catch (const std::exception &e) {
                EXODIA_CORE_WARN("ClockComponent deserialization failed: {0}", e.what());
            }
        }
    };
}; // namespace Exodia

#endif /* !CLOCKCOMPONENT_HPP_ */
