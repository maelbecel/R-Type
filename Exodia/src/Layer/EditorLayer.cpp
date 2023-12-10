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
        EXODIA_PROFILE_FUNCTION();

        static bool dockspaceOpen                 = true;
        static bool opt_fullscreen_persistant     = true;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
        bool opt_fullscreen = opt_fullscreen_persistant;

        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

        if (opt_fullscreen) {
            ImGuiViewport *viewport = ImGui::GetMainViewport();

            ImGui::SetNextWindowPos(viewport->Pos);
            ImGui::SetNextWindowSize(viewport->Size);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }

        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace", &dockspaceOpen, window_flags);
        ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        // DockSpace
        ImGuiIO& io = ImGui::GetIO();
        ImGuiStyle& style = ImGui::GetStyle();

        float minWinSizeX = style.WindowMinSize.x;

        style.WindowMinSize.x = 450.0f;
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
            ImGuiID dockspace_id = ImGui::GetID("DockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

        style.WindowMinSize.x = minWinSizeX;

        if (_ContentBrowser)
            _ContentBrowser->OnImGuiRender();

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
