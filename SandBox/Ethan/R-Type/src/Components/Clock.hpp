/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Clock
*/

#ifndef CLOCK_HPP_
    #define CLOCK_HPP_

    // Exodia includes
    #include "Exodia.hpp"

namespace RType {

    struct ClockComponent : public Exodia::Component {
        float Time;
        float Duration;
        bool  Infinite;
        bool  Active;

        ClockComponent(const ClockComponent &other) = default;
        ClockComponent(float duration = 60.0f, bool active = true, bool infinite = false) : Time(0.0f), Duration(duration), Infinite(infinite), Active(active) {};

        void Serialize(YAML::Emitter &out) override
        {
            out << YAML::Key << "ClockComponent";
            out << YAML::BeginMap;
            {
                out << YAML::Key << "Time"     << YAML::Value << Time;
                out << YAML::Key << "Duration" << YAML::Value << Duration;
                out << YAML::Key << "Infinite" << YAML::Value << Infinite;
                out << YAML::Key << "Active"   << YAML::Value << Active;
            }
            out << YAML::EndMap;
        }

        void Deserialize(const YAML::Node &node)
        {
            try {
                auto fade = node["ClockComponent"];

                Time     = fade["Time"].as<float>();
                Duration = fade["Duration"].as<float>();
                Infinite = fade["Infinite"].as<bool>();
                Active   = fade["Active"].as<bool>();
            } catch (YAML::BadConversion &error) {
                EXODIA_CORE_WARN("ClockComponent deserialization failed:\n\t{0}", error.what());
            }
        }

        void DeserializeData(Exodia::Buffer data) override
        {
            if (!data || data.Size == 0)
                return;
            try {
                size_t offset = 0;

                Memcopy(&Time, data.Data, sizeof(Time));
                offset += sizeof(Time);

                Memcopy(&Duration, data.Data + offset, sizeof(Duration));
                offset += sizeof(Duration);

                Memcopy(&Infinite, data.Data + offset, sizeof(Infinite));
                offset += sizeof(Infinite);

                Memcopy(&Active, data.Data + offset, sizeof(Active));
            } catch (std::exception &e) {
                EXODIA_CORE_WARN("ClockComponent deserialization failed:\n\t{0}", e.what());
            }
        }

        Exodia::Buffer SerializeData() override
        {
            try {
                Exodia::Buffer buffer(sizeof(float) * 2 + sizeof(bool));
                size_t offset = 0;

                std::memcpy(buffer.Data, &Time, sizeof(Time));
                offset += sizeof(Time);

                std::memcpy(buffer.Data + offset, &Duration, sizeof(Duration));
                offset += sizeof(Duration);

                std::memcpy(buffer.Data + offset, &Infinite, sizeof(Infinite));
                offset += sizeof(Infinite);

                std::memcpy(buffer.Data + offset, &Active, sizeof(Active));

                return buffer;
            } catch (std::exception &e) {
                EXODIA_CORE_WARN("ClockComponent serialization failed:\n\t{0}", e.what());

                return Exodia::Buffer();
            }
        }
    };
};

#endif /* !CLOCK_HPP_ */
