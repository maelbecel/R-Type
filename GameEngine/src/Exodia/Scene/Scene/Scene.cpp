/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Scene
*/

// Exodia Scene includes
#include "Scene.hpp"

// Exodia ECS includes
#include "Scene/Components/Components.hpp"
#include "ECS/Interface/IComponentContainer.hpp"

// Exodia Renderer includes
#include "Renderer/Renderer/Renderer2D.hpp"
#include "Renderer/Renderer/RendererAPI.hpp"
#include "Renderer/Renderer/Renderer.hpp"

namespace Exodia {

    //////////////////////////////
    // Constructor & Destructor //
    //////////////////////////////

    Scene::Scene(const std::string &name)
        : _Name(name), _ViewportWidth(0), _ViewportHeight(0), _IsRunning(false), _IsPaused(false) {
        _World = World::CreateWorld();
    }

    Scene::~Scene() { _World->DestroyWorld(); }

    /////////////
    // Methods //
    /////////////

    Ref<Scene> Scene::Copy(Ref<Scene> other) {
        if (other == nullptr)
            return nullptr;
        Ref<Scene> copyScene = CreateRef<Scene>(other->GetName());

        copyScene->_ViewportWidth = other->_ViewportWidth;
        copyScene->_ViewportHeight = other->_ViewportHeight;

        auto &srcWorld = other->GetWorld();
        auto &dstWorld = copyScene->GetWorld();

        srcWorld.ForEach<IDComponent, TagComponent>([&](Entity *entity, auto id, auto tag) {
            const UUID &uuid = id.Get().ID;
            const std::string &name = tag.Get().Tag;

            Entity *newEntity = entity->Duplicate(&dstWorld, uuid, name);

            copyScene->_EntityMap[uuid] = newEntity;
        });

        return copyScene;
    }

    GameObject Scene::CreateEntity(const std::string &name) { return CreateEntityWithUUID(UUID(), name); }

    GameObject Scene::CreateEntityWithUUID(UUID uuid, const std::string &name) {
        Entity *entity = _World->CreateEntity(uuid, name);

        entity->AddComponent<IDComponent>(uuid);
        entity->AddComponent<TransformComponent>();

        auto &tag = entity->AddComponent<TagComponent>().Get();

        tag.Tag = name.empty() ? "Entity" : name;

        _EntityMap[uuid] = entity;

        return GameObject(entity, this);
    }

    GameObject Scene::CreateNewEntity(const std::string &name) { return CreateNewEntityWithUUID(UUID(), name); }

    GameObject Scene::CreateNewEntityWithUUID(UUID uuid, const std::string &name) {
        Entity *entity = _World->CreateNewEntity(uuid, name);

        entity->AddComponent<IDComponent>(uuid);
        entity->AddComponent<TransformComponent>();

        auto &tag = entity->AddComponent<TagComponent>().Get();

        tag.Tag = name.empty() ? "Entity" : name;

        _EntityMap[uuid] = entity;

        return GameObject(entity, this);
    }

    GameObject Scene::DuplicateEntity(GameObject gameObject) {
        GameObject newGameObject = CreateEntity(gameObject.GetName());
        Entity *entity = gameObject.GetEntity();
        Entity *newEntity = newGameObject.GetEntity();

        for (IComponentContainer *component : entity->GetAllComponents()) {
            std::string name = component->GetTypeIndexOfComponent().name();
            std::string typeIndex = extractTypeName(name.c_str());

            newEntity->SetComponent(typeIndex, component);
        }

        return newGameObject;
    }

    void Scene::DestroyEntity(GameObject gameObject) {
        Entity *entity = gameObject.GetEntity();

        _World->DestroyEntity(entity);
    }

    void Scene::OnRuntimeStart() {
        if (_IsRunning)
            OnRuntimeStop();

        _IsRunning = true;

        for (auto &system : _Systems)
            _World->RegisterSystem(system);

        _World->LockMutex();
        _World->ForEach<CameraComponent>([&](Entity *entity, auto camera) {
            auto &cc = camera.Get();

            if (_ViewportWidth > 0 && _ViewportHeight > 0)
                cc.Camera.SetViewportSize(_ViewportWidth, _ViewportHeight);
        });
        _World->UnlockMutex();

        _World->LockMutex();
        _World->ForEach<ScriptComponent>([&](Entity *entity, auto script) {
            auto &sc = script.Get();

            if (sc.Instance == nullptr && !sc.Name.empty() && sc.InstantiateScript) {
                sc.Instance = sc.InstantiateScript(sc.Name);

                if (sc.Instance != nullptr) {
                    sc.Instance->HandleEntity = GameObject(entity, this);
                    sc.Instance->OnCreate();
                }
            }
        });
        _World->UnlockMutex();

        if (Renderer::GetAPI() == RendererAPI::API::None)
            return;

        _World->LockMutex();
        _World->ForEach<MusicComponent>([&](Entity *entity, ComponentHandle<MusicComponent> music) {
            MusicComponent &sc = music.Get();
            Ref<Sound2D> sound = AssetManager::GetAsset<Sound2D>(sc.Handle);

            if (sound == nullptr)
                return;
            if (sc.Play) {
                sound->SetVolume(sc.Volume);
                sound->SetLoop(true);

                Renderer2D::PlaySound(sc.Handle);
            }
        });
        _World->UnlockMutex();
    }

    void Scene::OnRuntimeStop() {
        if (!_IsRunning)
            return;

        _IsRunning = false;

        for (auto &system : _Systems)
            _World->UnregisterSystem(system);

        _World->ForEach<ScriptComponent>([&](Entity *entity, auto script) {
            auto &sc = script.Get();

            if (sc.Instance && !sc.Name.empty() && sc.DestroyScript) {
                sc.Instance->OnDestroy();
                sc.DestroyScript(&sc);
            }
        });

        if (Renderer::GetAPI() == RendererAPI::API::None)
            return;

        _World->ForEach<MusicComponent>([&](Entity *entity, auto music) {
            auto &sc = music.Get();

            Ref<Sound2D> sound = AssetManager::GetAsset<Sound2D>(sc.Handle);

            if (sound == nullptr)
                return;
            if (sc.Play)
                sound->Pause();
        });
    }

    void Scene::OnUpdateRuntime(Timestep ts) {
        if (!_IsRunning || !_IsPaused) {

            // -- Update the Scripts -- //
            _World->LockMutex();
            _World->ForEach<ScriptComponent>([&](Entity *entity, auto script) {
                auto &sc = script.Get();

                if (!sc.Instance && !sc.Name.empty() && sc.InstantiateScript) {
                    sc.Instance = sc.InstantiateScript(sc.Name);

                    if (sc.Instance != nullptr) {
                        sc.Instance->HandleEntity = entity;
                        sc.Instance->OnCreate();
                    }
                }

                if (sc.Instance)
                    sc.Instance->OnUpdate(ts);
            });
            _World->UnlockMutex();

            // -- Update the world -- //
            _World->Update(ts);

            // -- Get the main camera -- //
            Camera *mainCamera = nullptr;
            glm::mat4 cameraTransform;

            _World->LockMutex();
            _World->ForEach<TransformComponent, CameraComponent>([&](Entity *entity, auto transform, auto camera) {
                auto &cc = camera.Get();
                auto &tc = transform.Get();

                if (cc.Primary) {
                    mainCamera = &cc.Camera;
                    cameraTransform = tc.GetTransform();
                    return;
                }
            });
            _World->UnlockMutex();

            // -- Update and draw -- //
            if (mainCamera) {
                Renderer2D::BeginScene(*mainCamera, cameraTransform);

                RenderScene();

                Renderer2D::EndScene();
            }
        }
    }

    void Scene::OnUpdateEditor(UNUSED(Timestep ts), EditorCamera &camera) {
        Renderer2D::BeginScene(camera);

        RenderScene();

        Renderer2D::EndScene();
    }

    void Scene::OnViewportResize(uint32_t width, uint32_t height) {
        if (_ViewportWidth == width && _ViewportHeight == height)
            return;
        _ViewportWidth = width;
        _ViewportHeight = height;

        _World->ForEach<CameraComponent>([&](Entity *entity, auto camera) {
            auto &cc = camera.Get();

            if (!cc.FixedAspectRatio) {
                cc.Camera.SetViewportSize(width, height);
            }
        });
    }

    void Scene::RegisterSystem(EntitySystem *system) {
        if (_IsRunning)
            _World->RegisterSystem(system);
        else
            _Systems.push_back(system);
    }

    void Scene::RenderScene() {
        if (RendererAPI::GetAPI() == RendererAPI::API::None)
            return;

        _World->LockMutex();
        _World->ForEach<TransformComponent, SpriteRendererComponent, IDComponent>(
            [&](Entity *entity, auto transform, auto sprite, auto id) {
                auto &tc = transform.Get();
                auto &sc = sprite.Get();
                auto &ic = id.Get();

                Renderer2D::DrawSprite(tc.GetTransform(), sc, (int)ic.ID);
            });
        _World->UnlockMutex();

        _World->LockMutex();
        _World->ForEach<TransformComponent, CircleRendererComponent, IDComponent>(
            [&](Entity *entity, auto transform, auto circle, auto id) {
                auto &tc = transform.Get();
                auto &cc = circle.Get();
                auto &ic = id.Get();

                Renderer2D::DrawCircle(tc.GetTransform(), cc.Color, cc.Thickness, cc.Fade, (int)ic.ID);
            });
        _World->UnlockMutex();

        _World->LockMutex();
        _World->ForEach<TransformComponent, TextRendererComponent, IDComponent>(
            [&](Entity *entity, auto transform, auto text, auto id) {
                auto &tc = transform.Get();
                auto &txtc = text.Get();
                auto &ic = id.Get();

                Renderer2D::DrawText(tc.GetTransform(), txtc.Text, txtc, (int)ic.ID);
            });
        _World->UnlockMutex();

        _World->LockMutex();
        _World->ForEach<SoundComponent>([&](Entity *entity, auto sound) {
            auto &sc = sound.Get();

            Ref<Sound2D> soundRef = AssetManager::GetAsset<Sound2D>(sc.Handle);

            if (soundRef == nullptr)
                return;
            if (sc.Play && !soundRef->IsPlaying()) {
                soundRef->SetVolume(sc.Volume);
                soundRef->SetLoop(false);

                Renderer2D::PlaySound(sc.Handle);
            }
        });
        _World->UnlockMutex();
    }

    ///////////////////////
    // Getters & Setters //
    ///////////////////////

    const std::string &Scene::GetName() const { return _Name; }

    void Scene::SetName(const std::string &name) { _Name = name; }

    World &Scene::GetWorld() const { return *_World; }

    World *Scene::GetWorldPtr() { return _World; }

    GameObject Scene::GetPrimaryCamera() {
        Entity *primaryCamera = nullptr;

        _World->ForEach<CameraComponent>([&](Entity *entity, auto camera) {
            auto &cc = camera.Get();

            if (cc.Primary)
                primaryCamera = entity;
        });

        return GameObject(primaryCamera, this);
    }

    GameObject Scene::GetEntityByName(const std::string &name) {
        Entity *entity = nullptr;

        _World->ForEach<TagComponent>([&](Entity *entt, auto tag) {
            auto &tc = tag.Get();

            if (tc.Tag == name)
                entity = entt;
        });

        return GameObject(entity, this);
    }

    GameObject Scene::GetEntityByUUID(UUID uuid) {
        Entity *entity = nullptr;

        _World->ForEach<IDComponent>([&](Entity *entt, auto id) {
            auto &ic = id.Get();

            if (ic.ID == uuid) {
                entity = entt;
                return;
            }
        });

        return GameObject(entity, this);
    }

    bool Scene::IsRunning() const { return _IsRunning; }

    bool Scene::IsPaused() const { return _IsPaused; }

    void Scene::SetPaused(bool paused) { _IsPaused = paused; }

    AssetType Scene::GetType() const { return AssetType::Scene; }
}; // namespace Exodia
