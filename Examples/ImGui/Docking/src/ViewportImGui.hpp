/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** ViewportImGui
*/

#ifndef VIEWPORTIMGUI_HPP_
    #define VIEWPORTIMGUI_HPP_

    #include "Exodia.hpp"
    #include <imgui.h>
    #include <glm/glm.hpp>

namespace Exodia {

    class ViewportImGui {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
        public:

            ViewportImGui() = default;
            ~ViewportImGui() = default;

        /////////////
        // Methods //
        /////////////
        public:

            void OnImGuiRender(Ref<Framebuffer> framebuffer)
            {
                ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });

                ImGui::Begin("Viewport");
                ImVec2 viewportMinRegion = ImGui::GetWindowContentRegionMin();
                ImVec2 viewportMaxRegion = ImGui::GetWindowContentRegionMax();
                ImVec2 viewportOffset = ImGui::GetWindowPos();

                _ViewportBounds[0] = { viewportMinRegion.x + viewportOffset.x, viewportMinRegion.y + viewportOffset.y };
                _ViewportBounds[1] = { viewportMaxRegion.x + viewportOffset.x, viewportMaxRegion.y + viewportOffset.y };

                _ViewportFocused = ImGui::IsWindowFocused();
                _ViewportHovered = ImGui::IsWindowHovered();

                Application::Get().GetImGuiLayer()->SetBlockEvents(!_ViewportFocused && !_ViewportHovered);

                ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();

                _ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };

                uint32_t textureID = framebuffer->GetColorAttachmentRendererID();

                ImGui::Image(reinterpret_cast<ImTextureID>(textureID), ImVec2{ _ViewportSize.x, _ViewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
                ImGui::End();

                ImGui::PopStyleVar();
            }

        ////////////////
        // Attributes //
        ////////////////
        private:
            bool                         _ViewportFocused;
            bool                         _ViewportHovered;
            glm::vec2                    _ViewportSize;
            glm::vec2                    _ViewportBounds[2];
    };
};

#endif /* !VIEWPORTIMGUI_HPP_ */
