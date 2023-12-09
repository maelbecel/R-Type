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

    ContentBrowser::ContentBrowser(Ref<Project> project) : _Project(project), _ThumbnailCache(CreateRef<ThumbnailCache>(project)) {};

    /////////////
    // Methods //
    /////////////

    void ContentBrowser::OnImGuiRender()
    {
        ImGui::Begin("Content Browser");

        ImGui::End();
    };
};
