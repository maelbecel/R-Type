# SpriteRendererComponent

## Description

The `SpriteRendererComponent` struct represents a sprite renderer component. It is used to render sprites in a 2D scene. The `SpriteRendererComponent` struct inherits from the `RendererComponent` struct.

## Properties

| Name         | Type                | Description                                                                 |
|--------------|---------------------|-----------------------------------------------------------------------------|
| Color        | Vec4                | The color of the sprite.                                                    |
| Texture      | Ref\<SubTexture2D\> | The texture of the sprite.                                                  |
| TilingFactor | float               | The tiling factor of the sprite.                                            |

The `Texture` property is a reference to a `SubTexture2D` struct, which is a struct that represents a subtexture. The `SubTexture2D` struct contains the following properties:

| Name              | Type        | Description                                       |
|-------------------|-------------|---------------------------------------------------|
| Coords            | Vec2        | The coordinates of the subtexture in the texture. |
| TextureCellSize   | Vec2        | The size of the subtexture in the texture.        |
| TextureSpriteSize | Vec2        | The size of the subtexture in the sprite.         |
| AssetHandle       | AssetHandle | The asset handle of the texture.                  |

## Methods

- ```c++
  void DrawComponent();
  ```
  The `DrawComponent()` function is a virtual function that is overridden in the `SpriteRendererComponent` struct. This function is responsible for drawing the component's properties in the ImGui interface. It is called by the `OnImGuiRender()` function in the `RendererComponent` struct.
  The DrawComponent function in this C++ code is part of a GUI for a game engine, using the ImGui library. It allows the user to edit properties of a texture, such as color and tiling factor. It also supports drag-and-drop functionality to change the texture. If the texture is valid, it provides an option to remove the texture. The texture's validity is checked using its handle and the AssetManager.

## Usage

### Creating a sprite renderer

To create a sprite renderer, you can use the following code:

```c++
Entity *entity = _World->CreateEntity("Sprite Renderer");
entity->AddComponent<SpriteRendererComponent>();
```

### Setting the sprite renderer's color

To set the sprite renderer's color, you can use the following code:

```c++
SpriteRendererComponent *spriteRendererComponent = entity->GetComponent<SpriteRendererComponent>().Get();
spriteRendererComponent->Color = { 1.0f, 1.0f, 1.0f, 1.0f };
```

### Setting the sprite renderer's texture

To set the sprite renderer's texture, you can use the following code:

```c++
SpriteRendererComponent *spriteRendererComponent = entity->GetComponent<SpriteRendererComponent>().Get();
spriteRendererComponent->Texture = AssetManager::GetAsset<SubTexture2D>("assets/textures/texture.png");
```

### Setting the sprite renderer's tiling factor

To set the sprite renderer's tiling factor, you can use the following code:

```c++
SpriteRendererComponent *spriteRendererComponent = entity->GetComponent<SpriteRendererComponent>().Get();
spriteRendererComponent->TilingFactor = 1.0f;
```
