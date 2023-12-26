# Context

The Context part of the Renderer. It contains the classes that will be used to create contexts.

It defines the class `GraphicsContext`.

This class has the following methods:

## Create

```c++
static Scope<GraphicsContext> Create(void* window);
```

It creates a graphics context.

It takes the following parameters:

| Name   | Type  | Description |
|--------|-------|-------------|
| window | void* | The window  |

It can be used like this:

```c++
Scope<GraphicsContext> context = GraphicsContext::Create(window);
```

## Init

```c++
virtual void Init() = 0;
```

It initializes the graphics context.

It can be used like this:

```c++
context->Init();
```

## SwapBuffers

```c++
virtual void SwapBuffers() = 0;
```

It swaps the buffers.

It can be used like this:

```c++
context->SwapBuffers();
```
