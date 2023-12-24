# Shader

The Shader part of the Renderer. It contains the classes that will be used to create shaders.

## Create

```c++
static Ref<Shader> Create(const std::string& filepath);
static Ref<Shader> Create(const std::string &name, const std::string &vertexSrc,
                          const std::string &fragmentSrc);

```

It creates a shader.

It takes the following parameters:

| Name     | Type               | Description   |
|----------|--------------------|---------------|
| filepath | const std::string& | The filepath  |

or

| Name       | Type               | Description   |
|------------|--------------------|---------------|
| name       | const std::string& | The name      |
| vertexSrc  | const std::string& | The vertexSrc |
| fragmentSrc| const std::string& | The fragmentSrc |

It can be used like this:

```c++
Ref<Shader> shader = Shader::Create("assets/shaders/Texture.glsl");
```

## Bind

```c++
void Bind() const;
```

It binds the shader.

It can be used like this:

```c++
shader->Bind();
```

## Unbind

```c++
void Unbind() const;
```

It unbinds the shader.

It can be used like this:

```c++
shader->Unbind();
```

## GetName

```c++
const std::string &GetName() const;
```

It returns the name.

It returns a const std::string&.

It can be used like this:

```c++
std::string name = shader->GetName();
```

## SetInt

```c++
void SetInt(const std::string &name, int value);
```

It sets an int.

It takes the following parameters:

| Name  | Type               | Description |
|-------|--------------------|-------------|
| name  | const std::string& | The name    |
| value | int                | The value   |

It can be used like this:

```c++
shader->SetInt("u_Texture", 0);
```

## SetIntArray

```c++
void SetIntArray(const std::string &name, int *values, uint32_t count);
```

It sets an int array.

It takes the following parameters:

| Name   | Type               | Description |
|--------|--------------------|-------------|
| name   | const std::string& | The name    |
| values | int*               | The values  |
| count  | uint32_t           | The count   |

It can be used like this:

```c++
shader->SetIntArray("u_Textures", textures, 32);
```

## SetFloat

```c++
void SetFloat(const std::string &name, float value);
```

It sets a float.

It takes the following parameters:

| Name  | Type               | Description |
|-------|--------------------|-------------|
| name  | const std::string& | The name    |
| value | float              | The value   |

It can be used like this:

```c++
shader->SetFloat("u_Time", 0.0f);
```

## SetFloat2

```c++
void SetFloat2(const std::string &name, const glm::vec2 &value);
```

It sets a float2.

It takes the following parameters:

| Name  | Type               | Description      |
|-------|--------------------|------------------|
| name  | const std::string& | The name         |
| value | const glm::vec2&   | The value        |

It can be used like this:

```c++
shader->SetFloat2("u_ViewportSize", glm::vec2(1280, 720));
```

## SetFloat3

```c++
void SetFloat3(const std::string &name, const glm::vec3 &value);
```

It sets a float3.

It takes the following parameters:

| Name  | Type               | Description      |
|-------|--------------------|------------------|
| name  | const std::string& | The name         |
| value | const glm::vec3&   | The value        |

It can be used like this:

```c++
shader->SetFloat3("u_Color", glm::vec3(1.0f, 0.0f, 0.0f));
```

## SetFloat4

```c++
void SetFloat4(const std::string &name, const glm::vec4 &value);
```

It sets a float4.

It takes the following parameters:

| Name  | Type               | Description      |
|-------|--------------------|------------------|
| name  | const std::string& | The name         |
| value | const glm::vec4&   | The value        |

It can be used like this:

```c++
shader->SetFloat4("u_Color", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
```

## SetMat4

```c++
void SetMat4(const std::string &name, const glm::mat4 &value);
```

It sets a mat4.

It takes the following parameters:

| Name  | Type               | Description      |
|-------|--------------------|------------------|
| name  | const std::string& | The name         |
| value | const glm::mat4&   | The value        |


It can be used like this:

```c++
shader->SetMat4("u_Transform", transform);
```

## ShaderLibrary

The ShaderLibrary part of the Renderer. It contains the classes that will be used to create a shader library.

It defines the class `ShaderLibrary`.

This class has the following methods:

## Load

```c++
Ref<Shader> Load(const std::string &filepath);
Ref<Shader> Load(const std::string &name, const std::string &filepath);
```

It loads a shader.

It takes the following parameters:

| Name     | Type               | Description   |
|----------|--------------------|---------------|
| filepath | const std::string& | The filepath  |
| name     | const std::string& | The name      |

It can be used like this:

```c++
ShaderLibrary.Load("assets/shaders/Texture.glsl");
```

## Add

```c++
void Add(const Ref<Shader> &shader);
void Add(const std::string &name, const Ref<Shader> &shader);
```

It adds a shader.

It takes the following parameters:

| Name   | Type               | Description   |
|--------|--------------------|---------------|
| shader | const Ref<Shader>& | The shader    |
| name   | const std::string& | The name      |

It can be used like this:

```c++
ShaderLibrary.Add(shader);
```

## Get

```c++
Ref<Shader> Get(const std::string &name);
```

It returns a shader.

It takes the following parameters:

| Name | Type               | Description |
|------|--------------------|-------------|

It returns a Ref<Shader>.

It can be used like this:

```c++
Ref<Shader> shader = ShaderLibrary.Get("Texture");
```

## Exists

```c++
bool Exists(const std::string &name) const;
```

It returns if the shader exists.

It takes the following parameters:

| Name | Type               | Description |
|------|--------------------|-------------|
| name | const std::string& | The name    |

It returns a bool.

It can be used like this:

```c++
bool exists = ShaderLibrary.Exists("Texture");
```
```
