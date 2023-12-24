# Camera

Camera is the Camera class of the Renderer. It contains the classes that will be used to create cameras.

IT has te following method:

## Constructor

The constructor of the Camera class.

```c++
Camera(const glm::mat4 &projection = glm::mat4(1.0f));
```

It takes the following parameters:

| Name       | Type         | Description |
|------------|--------------|-------------|
| projection | const glm::mat4& | The projection |

It can be used like this:

```c++
Camera* camera = new Camera(projection);
```

## GetProjection

```c++
const glm::mat4 &GetProjection() const;
```

It returns the projection.

It can be used like this:

```c++
const glm::mat4& projection = camera->GetProjection();
```