# CameraComponent

## Description

The `CameraComponent` is a crucial component in game development that defines a camera in the game world. It is responsible for rendering the game scene from a specific perspective and position in the world. The `CameraComponent` contains the camera's projection matrix and view matrix, as well as other properties like field of view and near/far clipping planes.

## Properties

| Name             | Type        | Description                                                                                                                            |
|------------------|-------------|----------------------------------------------------------------------------------------------------------------------------------------|
| Camera           | SceneCamera | The camera component.                                                                                                                  |
| Primary          | Boolean     | Defines whether the camera is the primary camera. The primary camera is the camera that renders the game scene.                        |
| FixedAspectRatio | Boolean     | Defines whether the camera has a fixed aspect ratio. If enabled, the camera's aspect ratio will not change when the window is resized. |

The `CameraComponent` contains a `SceneCamera` object that defines the camera's projection matrix and view matrix. The `SceneCamera` object contains the following properties:

| Name              | Type  | Description                                                                                                                                                                                                                                                                                                                                                                            |
|-------------------|-------|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Projection Type   | Enum  | Defines the type of projection used by the camera. It can be either Orthographic or Perspective. Orthographic projection renders objects in the game world without perspective, making distant objects appear the same size as nearby objects. Perspective projection, on the other hand, renders objects with perspective, making distant objects appear smaller than nearby objects. |
| Perspective FOV   | Float | Represents the field of view of the camera when using Perspective projection. It is the extent of the observable game world that is seen at any given moment by the camera. It's usually defined in degrees.                                                                                                                                                                           |
| Perspective Near  | Float | Defines the near clipping plane of the camera when using Perspective projection. Any objects closer to the camera than the near clipping plane will not be rendered. This helps improve performance by not rendering objects that are too close to be seen.                                                                                                                            |
| Perspective Far   | Float | Defines the far clipping plane of the camera when using Perspective projection. Any objects further away from the camera than the far clipping plane will not be rendered. This also helps improve performance by not rendering objects that are too far to be seen.                                                                                                                   |
| Orthographic Size | Float | Represents the size of the camera's orthographic view volume when using Orthographic projection. This is essentially the height of the camera's view in world units.                                                                                                                                                                                                                   |
| Orthographic Near | Float | Defines the near clipping plane of the camera when using Orthographic projection. Any objects closer to the camera than the near clipping plane will not be rendered.                                                                                                                                                                                                                  |
| Orthographic Far  | Float | Defines the far clipping plane of the camera when using Orthographic projection. Any objects further away from the camera than the far clipping plane will not be rendered.                                                                                                                                                                                                            |

## Methods

- ```c++
  void DrawComponent();
  ```
  The `DrawComponent()` function is a virtual function that is overridden in the `CameraComponent` struct. This function is responsible for drawing the component's properties in the ImGui interface. It is called by the `OnImGuiRender()` function in the `SceneCamera` class.


## Usage

### Creating a camera

To create a camera, you can use the following code:

```c++
World *world = new World();
Entity *cameraEntity = _World->CreateEntity("Camera");
cameraEntity->AddComponent<CameraComponent>();
```

### Setting the camera's projection type

To set the camera's projection type, you can use the following code:

```c++
CameraComponent *cameraComponent = cameraEntity->GetComponent<CameraComponent>();
cameraComponent->Camera.SetProjectionType(SceneCamera::ProjectionType::Perspective);
```

### Setting the camera's perspective properties

To set the camera's perspective properties, you can use the following code:

```c++
CameraComponent *cameraComponent = cameraEntity->GetComponent<CameraComponent>().Get();
cameraComponent.Camera.SetProjectionType(SceneCamera::ProjectionType::Perspective);
cameraComponent.Camera.SetViewportSize(1600, 900);
...
```

