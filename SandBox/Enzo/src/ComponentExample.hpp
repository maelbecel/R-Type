/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** ComponentExample
*/

#ifndef COMPONENTEXAMPLE_HPP_
    #define COMPONENTEXAMPLE_HPP_

    #include "Exodia.hpp"

    // GLM includes
    #include <glm/glm.hpp>
    #include <glm/gtc/matrix_transform.hpp>
    #define GLM_ENABLE_EXPERIMENTAL
        #include <glm/gtx/quaternion.hpp>

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

    /**
     * @brief Animation component.
     *
     * @param CurrentFrame Current frame of the animation.
     * @param MaxFrame Max frame of the animation.
     * @param FrameTime Time between each frame.
     */
    struct Animation : public Component {
        static std::string GetStaticName()
        {
            return "Animation";
        }

        virtual std::string GetName() const
        {
            return GetStaticName();
        }

        float CurrentFrame;
        float MaxFrame;
        float FrameTime;
        float ElapsedTime = 0.0f;

        Animation(const Animation &) = default;
        Animation(float CurrentFrame = 0.0f, float MaxFrame = 0.0f, float FrameTime = 0.0f) : CurrentFrame(CurrentFrame), MaxFrame(MaxFrame), FrameTime(FrameTime) {};

        virtual void Serialize(UNUSED YAML::Emitter &out) override {};
    };

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

#endif /* !COMPONENTEXAMPLE_HPP_ */
