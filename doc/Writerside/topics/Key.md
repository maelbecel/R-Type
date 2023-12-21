# Key

The Key part of the Core. It contains the classes that will be used to manage keys.

It contains the following parts:

- [**Input**](#input) : The Input part of the Key. It contains the classes that will be used to manage inputs.
- [**KeyCodes**](#keycodes) : The KeyCodes part of the Key. It contains the classes that will be used to manage key codes.
- [**MouseButtonCodes**](#mousebuttoncodes) : The MouseButtonCodes part of the Key. It contains the classes that will be used to manage mouse button codes.

## Input

The Input class is used to manage inputs.

### IsKeyPressed

```c++
static bool IsKeyPressed(int key);
```

It checks if a key is pressed.

The method takes the following parameters:

| Name | Type | Description |
|------|------|-------------|
| key  | int  | The key     |

Here is an example of how to use it:

```c++
int key;
bool isPressed = Input::IsKeyPressed(key);
```

### IsKeyReleased

```c++
static bool IsKeyReleased(int key);
```

It checks if a key is released.

The method takes the following parameters:

| Name | Type | Description |
|------|------|-------------|
| key  | int  | The key     |

Here is an example of how to use it:

```c++
int key;
bool isReleased = Input::IsKeyReleased(key);
```

### IsMouseButtonPressed

```c++
static bool IsMouseButtonPressed(int button);
```

It checks if a mouse button is pressed.

The method takes the following parameters:

| Name   | Type | Description     |
|--------|------|-----------------|
| button | int  | The mouse button|

Here is an example of how to use it:

```c++
int button;
bool isPressed = Input::IsMouseButtonPressed(button);
```

### GetMousePosition

```c++
static glm::vec2 GetMousePosition();
```

It gets the mouse position.

Here is an example of how to use it:

```c++

glm::vec2 position = Input::GetMousePosition();
```

### GetMouseX

```c++
static float GetMouseX();
```

It gets the mouse X position.

Here is an example of how to use it:

```c++
std::cout << "Mouse X position: " << Input::GetMouseX() << std::endl;
```

### GetMouseY

```c++
static float GetMouseY();
```

It gets the mouse Y position.

Here is an example of how to use it:

```c++
std::cout << "Mouse Y position: " << Input::GetMouseY() << std::endl;
```

## KeyCodes

KeyCode is an enum class that contains the key codes.

## MouseButtonCodes

MouseButtonCode is an enum class that contains the mouse button codes.


