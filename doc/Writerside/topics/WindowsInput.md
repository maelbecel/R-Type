# WindowsInput

The input part of the Game Engine. It contains the classes that will be used to get the user inputs.

## IsKeyPressed

```c++
bool Input::IsKeyPressed(int key);
```

It returns true if the key is pressed.

The function takes the following parameters:

| Name | Type | Description      |
|------|------|------------------|
| key | int | The key to check |

Here is an example of how to use it:

```c++
if (Exodia::WindowsInput::IsKeyPressed(Exodia::Key::A))
    std::cout << "A is pressed" << std::endl;
```

## IsKeyReleased

```c++
bool Input::IsKeyReleased(int key);
```

It returns true if the key is released.

The function takes the following parameters:

| Name | Type | Description        |
|------|------|--------------------|
| key | int | The key to check   |

Here is an example of how to use it:

```c++
if (Exodia::WindowsInput::IsKeyReleased(Exodia::Key::A))
    std::cout << "A is released" << std::endl;
```

## IsMouseButtonPressed

```c++
bool Input::IsMouseButtonPressed(int button);
```

It returns true if the mouse button is pressed.

The function takes the following parameters:

| Name | Type | Description               |
|------|------|---------------------------|
| button | int | The mouse button to check |

Here is an example of how to use it:

```c++
if (Exodia::WindowsInput::IsMouseButtonPressed(Exodia::MouseButton::Left))
    std::cout << "Left mouse button is pressed" << std::endl;
```

## GetMousePosition

```c++
glm::vec2 Input::GetMousePosition();
```

It returns the mouse position.

Here is an example of how to use it:

```c++
glm::vec2 mousePosition = Exodia::WindowsInput::GetMousePosition();
```

## GetMouseX

```c++
float Input::GetMouseX();
```

It returns the mouse X position.


Here is an example of how to use it:

```c++
float mouseX = Exodia::WindowsInput::GetMouseX();
```

## GetMouseY

```c++
float Input::GetMouseY();
```

It returns the mouse Y position.

Here is an example of how to use it:

```c++
float mouseY = Exodia::WindowsInput::GetMouseY();
```