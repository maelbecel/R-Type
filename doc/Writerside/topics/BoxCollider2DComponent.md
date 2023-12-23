# BoxCollider2DComponent

## Description

The `BoxCollider2DComponent` struct represents a 2D box collider component. It is used to detect collisions between entities in a 2D scene. The `BoxCollider2DComponent` struct inherits from the `Collider2DComponent` struct.

## Properties

| Name         | Type    | Description                                                                       |
|--------------|---------|-----------------------------------------------------------------------------------|
| Offset       | Vec2    | The offset of the collider's center from the entity's center.                     |
| Size         | Vec2    | The size of the collider.                                                         |
| ColliderMask | uin32_t | The collider's mask, which defines the layers that the collider can collide with. |

## Methods

- ```c++
  void DrawComponent();
  ```
  The `DrawComponent()` function is a virtual function that is overridden in the `BoxCollider2DComponent` struct. This function is responsible for drawing the component's properties in the ImGui interface. It is called by the `OnImGuiRender()` function in the `Collider2DComponent` struct.
  ```c++
  ImGui::DragFloat2("Offset", glm::value_ptr(Offset));
  ImGui::DragFloat2("Size"  , glm::value_ptr(Size));
  ImGui::DragFloat2("Scale" , glm::value_ptr(Scale));
  ```

## Usage

### Creating a box collider

To create a box collider, you can use the following code:

```c++
Entity *entity = _World->CreateEntity("Box Collider");
entity->AddComponent<BoxCollider2DComponent>();
```

### Setting the box collider's offset

To set the box collider's offset, you can use the following code:

```c++
BoxCollider2DComponent *boxCollider2DComponent = entity->GetComponent<BoxCollider2DComponent>().Get();
boxCollider2DComponent->Offset = { 0.0f, 0.0f };
```

### Setting the box collider's size

To set the box collider's size, you can use the following code:

```c++
BoxCollider2DComponent *boxCollider2DComponent = entity->GetComponent<BoxCollider2DComponent>().Get();
boxCollider2DComponent->Size = { 1.0f, 1.0f };
```
