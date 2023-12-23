/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** SoundComponent
*/

#ifndef SOUNDCOMPONENT_HPP_
    #define SOUNDCOMPONENT_HPP_

    // Exodia ECS includes
    #include "ECS/Interface/Component.hpp"

    // Exodia Asset includes
    #include "Asset/Utils/AssetType.hpp"

namespace Exodia {

    struct SoundComponent : public Component {
        AssetHandle Handle;
        float       Volume;
        bool        Loop;

        SoundComponent(const SoundComponent &) = default;
        SoundComponent(AssetHandle handle = 0, float volume = 0.50f, bool loop = false) : Handle(handle), Volume(volume), Loop(loop) {};

        virtual void Serialize(YAML::Emitter &out)
        {
            out << YAML::Key << "SoundComponent";
            out << YAML::BeginMap;
            {
                out << YAML::Key << "Handle" << YAML::Value << (uint64_t)Handle;
                out << YAML::Key << "Volume" << YAML::Value << Volume;
                out << YAML::Key << "Loop"   << YAML::Value << Loop;
            }
            out << YAML::EndMap;
        }

        virtual void Deserialize(const YAML::Node &node)
        {
            try {
                auto sound = node["SoundComponent"];

                Handle = sound["Handle"].as<uint64_t>();
                Volume = sound["Volume"].as<float>();
                Loop   = sound["Loop"].as<bool>();
            } catch (YAML::BadConversion &error) {
                EXODIA_CORE_WARN("SoundComponent deserialization failed:\n\t{0}", error.what());
            }
        }

        virtual Buffer SerializeData() override
        {
            try {
                Buffer buffer(sizeof(Handle) + sizeof(Volume) + sizeof(Loop));
                size_t offset = 0;

                std::memcpy(buffer.Data, &Handle, sizeof(Handle));
                offset += sizeof(Handle);

                std::memcpy(buffer.Data + offset, &Volume, sizeof(Volume));
                offset += sizeof(Volume);

                std::memcpy(buffer.Data + offset, &Loop, sizeof(Loop));

                return buffer;
            } catch (std::exception &e) {
                EXODIA_CORE_WARN("SoundComponent serialization failed:\n\t{0}", e.what());

                return Buffer();
            }
        }

        virtual void DeserializeData(Buffer data) override
        {
            try {
                size_t offset = 0;

                Memcopy(&Handle, data.Data + offset, sizeof(Handle));
                offset += sizeof(Handle);

                Memcopy(&Volume, data.Data + offset, sizeof(Volume));
                offset += sizeof(Volume);

                Memcopy(&Loop, data.Data + offset, sizeof(Loop));
            } catch (std::exception &e) {
                EXODIA_CORE_WARN("SoundComponent deserialization failed:\n\t{0}", e.what());
            }
        }

        // TODO: DrawComponent
    };
};

#endif /* !SOUNDCOMPONENT_HPP_ */
