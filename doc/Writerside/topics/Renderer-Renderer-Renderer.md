# Renderer

The Renderer class of the Renderer. It contains the classes that will be used to create the renderer.


## SceneData

The SceneData struct of the Renderer. It contains the classes that will be used to create scene datas.

It contains the following values:

| Name | Type | Description |
|------|------|-------------|
| ViewProjectionMatrix | glm::mat4 | The view projection matrix |

It can be used like this:

```c++
SceneData sceneData;
```

## Init

```c++
static void Init();
```

It initializes the renderer.

It can be used like this:

```c++
Renderer::Init();
```

## Shutdown

```c++
static void Shutdown();
```

It shuts down the renderer.

It can be used like this:

```c++
Renderer::Shutdown();
```

## BeginScene

```c++
static void BeginScene(OrthogrpahicCamera &camera);
```

It begins the scene.

It takes the following parameters:

| Name | Type | Description |
|------|------|-------------|
| camera | OrthogrpahicCamera& | The camera |

It can be used like this:

```c++
Renderer::BeginScene(camera);
```

## EndScene

```c++
static void EndScene();
```

It ends the scene.

It can be used like this:

```c++
Renderer::EndScene();
```

## Submit

```c++
static void Submit(const Ref<Shader> &shader, const Ref<VertexArray> &vertexArray, const glm::mat4 &transform = glm::mat4(1.0f));
```

It submits the shader, vertex array and transform.

It takes the following parameters:

| Name        | Type                      | Description      |
|-------------|---------------------------|------------------|
| shader      | const Ref\<Shader\>&      | The shader       |
| vertexArray | const Ref\<VertexArray\>& | The vertex array |
| transform   | const glm::mat4&          | The transform    |

It can be used like this:

```c++
Renderer::Submit(shader, vertexArray, transform);
```

## OnWindowResize

```c++
static void OnWindowResize(uint32_t width, uint32_t height);
```

It resizes the window.

It takes the following parameters:

| Name | Type | Description |
|------|------|-------------|
| width | uint32_t | The width |
| height | uint32_t | The height |

It can be used like this:

```c++
Renderer::OnWindowResize(width, height);
```

## GetAPI

```c++
static RendererAPI::API GetAPI();
```

It returns the API.

It returns a RendererAPI::API.

It can be used like this:

```c++
RendererAPI::API api = Renderer::GetAPI();
```







