/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Animation
*/

#ifndef ANIMATION_HPP_
#define ANIMATION_HPP_

// Exodia includes
#include "Exodia.hpp"

// External includes
#include <vector>

namespace RType {

    /**
     * @brief Animation Component.
     *
     * This component represents an animation in the game.
     * It contains :
     * - A list of frames (in SubTexture2D format)
     * - A boolean indicating if the animation is playing
     * - A boolean indicating if the animation should repeat
     * - A float indicating the frame rate of the animation (in seconds) (FrameRate represents the time between each
     * frame) (like Timestep)
     * - A float indicating the time since the last frame change (in seconds)
     * - An integer indicating the current frame of the animation
     */
    struct AnimationComponent : public Exodia::Component {
        std::vector<Ref<Exodia::SubTexture2D>>
            Frames; // !< List containing all the frames of the animation in SubTexture2D format

        bool IsPlaying; // !< Boolean indicating if the animation is playing
        bool Repeat;    // !< Boolean indicating if the animation should repeat

        float FrameRate;  // !< Float indicating the frame rate of the animation (in seconds) (FrameRate represents the
                          // time between each frame) (like Timestep)
        float FrameTimer; // !< Float indicating the time since the last frame change (in seconds)

        int CurrentFrameIndex; // !< Integer indicating the current frame of the animation

        AnimationComponent(const AnimationComponent &other)
            : Frames(other.Frames), IsPlaying(other.IsPlaying), Repeat(other.Repeat), FrameRate(other.FrameRate),
              FrameTimer(other.FrameTimer), CurrentFrameIndex(other.CurrentFrameIndex){};
        AnimationComponent(const std::vector<Ref<Exodia::SubTexture2D>> &frames = {})
            : Frames(frames), IsPlaying(false), Repeat(false), FrameRate(0.0f), FrameTimer(0.0f),
              CurrentFrameIndex(0){};

        AnimationComponent &operator=(const AnimationComponent &other) {
            Frames = other.Frames;
            IsPlaying = other.IsPlaying;
            Repeat = other.Repeat;
            FrameRate = other.FrameRate;
            FrameTimer = other.FrameTimer;
            CurrentFrameIndex = other.CurrentFrameIndex;

            return *this;
        }

        void DeserializeData(Exodia::Buffer data) {
            if (!data || data.Size == 0)
                return;
            try {
                size_t offset = 0;

                Memcopy(&IsPlaying, data.Data, sizeof(IsPlaying));
                offset += sizeof(IsPlaying);

                Memcopy(&Repeat, data.Data + offset, sizeof(Repeat));
                offset += sizeof(Repeat);

                Memcopy(&FrameRate, data.Data + offset, sizeof(FrameRate));
                offset += sizeof(FrameRate);

                Memcopy(&FrameTimer, data.Data + offset, sizeof(FrameTimer));
                offset += sizeof(FrameTimer);

                Memcopy(&CurrentFrameIndex, data.Data + offset, sizeof(CurrentFrameIndex));
                offset += sizeof(CurrentFrameIndex);

                EXODIA_CORE_WARN("AnimationComponent::DeserializeData: {0}", CurrentFrameIndex);

                size_t size = 0;

                Memcopy(&size, data.Data + offset, sizeof(size));

                offset += sizeof(size);

                for (size_t i = 0; i < size; i++) {
                    Exodia::AssetHandle assetHandle(0);
                    glm::vec2 coords;
                    glm::vec2 cellSize;
                    glm::vec2 spriteSize;

                    Memcopy(&assetHandle, data.Data + offset, sizeof(assetHandle));
                    offset += sizeof(assetHandle);

                    Memcopy(&coords, data.Data + offset, sizeof(coords));
                    offset += sizeof(coords);

                    Memcopy(&cellSize, data.Data + offset, sizeof(cellSize));
                    offset += sizeof(cellSize);

                    Memcopy(&spriteSize, data.Data + offset, sizeof(spriteSize));
                    offset += sizeof(spriteSize);

                    Ref<Exodia::SubTexture2D> subTexture2D =
                        Exodia::SubTexture2D::CreateFromCoords(assetHandle, coords, cellSize, spriteSize);

                    Frames.push_back(subTexture2D);
                }
            } catch (const std::exception &e) {
                EXODIA_ERROR("Error while deserializing AnimationComponent: {0}", e.what());
            }
        }

        Exodia::Buffer SerializeData() {
            try {
                size_t size = sizeof(IsPlaying) + sizeof(Repeat) + sizeof(FrameRate) + sizeof(FrameTimer) +
                              sizeof(CurrentFrameIndex) + sizeof(Frames.size());
                size_t offset = 0;
                Exodia::Buffer buffer(size);
                size_t frame = Frames.size();

                Memcopy(buffer.Data, &IsPlaying, sizeof(IsPlaying));
                offset += sizeof(IsPlaying);

                Memcopy(buffer.Data + offset, &Repeat, sizeof(Repeat));
                offset += sizeof(Repeat);

                Memcopy(buffer.Data + offset, &FrameRate, sizeof(FrameRate));
                offset += sizeof(FrameRate);

                Memcopy(buffer.Data + offset, &FrameTimer, sizeof(FrameTimer));
                offset += sizeof(FrameTimer);

                Memcopy(buffer.Data + offset, &CurrentFrameIndex, sizeof(CurrentFrameIndex));
                offset += sizeof(CurrentFrameIndex);

                Memcopy(buffer.Data + offset, &frame, sizeof(frame));
                offset += sizeof(frame);

                for (size_t i = 0; i < frame; i++) {
                    Ref<Exodia::SubTexture2D> Texture = Frames[i];

                    buffer.Resize(buffer.Size + sizeof(Texture->GetAssetHandle()) + sizeof(Texture->GetCoords()) +
                                  sizeof(Texture->GetTextureCellSize()) + sizeof(Texture->GetTextureSpriteSize()));

                    Exodia::AssetHandle assetHandle = Texture->GetAssetHandle();

                    std::memcpy(buffer.Data + offset, &assetHandle, sizeof(Texture->GetAssetHandle()));
                    offset += sizeof(Texture->GetAssetHandle());

                    std::memcpy(buffer.Data + offset, &(Texture->GetCoords()), sizeof(Texture->GetCoords()));
                    offset += sizeof(Texture->GetCoords());

                    std::memcpy(buffer.Data + offset, &Texture->GetTextureCellSize(),
                                sizeof(Texture->GetTextureCellSize()));
                    offset += sizeof(Texture->GetTextureCellSize());

                    std::memcpy(buffer.Data + offset, &Texture->GetTextureSpriteSize(),
                                sizeof(Texture->GetTextureSpriteSize()));
                    offset += sizeof(Texture->GetTextureSpriteSize());
                }
                return buffer;
            } catch (const std::exception &e) {
                EXODIA_ERROR("Error while serializing AnimationComponent: {0}", e.what());
            }
            return Exodia::Buffer();
        }

        void Serialize(YAML::Emitter &out) override {
            out << YAML::Key << "Animation";
            out << YAML::BeginMap;
            {
                out << YAML::Key << "IsPlaying" << YAML::Value << IsPlaying;
                out << YAML::Key << "Repeat" << YAML::Value << Repeat;
                out << YAML::Key << "FrameRate" << YAML::Value << FrameRate;
                out << YAML::Key << "FrameTimer" << YAML::Value << FrameTimer;
                out << YAML::Key << "CurrentFrameIndex" << YAML::Value << CurrentFrameIndex;

                out << YAML::Key << "Frames" << YAML::Value << YAML::Flow;
                out << YAML::BeginSeq;
                {
                    for (auto &frame : Frames) {
                        if (frame == nullptr || frame->GetTexture() == nullptr)
                            continue;
                        out << YAML::BeginMap;
                        {
                            out << YAML::Key << "AssetHandle" << YAML::Value << (uint64_t)frame->GetAssetHandle();
                            out << YAML::Key << "Coords" << YAML::Value << YAML::Flow;
                            { out << YAML::BeginSeq << frame->GetCoords().x << frame->GetCoords().y << YAML::EndSeq; }
                            out << YAML::Key << "CellSize" << YAML::Value << YAML::Flow;
                            {
                                out << YAML::BeginSeq << frame->GetTextureCellSize().x << frame->GetTextureCellSize().y
                                    << YAML::EndSeq;
                            }
                            out << YAML::Key << "SpriteSize" << YAML::Value << YAML::Flow;
                            {
                                out << YAML::BeginSeq << frame->GetTextureSpriteSize().x
                                    << frame->GetTextureSpriteSize().y << YAML::EndSeq;
                            }
                        }
                        out << YAML::EndMap;
                    }
                }
                out << YAML::EndSeq;
            }
            out << YAML::EndMap;
        }

        void Deserialize(const YAML::Node &node) override {
            try {
                auto sprite = node["Animation"];

                IsPlaying = sprite["IsPlaying"].as<bool>();
                Repeat = sprite["Repeat"].as<bool>();
                FrameRate = sprite["FrameRate"].as<float>();
                FrameTimer = sprite["FrameTimer"].as<float>();
                CurrentFrameIndex = sprite["CurrentFrameIndex"].as<int>();

                auto frames = sprite["Frames"];

                if (!frames)
                    return;

                for (auto frame : frames) {
                    if (frame["AssetHandle"] && frame["Coords"] && frame["CellSize"] && frame["SpriteSize"]) {
                        glm::vec2 coords = glm::vec2(frame["Coords"][0].as<float>(), frame["Coords"][1].as<float>());
                        glm::vec2 cellSize =
                            glm::vec2(frame["CellSize"][0].as<float>(), frame["CellSize"][1].as<float>());
                        glm::vec2 spriteSize =
                            glm::vec2(frame["SpriteSize"][0].as<float>(), frame["SpriteSize"][1].as<float>());

                        Exodia::AssetHandle assetHandle = frame["AssetHandle"].as<uint64_t>();

                        Ref<Exodia::SubTexture2D> subTexture2D =
                            Exodia::SubTexture2D::CreateFromCoords(assetHandle, coords, cellSize, spriteSize);

                        Frames.push_back(subTexture2D);
                    }
                }
            } catch (YAML::BadConversion &error) {
                EXODIA_CORE_WARN("Animation has invalid data !\n\t{0}", error.what());
            }
        }
    };
}; // namespace RType

#endif /* !ANIMATION_HPP_ */