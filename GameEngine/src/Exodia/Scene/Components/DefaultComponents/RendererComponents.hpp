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
#include "Scene/Components/Component.hpp"

// Exodia Debug includes
#include "Exodia-Debug.hpp"

// External include
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

// ImGui includes
#include <imgui.h>

namespace Exodia {

    struct SpriteRendererComponent : public Component {
        glm::vec4 Color;
        Ref<SubTexture2D> Texture;
        float TilingFactor;

        SpriteRendererComponent(const SpriteRendererComponent &) = default;
        SpriteRendererComponent(const glm::vec4 &color = glm::vec4(1.0f)) : Color(color), TilingFactor(1.0f){};

        virtual void Serialize(YAML::Emitter &out) {
            out << YAML::Key << "SpriteRendererComponent";
            out << YAML::BeginMap;
            {
                out << YAML::Key << "Color" << YAML::Value << YAML::Flow;
                { out << YAML::BeginSeq << Color.x << Color.y << Color.z << Color.w << YAML::EndSeq; }
                out << YAML::Key << "TilingFactor" << YAML::Value << TilingFactor;

                if (Texture != nullptr && Texture->GetTexture() != nullptr) {
                    out << YAML::Key << "Texture" << YAML::Value;
                    out << YAML::BeginMap;
                    {
                        out << YAML::Key << "AssetHandle" << YAML::Value << (uint64_t)Texture->GetTexture()->Handle;
                        out << YAML::Key << "Coords" << YAML::Value << YAML::Flow;
                        { out << YAML::BeginSeq << Texture->GetCoords().x << Texture->GetCoords().y << YAML::EndSeq; }
                        out << YAML::Key << "CellSize" << YAML::Value << YAML::Flow;
                        {
                            out << YAML::BeginSeq << Texture->GetTextureCellSize().x << Texture->GetTextureCellSize().y
                                << YAML::EndSeq;
                        }
                        out << YAML::Key << "SpriteSize" << YAML::Value << YAML::Flow;
                        {
                            out << YAML::BeginSeq << Texture->GetTextureSpriteSize().x
                                << Texture->GetTextureSpriteSize().y << YAML::EndSeq;
                        }
                    }
                    out << YAML::EndMap;
                }
            }
            out << YAML::EndMap;
        }

        virtual void Deserialize(const YAML::Node &node) {
            try {
                auto sprite = node["SpriteRendererComponent"];

                Color = glm::vec4(sprite["Color"][0].as<float>(), sprite["Color"][1].as<float>(),
                                  sprite["Color"][2].as<float>(), sprite["Color"][3].as<float>());

                TilingFactor = sprite["TilingFactor"].as<float>();

                auto texture = sprite["Texture"];

                if (!texture)
                    return;

                if (texture["AssetHandle"] && texture["Coords"] && texture["CellSize"] && texture["SpriteSize"]) {
                    glm::vec2 coords = glm::vec2(texture["Coords"][0].as<float>(), texture["Coords"][1].as<float>());
                    glm::vec2 cellSize =
                        glm::vec2(texture["CellSize"][0].as<float>(), texture["CellSize"][1].as<float>());
                    glm::vec2 spriteSize =
                        glm::vec2(texture["SpriteSize"][0].as<float>(), texture["SpriteSize"][1].as<float>());

                    AssetHandle assetHandle = texture["AssetHandle"].as<uint64_t>();

                    Texture = SubTexture2D::CreateFromCoords(assetHandle, coords, cellSize, spriteSize);
                }
            } catch (YAML::BadConversion &error) {
                EXODIA_CORE_WARN("SpriteRendererComponent has invalid data !\n\t{0}", error.what());
            }
        }

        virtual Buffer SerializeData() override {
            try {
                Buffer buffer(sizeof(Color) + sizeof(TilingFactor) + sizeof(bool));
                size_t offset = 0;

                std::memcpy(buffer.Data, &Color, sizeof(Color));
                offset += sizeof(Color);
                std::memcpy(buffer.Data + offset, &TilingFactor, sizeof(TilingFactor));
                offset += sizeof(TilingFactor);

                bool hasTexture = (Texture != nullptr);

                std::memcpy(buffer.Data, &hasTexture, sizeof(bool));
                offset += sizeof(bool);

                if (Texture) {
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
            } catch (std::exception &e) {
                EXODIA_CORE_WARN("SpriteRendererComponent serialization failed: {0}", e.what());
                return Buffer();
            }
        }

        virtual void DeserializeData(Buffer data) override {
            try {
                if (!data || data.Size == 0)
                    return;

                size_t offset = 0;
                bool hasTexture = false;

                Memcopy(&Color, data.Data + offset, sizeof(Color));
                offset += sizeof(Color);
                Memcopy(&TilingFactor, data.Data + offset, sizeof(TilingFactor));
                offset += sizeof(TilingFactor);

                std::memcpy(&hasTexture, data.Data, sizeof(bool));
                offset += sizeof(bool);

                if (!hasTexture)
                    return;
                Exodia::AssetHandle assetHandle;
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

                Texture = SubTexture2D::CreateFromCoords(assetHandle, coords, cellSize, spriteSize);
            } catch (std::exception &e) {
                EXODIA_CORE_WARN("SpriteRendererComponent deserialization failed: {0}", e.what());
            }
        }

        virtual void DrawComponent() override {
            std::string label = "None";
            bool isTextureValid = false;

            ImGui::ColorEdit4("Color", glm::value_ptr(Color));

            AssetHandle textureHandle = Texture != nullptr ? Texture->GetAssetHandle() : AssetHandle(0);

            if (textureHandle != 0) {
                if (AssetManager::IsAssetHandleValid(textureHandle) &&
                    AssetManager::GetAssetType(textureHandle) == AssetType::Texture2D) {
                    const AssetSpecification &spec =
                        Project::GetActive()->GetEditorAssetManager()->GetAssetSpecification(textureHandle);

                    label = spec.Path.filename().string();
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
            ImGui::TextUnformatted("Texture");

            ImGui::DragFloat("Tiling Factor", &TilingFactor, 0.1f, 0.0f, 100.0f);
        }
    };

    struct CircleRendererComponent : public Component {
        glm::vec4 Color;
        float Thickness;
        float Fade;

        CircleRendererComponent(const CircleRendererComponent &) = default;
        CircleRendererComponent(const glm::vec4 &color = glm::vec4(1.0f))
            : Color(color), Thickness(1.0f), Fade(0.005f){};

        virtual void Serialize(YAML::Emitter &out) {
            out << YAML::Key << "CircleRendererComponent";
            out << YAML::BeginMap;
            {
                out << YAML::Key << "Color" << YAML::Value << YAML::Flow;
                { out << YAML::BeginSeq << Color.x << Color.y << Color.z << Color.w << YAML::EndSeq; }
                out << YAML::Key << "Thickness" << YAML::Value << Thickness;
                out << YAML::Key << "Fade" << YAML::Value << Fade;
            }
            out << YAML::EndMap;
        }

        virtual void Deserialize(const YAML::Node &node) {
            try {
                auto circle = node["CircleRendererComponent"];

                Color = glm::vec4(circle["Color"][0].as<float>(), circle["Color"][1].as<float>(),
                                  circle["Color"][2].as<float>(), circle["Color"][3].as<float>());

                Thickness = circle["Thickness"].as<float>();
                Fade = circle["Fade"].as<float>();
            } catch (YAML::BadConversion &e) {
                EXODIA_CORE_WARN("CircleRendererComponent deserialization failed: {0}", e.what());
            }
        }

        virtual void DrawComponent() override {
            ImGui::ColorEdit4("Color", glm::value_ptr(Color));
            ImGui::DragFloat("Thickness", &Thickness);
            ImGui::DragFloat("Fade", &Fade);
        }

        virtual Buffer SerializeData() override {
            try {
                Buffer buffer(sizeof(Color) + sizeof(Thickness) + sizeof(Fade));
                size_t offset = 0;

                std::memcpy(buffer.Data, &Color, sizeof(Color));
                offset += sizeof(Color);
                std::memcpy(buffer.Data + offset, &Thickness, sizeof(Thickness));
                offset += sizeof(Thickness);
                std::memcpy(buffer.Data + offset, &Fade, sizeof(Fade));
                return buffer;

            } catch (std::exception &e) {
                EXODIA_CORE_WARN("CircleRendererComponent serialization failed: {0}", e.what());
                return Buffer();
            }
        }

        virtual void DeserializeData(Buffer data) override {
            if (!data || data.Size == 0)
                return;

            try {
                size_t offset = 0;

                Memcopy(&Color, data.Data + offset, sizeof(Color));
                offset += sizeof(Color);
                Memcopy(&Thickness, data.Data + offset, sizeof(Thickness));
                offset += sizeof(Thickness);
                Memcopy(&Fade, data.Data + offset, sizeof(Fade));
            } catch (std::exception &e) {
                EXODIA_CORE_WARN("CircleRendererComponent deserialization failed: {0}", e.what());
            }
        }
    };

    struct TextRendererComponent : public Component {
        std::string Text;
        glm::vec4 Color;
        AssetHandle Font;
        float Kerning;
        float LineSpacing;

        TextRendererComponent(const TextRendererComponent &) = default;
        TextRendererComponent(const std::string &text = "", const glm::vec4 &color = glm::vec4(1.0f))
            : Text(text), Color(color), Font(0), Kerning(0.0f), LineSpacing(0.0f){};

        virtual void Serialize(YAML::Emitter &out) {
            out << YAML::Key << "TextRendererComponent";
            out << YAML::BeginMap;
            {
                out << YAML::Key << "Text" << YAML::Value << Text;
                out << YAML::Key << "Color" << YAML::Value << YAML::Flow;
                { out << YAML::BeginSeq << Color.x << Color.y << Color.z << Color.w << YAML::EndSeq; }
                out << YAML::Key << "Font" << YAML::Value << (uint64_t)Font;
                out << YAML::Key << "Kerning" << YAML::Value << Kerning;
                out << YAML::Key << "LineSpacing" << YAML::Value << LineSpacing;
            }
            out << YAML::EndMap;
        }

        virtual void Deserialize(const YAML::Node &node) {
            try {
                auto text = node["TextRendererComponent"];

                Text = text["Text"].as<std::string>();

                Color = glm::vec4(text["Color"][0].as<float>(), text["Color"][1].as<float>(),
                                  text["Color"][2].as<float>(), text["Color"][3].as<float>());

                Font = text["Font"].as<uint64_t>();

                Kerning = text["Kerning"].as<float>();
                LineSpacing = text["LineSpacing"].as<float>();
            } catch (YAML::BadConversion &error) {
                EXODIA_CORE_WARN("TextRendererComponent deserialization failed:\n\t{0}", error.what());
            }
        }

        // TODO: Implement TextRendererComponent::DrawComponent();

        virtual Buffer SerializeData() override {
            try {
                Buffer buffer(sizeof(glm::mat4) + sizeof(Font) + (sizeof(float) * 2) + sizeof(bool) +
                              (sizeof(char) * Text.size()));
                size_t offset = 0;

                std::memcpy(buffer.Data, &Color, sizeof(Color));
                offset += sizeof(Color);
                std::memcpy(buffer.Data + offset, &Font, sizeof(Font));
                offset += sizeof(Font);
                std::memcpy(buffer.Data + offset, &Kerning, sizeof(Kerning));
                offset += sizeof(Kerning);
                std::memcpy(buffer.Data + offset, &LineSpacing, sizeof(LineSpacing));
                offset += sizeof(LineSpacing);

                bool hasText = (Text.size() > 0);

                std::memcpy(buffer.Data + offset, &hasText, sizeof(bool));

                if (hasText)
                    std::memcpy(buffer.Data + offset, Text.data(), sizeof(char) * Text.size());

                return buffer;
            } catch (std::exception &e) {
                EXODIA_CORE_WARN("TextComponent serialization failed: {0}", e.what());
                return Buffer();
            }
        }

        virtual void DeserializeData(Buffer data) override {
            if (!data || data.Size == 0)
                return;

            try {
                size_t offset = 0;
                bool hasText = false;

                Memcopy(&Color, data.Data + offset, sizeof(Color));
                offset += sizeof(Color);
                Memcopy(&Font, data.Data + offset, sizeof(Font));
                offset += sizeof(Font);
                Memcopy(&Kerning, data.Data + offset, sizeof(Kerning));
                offset += sizeof(Kerning);
                Memcopy(&LineSpacing, data.Data + offset, sizeof(LineSpacing));
                offset += sizeof(LineSpacing);
                Memcopy(&hasText, data.Data + offset, sizeof(bool));
                offset += sizeof(bool);

                if (hasText) {
                    for (uint32_t i = 0; i < (data.Size - offset); i++)
                        Text.push_back((char)data.Data[i + offset]);
                }
            } catch (std::exception &e) {
                EXODIA_CORE_WARN("TextRendererComponent deserialization failed: {0}", e.what());
            }
        }
    };
}; // namespace Exodia

#endif /* !RENDERERCOMPONENTS_HPP_ */
