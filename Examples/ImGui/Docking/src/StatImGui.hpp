/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** StatImGui
*/

#ifndef STATIMGUI_HPP_
    #define STATIMGUI_HPP_

    #include "Exodia.hpp"
    #include <imgui.h>

namespace Exodia {

    class StatImGui {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
        public:

            StatImGui() = default;
            ~StatImGui() = default;

        /////////////
        // Methods //
        /////////////
        public:

            void OnImGuiRender()
            {
                auto stats = Renderer2D::GetStats();

                ImGui::Begin("Stats");

                ImGui::TextUnformatted("Renderer2D Stats:");
                ImGui::Text("Draw Calls: %d", stats.DrawCalls);
                ImGui::Text("Quads: %d", stats.QuadCount);
                ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
                ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

                ImGui::End();
            }
    };
};

#endif /* !STATIMGUI_HPP_ */
