# RendererAPI

The RendererAPI class of the Renderer. It contains the classes that will be used to create the renderer API.

It defines the following classes and method:


## API

The API enum of the RendererAPI. It contains the classes that will be used to create API.

It contains the following values:

- **None** : The None value of the API. It contains the classes that will be used to create none.
- **OpenGL** : The OpenGL value of the API. It contains the classes that will be used to create OpenGL.
- **SFML** : The SFML value of the API. It contains the classes that will be used to create SFML.

It can be used like this:

```c++
RendererAPI::API api = RendererAPI::API::None;
```

## Init

```c++  
static void Init();
```

It initializes the renderer API.

It can be used like this:

```c++
RendererAPI::Init();
```

## Clear

```c++
static void Clear();
```

It clears the renderer API.

It can be used like this:

```c++
RendererAPI::Clear();
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
RendererAPI::DrawIndexed(vertexArray, indexCount);
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
RendererAPI::DrawLines(vertexArray, indexCount);
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
RendererAPI::SetLineWidth(width);
```

## SetClearColor

```c++
static void SetClearColor(const glm::vec4 &color);
```

It sets the clear color.

It takes the following parameters:

| Name  | Type          | Description |
|-------|---------------|-------------|
| color | const glm::vec4& | The color   |

It can be used like this:

```c++
RendererAPI::SetClearColor(color);
```

## SetViewport

```c++
static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
```

It sets the viewport.

It takes the following parameters:

| Name  | Type  | Description |
|-------|-------|-------------|
| x     | uint32_t | The x       |
| y     | uint32_t | The y       |
| width | uint32_t | The width   |
| height | uint32_t | The height   |

It can be used like this:

```c++
RendererAPI::SetViewport(x, y, width, height);
```

## GetAPI

```c++
static RendererAPI::API GetAPI();
```

It returns the API.

It returns a RendererAPI::API.

It can be used like this:

```c++
RendererAPI::API api = RendererAPI::GetAPI();
```

## SetAPI

```c++
static void SetAPI(RendererAPI::API api);
```

It sets the API.

It takes the following parameters:

| Name | Type               | Description |
|------|--------------------|-------------|
| api  | RendererAPI::API | The API     |

It can be used like this:

```c++
RendererAPI::SetAPI(api);
```
