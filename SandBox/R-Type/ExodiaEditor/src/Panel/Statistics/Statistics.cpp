/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Statistics
*/

#include "Statistics.hpp"
#include "Exodia.hpp"

namespace Exodia {

    /////////////
    // Methods //
    /////////////

    void StatistcsPanel::OnImGuiRender() {
        ImGui::Begin("Statistics");
        ImGui::Text("FPS: %.1f", Application::Get().GetStatistics().FPS);
        ImGui::Text("Frame Time: %.3f ms", Application::Get().GetStatistics().FrameTime);
        ImGui::Text("Memory Usage: %ld KB", Application::Get().GetStatistics().MemoryUsage / 1024);
        ImGui::Separator();
        ImGui::Text("Renderer Statistics :");
        ImGui::Text("Draw Calls: %d", Renderer2D::GetStats().DrawCalls);
        ImGui::Text("Quad Count: %d", Renderer2D::GetStats().QuadCount);
        ImGui::Text("Vertex Count: %d", Renderer2D::GetStats().GetTotalVertexCount());
        ImGui::Text("Index Count: %d", Renderer2D::GetStats().GetTotalIndexCount());
        ImGui::End();
    }
}; // namespace Exodia
