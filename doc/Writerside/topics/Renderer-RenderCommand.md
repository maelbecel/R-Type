# RenderCommand

The RenderCommand class of the Renderer. It contains the classes that will be used to create render commands.

## Init

```c++
static void Init();
```

It initializes the render command.

It can be used like this:

```c++
RenderCommand::Init();
```

## Clear

```c++
static void Clear();
```

It clears the render command.

It can be used like this:

```c++
RenderCommand::Clear();
```

## DrawIndexed

```c++
static void DrawIndexed(const Ref<VertexArray> &vertexArray, uint32_t indexCount = 0);
```

It draws the indexed.

It takes the following parameters:

| Name        | Type                      | Description      |
|-------------|---------------------------|------------------|
| vertexArray | const Ref\<VertexArray\>& | The vertex array |
| indexCount  | uint32_t                  | The index count  |


It can be used like this:

```c++
RenderCommand::DrawIndexed(vertexArray, indexCount);
```

## DrawLines

```c++
static void DrawLines(const Ref<VertexArray> &vertexArray, uint32_t indexCount = 0);
```

It draws the lines.

It takes the following parameters:

| Name        | Type                      | Description      |
|-------------|---------------------------|------------------|
| vertexArray | const Ref\<VertexArray\>& | The vertex array |
| indexCount  | uint32_t                  | The index count  |

It can be used like this:

```c++
RenderCommand::DrawLines(vertexArray, indexCount);
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
RenderCommand::SetLineWidth(width);
```

## SetClearColor

```c++
static void SetClearColor(const glm::vec4 &color);
```

It sets the clear color.

It takes the following parameters:

| Name  | Type               | Description |
|-------|--------------------|-------------|
| color | const glm::vec4& | The color   |

It can be used like this:

```c++
RenderCommand::SetClearColor(color);
```

## SetViewport

```c++
static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
```

It sets the viewport.

It takes the following parameters:

| Name   | Type     | Description |
|--------|----------|-------------|
| x      | uint32_t | The x       |
| y      | uint32_t | The y       |
| width  | uint32_t | The width   |
| height | uint32_t | The height  |

It can be used like this:

```c++
RenderCommand::SetViewport(x, y, width, height);
```

