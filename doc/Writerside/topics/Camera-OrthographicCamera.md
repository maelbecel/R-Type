# OrthographicCamera

The OrthographicCamera class of the Camera. It contains the classes that will be used to create orthographic cameras.

It has te following method:

## Constructor

```c++
OrthographicCamera(float left, float right, float bottom, float top);
```

The constructor of the OrthographicCamera class.

It takes the following parameters:

| Name   | Type  | Description |
|--------|-------|-------------|
| left   | float | The left |
| right  | float | The right |
| bottom | float | The bottom |
| top    | float | The top |

It can be used like this:

```c++
OrthographicCamera* orthographicCamera = new OrthographicCamera(left, right, bottom, top);
```

## GetProjection

```c++
const glm::vec3 &GetProjection() const;
```

It returns the projection.

It can be used like this:

```c++
const glm::vec3& projection = orthographicCamera->GetProjection();
```

## GetProjectionMatrix

```c++
const glm::mat4 &GetProjectionMatrix() const;
```

It returns the projection matrix.

It can be used like this:

```c++
const glm::mat4& projectionMatrix = orthographicCamera->GetProjectionMatrix();
```

## GetViewProjectionMatrix

```c++
const glm::mat4 &GetViewProjectionMatrix() const;
```

It returns the view projection matrix.

It can be used like this:

```c++
const glm::mat4& viewProjectionMatrix = orthographicCamera->GetViewProjectionMatrix();
```

## GetRotation

```c++
float GetRotation() const;
```

It returns the rotation.

It can be used like this:

```c++
float rotation = orthographicCamera->GetRotation();
```

## SetPosition

```c++
void SetPosition(fconst glm::vec3 &position);
```

It sets the position.

It takes the following parameters:

| Name       | Type               | Description |
|------------|--------------------|-------------|
| position   | const glm::vec3& | The position |

It can be used like this:

```c++
orthographicCamera->SetPosition(position);
```

## SetRotation

```c++
void SetRotation(float rotation);
```

It sets the rotation.

It takes the following parameters:

| Name     | Type  | Description |
|----------|-------|-------------|
| rotation | float | The rotation |

It can be used like this:

```c++
orthographicCamera->SetRotation(rotation);
```

## SetProjection

```c++
void SetProjection(float left, float right, float bottom, float top);
```

It sets the projection.

It takes the following parameters:

| Name   | Type  | Description |
|--------|-------|-------------|
| left   | float | The left |
| right  | float | The right |
| bottom | float | The bottom |
| top    | float | The top |

It can be used like this:

```c++
orthographicCamera->SetProjection(left, right, bottom, top);
```


