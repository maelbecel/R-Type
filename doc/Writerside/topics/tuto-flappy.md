# How to recreate the game

## Tools

To recreate the game, you will need to use the following tools, you can 

### Collider

The Collider tool contain the following function :
The function `PointInTriangle` is a static function that determines whether a given point is inside a triangle or not.
```c++
static bool PointInTriangle(const glm::vec2 &position, glm::vec2 &pa, const glm::vec2 &pb, const glm::vec2 &pc) {
    float s = pa.y * pc.x - pa.x * pc.y + (pc.y - pa.y) * position.x + (pa.x - pc.x) * position.y;
    float t = pa.x * pb.y - pa.y * pb.x + (pa.y - pb.y) * position.x + (pb.x - pa.x) * position.y;

    if ((s < 0) != (t < 0))
        return false;

    float A = -pb.y * pc.x + pa.y * (pc.x - pb.x) + pa.x * (pb.y - pc.y) + pb.x * pc.y;

    return A < 0 ? (s <= 0 && s + t >= A) : (s >= 0 && s + t <= A);
}
```

It takes the following parameters:

| Name     | Type     | Description |
|----------|----------|-------------|
| position | glm::vec2& | The position |
| pa       | glm::vec2& | The pa       |
| pb       | glm::vec2& | The pb       |
| pc       | glm::vec2& | The pc       |

It returns a bool.

### Color

The Color tool define the following colors :
```c++
static glm::vec4 Black = {0.0f, 0.0f, 0.0f, 1.0f};
static glm::vec4 White = {1.0f, 1.0f, 1.0f, 1.0f};
```

The Color tool contain the following function :

The function `HSVtoRGB` is a static function that converts a color from HSV to RGB.
```c++
    static glm::vec4 HSVtoRGB(const glm::vec3 &hsv) {
        int H = (int)(hsv.x * 360.0f);

        double S = hsv.y;
        double V = hsv.z;
        double C = S * V;
        double X = C * (1 - abs(fmod(H / 60.0, 2) - 1));
        double m = V - C;
        double Rs;
        double Gs;
        double Bs;

        if (H >= 0 && H < 60) {
            Rs = C;
            Gs = X;
            Bs = 0;
        } else if (H >= 60 && H < 120) {
            Rs = X;
            Gs = C;
            Bs = 0;
        } else if (H >= 120 && H < 180) {
            Rs = 0;
            Gs = C;
            Bs = X;
        } else if (H >= 180 && H < 240) {
            Rs = 0;
            Gs = X;
            Bs = C;
        } else if (H >= 240 && H < 300) {
            Rs = X;
            Gs = 0;
            Bs = C;
        } else {
            Rs = C;
            Gs = 0;
            Bs = X;
        }

        return {(Rs + m), (Gs + m), (Bs + m), 1.0f};
    }
```

### ParticleProps

The ParticleProps tool define the following properties :
```c++
    struct ParticleProps {
        glm::vec2 Position;
        glm::vec2 Velocity;
        glm::vec2 VelocityVariation;
        glm::vec4 ColorBegin;
        glm::vec4 ColorEnd;
        float SizeBegin;
        float SizeEnd;
        float SizeVariation;
        float LifeTime = 1.0f;
        int NumberOfParticles = 100;
    };
```

### Random

The Random class contains the following function :

The function `Init` is a static function that initializes the random class.
```c++
    static void Init() { _Engine.seed(std::random_device()()); }
```

The function `Float` is a static function that returns a random float.
```c++
    static float Float() { return (float)_Distribution(_Engine); }
```

## Main part

### Entrypoint

First, we need to create the entrypoint of the game. To do so, we need to create a class that inherits from the `Application` class.
```c++
    Application *CreateApplication(ApplicationCommandLineArgs args) {
        EXODIA_PROFILE_FUNCTION();

        ApplicationSpecification spec;

        spec.Name = "FlappyBird";
        spec.CommandLineArgs = args;

        return new FlappyBird::FlappyBirdClient(spec);
    }
```

### Client

Then, we will create the `FlappyBirdClient` class that inherits from the `Application` class.
It will be used to create the game.
```c++
    class FlappyBirdClient : public Application {
    public:
        FlappyBirdClient(const ApplicationSpecification &spec);
        ~FlappyBirdClient();
    };
```

## GameLayer

We need now to create the `GameLayer` class that inherits from the `Layer` class.
The layer is a used to handle the game.

### GameState

We begin by creating the `GameState` that will be handles the diferent state of game:

```c++
enum class GameState { Play, Menu, GameOver };
```

### GameLayer() {id="gamelayer_1"}

We start by creating a constructor.

```c++
    GameLayer::GameLayer() : Layer("Flappy Bird"), _State(GameState::Menu), _Blink(false), _Time(0.0f) {
```

The constructor will call the `Random::Init` to initialize the random class.

```c++
        Random::Init();
```

Then he will load the project and initialize the player:

```c++
Ref<Exodia::Project> project = Exodia::Project::Load("./Assets/FlappyBird.proj");
project->RegisterScript("Player", []() -> Exodia::ScriptableEntity * { return new FlappyBird::Player; });
```

The `.proj` file is uses to store the project information like that:

```
Project:
  Name: FlappyBird
  AssetsDirectory: ""
  AssetRegistryPath: "AssetRegistry.asset"
```

### OnAttach()

The `OnAttach` method is call when the layer is attached to the application.

```c++
    void GameLayer::OnAttach()
```

It will only initialize the level.

```c++
        EXODIA_PROFILE_FUNCTION();
        _Level.Init();
```

### OnUpdate()

The function `OnUpdate` updates the game state, prepares the renderer, and updates the scene based on the current game state.

```c++
    void GameLayer::OnUpdate(Exodia::Timestep ts)
```

It takes the following parameter:

| Name | Type | Description |
|------|------|-------------|
| ts   | Exodia::Timestep | The ts      |


The `OnUpdate` function will start by clean the screen with the renderer

```c++
        {
            EXODIA_PROFILE_SCOPE("Renderer Prep");

            Renderer2D::ResetStats();
            RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
            RenderCommand::Clear();
        }
```

Then, we will update the game.

```c++
        {
            EXODIA_PROFILE_SCOPE("Game Update");

            _Time += ts;

            if ((int)(_Time * 10.0f) % 8 > 4)
                _Blink = !_Blink;
            if (_Level.IsGameOver())
                _State = GameState::GameOver;
        }
```

And finally, we will update the scene

```c++
        {
            EXODIA_PROFILE_SCOPE("Scene Update");

            switch (_State) {
            case GameState::Play:
                _Level.OnUpdate(ts);
                break;
            default:
                _Level.OnRender(ts);
                break;
            }
        }
```

### OnImGUIRender()

The function `OnImGUIRender()` is responsible for rendering the user interface elements in the game, including the score, menu, game over screen, and debug statistics.

```c++
    void GameLayer::OnImGUIRender()
```

What we need to render will depend on the game state.

If the game is in the menu, we will display the main menu with juste a `Click to play !` button.

```c++
        ImVec2 pos = ImGui::GetWindowPos();

        uint32_t width = Exodia::Application::Get().GetWindow().GetWidth();

        pos.x += width / 2.0f - 400.0f;
        pos.y += 100.0f;

        if (_Blink)
            ImGui::GetForegroundDrawList()->AddText(ImGui::GetFont(), 120.0f, pos, IM_COL32_WHITE,
                                                    "Click to play !");
```

If we are in game, it will display the score :

```c++
            std::string score = std::string("Score : " + std::to_string(_Level.GetScore()));

            ImGui::GetForegroundDrawList()->AddText(ImGui::GetFont(), 48.0f, ImGui::GetWindowPos(), IM_COL32_WHITE,
                                                    score.c_str());
```

If the game is over, it will display the game over screen with the score and a `Click to play again !` button.

```c++
            ImVec2 pos = ImGui::GetWindowPos();

            uint32_t width = Exodia::Application::Get().GetWindow().GetWidth();

            pos.x += width / 2.0f - 400.0f;
            pos.y += 100.0f;

            if (_Blink)
                ImGui::GetForegroundDrawList()->AddText(ImGui::GetFont(), 120.0f, pos, IM_COL32_WHITE,
                                                        "Click to play !");

            pos.x += 200.0f;
            pos.y += 150.0f;

            std::string score = std::string("Score : " + std::to_string(_Level.GetScore()));

            ImGui::GetForegroundDrawList()->AddText(ImGui::GetFont(), 120.0f, pos, IM_COL32_WHITE, score.c_str());
```

We can also add a debug part that will be call if we make using the debug mode.
This will add a window with the FPS, the frame time, the memory usage, the draw calls, the quad count, the vertex count and the index count.
```c++
#ifdef EXODIA_DEBUG
        ImGui::Begin("R-Type Statistics");
        ImGui::Text("FPS: %.1f", Application::Get().GetStatistics().FPS);
        ImGui::Text("Frame Time: %.3f ms", Application::Get().GetStatistics().FrameTime);
        ImGui::Text("Memory Usage: %ld KB", Application::Get().GetStatistics().MemoryUsage / 1024);
        ImGui::Separator();
        ImGui::Text("Renderer Statistics:");
        ImGui::Text("Draw Calls: %d", Renderer2D::GetStats().DrawCalls);
        ImGui::Text("Quad Count: %d", Renderer2D::GetStats().QuadCount);
        ImGui::Text("Vertex Count: %d", Renderer2D::GetStats().GetTotalVertexCount());
        ImGui::Text("Index Count: %d", Renderer2D::GetStats().GetTotalIndexCount());
        ImGui::Separator();
        ImGui::End();
#endif
```

### OnEvent()

The function `OnEvent` in the `GameLayer` class dispatches events to their corresponding event handlers.

```c++
    void GameLayer::OnEvent(Exodia::Event &event)
```

It takes the following parameter:

| Name  | Type | Description |
|-------|------|-------------|
| event | Exodia::Event& | The event    |

The `OnEvent` function will dispatch the event of `KeyPressedEvent` to handle the `Click to Play !` action and the event of `MouseButtonPressedEvent` to handle when the key space is pressed to jump.

```c++
        EventDispatcher dispatcher(event);

        dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(GameLayer::OnKeyPressedEvent));
        dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_EVENT_FN(GameLayer::OnMouseButtonPressedEvent));
```

### OnKeyPressedEvent()

The function `OnKeyPressedEvent` in the `GameLayer` class handles the `Click to Play !` action.

```c++
    bool GameLayer::OnKeyPressedEvent(KeyPressedEvent &event)
```

It takes the following parameter:

| Name  | Type | Description |
|-------|------|-------------|
| event | KeyPressedEvent& | The event    |

It will call the `OnKeyPressed` function of the level.

```c++
        _Level.OnKeyPressed(event.GetKeyCode());
```

It will always return true.

### OnMouseButtonPressedEvent()

The function `OnMouseButtonPressedEvent` in the `GameLayer` class handles the `Click to Play !` action.

```c++
    bool GameLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent &event)
```

It takes the following parameter:

| Name  | Type | Description |
|-------|------|-------------|
| event | MouseButtonPressedEvent& | The event    |

Then we will check if the game is over to reset it.

```c++
if (_State == GameState::GameOver)
            _Level.Reset();
```

Otherwise, we will set the status to play.

```c++
        _State = GameState::Play;
        _Level.Play();
```

It will always return true.

## Level

The `Level` class is uses to manage the game, it inherits from `EventSubscriber<Exodia::Events::OnEntityDestroyed>`.

### Level() {id="level_1"}

We start by creating the constructor

```c++
    Level::Level() : _Scene(nullptr), _GameOver(false), _EditorCamera(30.0f, 1.778f, 0.1f, 1000.0f){};
```

### OnUpdate() {id="onupdate_1"}

The function updates the game level by moving spikes and updating the score based on the position of the spaceship.

```c++
    void Level::OnUpdate(Exodia::Timestep ts)
```

The parameter `ts` in the above code represents the timestep, which is the amount of
time that has passed since the last update. It is used to update the game logic and perform
calculations based on the elapsed time.

It takes the following parameter:

| Name | Type | Description |
|------|------|-------------|
| ts   | Exodia::Timestep | The ts      |

In this code, nothing is being returned. The return statement is used to exit the
function early if certain conditions are met, but it does not return any value.

We start by checking if we have a scene and a ship.

```c++
        if (_Scene == nullptr)
            return;

        Exodia::GameObject ship = nullptr;
        ship = _Scene->GetEntityByName("SpaceShip");
        if (ship == nullptr)
            return;
```

Then, we update the score, because the obstacle is every 20 unit of distance, we can juste divide the position of the ship by 20 to get the score.

```c++
        score = (ship.GetComponent<TransformComponent>().Translation.x) / 20.0f;
```

Then, we update the spikes.

For each spike we verify that he exists and if it exists, we will check if he is outside the screen on the left.
That mean that the spike is no longer render, so we create a new spike on the right.

```c++
        auto spike_haut = _Scene->GetEntityByName("spike_haut");
        auto spike_bas = _Scene->GetEntityByName("spike_bas");

        if (spike_haut != nullptr && spike_bas != nullptr) {

            float rand = Random::Float() * 8.0f - 4.0f;
            float diff = 8.5f;
            glm::vec4 color = {Random::Float(), Random::Float(), Random::Float(), 1};

            auto &ts_h = spike_haut.GetComponent<TransformComponent>();

            if (ts_h.Translation.x <
                _Scene->GetEntityByName("SpaceShip").GetComponent<TransformComponent>().Translation.x - 15.0f) {
                ts_h.Translation.x += 40.0f;
                ts_h.Translation.y = rand + diff;
                auto &sp_h = spike_haut.GetComponent<SpriteRendererComponent>();
                sp_h.Color = color;
            }

            auto &ts_b = spike_bas.GetComponent<TransformComponent>();

            if (ts_b.Translation.x <
                _Scene->GetEntityByName("SpaceShip").GetComponent<TransformComponent>().Translation.x - 15.0f) {
                ts_b.Translation.x += 40.0f;
                ts_b.Translation.y = rand - diff - 3.0f;
                auto &sp_b = spike_bas.GetComponent<SpriteRendererComponent>();
                sp_b.Color = color;
            }
        }
```

Then we call the `OnUpdateRuntime` function of the scene.

```c++
        _Scene->OnUpdateRuntime(ts);
```

### OnRender() {id="onrender_1"}

The function `OnRender` updates the editor camera and calls the `OnUpdateEditor` function of the scene with the given timestep and editor camera.

```c++
    void Level::OnRender(Exodia::Timestep ts)
```

It takes the following parameter:

| Name | Type | Description |
|------|------|-------------|
| ts   | Exodia::Timestep | The ts      |

We start by updating the editor camera.

```c++
        _EditorCamera.OnUpdate(ts);
```

Then we call the `OnUpdateEditor` function of the scene.

```c++
        _Scene->OnUpdateEditor(ts, _EditorCamera);
```


### Reset() {id="reset_1"}

The Reset function resets the level by setting the _GameOver flag to false, stopping the runtime of the scene, destroying all entities, initializing the level, and starting the runtime of the scene again.

```c++
    void Level::Reset()
```

We start by setting the `_GameOver` flag to false.

```c++
        _GameOver = false;
```

Then we stop the runtime of the scene.

```c++
        _Scene->OnRuntimeStop();
```

Then we destroy all entities.

```c++
        _Scene->DestroyAllEntities();
```

Then we initialize the level.

```c++
        Init();
```

And finally we start the runtime of the scene.

```c++
        _Scene->OnRuntimeStart();
```

### Init() {id="init_1"}

The function initializes the level by loading prefabs, setting the position and color of spike entities, and resizing the viewport.

```c++
    void Level::Init()
```

We start by creating the scene.

```c++
_Scene = CreateRef<Scene>();
```

Then we load the prefabs.

```c++
        PrefabsImporter::LoadPrefabs("Assets/Prefabs/FlappyBird.prefab", _Scene);
        PrefabsImporter::LoadPrefabs("Assets/Prefabs/Camera.prefab", _Scene);
        PrefabsImporter::LoadPrefabs("Assets/Prefabs/obstacle.prefab", _Scene);
```


Then we create the spikes.

```c++
        auto spike_haut = _Scene->Instantiate("spike_haut");
        auto spike_bas = _Scene->Instantiate("spike_bas");
```

Then we set the position and color of the spikes.

```c++
        float rand = Random::Float() * 8.0f - 4.0f;
        float diff = 8.5f;
        glm::vec4 color = {Random::Float(), Random::Float(), Random::Float(), 1};

        auto &ts_h = spike_haut.GetComponent<TransformComponent>();
        ts_h.Translation.x = 10.0f;
        ts_h.Translation.y = rand + diff;
        auto &sp_h = spike_haut.GetComponent<SpriteRendererComponent>();
        sp_h.Color = color;

        auto &ts_b = spike_bas.GetComponent<TransformComponent>();
        ts_b.Translation.x = 10.0f;
        ts_b.Translation.y = rand - diff - 3.0f;
        auto &sp_b = spike_bas.GetComponent<SpriteRendererComponent>();
        sp_b.Color = color;
```

Then we resize the viewport.

```c++
        _Scene->OnViewportResize(Application::Get().GetWindow().GetWidth(), Application::Get().GetWindow().GetHeight());
```

### Play()

The Play function sets up and initializes various systems and event subscriptions for a game level.

```c++
    void Level::Play()
```

We start by verifying if the scene exist.

```c++
        if (_Scene == nullptr)
            return;
```

Then we register all systems.

```c++
        auto colision = new CollisionSystem();

        _Scene->RegisterSystem(new ParticleSystem());
        _Scene->RegisterSystem(new GravitySystem());
        _Scene->RegisterSystem(new MovingSystem());
        _Scene->RegisterSystem(colision);
```

Then we add subscribers to the scene.

```c++
        _Scene->AddSubscriber<Exodia::Events::OnCollisionEntered>(colision);
        _Scene->AddSubscriber<Exodia::Events::OnEntityDestroyed>(this);
```


Finally, we start the runtime of the scene.

```c++
        _Scene->OnRuntimeStart();
```

### OnKeyPressed() {id="onkeypressed_1"}

The function `OnKeyPressed` handles the `Space` key press event by applying an upward force to the spaceship.

```c++
    void Level::OnKeyPressed(int key)
```

It takes the following parameter:

| Name | Type | Description |
|------|------|-------------|
| key  | int  | The key      |

We start by verifying if the scene exist.

```c++
        if (_Scene == nullptr)
            return;
```

Then we call the `OnKeyPressedEvent` of the scene.

```c++
_Scene->OnKeyPressedEvent(key);
```

### IsGameOver() {id="isgameover_1"}

The function `IsGameOver` returns the value of the _GameOver flag.

```c++
    bool Level::IsGameOver()
```

It returns a bool.

### Recieve

The `void Receive(UNUSED(World *world), const Events::OnEntityDestroyed &event) override` function is an overridden function from the `EventSubscriber` class. It is used to handle the `OnEntityDestroyed` event.

```c++
    void Receive(UNUSED(World *world), const Events::OnEntityDestroyed &event) override
```

It takes the following parameter:

| Name  | Type | Description |
|-------|------|-------------|
| world | World* | The world    |
| event | const Events::OnEntityDestroyed& | The event    |

We will get the tag of the entity that as been destroyed.

```c++
            auto &tg = event.Entity->GetComponent<TagComponent>().Get();
```

Then, if the tag is `SpaceShip`, we will set the `_GameOver` flag to true.

```c++
            if (tg.Tag.find("SpaceShip") != std::string::npos)
                _GameOver = true;
```



## Player

The `Player` class is uses to manage the player, it inherits from `ScriptableEntity`.

### OnCreate() {id="oncreate_1"}

The function initializes the properties of the player's smoke and engine particles.

```c++
    void Player::OnCreate()
```

We start by initializing the time info.

```c++
        _Time = 0.0f;
        _EnginePower = 1.0f;
        _SmokeEmitInterval = 0.4f;
        _SmokeNextEmitTime = 0.4f;
```

Then we initialize the smoke particle.

```c++
        _SmokeParticle.Position = {0.0f, 0.0f};
        _SmokeParticle.Velocity = {-2.0f, 0.0f};
        _SmokeParticle.VelocityVariation = {4.0f, 2.0f};
        _SmokeParticle.SizeBegin = 0.35f;
        _SmokeParticle.SizeEnd = 0.0f;
        _SmokeParticle.SizeVariation = 0.15f;
        _SmokeParticle.ColorBegin = {0.8f, 0.8f, 0.8f, 1.0f};
        _SmokeParticle.ColorEnd = {0.6f, 0.6f, 0.6f, 1.0f};
        _SmokeParticle.LifeTime = 1.0f;
        _SmokeParticle.NumberOfParticles = 2;
```

Finally, we can initialize the engine particle.

```c++
        _EngineParticle.Position = {0.0f, 0.0f};
        _EngineParticle.Velocity = {-2.0f, 0.0f};
        _EngineParticle.VelocityVariation = {3.0f, 1.0f};
        _EngineParticle.SizeBegin = 0.5f;
        _EngineParticle.SizeEnd = 0.0f;
        _EngineParticle.SizeVariation = 0.3f;
        _EngineParticle.ColorBegin = {254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f};
        _EngineParticle.ColorEnd = {254 / 255.0f, 212 / 255.0f, 123 / 255.0f, 1.0f};
        _EngineParticle.LifeTime = 1.0f;
        _EngineParticle.NumberOfParticles = 10;
```

### OnUpdate() {id="onupdate_2"}

The function updates the player's position, emits smoke particles, rotates the player based on
velocity, and destroys the player if it goes out of bounds.

```c++
    void Player::OnUpdate(Exodia::Timestep ts)
```

We start by emit smoke particle at regular interval.

```c++
        if (_Time > _SmokeNextEmitTime) {
            _SmokeParticle.Position = {GetComponent<TransformComponent>().Translation.x,
                                       GetComponent<TransformComponent>().Translation.y};

            Emit(_SmokeParticle);

            _SmokeNextEmitTime += _SmokeEmitInterval;
        }
```

Then we apply a rotation effect to the spaceship.

```c++
        TransformComponent &tc = GetComponent<TransformComponent>();
        RigidBody2DComponent &rbc = GetComponent<RigidBody2DComponent>();

        tc.Rotation.z = rbc.Velocity.y * 0.1f;
```

Finally, we check if the player go out of screen to killed it.

```c++
        auto &pos = GetComponent<TransformComponent>().Translation;

        if (pos.y < -10.0f || pos.y > 10.0f)
            HandleEntity.GetScene()->DestroyEntity(HandleEntity);
```

### OnCollisionEnter() {id="oncollisionenter_1"}

The OnCollisionEnter function logs a collision with an entity and sets the player's "dead" flag
to true, then destroys the entity.

```c++
    void Player::OnCollisionEnter(Entity *other)
```

It takes the following parameter:

| Name  | Type    | Description        |
|-------|---------|--------------------|
| other | Entity* | The collide entity |

We start by set the player set the player's "dead" flag to true.

```c++
        _Dead = true;
```

Then we destroy the entity.

```c++
        HandleEntity.GetScene()->DestroyEntity(HandleEntity);
```

### OnKeyPressed() {id="onkeypressed_2"}

The function `OnKeyPressed` increases the velocity of the player's rigid body and emits engine
particles when the space key is pressed.

```c++
    void Player::OnKeyPressed(int keycode)
```

We check if the key pressed is space.

```c++
if (keycode != Key::SPACE)
    return;
```

Then we move the player.

```c++
            RigidBody2DComponent &rbc = GetComponent<RigidBody2DComponent>();
            TransformComponent &tc = GetComponent<TransformComponent>();

            rbc.Velocity.y += _EnginePower;

            if (rbc.Velocity.y > 0.0f)
                rbc.Velocity.y += _EnginePower * 2.0f;

```

Then we emit the engine particle.

```c++
            glm::vec2 emissionPoint = {0.0f, -0.6f};
            float rotation = glm::radians(tc.Rotation.z);
            glm::vec2 rotated =
                glm::rotate(glm::mat4(1.0f), rotation, {0.0f, 0.0f, 1.0f}) * glm::vec4(emissionPoint, 0.0f, 1.0f);

            _EngineParticle.Position = glm::vec2(tc.Translation.x, tc.Translation.y) + glm::vec2(rotated.x, rotated.y);
            _EngineParticle.Velocity.y = -rbc.Velocity.y * 0.2f - 0.2f;

            Emit(_EngineParticle);
```

### Emit() {id="emit_1"}

The function emits a specified number of particles with various properties such as position, rotation, size, color, lifetime, velocity, and gravity.
The "props" parameter is of type "ParticleProps", which is a user-defined struct or
class that contains properties for creating particles. It likely includes information such as
the number of particles to create, the position of the particles, their size, color, lifetime,
velocity, and other relevant attributes.

```c++
    void Player::Emit(const ParticleProps &props)
```

We will create new entities for each particle.

```c++
        for (int i = 0; i < props.NumberOfParticles; i++) {
            GameObject particle = HandleEntity.GetScene()->CreateNewEntity("Particle #" + std::to_string(i));
```

Then we apply the movement using the `TransformComponent`.

```c++
            TransformComponent &tc = particle.GetComponent<TransformComponent>();

            tc.Translation.x = props.Position.x;
            tc.Translation.y = props.Position.y;
            tc.Rotation.z = Random::Float();
            tc.Scale = glm::vec3(props.SizeBegin + props.SizeVariation * (Random::Float() - 0.5f));
```

Then we apply the color using the `SpriteRendererComponent`.

```c++
            SpriteRendererComponent &src = particle.AddComponent<SpriteRendererComponent>();

            src.Color = props.ColorBegin;
```

We can now apply the particle information with the `ParticleComponent`.

```c++
            ParticleComponent &pc = particle.AddComponent<ParticleComponent>();

            pc.LifeTime = props.LifeTime;
            pc.LifeRemaining = props.LifeTime;
            pc.ColorBegin = props.ColorBegin;
            pc.ColorEnd = props.ColorEnd;
            pc.SizeBegin = props.SizeBegin + props.SizeVariation * (Random::Float() - 0.5f);
            pc.SizeEnd = props.SizeEnd;
```

Finally, we apply the velocity with the `RigidBody2DComponent`.

```c++
            RigidBody2DComponent &rbc = particle.AddComponent<RigidBody2DComponent>();

            rbc.Type = RigidBody2DComponent::BodyType::Dynamic;
            rbc.Velocity = props.Velocity;
            rbc.Velocity.x += props.VelocityVariation.x * (Random::Float() - 0.5f);
            rbc.Velocity.y += props.VelocityVariation.y * (Random::Float() - 0.5f);
            rbc.GravityScale = 0.0f;
            rbc.Mass = 0.0f;
```

## Particles

The `ParticleSystem` class is uses to manage the particles.

### Particle

The `Particle` struct is uses to manage the particles.

```c++
    struct Particle {
        glm::vec2 Position;
        glm::vec2 Velocity;
        glm::vec4 ColorBegin;
        glm::vec4 ColorEnd;
        float Rotation = 0.0f;
        float SizeBegin;
        float SizeEnd;
        float LifeTime = 1.0f;
        float LifeRemaining = 0.0f;
        bool Active = false;
    };
```

### ParticleSystem() {id="particlesystem_1"}

The above function is a constructor for the ParticlesSystem class that initializes the _ParticleListIndex to 999 and resizes the _ParticleList vector to 1000.

```c++
    ParticleSystem::ParticleSystem() : _ParticleListIndex(999) { _ParticleList.resize(1000); }
```

### Emit() {id="emit_2"}

The function emits a particle with specified properties and updates the particle list index.

```c++
    void ParticleSystem::Emit(const ParticleProps &props)
```

It takes the following parameter:

| Name  | Type | Description |
|-------|------|-------------|
| props | const ParticleProps& | The props    |

We start by getting the particle.

```c++
        Particle &particle = _ParticleList[_ParticleListIndex];
```

Then we inactivate it.

```c++
particle.Active = true;
```

We set the position of the particle.

```c++
        particle.Position = props.Position;
```

We set the rotation of the particle.

```c++
        particle.Rotation = Random::Float() * 2.0f * glm::pi<float>();
```

We set the velocity of the particle.

```c++
        particle.Velocity = props.Velocity;
        particle.Velocity.x += props.VelocityVariation.x * (Random::Float() - 0.5f);
        particle.Velocity.y += props.VelocityVariation.y * (Random::Float() - 0.5f);
```

We set the color of the particle.

```c++
        particle.ColorBegin = props.ColorBegin;
        particle.ColorEnd = props.ColorEnd;
```

We set the size of the particle.

```c++
        particle.SizeBegin = props.SizeBegin + props.SizeVariation * (Random::Float() - 0.5f);
        particle.SizeEnd = props.SizeEnd;
```

We set the lifetime of the particle.

```c++
        particle.LifeTime = props.LifeTime;
        particle.LifeRemaining = props.LifeTime;
```

Finally, we update the particle list index.

```c++
        _ParticleListIndex--;
        _ParticleListIndex = _ParticleListIndex % _ParticleList.size();
```

### OnUpdate() {id="onupdate_3"}

The function updates the position, rotation, and remaining life of each active particle in a particle system.

```c++
    void ParticleSystem::OnUpdate(Exodia::Timestep ts)
```

It takes the following parameter:

| Name | Type | Description |
|------|------|-------------|
| ts   | Exodia::Timestep | The ts      |

We start by iterating over the particle list.

```c++
        for (auto &particle : _ParticleList) {
```

Then we check if the particle is active.

```c++
            if (!particle.Active)
                continue;
```

We can now check if the particle should be dead.

```c++
            if (particle.LifeRemaining <= 0.0f) {
                particle.Active = false;
                continue;
            }
```

Finally, we update the information about the particle.

```c++
            particle.LifeRemaining -= ts;
            particle.Position += particle.Velocity * (float)ts;
            particle.Rotation += 0.01f * ts;
```

### OnRender() {id="onrender_2"}

The function iterates through a list of particles and renders them with their respective
position, size, rotation, and color.

```c++
    void ParticleSystem::OnRender()
```

We start by iterating over the particle list.

```c++
        for (auto &particle : _ParticleList) {
```

Then we check if the particle is active.

```c++
            if (!particle.Active)
                continue;
```

We can now create a color depending on its life.

```c++
            float life = particle.LifeRemaining / particle.LifeTime;

            glm::vec4 color = glm::lerp(particle.ColorEnd, particle.ColorBegin, life);

            color.a = color.a * life;
```

And same for the size.

```c++
            float size = glm::lerp(particle.SizeEnd, particle.SizeBegin, life);
```

Finally, we render the particle.

```c++
            Exodia::Renderer2D::DrawRotatedQuad(particle.Position, // Position
                                                {size, size},      // Size
                                                particle.Rotation, // Rotation
                                                color              // Color
            );
```

## Prefabs

Now that we have our game we will see how to create entities.

We will use for that prefabs.

### Camera

The camera prefab is uses to create a camera.

```
Prefab: Camera
TransformComponent:
    Translation: [0, 0, 0]
    Rotation: [0, 0, 0]
    Scale: [1, 1, 1]
Entities:
  - Entity: 85202154120512
    TagComponent:
      Tag: PlayerCamera
    TransformComponent:
      Translation: [0, 0, 15]
      Rotation: [0, 0, 0]
      Scale: [1, 1, 1]
    CameraComponent:
      Camera:
        ProjectionType: 0
        PerspectiveFOV: 45
        PerspectiveNear: 0.01
        PerspectiveFar: 1000
        OrthographicSize: 10
        OrthographicNear: -1
        OrthographicFar: 1
      Primary: true
      FixedAspectRatio: true
    RigidBody2DComponent:
      BodyType: Dynamic
      Velocity: [5, 0]
      GravityScale: 0
      Mass: 0
```

### Obstacle

Obsctacle prefab is uses to create the spikes.

```
Prefab: Obstacle
TransformComponent:
    Translation: [0, 0, 0]
    Rotation: [0, 0, 0]
    Scale: [1, 1, 1]
Entities:
  - Entity: 87451251542121
    TagComponent:
      Tag: spike_bas
    TransformComponent:
      Translation: [20, -8, 0]
      Rotation: [0, 0, 0]
      Scale: [5, 15, 15]
    RigidBody2DComponent:
      BodyType: Dynamic
      Velocity: [0, 0]
      GravityScale: 0.0
      Mass: 0.0
    SpriteRendererComponent:
      Color: [1, 1, 1, 1]
      TilingFactor: 1
      Texture:
        AssetHandle: 45120015123131
        Coords: [0, 0]
        CellSize: [1, 1]
        SpriteSize: [225, 450]
    BoxCollider2DComponent:
      Offset: [0, 0]
      Size: [0.5, 0.5]
      Mask: 0xFFFFFFFF
  - Entity: 87451251542122
    TagComponent:
      Tag: spike_haut
    TransformComponent:
      Translation: [20, 8, 0]
      Rotation: [0, 0, 0]
      Scale: [5, 15, 15]
    RigidBody2DComponent:
      BodyType: Dynamic
      Velocity: [0, 0]
      GravityScale: 0.0
      Mass: 0.0
    SpriteRendererComponent:
      Color: [1, 1, 1, 1]
      TilingFactor: 1
      Texture:
        AssetHandle: 45120015123131
        Coords: [0, 0]
        CellSize: [1, 1]
        SpriteSize: [225, 450]
    BoxCollider2DComponent:
      Offset: [0, 0]
      Size: [0.5, 0.5]
      Mask: 0xFFFFFFFF
```

### Player {id="player_1"}

Player prefab is uses to create the player.

```
Prefab: Player
TransformComponent:
    Translation: [0, 0, 0]
    Rotation: [0, 0, 0]
    Scale: [1, 1, 1]
Entities:
  - Entity: 87451251541121
    TagComponent:
      Tag: SpaceShip
    TransformComponent:
      Translation: [-5, 0, 0]
      Rotation: [0, 0, 0]
      Scale: [1, 1, 1]
    ScriptComponent:
      Name: Player
    BoxCollider2DComponent:
      Offset: [0, 0]
      Size: [0.5, 0.5]
      Mask: 0xFFFFFFFF
    RigidBody2DComponent:
      BodyType: Dynamic
      Velocity: [5, 0]
      GravityScale: 0.4
      Mass: 0.4
    SpriteRendererComponent:
      Color: [1, 1, 1, 1]
      TilingFactor: 1
      Texture:
        AssetHandle: 14815285158415
        Coords: [0, 0]
        CellSize: [1, 1]
        SpriteSize: [10, 13]
```
