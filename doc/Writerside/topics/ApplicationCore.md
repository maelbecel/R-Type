# Application

The Application part define 2 classes :
- [**Application**](#application) : The Application class is used to manage the application.
- [**Window**](#window) : The Window class is used to manage the window.


## Application

The Application class is used to manage the application.

### CreateApplication

```c++
    Application *CreateApplication(ApplicationCommandLineArgs args = ApplicationCommandLineArgs());
```

It creates an application.

The method takes the following parameters:

| Name  | Type                       | Description                            |
|-------|----------------------------|----------------------------------------|
| args  | ApplicationCommandLineArgs | The application command line arguments |

### ApplicationCommandLineArgs

```c++
    struct ApplicationCommandLineArgs {
        int    Count = 0;
        char **Args  = nullptr;

        const char *operator[](int index) const
        {
            EXODIA_CORE_ASSERT(index < Count, "Index out of range !");
            return Args[index];
        }
    };
```

The ApplicationCommandLineArgs struct is used to define the application command line arguments.

### ApplicationSpecification

```c++
    struct ApplicationSpecification {
        std::string Name = "Exodia Application";
        std::string WorkingDirectory;
        ApplicationCommandLineArgs CommandLineArgs;
    };
```

The ApplicationSpecification struct is used to define the application specification.

### Constructor

```c++
    Application(const ApplicationSpecification &specification);
```

It creates an application.

The constructor takes the following parameters:

| Name          | Type                          | Description                  |
|---------------|-------------------------------|------------------------------|
| specification | ApplicationSpecification &    | The application specification|

Here is an example of how to use it:

```c++
ApplicationSpecification specification;
Exodia::Application application(specification);
```

### Run

```c++
    void Run();
```

It runs the application.

Here is an example of how to use it:

```c++
application.Run();
```

### Close

```c++
    void Close();
```

It closes the application.

Here is an example of how to use it:

```c++
application.Close();
```

### OnEvent

```c++
    void OnEvent(Event &event);
```

It handles an event.

The method takes the following parameters:

| Name  | Type  | Description |
|-------|-------|-------------|
| event | Event & | The event   |

Here is an example of how to use it:

```c++
Event event;
application.OnEvent(event);
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
application.PushLayer(layer);
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
application.PushOverlay(overlay);
```

### GetImGuiLayer

```c++
    ImGuiLayer *GetImGuiLayer() const;
```

It returns the ImGui layer.

Here is an example of how to use it:

```c++
ImGuiLayer *layer = application.GetImGuiLayer();
```

### GetSpecification
    
```c++
    const ApplicationSpecification &GetSpecification() const;
```

It returns the application specification.

Here is an example of how to use it:

```c++
ApplicationSpecification specification = application.GetSpecification();
```

### Get

```c++
    static Application &Get();
```

It returns the application.

Here is an example of how to use it:

```c++
Application &application = Application::Get();
```

### GetWindow

```c++
    Window &GetWindow() const;
```

It returns the window.

Here is an example of how to use it:

```c++
Window &window = application.GetWindow();
```


## Window

The Window class is used to manage the window.

### WindowProps

```c++
    struct WindowProps {
        std::string  Title;  /*!< The title of the window */
        uint32_t     Width;  /*!< The width of the window */
        uint32_t     Height; /*!< The height of the window */
 
        WindowProps(const std::string &title = "Exodia Engine", uint32_t width = 1600, uint32_t height = 900) : Title(title), Width(width), Height(height) {};
    };
```

The WindowProps struct is used to define the window properties.

### Create

```c++
    static Scope<Window> Create(const WindowProps &props = WindowProps());
```

It creates a window.

The method takes the following parameters:

| Name  | Type  | Description |
|-------|-------|-------------|
| props | WindowProps & | The window properties |

Here is an example of how to use it:

```c++
WindowProps props;
Scope<Window> window = Window::Create(props);
```

### GetWidth

```c++
    virtual uint32_t GetWidth() const = 0;
```

It returns the width of the window.

Here is an example of how to use it:

```c++
uint32_t width = window->GetWidth();
```

### GetHeight

```c++
    virtual uint32_t GetHeight() const = 0;
```

It returns the height of the window.

Here is an example of how to use it:

```c++
uint32_t height = window->GetHeight();
```

### SetEventCallback

```c++
    virtual void SetEventCallback(const std::function<void(Event &)> &callback) = 0;
```

It sets the event callback.

The method takes the following parameters:

| Name     | Type                          | Description |
|----------|-------------------------------|-------------|
| callback | const std::function<void(Event &)> & | The callback |

Here is an example of how to use it:

```c++
window->SetEventCallback([](Event &event) {
    std::cout << "Event received" << std::endl;
});
```

### SetVSync

```c++
    virtual void SetVSync(bool enabled) = 0;
```

It sets the VSync.

The method takes the following parameters:

| Name    | Type  | Description |
|---------|-------|-------------|
| enabled | bool  | The VSync   |

Here is an example of how to use it:

```c++
bool enabled = true;
window->SetVSync(enabled);
```

### IsVSync

```c++
    virtual bool IsVSync() const = 0;
```

It returns true if the VSync is enabled, false otherwise.

Here is an example of how to use it:

```c++
bool enabled = window->IsVSync();
```

### GetNativeWindow

```c++
    virtual void *GetNativeWindow() const = 0;
```

It returns the native window.

Here is an example of how to use it:

```c++
void *nativeWindow = window->GetNativeWindow();
```

