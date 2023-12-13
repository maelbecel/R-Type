/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** RendererComponents
*/

#ifndef RENDERERCOMPONENTS_HPP_
    #define RENDERERCOMPONENTS_HPP_

    // Exodia Renderer includes
    #include "Renderer/Texture/SubTexture2D.hpp"

    // Exodia ECS includes
    #include "ECS/Interface/Component.hpp"

    // Exodia Debug includes
    #include "Debug/Logs.hpp"

    // External include
    #include <glm/glm.hpp>

namespace Exodia {

    struct SpriteRendererComponent : public Component {
        static std::string GetStaticName()
        {
            return "SpriteRendererComponent";
        }

        std::string GetName() const override
        {
            return GetStaticName();
        }

        glm::vec4         Color;
        Ref<SubTexture2D> Texture;
        float             TilingFactor;

        SpriteRendererComponent(const SpriteRendererComponent &) = default;
        SpriteRendererComponent(const glm::vec4 &color = glm::vec4(1.0f)) : Color(color), TilingFactor(1.0f) {};

        virtual void Serialize(YAML::Emitter &out)
        {
            out << YAML::Key << "SpriteRendererComponent";
            out << YAML::BeginMap;
            {
                out << YAML::Key << "Color"        << YAML::Value << YAML::Flow;
                {
                    out << YAML::BeginSeq << Color.x << Color.y << Color.z << Color.w << YAML::EndSeq;
                }
                out << YAML::Key << "TilingFactor" << YAML::Value << TilingFactor;

                if (Texture && Texture->GetTexture()) {}
                    out << YAML::Key << "Texture" << YAML::Value;
                    out << YAML::BeginMap;
                    {
                        out << YAML::Key << "AssetHandle" << YAML::Value << (uint64_t)Texture->GetAssetHandle();
                        out << YAML::Key << "Coords"      << YAML::Value << YAML::Flow;
                        {
                            out << YAML::BeginSeq << Texture->GetCoords().x << Texture->GetCoords().y << YAML::EndSeq;
                        }
                        out << YAML::Key << "CellSize"    << YAML::Value << YAML::Flow;
                        {
                            out << YAML::BeginSeq << Texture->GetTextureCellSize().x << Texture->GetTextureCellSize().y << YAML::EndSeq;
                        }
                        out << YAML::Key << "SpriteSize"  << YAML::Value << YAML::Flow;
                        {
                            out << YAML::BeginSeq << Texture->GetTextureSpriteSize().x << Texture->GetTextureSpriteSize().y << YAML::EndSeq;
                        }
                    }
                    out << YAML::EndMap;
            }
            out << YAML::EndMap;
        }

        virtual void Deserialize(const YAML::Node &node)
        {
            try {
                auto sprite = node["SpriteRendererComponent"];

                Color = glm::vec4(sprite["Color"][0].as<float>(), sprite["Color"][1].as<float>(), sprite["Color"][2].as<float>(), sprite["Color"][3].as<float>());

                TilingFactor = sprite["TilingFactor"].as<float>();

                if (sprite["AssetHandle"] && sprite["Coords"] && sprite["CellSize"] && sprite["SpriteSize"]) {
                    glm::vec2 coords        = glm::vec2(sprite["Coords"][0].as<float>(), sprite["Coords"][1].as<float>());
                    glm::vec2 cellSize      = glm::vec2(sprite["CellSize"][0].as<float>(), sprite["CellSize"][1].as<float>());
                    glm::vec2 spriteSize    = glm::vec2(sprite["SpriteSize"][0].as<float>(), sprite["SpriteSize"][1].as<float>());

                    AssetHandle assetHandle = sprite["AssetHandle"].as<uint64_t>();

                    Texture = CreateRef<SubTexture2D>(assetHandle, coords, cellSize, spriteSize);
                }
            } catch (YAML::BadConversion &e) {
                EXODIA_CORE_WARN("SpriteRendererComponent has invalid data !");
            }
        }
    };

    struct CircleRendererComponent : public Component {
        static std::string GetStaticName()
        {
            return "CircleRendererComponent";
        }

        std::string GetName() const
        {
            return GetStaticName();
        }

        glm::vec4      Color;
        float          Thickness;
        float          Fade;

        CircleRendererComponent(const CircleRendererComponent &) = default;
        CircleRendererComponent(const glm::vec4 &color = glm::vec4(1.0f)) : Color(color), Thickness(1.0f), Fade(0.005f) {};

        virtual void Serialize(YAML::Emitter &out)
        {
            out << YAML::Key << "CircleRendererComponent";
            out << YAML::BeginMap;
            {
                out << YAML::Key << "Color"     << YAML::Value << YAML::Flow;
                {
                    out << YAML::BeginSeq << Color.x << Color.y << Color.z << Color.w << YAML::EndSeq;
                }
                out << YAML::Key << "Thickness" << YAML::Value << Thickness;
                out << YAML::Key << "Fade"      << YAML::Value << Fade;
            }
            out << YAML::EndMap;
        }

        virtual void Deserialize(const YAML::Node &node)
        {
            try {
                auto circle = node["CircleRendererComponent"];

                Color = glm::vec4(circle["Color"][0].as<float>(), circle["Color"][1].as<float>(), circle["Color"][2].as<float>(), circle["Color"][3].as<float>());

                Thickness = circle["Thickness"].as<float>();
                Fade      = circle["Fade"].as<float>();
            } catch (YAML::BadConversion &e) {
                EXODIA_CORE_WARN("CircleRendererComponent deserialization failed: {0}", e.what());
            }
        }
    };

    // TODO: Implement Text Renderer Component when available
};

#endif /* !RENDERERCOMPONENTS_HPP_ */
