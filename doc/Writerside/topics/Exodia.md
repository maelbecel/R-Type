# Exodia

Exodia is a game engine written in C++.
This part of the Game Engine is divided in multiple parts :

- [**Asset**](Asset.md) : The asset part of the Game Engine. It contains the classes that will be used to load assets.
- [**Core**](Core.md) : The core part of the Game Engine. It contains the ECS and the main classes of the Game Engine.
- [**Debug**](Debug.md) : The debug part of the Game Engine. It contains the classes that will be used to debug the Game Engine.
- [**ECS**](ECS.md) : The ECS part of the Game Engine. It contains the classes that will be used to create the ECS.
- [**Events**](Events.md) : The events part of the Game Engine. It contains the classes that will be used to handle events.
- [**ImGUI**](ImGUI-GUI.md) : The ImGui part of the Game Engine. It contains the classes that will be used to create and use ImGui.
- [**Math**](Math.md) : The math part of the Game Engine. It contains the classes that will be used to do math.
- [**Project**](Project.md) : The project part of the Game Engine. It contains the classes that will be used to create a project.
- [**Renderer**](Renderer.md) : The renderer part of the Game Engine. It contains the classes that will be used to render the game.
- [**Scene**](Scene.md) : The scene part of the Game Engine. It contains the classes that will be used to create a scene.
- [**Script**](Script.md) : The script part of the Game Engine. It contains the classes that will be used to create a script.

It also contains an entrypoint that will be used to create the game : 

```c++
int main(int ac, char **av)
{
    Exodia::Log::Init("R-Type");

    EXODIA_PROFILE_BEGIN_SESSION("Startup", "ExodiaProfile-Startup.json");
    Exodia::Application *App = Exodia::CreateApplication({ ac, av });
    EXODIA_PROFILE_END_SESSION();

    EXODIA_PROFILE_BEGIN_SESSION("Runtime", "ExodiaProfile-Runtime.json");
    App->Run();
    EXODIA_PROFILE_END_SESSION();

    EXODIA_PROFILE_BEGIN_SESSION("Shutdown", "ExodiaProfile-Shutdown.json");
    delete App;
    EXODIA_PROFILE_END_SESSION();

    return 0;
}
```

