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

    SceneHierarchy::SceneHierarchy(const Ref<Scene> &context) { SetContext(context); }

    /////////////
    // Methods //
    /////////////

    void SceneHierarchy::OnImGuiRender() {
        DrawSceneHierarchy();
        DrawProperties();
        DrawSystems();
    }

    void SceneHierarchy::DrawSystems() {
        ImGui::Begin("Systems");

        if (_Context) {
            for (auto &system : Project::GetActive()->GetSystemsFactory()) {
                bool enabled = _Context->HasSystems(system.first);
                bool prevEnabled = enabled;

                if (ImGui::Checkbox(system.first.c_str(), &enabled)) {
                    if (enabled != prevEnabled) {
                        if (enabled)
                            _Context->RegisterSystem(system.second());
                        else
                            _Context->UnregisterSystem(system.first);
                    }
                }
            }
        }

        ImGui::End();
    }

    void SceneHierarchy::DrawSceneHierarchy() {
        ImGui::Begin("Scene Hierarchy");

        if (_Context) {
            if (ImGui::BeginPopupContextWindow(0, ImGuiMouseButton_Right)) {
                if (ImGui::MenuItem("Create Empty Entity"))
                    _Context->CreateEntity("Empty Entity");
                ImGui::EndPopup();
            }

            _Context->GetWorld().ForAll([&](Entity *entity) {
                if (entity->HasComponent<ParentComponent>() &&
                    _Context->GetEntityByUUID(entity->GetComponent<ParentComponent>().Get().Parent).GetEntity() !=
                        nullptr)
                    return;
                DrawEntityNode(entity);
            });

            if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
                _SelectedEntity = nullptr;
        }

        ImGui::End();
    }

    void SceneHierarchy::DrawProperties() {
        ImGui::Begin("Properties");

        if (_SelectedEntity)
            DrawComponents(_SelectedEntity);

        ImGui::End();
    }

    void SceneHierarchy::DrawEntityNode(Entity *entity) {
        if (entity == nullptr)
            return;

        auto tc = entity->GetComponent<TagComponent>();

        if (!tc)
            return;
        auto &tag = tc.Get();

        if (entity->HasComponent<ChildrenComponent>()) {
            auto &children = entity->GetComponent<ChildrenComponent>().Get();

            ImGuiTreeNodeFlags flags =
                ((_SelectedEntity == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;

            flags |= ImGuiTreeNodeFlags_SpanAvailWidth;

            bool opened = ImGui::TreeNodeEx((void *)(uint64_t)(uint32_t)(*entity), flags, "%s", tag.Tag.c_str());

            if (ImGui::IsItemClicked())
                _SelectedEntity = entity;

            if (opened) {
                for (auto &child : children.Children)
                    DrawEntityNode(_Context->GetEntityByUUID(child).GetEntity());
                ImGui::TreePop();
            }
        } else {
            ImGuiTreeNodeFlags flags = ((_SelectedEntity == entity) ? ImGuiTreeNodeFlags_Selected : 0) |
                                       ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;

            flags |= ImGuiTreeNodeFlags_SpanAvailWidth;

            ImGui::TreeNodeEx((void *)(uint64_t)(uint32_t)(*entity), flags, "%s", tag.Tag.c_str());

            if (ImGui::IsItemClicked())
                _SelectedEntity = entity;
        }

        bool entityDeleted = false;
        bool showPopupForThisEntity = (_SelectedEntity == entity);

        if (showPopupForThisEntity && ImGui::BeginPopupContextItem()) {
            if (entity->HasComponent<ChildrenComponent>()) {
                if (ImGui::MenuItem("Create Empty Entity")) {
                    Entity *child = _Context->CreateNewEntity("Empty Entity").GetEntity();

                    child->AddComponent<ParentComponent>(entity->GetEntityID());

                    entity->GetComponent<ChildrenComponent>().Get().AddChild(child->GetEntityID());
                }
            }
            if (ImGui::MenuItem("Delete Entity"))
                entityDeleted = true;
            ImGui::EndPopup();
        }

        if (entityDeleted) {
            _Context->DestroyEntity(entity);
            if (_SelectedEntity == entity) {
                _SelectedEntity = nullptr;
            }
        }
    }

    void SceneHierarchy::DisplayAddComponentEntry(const std::string &name,
                                                  const std::function<IComponentContainer *(Buffer)> &factory) {
        if (!_SelectedEntity->Has(name)) {
            if (ImGui::MenuItem(name.c_str())) {
                IComponentContainer *component = factory(Buffer());

                _SelectedEntity->AddComponent(component);

                ImGui::CloseCurrentPopup();
            }
        }
    }

    void SceneHierarchy::DrawComponents(Entity *entity) {
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
            auto &components = Project::GetActive()->GetComponentsFactory();

            for (auto &component : components)
                DisplayAddComponentEntry(component.first, component.second);
            ImGui::EndPopup();
        }
        ImGui::PopItemWidth();

        for (auto &component : entity->GetAllComponents()) {
            component->OnImGuiRender();
        }
    }

    ///////////////////////
    // Getters & Setters //
    ///////////////////////

    void SceneHierarchy::SetContext(Ref<Scene> context) {
        _Context = context;
        _SelectedEntity = nullptr;
    }

    void SceneHierarchy::SetSelectedEntity(GameObject gameObject) { _SelectedEntity = gameObject.GetEntity(); }

    GameObject SceneHierarchy::GetSelectedEntity() const { return {_SelectedEntity, _Context.get()}; };
}; // namespace Exodia
