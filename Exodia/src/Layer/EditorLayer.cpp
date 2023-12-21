/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** ExodiaEngine
*/

#include "EditorLayer.hpp"
#include <imgui.h>
#include <ImGuizmo.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Exodia {

    //////////////////////////////
    // Constructor & Destructor //
    //////////////////////////////

    EditorLayer::EditorLayer() : Layer("Exodia Editor"), _EditorCamera(30.0f, 1.778f, 0.1f, 1000.0f), _ActiveScene(nullptr), _SceneState(SceneState::Edit), _ViewportSize{ 0.0f, 0.0f }, _ViewportHovered(false), _GuizmoType(-1) {};

    /////////////
    // Methods //
    /////////////

    void EditorLayer::OnAttach()
    {
        EXODIA_PROFILE_FUNCTION();

        Exodia::FramebufferSpecification fbSpec;

        fbSpec.Width       = Application::Get().GetWindow().GetWidth();
        fbSpec.Height      = Application::Get().GetWindow().GetHeight();
        fbSpec.Attachments = {
            FramebufferTextureFormat::RGBA8,
            FramebufferTextureFormat::RED_INTEGER,
            FramebufferTextureFormat::Depth
        };

        _Framebuffer = Exodia::Framebuffer::Create(fbSpec);

        _EditorScene = CreateRef<Scene>();

        _ActiveScene = _EditorScene;

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

        _PlayButton  = TextureImporter::LoadTexture2D("./Assets/Icons/ToolBar/PlayButton.png");
        _StopButton  = TextureImporter::LoadTexture2D("./Assets/Icons/ToolBar/StopButton.png");
        _PauseButton = TextureImporter::LoadTexture2D("./Assets/Icons/ToolBar/PauseButton.png");

        Renderer2D::SetLineWidth(4.0f);
    }

    void EditorLayer::OnDetach()
    {
        EXODIA_PROFILE_FUNCTION();
    }

    void EditorLayer::OnUpdate(UNUSED(Exodia::Timestep ts))
    {
        EXODIA_PROFILE_FUNCTION();

        Renderer2D::ResetStats();

        FramebufferSpecification spec = _Framebuffer->GetSpecification();

        // Resize the viewport
        if (_ViewportSize.x > 0.0f && _ViewportSize.y > 0.0f && (spec.Width != _ViewportSize.x || spec.Height != _ViewportSize.y)) {
            _Framebuffer->Resize((uint32_t)_ViewportSize.x, (uint32_t)_ViewportSize.y);
            _EditorCamera.SetViewportSize(_ViewportSize.x, _ViewportSize.y);
            
            if (_ActiveScene)
                _ActiveScene->OnViewportResize((uint32_t)_ViewportSize.x, (uint32_t)_ViewportSize.y);
        }

        // Bind the Framebuffer
        _Framebuffer->Bind();

        // Clear the screen
        RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
        RenderCommand::Clear();
        _Framebuffer->ClearAttachment(1, -1);

        switch(_SceneState) {
            case SceneState::Edit:
                _EditorCamera.OnUpdate(ts);

                if (_ActiveScene)
                    _ActiveScene->OnUpdateEditor(ts, _EditorCamera);
                break;
            case SceneState::Play:
                if (_ActiveScene)
                    _ActiveScene->OnUpdateRuntime(ts);
                break;
            default:
                break;
        }

         // Get Mouse Position in the Viewport window
        auto[mx, my] = ImGui::GetMousePos();

        mx -= _ViewportBounds[0].x;
        my -= _ViewportBounds[0].y;

        glm::vec2 viewportSize = _ViewportBounds[1] - _ViewportBounds[0];

        my = viewportSize.y - my;

        int mouseX = (int)mx;
        int mouseY = (int)my;

        // If the mouse is in the viewport window
        if (mouseX >= 0 && mouseY >= 0 && mouseX < (int)viewportSize.x && mouseY < (int)viewportSize.y) {
            int pixelData = _Framebuffer->ReadPixel(1, mouseX, mouseY);

            _HoveredEntity = (pixelData == -1) ? Entity() : Entity(&_ActiveScene->GetWorld(), (uint64_t)pixelData);
        }

        OnOverlayRender();

        // Unbind the Framebuffer
        _Framebuffer->Unbind();
    }

    void EditorLayer::OnImGUIRender()
    {
        EXODIA_PROFILE_FUNCTION();

            // -- DockSpace ----------------------------------------------------

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

        style.WindowMinSize.x = 300.0f;
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
            ImGuiID dockspace_id = ImGui::GetID("DockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

        style.WindowMinSize.x = minWinSizeX;

            // -- Menu Bar -----------------------------------------------------

        if (ImGui::BeginMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("Open Project...", "Ctrl+O"))
                    OpenProject();
                ImGui::Separator();

                if (ImGui::MenuItem("New Scene", "Ctrl+N"))
                    NewScene();
                if (ImGui::MenuItem("Save Scene", "Ctrl+S"))
                    SaveScene();
                if (ImGui::MenuItem("Save Scene As...", "Ctrl+Shift+S"))
                    SaveSceneAs();
                ImGui::Separator();

                if (ImGui::MenuItem("Exit"))
                    Application::Get().Close();                
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

            // -- Tool Bar -----------------------------------------------------

        ToolBarRendering();

            // -- Scene Hierarchy ----------------------------------------------

        _SceneHierarchy.OnImGuiRender();

            // -- Content Browser ----------------------------------------------

        if (_ContentBrowser)
            _ContentBrowser->OnImGuiRender();

            // -- Viewport -----------------------------------------------------

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
        ImGui::Begin("Viewport");

        ImVec2 viewportMinRegion = ImGui::GetWindowContentRegionMin();
        ImVec2 viewportMaxRegion = ImGui::GetWindowContentRegionMax();
        ImVec2 viewportOffset = ImGui::GetWindowPos();

        _ViewportBounds[0] = { viewportMinRegion.x + viewportOffset.x, viewportMinRegion.y + viewportOffset.y };
        _ViewportBounds[1] = { viewportMaxRegion.x + viewportOffset.x, viewportMaxRegion.y + viewportOffset.y };

        _ViewportHovered = ImGui::IsWindowHovered();

        Application::Get().GetImGuiLayer()->SetBlockEvents(!_ViewportHovered);

        ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();

        _ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };

        ImGui::Image(reinterpret_cast<ImTextureID>(_Framebuffer->GetColorAttachmentRendererID()), ImVec2{ _ViewportSize.x, _ViewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

            // 1. Drag and Drop
        if (ImGui::BeginDragDropTarget()) {
            const ImGuiPayload *payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM");

            if (payload) {
                AssetHandle handle = *(AssetHandle *)payload->Data;

                OpenScene(handle);
            }
            ImGui::EndDragDropTarget();
        }

            // 2. ImGuizmo

        Entity *selectedEntity = _SceneHierarchy.GetSelectedEntity();

        if (selectedEntity && selectedEntity->GetEntityID() != Entity::InvalidEntityID && _GuizmoType != -1) {
            ImGuizmo::SetOrthographic(false);
            ImGuizmo::SetDrawlist();
            ImGuizmo::SetRect(_ViewportBounds[0].x, _ViewportBounds[0].y, _ViewportBounds[1].x - _ViewportBounds[0].x, _ViewportBounds[1].y - _ViewportBounds[0].y);

            // -- Editor Camera
            const glm::mat4 &cameraProjection = _EditorCamera.GetProjection();
            glm::mat4 cameraView = _EditorCamera.GetViewMatrix();

            // Entity Transform
            auto transformComponent = selectedEntity->GetComponent<TransformComponent>();

            if (transformComponent) {
                auto &tc = transformComponent.Get();
                glm::mat4 transform = tc.GetTransform();

                // Snapping
                bool snap = Input::IsKeyPressed(Exodia::Key::LEFTCONTROL);
                float snapValue = 0.5f; // Snap to 0.5m for translation/scale

                // Snap to 45 degrees for rotation
                if (_GuizmoType == ImGuizmo::OPERATION::ROTATE)
                    snapValue = 45.0f;

                float snapValues[3] = { snapValue, snapValue, snapValue };

                ImGuizmo::Manipulate(glm::value_ptr(cameraView), glm::value_ptr(cameraProjection), (ImGuizmo::OPERATION)_GuizmoType, ImGuizmo::MODE::LOCAL, glm::value_ptr(transform), nullptr, snap ? snapValues : nullptr);

                if (ImGuizmo::IsUsing()) {
                    glm::vec3 translation;
                    glm::vec3 rotation;
                    glm::vec3 scale;

                    Math::DecomposeTransform(transform, translation, rotation, scale);

                    glm::vec3 deltaRotation = rotation - tc.Rotation;

                    tc.Translation = translation;
                    tc.Rotation   += deltaRotation;
                    tc.Scale       = scale;
                }
            }
        }

        ImGui::End();
        ImGui::PopStyleVar();

            // -- End DockSpace ------------------------------------------------

        ImGui::End();
    }

    void EditorLayer::OnEvent(UNUSED(Exodia::Event &event)) {};

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
            ScriptEngine::Init();

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

    void EditorLayer::NewScene()
    {
        _ActiveScene     = CreateRef<Scene>();

        _EditorScene     = _ActiveScene;

        _EditorScenePath = std::filesystem::path();

        _SceneHierarchy.SetContext(_ActiveScene);
    }

    void EditorLayer::OpenScene(AssetHandle handle)
    {
        if (_SceneState != SceneState::Edit)
            OnSceneStop();
        Ref<Scene> readOnly = AssetManager::GetAsset<Scene>(handle);
        Ref<Scene> scene    = Scene::Copy(readOnly);

        _EditorScene = scene;
        _ActiveScene = _EditorScene;

        _SceneHierarchy.SetContext(_ActiveScene);
        _EditorScenePath = Project::GetActive()->GetEditorAssetManager()->GetFilePath(handle);
    }

    void EditorLayer::SaveScene()
    {
        if (!_EditorScenePath.empty())
            SceneImporter::SaveScene(_ActiveScene, _EditorScenePath);
        else
            SaveSceneAs();
    }

    void EditorLayer::SaveSceneAs()
    {
        std::string path = FileDialog::SaveFile("exodia");

        if (path.empty())
            return;

        SceneImporter::SaveScene(_ActiveScene, path);

        _EditorScenePath = path;
    }

    void EditorLayer::OnSceneStart()
    {
        _SceneState = SceneState::Play;

        _ActiveScene = Scene::Copy(_EditorScene);

        _ActiveScene->OnRuntimeStart();
        _SceneHierarchy.SetContext(_ActiveScene);
    }

    void EditorLayer::OnSceneStop()
    {
        if (_SceneState == SceneState::Play)
            _ActiveScene->OnRuntimeStop();
        _SceneState = SceneState::Edit;
        _ActiveScene = _EditorScene;

        _SceneHierarchy.SetContext(_ActiveScene);
    }

    ///////////////////
    // ImGui Methods //
    ///////////////////

    void EditorLayer::ToolBarRendering()
    {
        ImGui::PushStyleVar  (ImGuiStyleVar_WindowPadding   , ImVec2(0, 2));
        ImGui::PushStyleVar  (ImGuiStyleVar_ItemInnerSpacing, ImVec2(0, 0));
        ImGui::PushStyleColor(ImGuiCol_Button               , ImVec4(0, 0, 0, 0));

        auto &colors = ImGui::GetStyle().Colors;
        const auto &buttonHovered = colors[ImGuiCol_ButtonHovered];

        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(buttonHovered.x, buttonHovered.y, buttonHovered.z, 0.5f));

        const auto &buttonActive = colors[ImGuiCol_ButtonActive];

        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(buttonActive.x, buttonActive.y, buttonActive.z, 0.5f));
        ImGui::Begin("##toolbar", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

        bool toolbarEnabled = (bool)_ActiveScene;

        ImVec4 tintColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

        if (!toolbarEnabled)
            tintColor.w = 0.5f;

        float size = ImGui::GetWindowHeight() - 4.0f;

        ImGui::SetCursorPosX((ImGui::GetWindowContentRegionMax().x * 0.5f) - (size * 0.5f));

        bool hasPlayButton = _SceneState == SceneState::Edit || _SceneState == SceneState::Play;
        bool hasPauseButton = _SceneState != SceneState::Edit;

        if (hasPlayButton) {
            Ref<Texture2D> icon = (_SceneState == SceneState::Edit) ? _PlayButton : _StopButton;

            if (ImGui::ImageButton(reinterpret_cast<ImTextureID>(icon->GetRendererID()), ImVec2(size, size), ImVec2(0, 0), ImVec2(1, 1), 0, ImVec4(0, 0, 0, 0), tintColor) && toolbarEnabled) {
                if (_SceneState == SceneState::Edit)
                    OnSceneStart();
                else if (_SceneState == SceneState::Play)
                    OnSceneStop();
            }
        }

        if (hasPauseButton) {
            bool isPaused = _ActiveScene->IsPaused();

            ImGui::SameLine();
            {
                Ref<Texture2D> icon = _PauseButton;

                if (ImGui::ImageButton(reinterpret_cast<ImTextureID>(icon->GetRendererID()), ImVec2(size, size), ImVec2(0, 0), ImVec2(1, 1), 0, ImVec4(0, 0, 0, 0), tintColor) && toolbarEnabled)
                    _ActiveScene->SetPaused(!isPaused);
            }
        }

        ImGui::PopStyleVar(2);
        ImGui::PopStyleColor(3);
        ImGui::End();
    }

    void EditorLayer::OnOverlayRender()
    {
        if (_SceneState == SceneState::Play) {
            Entity *camera = _ActiveScene->GetPrimaryCamera();

            if (!camera)
                return;

            Renderer2D::BeginScene(camera->GetComponent<CameraComponent>().Get().Camera, camera->GetComponent<TransformComponent>().Get().GetTransform());
        } else
            Renderer2D::BeginScene(_EditorCamera);

        // Draw Selected Entity Outline
        Entity *selectedEntity = _SceneHierarchy.GetSelectedEntity();

        if (selectedEntity) {
            auto transform = selectedEntity->GetComponent<TransformComponent>();

            if (transform) {
                auto &transformComponent = transform.Get();

                Renderer2D::DrawRect(transformComponent.GetTransform(), glm::vec4(1.0f, 0.5f, 0.0f, 1.0f));
            }
        }

        Renderer2D::EndScene();
    }
};
