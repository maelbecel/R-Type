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
#include <misc/cpp/imgui_stdlib.h>

namespace Exodia {

    //////////////////////////////
    // Constructor & Destructor //
    //////////////////////////////

    SceneHierarchy::SceneHierarchy(const Ref<Scene> &context)
    {
        SetContext(context);
    }

    /////////////
    // Methods //
    /////////////

    void SceneHierarchy::OnImGuiRender()
    {
        DrawSceneHierarchy();
        DrawProperties();
    }

    void SceneHierarchy::DrawSceneHierarchy()
    {
        ImGui::Begin("Scene Hierarchy");

        if (_Context) {
            if (ImGui::BeginPopupContextWindow(0, ImGuiMouseButton_Right)) {
                if (ImGui::MenuItem("Create Empty Entity"))
                    _Context->CreateEntity("Empty Entity");
                ImGui::EndPopup();
            }

            _Context->GetWorld().ForAll([&](Entity *entity) {
                DrawEntityNode(entity);
            });

            if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
                _SelectedEntity = nullptr;
        }

        ImGui::End();
    }

    void SceneHierarchy::DrawProperties()
    {
        ImGui::Begin("Properties");

        if (_SelectedEntity)
            DrawComponents(_SelectedEntity);

        ImGui::End();
    }

    void SceneHierarchy::DrawEntityNode(Entity *entity)
    {
        auto &tag = entity->GetComponent<TagComponent>().Get();

        if (entity->HasComponent<ChildrenComponent>()) {
            if (entity->HasComponent<ParentComponent>())
                return;
            auto &children = entity->GetComponent<ChildrenComponent>().Get();

            ImGuiTreeNodeFlags flags = ((_SelectedEntity == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;

            flags |= ImGuiTreeNodeFlags_SpanAvailWidth;

            bool opened = ImGui::TreeNodeEx((void *)(uint64_t)(uint32_t)(*entity), flags, tag.Tag.c_str());

            if (ImGui::IsItemClicked())
                _SelectedEntity = entity;

            if (opened) {
                for (auto &child : children.Children)
                    DrawEntityNode(_Context->GetEntityByUUID(child));
                ImGui::TreePop();
            }
        } else {
            ImGuiTreeNodeFlags flags = ((_SelectedEntity == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;

            flags |= ImGuiTreeNodeFlags_SpanAvailWidth;

            ImGui::TreeNodeEx((void *)(uint64_t)(uint32_t)(*entity), flags, tag.Tag.c_str());

            if (ImGui::IsItemClicked())
                _SelectedEntity = entity;
        }

        bool entityDeleted = false;
        bool showPopupForThisEntity = (_SelectedEntity == entity);

        if (showPopupForThisEntity && ImGui::BeginPopupContextItem()) {
            if (ImGui::MenuItem("Delete Entity")) {
                entityDeleted = true;
            }
            ImGui::EndPopup();
        }

        if (entityDeleted) {
            _Context->DestroyEntity(entity);
            if (_SelectedEntity == entity) {
                _SelectedEntity = nullptr;
            }
        }
    }

    void SceneHierarchy::DrawComponents(UNUSED Entity *entity)
    {
        // 1. Get all components that currently exist.
        // 2. Iterate over all components.
        // 3. If the entity has the component, draw it.

        //for (auto &component : entity->GetAllComponents()) {
        //    (void)component;

            /*DrawComponent<TransformComponent>("Transform", entity, [](auto &component)
            {
                DrawVec3Control("Translation", component.Translation);

                glm::vec3 rotation = glm::degrees(component.Rotation);

                DrawVec3Control("Rotation", rotation);

                component.Rotation = glm::radians(rotation);

                DrawVec3Control("Scale", component.Scale, 1.0f);
            });*/
        //}
    }

    ///////////////////////
    // Getters & Setters //
    ///////////////////////

    void SceneHierarchy::SetContext(Ref<Scene> context)
    {
        _Context = context;
        _SelectedEntity = nullptr;
    }

    void SceneHierarchy::SetSelectedEntity(Entity *entity)
    {
        _SelectedEntity = entity;
    }

    Entity *SceneHierarchy::GetSelectedEntity() const
    {
        return _SelectedEntity;
    }
};
