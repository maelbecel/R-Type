# ImGuiToolsUI

The ImGuiToolsUI part of the ImGUI. It contains the classes that will be used to create and use the ImGuiToolsUI.

It defines two principal functions:

## DrawComponent

```c++
template<typename Component, typename UIFunction>
inline static void DrawComponent(const std::string &name, Entity *entity, UIFunction function)
```

It draws a component using the ImGuiTools UI.

The method takes the following parameters:

| Name | Type | Description |
|------|------|-------------|
| name | const std::string& | The name |
| entity | Entity* | The entity |
| function | UIFunction | The function |

It can be used like this:

```c++
ImGuiToolsUI::DrawComponent<TagComponent>("Tag", entity, [](auto &component)
{
    ImGui::InputText("##Tag", &component.Tag);
});
```

## DrawVec3Control

```c++
inline static void DrawVec3Control(const std::string &label, glm::vec3 &values, float resetValue = 0.0f, float columnWidth = 100.0f)
```

It draws a Vec3 control using the ImGuiTools UI.

The method takes the following parameters:

| Name | Type | Description |
|------|------|-------------|
| label | const std::string& | The label |
| values | glm::vec3& | The values |
| resetValue | float | The reset value |
| columnWidth | float | The column width |

It can be used like this:

```c++
ImGuiToolsUI::DrawVec3Control("Translation", transformComponent.Translation);
```
