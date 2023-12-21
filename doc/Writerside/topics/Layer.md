# Layer

The Layer part of the Core. It contains the classes that will be used to manage layers.
It contains the following parts:
- [**Layer**](#layer) : The Layer part of the Layer. It contains the classes that will be used to manage layers.
- [**LayerStack**](#layerstack) : The LayerStack part of the Layer. It contains the classes that will be used to manage layer stacks.

## Layer

The Layer class is used to manage layers.

### Constructor

```c++
Layer(const std::string &name = "Layer");
```

It creates a layer.

The constructor takes the following parameters:

| Name  | Type          | Description |
|-------|---------------|-------------|
| name  | std::string & | The name    |

Here is an example of how to use it:

```c++
std::string name;
Layer layer(name);
```

### OnAttach

```c++
virtual void OnAttach();
```

It attaches the layer.

Here is an example of how to use it:

```c++
layer.OnAttach();
```

### OnDetach

```c++
virtual void OnDetach();
```

It detaches the layer.

Here is an example of how to use it:

```c++
layer.OnDetach();
```

### OnUpdate

```c++
virtual void OnUpdate(Timestep ts);
```

It updates the layer.

The method takes the following parameters:

| Name | Type    | Description |
|------|---------|-------------|
| ts   | Timestep | The timestep |

Here is an example of how to use it:

```c++
layer.OnUpdate(ts);
```

### OnEvent

```c++
virtual void OnEvent(Event &event);
```

It handles an event.

The method takes the following parameters:

| Name  | Type  | Description |
|-------|-------|-------------|
| event | Event & | The event   |

Here is an example of how to use it:

```c++
Event event;
layer.OnEvent(event);
```

### OnImGuiRender

```c++
virtual void OnImGuiRender();
```

It renders the ImGui.

Here is an example of how to use it:

```c++
layer.OnImGuiRender();
```

## LayerStack

The LayerStack class is used to manage layer stacks.

### Constructor {id=constructor1}

```c++

```c++
LayerStack();
```

It creates a layer stack.

Here is an example of how to use it:

```c++
LayerStack layerStack;
```

### PushLayer

```c++
void PushLayer(Layer *layer);
```

It pushes a layer.

The method takes the following parameters:

| Name  | Type  | Description |
|-------|-------|-------------|
| layer | Layer * | The layer   |

Here is an example of how to use it:

```c++
Layer *layer;
layerStack.PushLayer(layer);
```

### PushOverlay

```c++
void PushOverlay(Layer *overlay);
```

It pushes an overlay.

The method takes the following parameters:

| Name    | Type  | Description |
|---------|-------|-------------|
| overlay | Layer * | The overlay |

Here is an example of how to use it:

```c++
Layer *overlay;
layerStack.PushOverlay(overlay);
```

### PopLayer

```c++
void PopLayer(Layer *layer);
```

It pops a layer.

The method takes the following parameters:

| Name  | Type  | Description |
|-------|-------|-------------|
| layer | Layer * | The layer   |

Here is an example of how to use it:

```c++
Layer *layer;
layerStack.PopLayer(layer);
```

### PopOverlay

```c++
void PopOverlay(Layer *overlay);
```

It pops an overlay.

The method takes the following parameters:

| Name    | Type  | Description |
|---------|-------|-------------|
| overlay | Layer * | The overlay |

Here is an example of how to use it:

```c++
Layer *overlay;
layerStack.PopOverlay(overlay);
```

### begin

```c++
std::vector<Layer *>::const_iterator begin();
std::vector<Layer *>::const_iterator begin() const;
```

It starts the iterator.

Here is an example of how to use it:

```c++
layerStack.begin();
```

### end

```c++
std::vector<Layer *>::const_iterator end();
std::vector<Layer *>::const_iterator end() const;
```

It ends the iterator.

Here is an example of how to use it:

```c++
layerStack.end();
```

### rbegin

```c++
std::vector<Layer *>::const_reverse_iterator rbegin();
std::vector<Layer *>::const_reverse_iterator rbegin() const;
```

It starts the reverse iterator.

Here is an example of how to use it:

```c++
layerStack.rbegin();
```

### rend

```c++
std::vector<Layer *>::const_reverse_iterator rend();
std::vector<Layer *>::const_reverse_iterator rend() const;
```

It ends the reverse iterator.

Here is an example of how to use it:

```c++
layerStack.rend();
```

