/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** ContentBrowser
*/

// Panel includes
#include "ContentBrowser.hpp"

// ImGui includes
#include <imgui.h>

namespace Exodia {

    //////////////////////////////
    // Constructor & Destructor //
    //////////////////////////////

    ContentBrowser::ContentBrowser(Ref<Project> project) : _Project(project), _ThumbnailCache(CreateRef<ThumbnailCache>(project)), _BaseDirectory(project->GetAssetDirectory()), _CurrentDirectory(_BaseDirectory)
    {
        _TreeNodes.push_back(TreeNode(".", 0));

        _DirectoryIcon = TextureImporter::LoadTexture2D("./Assets/Icons/ContentBrowser/DirectoryIcon.png");
        _FileIcon      = TextureImporter::LoadTexture2D("./Assets/Icons/ContentBrowser/FileIcon.png");

        RefreshTreeAsset();
    }

    /////////////
    // Methods //
    /////////////

    void ContentBrowser::OnImGuiRender()
    {
        ImGui::Begin("Content Browser");

        GoToParentDirectory();

        static float padding = 30.0f;
        static float thumbnailSize = 150.0f;

        float cellSize = thumbnailSize + padding;
        float panelWidth = ImGui::GetContentRegionAvail().x;

        int columnCount = (int)(panelWidth / cellSize);

        if (columnCount < 1)
            columnCount = 1;

        ImGui::Columns(columnCount, 0, false);

        DrawFile(thumbnailSize);

        ImGui::Columns(1);

        ImGui::End();
    }

    void ContentBrowser::GoToParentDirectory()
    {
        if (_CurrentDirectory != std::filesystem::path(_BaseDirectory)) {
            ImGui::SameLine();

            if (ImGui::Button("<-"))
                _CurrentDirectory = _CurrentDirectory.parent_path();
        }
    }

    void ContentBrowser::DrawFile(float thumbnailSize)
    {
        for (auto &directoryEntry : std::filesystem::directory_iterator(_CurrentDirectory)) {
            const auto &path         = directoryEntry.path();
            std::string filename     = path.filename().string();
            Ref<Texture2D> thumbnail = _DirectoryIcon;

            ImGui::PushID(filename.c_str());

            auto relativePath = std::filesystem::relative(path, Project::GetActiveAssetDirectory());

            if (!directoryEntry.is_directory()) {
                thumbnail = _ThumbnailCache->GetOrCreateThumbnail(relativePath);

                if (!thumbnail)
                    thumbnail = _FileIcon;
            }

            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
            ImGui::ImageButton(reinterpret_cast<ImTextureID>(thumbnail->GetRendererID()), { thumbnailSize, thumbnailSize }, { 0, 1 }, { 1, 0 });

            if (ImGui::BeginPopupContextItem()) {
                if (ImGui::MenuItem("Import")) {
                    Project::GetActive()->GetEditorAssetManager()->ImportAsset(relativePath);

                    RefreshTreeAsset();
                }
                ImGui::EndPopup();
            }

            ImGui::PopStyleColor();

            if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left)) {
                if (directoryEntry.is_directory())
                    _CurrentDirectory /= filename;
            }

            ImGui::TextWrapped(filename.c_str());
            ImGui::NextColumn();
            ImGui::PopID();
        }
    }

    void ContentBrowser::RefreshTreeAsset()
    {
        const auto &assetRegistry = _Project->GetEditorAssetManager()->GetAssetRegistry();

        for (const auto &[handle, spec] : assetRegistry) {
            uint32_t currentNodeIndex = 0;

            for (const auto &path : spec.Path) {
                auto it = _TreeNodes[currentNodeIndex].Children.find(path.generic_string());

                if (it != _TreeNodes[currentNodeIndex].Children.end()) {
                    currentNodeIndex = it->second;
                } else {
                    TreeNode node(path, handle);

                    node.Parent = currentNodeIndex;

                    _TreeNodes.push_back(node);
                    _TreeNodes[currentNodeIndex].Children[path] = _TreeNodes.size() - 1;

                    currentNodeIndex = _TreeNodes.size() - 1;
                }
            }
        }
    }
};
