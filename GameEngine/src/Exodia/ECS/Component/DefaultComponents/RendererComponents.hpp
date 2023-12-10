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

    // External include
    #include <yaml-cpp/yaml.h>
    #include <glm/glm.hpp>

namespace Exodia {

    struct SpriteRendererComponent {
        glm::vec4         Color;
        Ref<SubTexture2D> Texture;
        float             TilingFactor;

        SpriteRendererComponent(const SpriteRendererComponent &) = default;
        SpriteRendererComponent(const glm::vec4 &color = glm::vec4(1.0f)) : Color(color), TilingFactor(1.0f) {};

        void Serialize(YAML::Emitter &out)
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
    };

    struct CircleRendererComponent {
        glm::vec4      Color;
        float          Thickness;
        float          Fade;

        CircleRendererComponent(const CircleRendererComponent &) = default;
        CircleRendererComponent(const glm::vec4 &color = glm::vec4(1.0f)) : Color(color), Thickness(1.0f), Fade(0.005f) {};

        void Serialize(YAML::Emitter &out)
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
    };

    // TODO: Implement Text Renderer Component when available
};

#endif /* !RENDERERCOMPONENTS_HPP_ */
