# Default Components

The Game Engine provides some default components that you can use in your game.

1. [**Camera**](CameraComponent.md): A component that defines a camera in the game world. It contains the camera's projection matrix and view matrix, as well as other properties like field of view and near/far clipping planes.
2. **Collider2D**: A component that defines a 2D collider in the game world. It contains the collider's shape and size, as well as other properties like friction and bounciness.
    - [**BoxCollider2D**](BoxCollider2DComponent.md): A component that defines a 2D box collider in the game world. It contains the collider's size, as well as other properties like friction and bounciness.
    - [**CircleCollider2D**](CircleCollider2DComponent.md): A component that defines a 2D circle collider in the game world. It contains the collider's radius, as well as other properties like friction and bounciness.
3. [**ID**](IDComponent.md): A component that defines an entity's unique identifier. It contains the entity's ID.
4. **Prefab**: A component that defines an entity's prefab. It contains the entity's prefab.
    - [**Children**](ChildrenComponent.md): A component that defines an entity's children. It contains the entity's children.
    - [**Parent**](ParentComponent.md): A component that defines an entity's parent. It contains the entity's parent.
5. [**RigidBody2D**](RigidBody2D.md): A component that defines a 2D rigid body in the game world. It contains the rigid body's mass, velocity, and other properties like friction and bounciness.
6. **Renderer2D**: A component that defines a 2D renderer in the game world. It contains the renderer's sprite, color, and other properties like sorting layer and order in layer.
    - [**SpriteRenderer**](SpriteRendererComponent.md): A component that defines a sprite renderer in the game world. It contains the sprite's texture, color, and other properties like sorting layer and order in layer.
    - [**CircleRenderer**](CircleRenderer.md): A component that defines a circle renderer in the game world. It contains the circle's radius, color, and other properties like sorting layer and order in layer.
7. [**Script**](ScriptComponent.md): A component that defines an entity's script. It contains the entity's script.
8. [**Tag**](TagComponent.md): A component that defines an entity's tag. It contains the entity's tag.
9. [**Transform**](TransformComponent.md): A component that defines an entity's transform in the game world. It contains the entity's position, rotation, and scale.
