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

        bool ShouldFadeIn;
        bool ShouldFadeOut;

        bool Repeat;

        FadeComponent(const FadeComponent &other) = default;
        FadeComponent(float opacity = 1.0f, float fadeInSpeed = 1.0f, float fadeOutSpeed = 1.0f)
            : Opacity(opacity), FadeInSpeed(fadeInSpeed), FadeOutSpeed(fadeOutSpeed), ShouldFadeIn(false),
              ShouldFadeOut(false), Repeat(false){};

        void Serialize(YAML::Emitter &out) override {
            out << YAML::Key << "FadeComponent";
            out << YAML::BeginMap;
            {
                out << YAML::Key << "Opacity" << YAML::Value << Opacity;
                out << YAML::Key << "FadeInSpeed" << YAML::Value << FadeInSpeed;
                out << YAML::Key << "FadeOutSpeed" << YAML::Value << FadeOutSpeed;
                out << YAML::Key << "ShouldFadeIn" << YAML::Value << ShouldFadeIn;
                out << YAML::Key << "ShouldFadeOut" << YAML::Value << ShouldFadeOut;
                out << YAML::Key << "Repeat" << YAML::Value << Repeat;
            }
            out << YAML::EndMap;
        }

        void Deserialize(const YAML::Node &node) {
            try {
                auto fade = node["FadeComponent"];

                Opacity = fade["Opacity"].as<float>();
                FadeInSpeed = fade["FadeInSpeed"].as<float>();
                FadeOutSpeed = fade["FadeOutSpeed"].as<float>();
                ShouldFadeIn = fade["ShouldFadeIn"].as<bool>();
                ShouldFadeOut = fade["ShouldFadeOut"].as<bool>();
                Repeat = fade["Repeat"].as<bool>();
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

                Memcopy(&ShouldFadeIn, data.Data + offset, sizeof(ShouldFadeIn));
                offset += sizeof(ShouldFadeIn);

                Memcopy(&ShouldFadeOut, data.Data + offset, sizeof(ShouldFadeOut));
                offset += sizeof(ShouldFadeOut);

                Memcopy(&Repeat, data.Data + offset, sizeof(Repeat));
            } catch (std::exception &e) {
                EXODIA_CORE_WARN("FadeComponent deserialization failed:\n\t{0}", e.what());
            }
        }

        Exodia::Buffer SerializeData() override {
            try {
                Exodia::Buffer buffer(sizeof(float) * 3 + sizeof(bool) * 3);
                size_t offset = 0;

                std::memcpy(buffer.Data, &Opacity, sizeof(Opacity));
                offset += sizeof(Opacity);

                std::memcpy(buffer.Data + offset, &FadeInSpeed, sizeof(FadeInSpeed));
                offset += sizeof(FadeInSpeed);

                std::memcpy(buffer.Data + offset, &FadeOutSpeed, sizeof(FadeOutSpeed));
                offset += sizeof(FadeOutSpeed);

                std::memcpy(buffer.Data + offset, &ShouldFadeIn, sizeof(ShouldFadeIn));
                offset += sizeof(ShouldFadeIn);

                std::memcpy(buffer.Data + offset, &ShouldFadeOut, sizeof(ShouldFadeOut));
                offset += sizeof(ShouldFadeOut);

                std::memcpy(buffer.Data + offset, &Repeat, sizeof(Repeat));

                return buffer;
            } catch (std::exception &e) {
                EXODIA_CORE_WARN("FadeComponent serialization failed:\n\t{0}", e.what());

                return Exodia::Buffer();
            }
        }
    };
}; // namespace RType

#endif /* !FADE_HPP_ */
