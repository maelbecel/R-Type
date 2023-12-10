/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** SceneHierarchy
*/

// Panel includes
#include "SceneHierarchy.hpp"

// ImGui includes
#include <imgui.h>

namespace Exodia {

    /////////////
    // Methods //
    /////////////

    void SceneHierarchy::OnImGuiRender()
    {
        ImGui::Begin("Scene Hierarchy");

        ImGui::End();
    }

    ///////////////////////
    // Getters & Setters //
    ///////////////////////

    void SceneHierarchy::SetContext(Ref<Scene> context)
    {
        _Context = context;
        _SelectedEntity = {};
    }

    void SceneHierarchy::SetSelectedEntity(Entity entity)
    {
        _SelectedEntity = entity;
    }

    Entity SceneHierarchy::GetSelectedEntity() const
    {
        return _SelectedEntity;
    }
};
