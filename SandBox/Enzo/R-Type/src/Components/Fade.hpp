/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Fade
*/

#ifndef FADE_HPP_
#define FADE_HPP_

// Exodia includes
#include "Exodia.hpp"

namespace RType {

    struct FadeComponent : public Exodia::Component {
        float Opacity;

        float FadeInSpeed;
        float FadeOutSpeed;

        bool shouldFadeIn;
        bool shouldFadeOut;

        FadeComponent(const FadeComponent &other) = default;
        FadeComponent(float opacity = 1.0f, float fadeInSpeed = 1.0f, float fadeOutSpeed = 1.0f)
            : Opacity(opacity), FadeInSpeed(fadeInSpeed), FadeOutSpeed(fadeOutSpeed), shouldFadeIn(false),
              shouldFadeOut(false){};

        void Serialize(YAML::Emitter &out) override {
            out << YAML::Key << "FadeComponent";
            out << YAML::BeginMap;
            {
                out << YAML::Key << "Opacity" << YAML::Value << Opacity;
                out << YAML::Key << "FadeInSpeed" << YAML::Value << FadeInSpeed;
                out << YAML::Key << "FadeOutSpeed" << YAML::Value << FadeOutSpeed;
                out << YAML::Key << "shouldFadeIn" << YAML::Value << shouldFadeIn;
                out << YAML::Key << "shouldFadeOut" << YAML::Value << shouldFadeOut;
            }
            out << YAML::EndMap;
        }

        void Deserialize(const YAML::Node &node) {
            try {
                auto fade = node["FadeComponent"];

                Opacity = fade["Opacity"].as<float>();
                FadeInSpeed = fade["FadeInSpeed"].as<float>();
                FadeOutSpeed = fade["FadeOutSpeed"].as<float>();
                shouldFadeIn = fade["shouldFadeIn"].as<bool>();
                shouldFadeOut = fade["shouldFadeOut"].as<bool>();
            } catch (YAML::BadConversion &error) {
                EXODIA_CORE_WARN("FadeComponent deserialization failed:\n\t{0}", error.what());
            }
        }

        void DeserializeData(Exodia::Buffer data) override {
            if (!data || data.Size == 0)
                return;
            try {
                size_t offset = 0;

                Memcopy(&Opacity, data.Data, sizeof(Opacity));
                offset += sizeof(Opacity);

                Memcopy(&FadeInSpeed, data.Data + offset, sizeof(FadeInSpeed));
                offset += sizeof(FadeInSpeed);

                Memcopy(&FadeOutSpeed, data.Data + offset, sizeof(FadeOutSpeed));
                offset += sizeof(FadeOutSpeed);

                Memcopy(&shouldFadeIn, data.Data + offset, sizeof(shouldFadeIn));
                offset += sizeof(shouldFadeIn);

                Memcopy(&shouldFadeOut, data.Data + offset, sizeof(shouldFadeOut));
            } catch (std::exception &e) {
                EXODIA_CORE_WARN("FadeComponent deserialization failed:\n\t{0}", e.what());
            }
        }

        Exodia::Buffer SerializeData() override {
            try {
                Exodia::Buffer buffer(sizeof(float) * 3 + sizeof(bool) * 2);
                size_t offset = 0;

                std::memcpy(buffer.Data, &Opacity, sizeof(Opacity));
                offset += sizeof(Opacity);

                std::memcpy(buffer.Data + offset, &FadeInSpeed, sizeof(FadeInSpeed));
                offset += sizeof(FadeInSpeed);

                std::memcpy(buffer.Data + offset, &FadeOutSpeed, sizeof(FadeOutSpeed));
                offset += sizeof(FadeOutSpeed);

                std::memcpy(buffer.Data + offset, &shouldFadeIn, sizeof(shouldFadeIn));
                offset += sizeof(shouldFadeIn);

                std::memcpy(buffer.Data + offset, &shouldFadeOut, sizeof(shouldFadeOut));

                return buffer;
            } catch (std::exception &e) {
                EXODIA_CORE_WARN("FadeComponent serialization failed:\n\t{0}", e.what());

                return Exodia::Buffer();
            }
        }
    };
}; // namespace RType

#endif /* !FADE_HPP_ */
