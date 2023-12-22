# RigidBody2D

## Description

The `RigidBody2D` struct represents a 2D rigid body. It is used to simulate the physics of entities in a 2D scene.

## Properties

| Name         | Type     | Description                     |
|--------------|----------|---------------------------------|
| Body         | BodyType | The rigid body.                 |
| Velocity     | Vec2     | The rigid body's velocity.      |
| GravityScale | float    | The rigid body's gravity scale. |
| Mass         | float    | The rigid body's mass.          |

The `BodyType` enum is defined as follows:

```c++
enum class BodyType
{
    Static,
    Dynamic
};
```

## Methods

- ```c++
  void DrawComponent();
  ```
  The `DrawComponent()` function is a virtual function that is overridden in the `RigidBody2D` struct. This function is responsible for drawing the component's properties in the ImGui interface. It is called by the `OnImGuiRender()` function in the `RigidBody2D` struct.
  It defines an array of strings bodyTypeStrings[] that represent the possible values of the BodyType enum (Static and Dynamic).
  It gets the current BodyType of the RigidBody2D component and stores the corresponding string in currentBodyTypeString.
  It iterates over the bodyTypeStrings[] array. For each body type, it creates a selectable item in the dropdown list. If the current body type is equal to the body type of the selectable item, it sets the item as the default focus.
  If a different body type is selected from the dropdown list, it updates the Type of the RigidBody2D component to the selected body type.
  It creates a draggable 2D float input field with the label "Velocity" for editing the Velocity of the RigidBody2D component.
  It creates a draggable float input field with the label "Gravity Scale" for editing the GravityScale of the RigidBody2D component.
  It creates a draggable float input field with the label "Mass" for editing the Mass of the RigidBody2D component.

- ```c++
  static std::string BodyTypeToString(BodyType bodyType);
  ```
    The `BodyTypeToString()` function takes a BodyType enum as a parameter and returns a string representation of the body type.

- ```c++
    static BodyType StringToBodyType(const std::string &bodyTypeString);
    ```
    The `StringToBodyType()` function takes a string as a parameter and returns a BodyType enum representation of the string.

## Usage

### Creating a rigid body

To create a rigid body, you can use the following code:

```c++
Entity *entity = _World->CreateEntity("Rigid Body");
entity->AddComponent<RigidBody2D>();
```

### Setting the rigid body's type

To set the rigid body's type, you can use the following code:

```c++
RigidBody2D *rigidBody2D = entity->GetComponent<RigidBody2D>().Get();
rigidBody2D->Body = RigidBody2D::BodyType::Static;
```

### Setting the rigid body's velocity

To set the rigid body's velocity, you can use the following code:

```c++
RigidBody2D *rigidBody2D = entity->GetComponent<RigidBody2D>().Get();
rigidBody2D->Velocity = { 0.0f, 0.0f };
```

### Setting the rigid body's gravity scale

To set the rigid body's gravity scale, you can use the following code:

```c++
RigidBody2D *rigidBody2D = entity->GetComponent<RigidBody2D>().Get();
rigidBody2D->GravityScale = 1.0f;
```

### Setting the rigid body's mass

To set the rigid body's mass, you can use the following code:

```c++
RigidBody2D *rigidBody2D = entity->GetComponent<RigidBody2D>().Get();
rigidBody2D->Mass = 1.0f;
```
