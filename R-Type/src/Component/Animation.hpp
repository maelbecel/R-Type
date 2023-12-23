/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** ComponentExample
*/

#ifndef ANIMATIONCOMPONENT_HPP_
    #define ANIMATIONCOMPONENT_HPP_

    #include "Exodia.hpp"

namespace Exodia {

    /**
     * @brief Animation component.
     *
     * @param CurrentFrame Current frame of the animation.
     * @param MaxFrame Max frame of the animation.
     * @param FrameTime Time between each frame.
     */
    struct Animation : public Component {
        float CurrentFrame;
        float MaxFrame;
        float FrameTime;
        float ElapsedTime = 0.0f;

        Animation(const Animation &) = default;
        Animation(float CurrentFrame = 0.0f, float MaxFrame = 0.0f, float FrameTime = 0.0f) : CurrentFrame(CurrentFrame), MaxFrame(MaxFrame), FrameTime(FrameTime) {};

        virtual void Serialize(UNUSED(YAML::Emitter &out)) override {};

        virtual Buffer SerializeData()
        {
            try {
                uint64_t size = sizeof(float) * 4;
                Buffer buffer(size);

                std::memcpy(buffer.Data, &CurrentFrame, sizeof(float));
                std::memcpy(buffer.Data + sizeof(float), &MaxFrame, sizeof(float));
                std::memcpy(buffer.Data + sizeof(float) * 2, &FrameTime, sizeof(float));
                std::memcpy(buffer.Data + sizeof(float) * 3, &ElapsedTime, sizeof(float));

                return buffer;

            } catch (const std::exception &e) {
                EXODIA_CORE_ERROR("Error while serializing Animation component: {0}", e.what());
                return Buffer();
            }
        }

        virtual void DeserializeData(Buffer buffer)
        {
            try {
                uint64_t size = 0;
                Memcopy(&CurrentFrame, buffer.Data, sizeof(float));
                size += sizeof(float);
                Memcopy(&MaxFrame, buffer.Data + size, sizeof(float));
                size += sizeof(float);
                Memcopy(&FrameTime, buffer.Data + size, sizeof(float));
                size += sizeof(float);
                Memcopy(&ElapsedTime, buffer.Data + size, sizeof(float));
            } catch (const std::exception &e) {
                EXODIA_CORE_ERROR("Error while deserializing Animation component: {0}", e.what());
            }
        }
    };
};

#endif /* !ANIMATIONCOMPONENT_HPP_ */
