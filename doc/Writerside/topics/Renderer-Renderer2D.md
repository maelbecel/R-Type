# Renderer-Renderer2D

The Renderer2D class of the Renderer. It contains the classes that will be used to create the 2D renderer.

It defines the following method and structs:

## QuadVertex

The QuadVertex struct of the Renderer2D. It's used to create a quad vertex.

It has the following members:

| Name   | Type   | Description |
|--------|--------|-------------|
| Position | glm::vec3 | The position |
| Color | glm::vec4 | The color |
| TexCoord | glm::vec2 | The texture coordinate |
| TexIndex | float | The texture index |
| TilingFactor | float | The tiling factor |

It can be used like this:

```c++
QuadVertex vertex;
vertex.Position = position;
vertex.Color = color;
vertex.TexCoord = texCoord;
```

## CircleVertex

The CircleVertex struct of the Renderer2D. It's used to create a circle vertex.

It has the following members:

| Name   | Type      | Description |
|--------|-----------|-------------|
| WorldPosition | glm::vec3 | The world position |
| LocalPosition | glm::vec3 | The local position |
| Color | glm::vec4 | The color |
| Thickness | float     | The thickness |
| Fade | float     | The fade |
| EntityID | int       | The entity ID |

It can be used like this:

```c++
CircleVertex vertex;
vertex.WorldPosition = worldPosition;
vertex.LocalPosition = localPosition;
vertex.Color = color;
```

## LineVertex

The LineVertex struct of the Renderer2D. It's used to create a line vertex.

It has the following members:

| Name   | Type      | Description |
|--------|-----------|-------------|
| Position | glm::vec3 | The position |
| Color | glm::vec4 | The color |
| EntityID | int       | The entity ID |

It can be used like this:

```c++
LineVertex vertex;
vertex.Position = position;
vertex.Color = color;
```

## Statistics

The Statistics struct of the Renderer2D. It's used to create statistics.

It has the following members:

| Name   | Type   | Description |
|--------|--------|-------------|
| DrawCalls | uint32_t | The draw calls |
| QuadCount | uint32_t | The quad count |

It can be used like this:

```c++
Statistics statistics;
statistics.DrawCalls = drawCalls;
statistics.QuadCount = quadCount;
```

## CameraData

The CameraData struct of the Renderer2D. It's used to create camera data.

It has the following members:

| Name   | Type   | Description |
|--------|--------|-------------|
| ViewProjection | glm::mat4 | The view projection |

It can be used like this:

```c++
CameraData cameraData;
cameraData.ViewProjection = viewProjection;
```

## Renderer2DData

The Renderer2DData struct of the Renderer2D. It's used to create renderer 2D data.

It has the following members:

| Name                   | Type                                           | Description                      |
|------------------------|------------------------------------------------|----------------------------------|
| MaxQuads               | uint32_t                                       | The max quads                    |
| MaxVertices            | uint32_t                                       | The max vertices                 |
| MaxIndices             | uint32_t                                       | The max indices                  |
| MaxTextureSlots        | uint32_t                                       | The max texture slots            |
| QuadVertexArray        | Ref\<VertexArray\>                             | The quad vertex array            |
| QuadVertexBufferBase   | Ref\<VertexBuffer\>                            | The quad vertex buffer base      |
| QuadVertex             | Ref\<Shader\>                                  | The quad vertex buffer pointer   |
| CircleVertexArray      | Ref\<VertexArray\>                             | The circle vertex array          |
| CircleVertexBuffer     | Ref\<VertexBuffer\>                            | The circle vertex buffer         |
| CircleVertex           | Ref\<Shader\>                                  | The circle vertex buffer         |
| LineVertexArray        | Ref\<VertexArray\>                             | The line vertex array            |
| LineVertexBuffer       | Ref\<VertexBuffer\>                            | The line vertex buffer           |
| LineVertex             | Ref\<Shader\>                                  | The line vertex buffer           |
| WhiteTexture           | Ref\<Texture2D\>                               | The white texture                |
| QuadIndexCount         | uint32_t                                       | The quad index count             |
| QuadVertexBufferPtr    | QuadVertex*                                    | The quad vertex buffer pointer   |
| QuadVertexBufferBase   | QuadVertex*                                    | The quad vertex buffer base      |
| CircleIndexCount       | uint32_t                                       | The circle index count           |
| CircleVertexBufferBase | CircleVertex*                                  | The circle vertex buffer base    |
| CircleVertexBufferPtr  | CircleVertex*                                  | The circle vertex buffer pointer |
| LineIndexCount         | uint32_t                                       | The line index count             |
| LineVertexBufferBase   | LineVertex*                                    | The line vertex buffer base      |
| LineVertexBufferPtr    | LineVertex*                                    | The line vertex buffer pointer   |
| LineWidth              | float                                          | The line width                   |
| TextureSlots           | std::array\<Ref\<Texture2D\>, MaxTextureSlot\> | The texture slots                |
| TextureSlotIndex       | uint32_t                                       | The texture slot index           |
| QuadVertexPosition     | glm::vec4                                      | The quad vertex position         |
| Stats                  | Statistics                                     | The statistics                   |
| CameraBuffer           | CameraData                                     | The camera data                  |
| CameraUniformBuffer    | Ref\<UniformBuffer\>                           | The camera uniform buffer        |

## Init

```c++
static void Init();
```

It initializes the renderer 2D.

It can be used like this:

```c++
Renderer2D::Init();
```

## Shutdown

```c++
static void Shutdown();
```

It shuts down the renderer 2D.

It can be used like this:

```c++
Renderer2D::Shutdown();
```

## BeginScene

```c++
static void BeginScene(const OrthographicCamera &camera);
static void BeginScene(const Camera &camera, const glm::mat4 &transform);
static void BeginScene(const EditorCamera &camera);
```

It begins the scene.

It takes the following parameters:

| Name   | Type                      | Description |
|--------|---------------------------|-------------|
| camera | const OrthographicCamera& | The camera  |
| camera | const Camera&             | The camera  |
| camera | const EditorCamera&       | The camera  |
| transform | const glm::mat4&       | The transform  |

It can be used like this:

```c++
Renderer2D::BeginScene(camera);
```

## EndScene

```c++
static void EndScene();
```

It ends the scene.

It can be used like this:

```c++
Renderer2D::EndScene();
```

## Flush

```c++
static void Flush();
```

It flushes the renderer 2D.

It can be used like this:

```c++
Renderer2D::Flush();
```

## ResetStats

```c++
static void ResetStats();
```

It resets the statistics.

It can be used like this:

```c++
Renderer2D::ResetStats();
```

## DrawQuad

```c++
static void DrawQuad(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color);
static void DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color);
static void DrawQuad(const glm::mat4 &transform, const glm::vec4 &color, int entityID = -1);
static void DrawQuad(const glm::vec2 &position, const glm::vec2 &size, const Ref<Texture2D> &texture,
                     float tilingFactor = 1.0f, const glm::vec4 &tintColor = glm::vec4(1.0f));
static void DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const Ref<Texture2D> &texture,
                     float tilingFactor = 1.0f, const glm::vec4 &tintColor = glm::vec4(1.0f));
static void DrawQuad(const glm::mat4 &transform, const Ref<Texture2D> &texture, float tilingFactor = 1.0f,
                     const glm::vec4 &tintColor = glm::vec4(1.0f), int entityID = -1);
static void DrawQuad(const glm::vec2 &position, const glm::vec2 &size, const Ref<SubTexture2D> &subTexture,
                     float tilingFactor = 1.0f, const glm::vec4 &tintColor = glm::vec4(1.0f));
static void DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const Ref<SubTexture2D> &subTexture,
                     float tilingFactor = 1.0f, const glm::vec4 &tintColor = glm::vec4(1.0f));
static void DrawQuad(const glm::mat4 &transform, const Ref<SubTexture2D> &subTexture, float tilingFactor = 1.0f,
                     const glm::vec4 &tintColor = glm::vec4(1.0f), int entityID = -1);
```

It draws a quad.

It takes the following parameters:

| Name   | Type                      | Description |
|--------|---------------------------|-------------|
| position | const glm::vec2&       | The position |
| size | const glm::vec2&           | The size     |
| color | const glm::vec4&          | The color    |

or

| Name   | Type                      | Description |
|--------|---------------------------|-------------|
| position | const glm::vec3&       | The position |
| size | const glm::vec2&           | The size     |
| color | const glm::vec4&          | The color    |

or

| Name   | Type                      | Description |
|--------|---------------------------|-------------|
| transform | const glm::mat4&       | The transform |
| color | const glm::vec4&          | The color    |
| entityID | int                    | The entity ID    |

or

| Name   | Type                      | Description |
|--------|---------------------------|-------------|
| position | const glm::vec2&       | The position |
| size | const glm::vec2&           | The size     |
| texture | const Ref\<Texture2D\>&  | The texture  |
| tilingFactor | float              | The tiling factor |
| tintColor | const glm::vec4&       | The tint color    |

or

| Name   | Type                      | Description |
|--------|---------------------------|-------------|
| position | const glm::vec3&       | The position |
| size | const glm::vec2&           | The size     |
| texture | const Ref\<Texture2D\>&  | The texture  |
| tilingFactor | float              | The tiling factor |
| tintColor | const glm::vec4&       | The tint color    |

or

| Name   | Type                      | Description |
|--------|---------------------------|-------------|
| transform | const glm::mat4&       | The transform |
| texture | const Ref\<Texture2D\>&  | The texture  |
| tilingFactor | float              | The tiling factor |
| tintColor | const glm::vec4&       | The tint color    |
| entityID | int                    | The entity ID    |

or

| Name   | Type                      | Description |
|--------|---------------------------|-------------|
| position | const glm::vec2&       | The position |
| size | const glm::vec2&           | The size     |
| subTexture | const Ref\<SubTexture2D\>&  | The sub texture  |
| tilingFactor | float              | The tiling factor |
| tintColor | const glm::vec4&       | The tint color    |

or

| Name   | Type                      | Description |
|--------|---------------------------|-------------|
| position | const glm::vec3&       | The position |
| size | const glm::vec2&           | The size     |
| subTexture | const Ref\<SubTexture2D\>&  | The sub texture  |
| tilingFactor | float              | The tiling factor |
| tintColor | const glm::vec4&       | The tint color    |

or

| Name   | Type                      | Description |
|--------|---------------------------|-------------|
| transform | const glm::mat4&       | The transform |
| subTexture | const Ref\<SubTexture2D\>&  | The sub texture  |
| tilingFactor | float              | The tiling factor |
| tintColor | const glm::vec4&       | The tint color    |
| entityID | int                    | The entity ID    |

It can be used like this:

```c++
Renderer2D::DrawQuad(position, size, color);
```

## DrawRotatedQuad

```c++
        static void DrawRotatedQuad(const glm::vec2 &position, const glm::vec2 &size, float rotation,
                                    const glm::vec4 &color);
        static void DrawRotatedQuad(const glm::vec3 &position, const glm::vec2 &size, float rotation,
                                    const glm::vec4 &color);
        static void DrawRotatedQuad(const glm::vec2 &position, const glm::vec2 &size, float rotation,
                                    const Ref<Texture2D> &texture, float tilingFactor = 1.0f,
                                    const glm::vec4 &tintColor = glm::vec4(1.0f));
        static void DrawRotatedQuad(const glm::vec3 &position, const glm::vec2 &size, float rotation,
                                    const Ref<Texture2D> &texture, float tilingFactor = 1.0f,
                                    const glm::vec4 &tintColor = glm::vec4(1.0f));
        static void DrawRotatedQuad(const glm::vec2 &position, const glm::vec2 &size, float rotation,
                                    const Ref<SubTexture2D> &subTexture, float tilingFactor = 1.0f,
                                    const glm::vec4 &tintColor = glm::vec4(1.0f));
        static void DrawRotatedQuad(const glm::vec3 &position, const glm::vec2 &size, float rotation,
                                    const Ref<SubTexture2D> &subTexture, float tilingFactor = 1.0f,
                                    const glm::vec4 &tintColor = glm::vec4(1.0f));
```

It draws a rotated quad.

It takes the following parameters:

| Name   | Type                      | Description |
|--------|---------------------------|-------------|
| position | const glm::vec2&       | The position |
| size | const glm::vec2&           | The size     |
| rotation | float                 | The rotation |
    
or
    
| Name   | Type                      | Description |
|--------|---------------------------|-------------|
| position | const glm::vec3&       | The position |
| size | const glm::vec2&           | The size     |
| rotation | float                 | The rotation |

or

| Name   | Type                      | Description |
|--------|---------------------------|-------------|
| position | const glm::vec2&       | The position |
| size | const glm::vec2&           | The size     |
| rotation | float                 | The rotation |
| texture | const Ref\<Texture2D\>&  | The texture  |
| tilingFactor | float              | The tiling factor |
| tintColor | const glm::vec4&       | The tint color    |

or

| Name   | Type                      | Description |
|--------|---------------------------|-------------|
| position | const glm::vec3&       | The position |
| size | const glm::vec2&           | The size     |
| rotation | float                 | The rotation |
| texture | const Ref\<Texture2D\>&  | The texture  |
| tilingFactor | float              | The tiling factor |
| tintColor | const glm::vec4&       | The tint color    |

or

| Name   | Type                      | Description |
|--------|---------------------------|-------------|
| position | const glm::vec2&       | The position |
| size | const glm::vec2&           | The size     |
| rotation | float                 | The rotation |
| subTexture | const Ref\<SubTexture2D\>&  | The sub texture  |
| tilingFactor | float              | The tiling factor |
| tintColor | const glm::vec4&       | The tint color    |

or

| Name   | Type                      | Description |
|--------|---------------------------|-------------|
| position | const glm::vec3&       | The position |
| size | const glm::vec2&           | The size     |
| rotation | float                 | The rotation |
| subTexture | const Ref\<SubTexture2D\>&  | The sub texture  |
| tilingFactor | float              | The tiling factor |
| tintColor | const glm::vec4&       | The tint color    |

It can be used like this:

```c++
Renderer2D::DrawRotatedQuad(position, size, rotation, color);
```

## DrawSprite

```c++
static void DrawSprite(const glm::mat4 &transform, SpriteRendererComponent &spriteRendererComponent, int entityID = -1);
```

It draws a sprite.

It takes the following parameters:

| Name   | Type                      | Description |
|--------|---------------------------|-------------|
| transform | const glm::mat4&       | The transform |
| spriteRendererComponent | SpriteRendererComponent&  | The sprite renderer component  |
| entityID | int                    | The entity ID    |

It can be used like this:

```c++
Renderer2D::DrawSprite(transform, spriteRendererComponent);
```

## DrawCircle

```c++
static void DrawCircle(const glm::mat4 &transform, const glm::vec4 &color, float thickness = 1.0f, float fade = 0.005f, int entityID = -1);```
```

It draws a circle.

It takes the following parameters:

| Name   | Type                      | Description |
|--------|---------------------------|-------------|
| transform | const glm::mat4&       | The transform |
| color | const glm::vec4&          | The color    |
| thickness | float                 | The thickness |
| fade | float                 | The fade |
| entityID | int                    | The entity ID    |

It can be used like this:

```c++
Renderer2D::DrawCircle(transform, color);
```

## DrawLine

```c++
static void DrawLine(const glm::vec3 &pointA, const glm::vec3 &pointB, const glm::vec4 &color, int entityID = -1);
```

It draws a line.

It takes the following parameters:

| Name   | Type                      | Description |
|--------|---------------------------|-------------|
| pointA | const glm::vec3&       | The point A |
| pointB | const glm::vec3&       | The point B |
| color | const glm::vec4&          | The color    |
| entityID | int                    | The entity ID    |

It can be used like this:

```c++
Renderer2D::DrawLine(pointA, pointB, color);
```

## DrawRect

```c++
static void DrawRect(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color, int entityID = -1);
static void DrawRect(const glm::mat4 &transform, const glm::vec4 &color, int entityID = -1);
```

It draws a rect.

It takes the following parameters:

| Name   | Type                      | Description |
|--------|---------------------------|-------------|
| position | const glm::vec3&       | The position |
| size | const glm::vec2&           | The size     |
| color | const glm::vec4&          | The color    |
| entityID | int                    | The entity ID    |

or

| Name   | Type                      | Description |
|--------|---------------------------|-------------|
| transform | const glm::mat4&       | The transform |
| color | const glm::vec4&          | The color    |
| entityID | int                    | The entity ID    |

It can be used like this:

```c++
Renderer2D::DrawRect(position, size, color);
```

## PlaySound

```c++
        static void PlaySound(AssetHandle sound);
        static void PlaySound(Ref<Sound2D> sound);
```

It plays a sound.

It takes the following parameters:

| Name   | Type                      | Description |
|--------|---------------------------|-------------|
| sound | AssetHandle              | The sound |

or

| Name   | Type                      | Description |
|--------|---------------------------|-------------|
| sound | Ref\<Sound2D\>              | The sound |

It can be used like this:

```c++
Renderer2D::PlaySound(sound);
```

## FlushAndReset

```c++
static void FlushAndReset();
```

It flushes and resets the renderer 2D.

It can be used like this:

```c++
Renderer2D::FlushAndReset();
```

## ResetBatch

```c++
static void ResetBatch();
```

It resets the batch.

It can be used like this:

```c++
Renderer2D::ResetBatch();
```

## GetStats

```c++
static const Statistics &GetStats();
```

It returns the statistics.

It returns a const Statistics&.

It can be used like this:

```c++
const Statistics &statistics = Renderer2D::GetStats();
```

## GetLineWidth

```c++
static float GetLineWidth();
```

It returns the line width.

It returns a float.

It can be used like this:

```c++
float lineWidth = Renderer2D::GetLineWidth();
```

## SetLineWidth

```c++
static void SetLineWidth(float width);
```

It sets the line width.

It takes the following parameters:

| Name  | Type  | Description |
|-------|-------|-------------|
| width | float | The width   |

It can be used like this:

```c++
Renderer2D::SetLineWidth(width);
```
