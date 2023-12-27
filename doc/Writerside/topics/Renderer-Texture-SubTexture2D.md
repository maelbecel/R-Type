# SubTexture2D

The SubTexture2D class of the Renderer. It contains the classes that will be used to create subtextures.

It defines the class `SubTexture2D` with the following methods:

## Constructor

```c++
SubTexture2D(const AssetHandle &assetHandle);
SubTexture2D(const AssetHandle &assetHandle, const glm::vec2 &coords, const glm::vec2 &cellSize,
             const glm::vec2 &spriteSize);
```

It constructs a subtexture.

It takes the following parameters:

| Name       | Type                | Description   |
|------------|---------------------|---------------|
| assetHandle | const AssetHandle& | The asset handle |
| coords     | const glm::vec2&    | The coords    |
| cellSize   | const glm::vec2&    | The cell size |

It can be used like this:

```c++
SubTexture2D subTexture2D(assetHandle);
```

## CreateFromCoords

```c++
static Ref<SubTexture2D> CreateFromCoords(const AssetHandle &assetHandle, const glm::vec2 &coords,
                                          const glm::vec2 &cellSize, const glm::vec2 &spriteSize);
```

It creates a subtexture from coords.

It takes the following parameters:

| Name       | Type                | Description   |
|------------|---------------------|---------------|
| assetHandle | const AssetHandle& | The asset handle |
| coords     | const glm::vec2&    | The coords    |
| cellSize   | const glm::vec2&    | The cell size |

It can be used like this:

```c++
Ref<SubTexture2D> subTexture2D = SubTexture2D::CreateFromCoords(assetHandle, coords, cellSize, spriteSize);
```

## GetTexture

```c++
const Ref<Texture2D> &GetTexture() const;
```

It returns the texture.

It returns a reference to a Texture2D.

It can be used like this:

```c++
Ref<Texture2D> texture2D = subTexture2D->GetTexture();
```

## GetTextureCoords

```c++
const glm::vec2 *GetTextureCoords() const;
```

It returns the texture coords.

It returns a pointer to a glm::vec2.

It can be used like this:

```c++
const glm::vec2 *textureCoords = subTexture2D->GetTextureCoords();
```

## GetCoords

```c++
const glm::vec2 &GetCoords() const;
```

It returns the coords.

It returns a glm::vec2.

It can be used like this:

```c++
glm::vec2 coords = subTexture2D->GetCoords();
```

## GetTextureCellSize

```c++
const glm::vec2 &GetTextureCellSize() const;
```

It returns the texture cell size.

It returns a glm::vec2.

It can be used like this:

```c++
glm::vec2 textureCellSize = subTexture2D->GetTextureCellSize();
```

## GetTextureSpriteSize

```c++
const glm::vec2 &GetTextureSpriteSize() const;
```

It returns the texture sprite size.

It returns a glm::vec2.

It can be used like this:

```c++
glm::vec2 textureSpriteSize = subTexture2D->GetTextureSpriteSize();
```

## GetAssetHandle

```c++
const AssetHandle &GetAssetHandle() const;
```

It returns the asset handle.

It returns a reference to a AssetHandle.

It can be used like this:

```c++
AssetHandle assetHandle = subTexture2D->GetAssetHandle();
```

## SetCoords

```c++
void SetCoords(const glm::vec2 &coords);
```

It sets the coords.

It takes the following parameters:

| Name   | Type            | Description |
|--------|-----------------|-------------|
| coords | const glm::vec2 | The coords  |

It can be used like this:

```c++
subTexture2D->SetCoords(coords);
```

## SetTextureCellSize

```c++
void SetTextureCellSize(const glm::vec2 &textureCellSize);
```

It sets the texture cell size.

It takes the following parameters:

| Name             | Type            | Description |
|------------------|-----------------|-------------|
| textureCellSize | const glm::vec2 | The texture cell size |

It can be used like this:

```c++
subTexture2D->SetTextureCellSize(textureCellSize);
```

## SetTextureSpriteSize

```c++
void SetTextureSpriteSize(const glm::vec2 &textureSpriteSize);
```

It sets the texture sprite size.

It takes the following parameters:

| Name               | Type            | Description |
|--------------------|-----------------|-------------|
| textureSpriteSize | const glm::vec2 | The texture sprite size |

It can be used like this:

```c++
subTexture2D->SetTextureSpriteSize(textureSpriteSize);
```

## SetTexture

```c++
void SetTexture(const AssetHandle &handle);
```


