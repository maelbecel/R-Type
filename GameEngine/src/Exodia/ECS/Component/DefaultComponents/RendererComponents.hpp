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
    #include <glm/gtc/type_ptr.hpp>

    // ImGui includes
    #include <imgui.h>

namespace Exodia {

    struct SpriteRendererComponent : public Component {
        glm::vec4         Color;
        Ref<SubTexture2D> Texture;
        float             TilingFactor;

        SpriteRendererComponent(const SpriteRendererComponent &) = default;
        SpriteRendererComponent(const glm::vec4 &color = glm::vec4(1.0f)) : Color(color), TilingFactor(1.0f) {};

        virtual void Serialize(YAML::Emitter &out) override
        {
            out << YAML::Key << "SpriteRendererComponent";
            out << YAML::BeginMap;
            {
                out << YAML::Key << "Color"        << YAML::Value << YAML::Flow;
                {
                    out << YAML::BeginSeq << Color.x << Color.y << Color.z << Color.w << YAML::EndSeq;
                }
                out << YAML::Key << "TilingFactor" << YAML::Value << TilingFactor;

                if (Texture != nullptr && Texture->GetTexture() != nullptr) {
                    out << YAML::Key << "Texture" << YAML::Value;
                    out << YAML::BeginMap;
                    {
                        out << YAML::Key << "AssetHandle" << YAML::Value << (uint64_t)Texture->GetTexture()->Handle;
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
            }
            out << YAML::EndMap;
        }

        virtual void Deserialize(const YAML::Node &node) override
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

        virtual void DrawComponent() override
        {
            std::string label = "None";
            bool isTextureValid = false;

            ImGui::ColorEdit4("Color", glm::value_ptr(Color));

            AssetHandle textureHandle = Texture != nullptr ? Texture->GetAssetHandle() : AssetHandle(0);

            if (textureHandle != 0) {
                if (AssetManager::IsAssetHandleValid(textureHandle) && AssetManager::GetAssetType(textureHandle) == AssetType::Texture2D) {
                    const AssetSpecification &spec = Project::GetActive()->GetEditorAssetManager()->GetAssetSpecification(textureHandle);

                    label          = spec.Path.filename().string();
                    isTextureValid = true;
                } else
                    label = "Invalid";
            }
            ImVec2 buttonLabelSize = ImGui::CalcTextSize(label.c_str());

            buttonLabelSize.x += 20.0f;

            float buttonLabelWidth = glm::max<float>(100.0f, buttonLabelSize.x);

            ImGui::Button(label.c_str(), ImVec2(buttonLabelWidth, 0.0f));

            if (ImGui::BeginDragDropTarget()) {
                if (const ImGuiPayload *payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM")) {
                    AssetHandle handle = *(AssetHandle *)payload->Data;

                    if (AssetManager::GetAssetType(handle) == AssetType::Texture2D)
                        Texture->SetTexture(handle);
                    else
                        EXODIA_CORE_WARN("Invalid asset type for SpriteRendererComponent !");
                }
                ImGui::EndDragDropTarget();
            }

            if (isTextureValid) {
                ImGui::SameLine();

                ImVec2 xLabelSize = ImGui::CalcTextSize("X");

                float buttonSize = xLabelSize.y + ImGui::GetStyle().FramePadding.y * 2.0f;

                if (ImGui::Button("X", ImVec2(buttonSize, buttonSize)))
                    Texture->SetTexture(AssetHandle(0));
            }
            ImGui::SameLine();
            ImGui::Text("Texture");

            ImGui::DragFloat("Tiling Factor", &TilingFactor, 0.1f, 0.0f, 100.0f);
        }
    };

    struct CircleRendererComponent : public Component {
        glm::vec4      Color;
        float          Thickness;
        float          Fade;

        CircleRendererComponent(const CircleRendererComponent &) = default;
        CircleRendererComponent(const glm::vec4 &color = glm::vec4(1.0f)) : Color(color), Thickness(1.0f), Fade(0.005f) {};

        virtual void Serialize(YAML::Emitter &out) override
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

        virtual void Deserialize(const YAML::Node &node) override
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

        virtual void DrawComponent() override
        {
            ImGui::ColorEdit4("Color"   , glm::value_ptr(Color));
            ImGui::DragFloat("Thickness", &Thickness);
            ImGui::DragFloat("Fade"     , &Fade);
        }
    };

    // TODO: Implement Text Renderer Component when available
};

#endif /* !RENDERERCOMPONENTS_HPP_ */
