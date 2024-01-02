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

        virtual void Serialize(UNUSED(YAML::Emitter &out)) override{};

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
            try {
                std::memcpy(&ElapsedTime, buffer.Data, sizeof(float));
            } catch (const std::exception &e) {
                EXODIA_CORE_WARN("ClockComponent deserialization failed: {0}", e.what());
            }
        }
    };
}; // namespace Exodia

#endif /* !CLOCKCOMPONENT_HPP_ */
