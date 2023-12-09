/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** ExodiaEngine
*/

#include "EditorLayer.hpp"
#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Exodia {

    //////////////////////////////
    // Constructor & Destructor //
    //////////////////////////////

    EditorLayer::EditorLayer() : Layer("Exodia Editor") {};

    /////////////
    // Methods //
    /////////////

    void EditorLayer::OnAttach()
    {
        EXODIA_PROFILE_FUNCTION();

        auto commandLine = Application::Get().GetSpecification().CommandLineArgs;

        if (commandLine.Count > 1) {
            auto path = commandLine[1];

            OpenProject(path);

            if (Project::GetActive() == nullptr) {
                EXODIA_ERROR("Failed to open project: {0}", path);

                Application::Get().Close();
                return;
            }
        } else {
            if (!OpenProject()) {
                Application::Get().Close();
                return;
            }
            // TODO: If the user have no project create one and ask for a path and a name
        }
        
        _Texture = TextureImporter::LoadTexture2D("./Assets/Textures/Baldur.png");
    }

    void EditorLayer::OnDetach()
    {
        EXODIA_PROFILE_FUNCTION();
    }

    void EditorLayer::OnUpdate(UNUSED Exodia::Timestep ts)
    {
        EXODIA_PROFILE_FUNCTION();
    }

    void EditorLayer::OnImGUIRender()
    {
        _ContentBrowser->OnImGuiRender();

        ImGui::Begin("Settings");

        ImGui::Image(reinterpret_cast<ImTextureID>(_Texture->GetRendererID()), ImVec2(_Texture->GetWidth(), _Texture->GetHeight()), { 0, 1 }, { 1, 0 });

        ImGui::End();
    }

    void EditorLayer::OnEvent(UNUSED Exodia::Event &event) {};

    /////////////////////
    // Project Methods //
    /////////////////////

    void EditorLayer::NewProject()
    {
        Project::New();
    }

    bool EditorLayer::OpenProject()
    {
        std::string path = FileDialog::OpenFile("proj");

        if (path.empty())
            return false;

        OpenProject(path);
        return true;
    }

    void EditorLayer::OpenProject(const std::filesystem::path &path)
    {
        if (Project::Load(path)) {
            AssetHandle startScene = Project::GetActive()->GetConfig().StartScene;

            if (startScene)
                OpenScene(startScene);
            _ContentBrowser = CreateScope<ContentBrowser>(Project::GetActive());
        }
    }

    //TODO: void SaveProject(const std::filesystem::path &path);

    ///////////////////
    // Scene Methods //
    ///////////////////

    void EditorLayer::NewScene() {};

    void EditorLayer::OpenScene() {};

    void EditorLayer::OpenScene(UNUSED AssetHandle handle) {};

    void EditorLayer::SaveScene() {};

    void EditorLayer::SaveSceneAs() {};
};
