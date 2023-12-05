/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** DefaultPlayer
*/

#include "DockerLayer.hpp"
#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Exodia {

    // -- Layer ----------------------------------------------------------------

    //////////////////////////////
    // Constructor & Destructor //
    //////////////////////////////

    DockerLayer::DockerLayer() : Layer("DefaultLayer"), _CameraController(1600.0f / 900.0f), _SquareColor({ 0.2f, 0.3f, 0.8f, 1.0f }) {};

    /////////////
    // Methods //
    /////////////

    void DockerLayer::OnAttach()
    {
        FramebufferSpecification fbSpec;

        fbSpec.Width = 1280;
        fbSpec.Height = 720;
        fbSpec.Attachments = {
            FramebufferTextureFormat::RGBA8,
            FramebufferTextureFormat::RED_INTEGER,
            FramebufferTextureFormat::Depth
        };

        _Framebuffer = Framebuffer::Create(fbSpec);

        _Stats    = CreateRef<StatImGui>();
        _Viewport = CreateRef<ViewportImgui>();
    }

    void DockerLayer::OnUpdate(Timestep ts)
    {
        Exodia::Renderer2D::ResetStats();

        // Bind the framebuffer
        _Framebuffer->Bind();

        // Renderer Prep
        RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
        RenderCommand::Clear();

        // Clear Entity ID attachment to -1
        _Framebuffer->ClearAttachment(1, -1);

        // Update
        _CameraController.OnUpdate(ts);

        // Renderer Draw
        Renderer2D::BeginScene(_CameraController.GetCamera());

        Renderer2D::DrawRotatedQuad(
            { 0.0f, 0.0f },      // Position
            { 0.8f, 0.8f },      // Size
            glm::radians(-45.0f), // Rotation
            _SquareColor          // Color
        );

        Renderer2D::EndScene();

        // Unbind the framebuffer
        _Framebuffer->Unbind();
    }

    void DockerLayer::OnImGUIRender()
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
        ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
        ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        // DockSpace
        ImGuiIO& io = ImGui::GetIO();
        ImGuiStyle& style = ImGui::GetStyle();

        float minWinSizeX = style.WindowMinSize.x;

        style.WindowMinSize.x = 450.0f;
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

        style.WindowMinSize.x = minWinSizeX;

        if (ImGui::BeginMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("Exit"))
                    Application::Get().Close();
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        _Stats->OnImGuiRender();
        _Viewport->OnImGuiRender(_Framebuffer);

        ImGui::End();
    }

    void DockerLayer::OnEvent(Event &event)
    {
        _CameraController.OnEvent(event);
    }
};
