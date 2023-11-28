# ImGui Docking

## What is this ?

ImGui Docking refers to the ability of ImGui (Dear ImGui), a popular GUI library for immediate mode graphical user interfaces, to enable a docking system within its framework.
Docking allows users to create complex layouts by arranging various windows within an application in a flexible and customizable way.

With ImGui Docking, users can :
- Create Multi-Window Interfaces: ImGui allows the creation of multiple windows within an application. The docking feature enables these windows to be organized, rearranged, and grouped together dynamically based on the user's preferences.
- Drag and Drop Interface Elements: Users can drag and drop individual windows or interface elements to dock them into specific areas of the application window.
- Resizable and Movable Windows: Docked windows are resizable and movable, allowing users to adjust their size and position within the layout.
- Tabbed Interface: Windows can be organized as tabs within a single window or floated as separate windows, providing flexibility in managing different views and functionalities.
- Customization: Users can often customize the appearance, behavior, and docking behavior, allowing developers to tailor the docking system to suit their application's specific requirements.

## How to use it ?

### Initialization

Create a basic application window like the following:

```cpp
class ApplicationExample : public Application {
    public:
        ApplicationExample(const ApplicationSpecification &spec) : Application(spec)
        {
            PushLayer(new DockerLayer());
        }

        ~ApplicationExample() = default;
};
```

We create a new layer and push it to the layer stack. This layer will be responsible for the docking system.

### Creating a DockerLayer

When the Layer is create go inside the `OnImGUIRender()`.
In this function use this following code :

```cpp
void DockerLayer::OnImGUIRender()
{
    EXODIA_PROFILE_FUNCTION();

    static bool dockspaceOpen                 = true;
    static bool opt_fullscreen_persistant     = true;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
    bool opt_fullscreen = opt_fullscreen_persistant;

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

    if (opt_fullscreen) {
        ImGuiViewport *viewport = ImGui::GetMainViewport();

        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }

    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
    ImGui::PopStyleVar();

    if (opt_fullscreen)
        ImGui::PopStyleVar(2);

    // DockSpace
    ImGuiIO& io = ImGui::GetIO();
    ImGuiStyle& style = ImGui::GetStyle();

    float minWinSizeX = style.WindowMinSize.x;

    style.WindowMinSize.x = 450.0f;
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }

    style.WindowMinSize.x = minWinSizeX;

    ImGui::End();
}
```

You will have this result :

![Docking](./img/docking.png)

Note, nothing have changed, but we have now a DockSpace.

### Creating ImGui Windows

- Stats Window

```cpp
class StatImGui {
    public:

        StatImGui() = default;
        ~StatImGui() = default;

        void OnImGuiRender()
        {
            auto stats = Renderer2D::GetStats();

            ImGui::Begin("Stats");

            ImGui::Text("Renderer2D Stats:");
            ImGui::Text("Draw Calls: %d", stats.DrawCalls);
            ImGui::Text("Quads: %d", stats.QuadCount);
            ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
            ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

            ImGui::End();
        }
};
```

It's a simple ImGui Window, nothing special.
That write the stats of the Renderer2D.

![Stats](./img/stats.png)

### How to dock a window ?

To dock the window you just need to click on the title bar of the window and drag it to the place you want.

![Docking](./img/docking.png)

You will have little blue square that will appear, it's the place where you can dock the window.
For examples, we will place the stats window on the right blue square of the window.

![Docking](./img/docking2.png)

## What good features can he provide ?

In the game engine, we have a `Framebuffer` class. This class is used to render the scene in a texture.

## Create your first frame buffer

```cpp
void DockerLayer::OnAttach()
{
    FramebufferSpecification fbSpec;

    fbSpec.Width = 1280;
    fbSpec.Height = 720;
    fbSpec.Attachments = {
        FramebufferTextureFormat::RGBA8,
        FramebufferTextureFormat::RED_INTEGER,
        FramebufferTextureFormat::Depth
    };

    _Framebuffer = Framebuffer::Create(fbSpec);

    // -- ImGui Windows Init..
}
```

You need to create a `FramebufferSpecification` and set the width, height and the attachments.
- `FramebufferTextureFormat::RGBA8` is the color attachment.
- `FramebufferTextureFormat::RED_INTEGER` is the picking attachment.
- `FramebufferTextureFormat::Depth` is the depth attachment.

You had your FramebufferSpecification to the `Framebuffer::Create()` function and you will have your framebuffer.

After that you want to render the scene in the framebuffer, you need to do this :

```cpp
void DockerLayer::OnUpdate(Timestep ts)
{
    // Bind the framebuffer
    _Framebuffer->Bind();

    // Renderer Prep
    RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
    RenderCommand::Clear();

    // Clear Entity ID attachment to -1
    _Framebuffer->ClearAttachment(1, -1);

    // Update
    _CameraController.OnUpdate(ts);

    // Renderer Draw
    Renderer2D::BeginScene(_CameraController.GetCamera());

    Renderer2D::DrawRotatedQuad(
        { 0.0f, 0.0f },      // Position
        { 0.8f, 0.8f },      // Size
        glm::radians(-45.0f), // Rotation
        _SquareColor          // Color
    );

    Renderer2D::EndScene();

    // Unbind the framebuffer
    _Framebuffer->Unbind();
}
```

Your layer update need to begin with the `Framebuffer::Bind()` for bind the framebuffer.
And end with the `Framebuffer::Unbind()` for unbind the framebuffer.
Between that you clear the framebuffer and render the scene in the framebuffer.

With this code, we can now create a Viewport ImGui Window.

```cpp
void OnImGuiRender(Ref<Framebuffer> framebuffer)
{
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });

    ImGui::Begin("Viewport");
    ImVec2 viewportMinRegion = ImGui::GetWindowContentRegionMin();
    ImVec2 viewportMaxRegion = ImGui::GetWindowContentRegionMax();
    ImVec2 viewportOffset = ImGui::GetWindowPos();

    _ViewportBounds[0] = { viewportMinRegion.x + viewportOffset.x, viewportMinRegion.y + viewportOffset.y };
    _ViewportBounds[1] = { viewportMaxRegion.x + viewportOffset.x, viewportMaxRegion.y + viewportOffset.y };

    _ViewportFocused = ImGui::IsWindowFocused();
    _ViewportHovered = ImGui::IsWindowHovered();

    Application::Get().GetImGuiLayer()->SetBlockEvents(!_ViewportFocused && !_ViewportHovered);

    ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();

    _ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };

    uint32_t textureID = framebuffer->GetColorAttachmentRendererID();

    ImGui::Image(reinterpret_cast<ImTextureID>(textureID), ImVec2{ _ViewportSize.x, _ViewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
    ImGui::End();

    ImGui::PopStyleVar();
}
```

Here is the result :
![Viewport](./img/viewport.png)

# Running the example

To run the example, you can use the following commands:

```bash
./bin_examples/imgui_Docking
```
