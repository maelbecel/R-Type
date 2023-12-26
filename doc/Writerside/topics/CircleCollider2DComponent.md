# CircleCollider2DComponent

## Description

The `CircleCollider2DComponent` struct represents a 2D circle collider component. It is used to detect collisions between entities in a 2D scene. The `CircleCollider2DComponent` struct inherits from the `Collider2DComponent` struct.

## Properties

| Name         | Type    | Description                                                                       |
|--------------|---------|-----------------------------------------------------------------------------------|
| Offset       | Vec2    | The offset of the collider's center from the entity's center.                     |
| Radius       | float   | The radius of the collider.                                                       |
| ColliderMask | uin32_t | The collider's mask, which defines the layers that the collider can collide with. |

## Methods

- ```c++
  void DrawComponent();
  ```
  The `DrawComponent()` function is a virtual function that is overridden in the `CircleCollider2DComponent` struct. This function is responsible for drawing the component's properties in the ImGui interface. It is called by the `OnImGuiRender()` function in the `Collider2DComponent` struct.
  ```c++
  ImGui::DragFloat2("Offset", glm::value_ptr(Offset));
  ImGui::DragFloat("Radius", &Radius); 
  ```

## Usage

### Creating a circle collider

To create a circle collider, you can use the following code:

```c++
Entity *entity = _World->CreateEntity("Circle Collider");
entity->AddComponent<CircleCollider2DComponent>();
```

### Setting the circle collider's offset

To set the circle collider's offset, you can use the following code:

```c++
CircleCollider2DComponent *circleCollider2DComponent = entity->GetComponent<CircleCollider2DComponent>().Get();
circleCollider2DComponent->Offset = { 0.0f, 0.0f };
```

### Setting the circle collider's radius

To set the circle collider's radius, you can use the following code:

```c++
CircleCollider2DComponent *circleCollider2DComponent = entity->GetComponent<CircleCollider2DComponent>().Get();
circleCollider2DComponent->Radius = 0.3f;
```