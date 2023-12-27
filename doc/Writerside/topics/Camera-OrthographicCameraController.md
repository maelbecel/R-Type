# OrthographicCameraController

The OrthographicCameraController class of the Camera. It contains the classes that will be used to create orthographic camera controllers.

It defines multiple methods and structs:

## Constructor

```c++
OrthographicCameraController(float aspectRatio, bool rotation = false);
```

The constructor of the OrthographicCameraController class.

It takes the following parameters:

| Name        | Type    | Description |
|-------------|---------|-------------|
| aspectRatio | float   | The aspect ratio |
| rotation    | bool    | The rotation |

It can be used like this:

```c++
OrthographicCameraController* orthographicCameraController = new OrthographicCameraController(aspectRatio, rotation);
```

## OrthographicCameraBounds

It defines the OrthographicCameraBounds struct that contains the bounds of the OrthographicCamera.
It has the following parameters:

| Name | Type | Description |
|------|------|-------------|
| Left | float | The left |
| Right | float | The right |
| Bottom | float | The bottom |
| Top | float | The top |

With a ```float GetWidth()``` and ```float GetHeight()``` methods.

## OnUpdate

```c++
void OnUpdate(Timestep ts);
```

This function updates the OrthographicCameraController.

It takes the following parameters:

| Name | Type | Description |
|------|------|-------------|
| ts | Timestep | The timestep |

It can be used like this:

```c++
orthographicCameraController->OnUpdate(ts);
```

## OnEvent

```c++
void OnEvent(Event &e);
```

This function is call when an event is triggered.

It takes the following parameters:

| Name | Type | Description |
|------|------|-------------|
| e | Event& | The event |

It can be used like this:

```c++
orthographicCameraController->OnEvent(e);
```


## OnResize

```c++
void OnResize(float width, float height);
```

This function is call when the window is resized.

It takes the following parameters:

| Name | Type | Description |
|------|------|-------------|
| width | float | The width |
| height | float | The height |

It can be used like this:

```c++
orthographicCameraController->OnResize(width, height);
```

## GetCamera

```c++
OrthographicCamera &GetCamera();
```

It returns the OrthographicCamera.

It can be used like this:

```c++
OrthographicCamera& orthographicCamera = orthographicCameraController->GetCamera();
```

## SetZoomLevel

```c++
void SetZoomLevel(float level);
```

It sets the zoom level.

It takes the following parameters:

| Name | Type | Description |
|------|------|-------------|
| level | float | The level |


It can be used like this:

```c++
orthographicCameraController->SetZoomLevel(level);
```

## GetZoomLevel

```c++
float GetZoomLevel() const;
```

It returns the zoom level.

It can be used like this:

```c++
float zoomLevel = orthographicCameraController->GetZoomLevel();
```

## GetBounds

```c++
const OrthographicCameraBounds &GetBounds() const;
```

It returns the bounds.

It can be used like this:

```c++
const OrthographicCameraBounds& bounds = orthographicCameraController->GetBounds();
```

