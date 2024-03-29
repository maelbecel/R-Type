/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** ImGuiLayer
*/

// Exodia ImGUI
#include "ImGuiLayer.hpp"

// -- ImGui includes --
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <imgui_internal.h>

// Exodia Core
#include "Core/Application/Application.hpp"

// Exodia Debug
#include "Debug/Profiling.hpp"

// External includes
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Exodia {

    //////////////////////////////
    // Constructor & Destructor //
    //////////////////////////////

    ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer"), _BlockEvents(true), _Time(0.0f){};

    /////////////
    // Methods //
    /////////////

    void ImGuiLayer::OnAttach() {
        EXODIA_PROFILE_FUNCTION(); // Performance instrumentation profiling for the function

        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        // Setup Platform/Renderer bindings
        ImGuiIO &io = ImGui::GetIO();

        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
        // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;   // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport / Platform Windows
        // io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
        // io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

        io.Fonts->AddFontFromFileTTF("Assets/Font/OpenSans/OpenSans-Bold.ttf", 18.0f);

        io.FontDefault = io.Fonts->AddFontFromFileTTF("Assets/Font/OpenSans/OpenSans-Regular.ttf", 18.0f);

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();

        // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular
        // ones.
        ImGuiStyle &style = ImGui::GetStyle();

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        SetDarkThemeColors();

        Application &app = Application::Get();
        GLFWwindow *window = static_cast<GLFWwindow *>(app.GetWindow().GetNativeWindow());

        // Setup Platform/Renderer bindings
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 410");
    }

    void ImGuiLayer::OnDetach() {
        EXODIA_PROFILE_FUNCTION(); // Performance instrumentation profiling for the function

        // Cleanup
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();

        ImGui::DestroyContext();
    }

    void ImGuiLayer::OnEvent(Event &event) {
        if (_BlockEvents) {
            ImGuiIO &io = ImGui::GetIO();

            event.Handled |= event.IsInCategory(EventCategory::EventCategoryMouse) & io.WantCaptureMouse;
            event.Handled |= event.IsInCategory(EventCategory::EventCategoryKeyboard) & io.WantCaptureKeyboard;
        }
    }

    void ImGuiLayer::Begin() {
        EXODIA_PROFILE_FUNCTION(); // Performance instrumentation profiling for the function

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();

        ImGui::NewFrame();
    }

    void ImGuiLayer::End() {
        EXODIA_PROFILE_FUNCTION(); // Performance instrumentation profiling for the function

        ImGuiIO &io = ImGui::GetIO();
        Application &app = Application::Get();

        io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());

        // Rendering
        ImGui::Render();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            GLFWwindow *backup_current_context = glfwGetCurrentContext();

            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();

            glfwMakeContextCurrent(backup_current_context);
        }
    }

    ///////////////////////
    // Setters & Getters //
    ///////////////////////

    void ImGuiLayer::SetBlockEvents(bool block) { _BlockEvents = block; }

    uint32_t ImGuiLayer::GetActiveWidgetID() const { return GImGui->ActiveId; }

    void ImGuiLayer::SetDarkThemeColors() {
        auto &colors = ImGui::GetStyle().Colors;

        // Background
        colors[ImGuiCol_WindowBg] = ImVec4{0.10f, 0.1050f, 0.110f, 1.0f};

        // Headers
        colors[ImGuiCol_Header] = ImVec4{0.20f, 0.2050f, 0.210f, 1.0f};
        colors[ImGuiCol_HeaderHovered] = ImVec4{0.30f, 0.3050f, 0.310f, 1.0f};
        colors[ImGuiCol_HeaderActive] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};

        // Buttons
        colors[ImGuiCol_Button] = ImVec4{0.20f, 0.2050f, 0.210f, 1.0f};
        colors[ImGuiCol_ButtonHovered] = ImVec4{0.30f, 0.3050f, 0.310f, 1.0f};
        colors[ImGuiCol_ButtonActive] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};

        // Frame BG
        colors[ImGuiCol_FrameBg] = ImVec4{0.20f, 0.2050f, 0.210f, 1.0f};
        colors[ImGuiCol_FrameBgHovered] = ImVec4{0.30f, 0.3050f, 0.310f, 1.0f};
        colors[ImGuiCol_FrameBgActive] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};

        // Tabs
        colors[ImGuiCol_Tab] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};
        colors[ImGuiCol_TabHovered] = ImVec4{0.38f, 0.3805f, 0.381f, 1.0f};
        colors[ImGuiCol_TabActive] = ImVec4{0.28f, 0.2805f, 0.281f, 1.0f};
        colors[ImGuiCol_TabUnfocused] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};
        colors[ImGuiCol_TabUnfocusedActive] = ImVec4{0.20f, 0.2050f, 0.210f, 1.0f};

        // Title
        colors[ImGuiCol_TitleBg] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};
        colors[ImGuiCol_TitleBgActive] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};
        colors[ImGuiCol_TitleBgCollapsed] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};
    }
}; // namespace Exodia
