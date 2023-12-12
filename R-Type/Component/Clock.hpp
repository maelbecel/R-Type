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
        static std::string GetStaticName()
        {
            return "Clock";
        }

        virtual std::string GetName() const
        {
            return GetStaticName();
        }

        float ElapsedTime;

        Clock(const Clock &) = default;
        Clock(float ElapsedTime = 0.0f) : ElapsedTime(ElapsedTime) {};

        virtual void Serialize(UNUSED YAML::Emitter &out) override {};
    };
};

#endif /* !CLOCKCOMPONENT_HPP_ */
