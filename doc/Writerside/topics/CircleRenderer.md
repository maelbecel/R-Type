# CircleRenderer

## Description

The `CircleRenderer` struct represents a circle renderer component. It is used to render circles in a 2D scene. The `CircleRenderer` struct inherits from the `Renderer2DComponent` struct.

## Properties

| Name         | Type    | Description                                                                 |
|--------------|---------|-----------------------------------------------------------------------------|
| Color        | Vec4    | The color of the circle.                                                    |
| Thickness    | float   | The thickness of the circle's outline.                                      |
| Fade         | float   | The fade of the circle.                                                     |

## Methods

- ```c++
  void DrawComponent();
  ```
  The `DrawComponent()` function is a virtual function that is overridden in the `CircleRenderer` struct. This function is responsible for drawing the component's properties in the ImGui interface. It is called by the `OnImGuiRender()` function in the `Renderer2DComponent` struct.
  ```c++
  ImGui::ColorEdit4("Color", glm::value_ptr(Color));
  ImGui::DragFloat("Thickness", &Thickness);
  ImGui::DragFloat("Fade", &Fade);
  ```


## Usage

### Creating a circle renderer

To create a circle renderer, you can use the following code:

```c++
Entity *entity = _World->CreateEntity("Circle Renderer");
entity->AddComponent<CircleRenderer>();
```

### Setting the circle renderer's color

To set the circle renderer's color, you can use the following code:

```c++
CircleRenderer *circleRenderer = entity->GetComponent<CircleRenderer>().Get();
circleRenderer->Color = { 1.0f, 1.0f, 1.0f, 1.0f };
```

### Setting the circle renderer's thickness

To set the circle renderer's thickness, you can use the following code:

```c++
CircleRenderer *circleRenderer = entity->GetComponent<CircleRenderer>().Get();
circleRenderer->Thickness = 0.1f;
```

### Setting the circle renderer's fade

To set the circle renderer's fade, you can use the following code:

```c++
CircleRenderer *circleRenderer = entity->GetComponent<CircleRenderer>().Get();
circleRenderer->Fade = 0.5f;
```

