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

// External includes
#include <cstring>

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

            bool opened = ImGui::TreeNodeEx((void *)(uint64_t)(uint32_t)(*entity), flags, "%s", tag.Tag.c_str());

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

            ImGui::TreeNodeEx((void *)(uint64_t)(uint32_t)(*entity), flags, "%s", tag.Tag.c_str());

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

    void SceneHierarchy::DrawComponents(Entity *entity)
    {
        if (entity->HasComponent<TagComponent>()) {
            auto &tag = entity->GetComponent<TagComponent>().Get().Tag;
            char buffer[256];

            std::memset(buffer, 0, sizeof(buffer));
            std::strncpy(buffer, tag.c_str(), sizeof(buffer));

            if (ImGui::InputText("Tag", buffer, sizeof(buffer)))
                tag = std::string(buffer);
        }

        ImGui::SameLine();
        ImGui::PushItemWidth(-1);

        if (ImGui::Button("Add Component"))
            ImGui::OpenPopup("AddComponent");

        if (ImGui::BeginPopup("AddComponent")) {

            /*DisplayAddComponentEntry<CameraComponent>("Camera");
            DisplayAddComponentEntry<SpriteRendererComponent>("Sprite Renderer");
            DisplayAddComponentEntry<CircleRendererComponent>("Circle Renderer");
            DisplayAddComponentEntry<NativeScriptComponent>("Native Script");
            DisplayAddComponentEntry<Rigidbody2DComponent>("Rigidbody 2D");
            DisplayAddComponentEntry<BoxCollider2DComponent>("Box Collider 2D");
            DisplayAddComponentEntry<CircleCollider2DComponent>("Circle Collider 2D");*/

            ImGui::EndPopup();
        }
        ImGui::PopItemWidth();

        for (auto &component : entity->GetAllComponents())
            component->OnImGuiRender();
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
