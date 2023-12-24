/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Scene
*/

// Exodia Scene includes
#include "Scene.hpp"

// Exodia ECS includes
#include "ECS/Component/Components.hpp"

// Exodia Renderer includes
#include "Renderer/Renderer/Renderer2D.hpp"
#include "Renderer/Renderer/RendererAPI.hpp"

namespace Exodia {

    //////////////////////////////
    // Constructor & Destructor //
    //////////////////////////////

    Scene::Scene(const std::string &name) : _Name(name), _ViewportWidth(0), _ViewportHeight(0), _IsRunning(false), _IsPaused(false)
    {
        _World = World::CreateWorld();
    }

    Scene::~Scene()
    {
        _World->DestroyWorld();
    }

    /////////////
    // Methods //
    /////////////

    Ref<Scene> Scene::Copy(Ref<Scene> other)
    {
        if (other == nullptr)
            return nullptr;

        Ref<Scene> copyScene = CreateRef<Scene>(other->GetName());

        copyScene->_ViewportWidth  = other->_ViewportWidth;
        copyScene->_ViewportHeight = other->_ViewportHeight;

        auto &srcWorld = other->GetWorld();
        auto &dstWorld = copyScene->GetWorld();

        srcWorld.ForEach<IDComponent, TagComponent>([&](Entity *entity, auto id, auto tag) {
            UUID uuid = id.Get().ID;
            const std::string &name = tag.Get().Tag;

            entity->Duplicate(&dstWorld, uuid, name);
        });

        return copyScene;
    }

    Entity *Scene::CreateEntity(const std::string &name)
    {
        return _World->CreateEntity(name);
    }

    Entity *Scene::CreateEntityWithUUID(UUID uuid, const std::string &name)
    {
        return _World->CreateEntity(uuid, name);
    }

    Entity *Scene::DuplicateEntity(Entity *entity)
    {
        std::string name = entity->GetComponent<TagComponent>().Get().Tag;

        return entity->Duplicate(_World, UUID(), name);
    }

    void Scene::DestroyEntity(Entity *entity)
    {
        _World->DestroyEntity(entity);
    }

    void Scene::OnRuntimeStart()
    {
        if (_IsRunning)
            OnRuntimeStop();

        _IsRunning = true;

        for (auto &system : _Systems)
            _World->RegisterSystem(system);

        _World->ForEach<CameraComponent>([&](Entity *entity, auto camera) {
            auto &cc = camera.Get();

            if (_ViewportWidth > 0 && _ViewportHeight > 0)
                cc.Camera.SetViewportSize(_ViewportWidth, _ViewportHeight);
        });

        _World->ForEach<ScriptComponent>([&](Entity *entity, auto script) {
            auto &sc = script.Get();

            if (sc.Instance == nullptr && !sc.Name.empty() && sc.InstantiateScript) {
                sc.Instance = sc.InstantiateScript(sc.Name);

                if (sc.Instance != nullptr) {
                    sc.Instance->HandleEntity = entity;
                    sc.Instance->OnCreate();
                }
            }
        });
    }

    void Scene::OnRuntimeStop()
    {
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
    }

    void Scene::OnUpdateRuntime(Timestep ts)
    {
        if (!_IsPaused) {

            // -- Update the Scripts -- //
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

            // -- Update the world -- //
            _World->Update(ts);

            // -- Get the main camera -- //
            Camera *mainCamera = nullptr;
            glm::mat4 cameraTransform;

            _World->ForEach<TransformComponent, CameraComponent>([&](Entity *entity, auto transform, auto camera) {
                auto &cc = camera.Get();
                auto &tc = transform.Get();

                if (cc.Primary) {
                    mainCamera = &cc.Camera;
                    cameraTransform = tc.GetTransform();
                    return;
                }
            });

            // -- Update and draw -- //
            if (mainCamera) {
                Renderer2D::BeginScene(*mainCamera, cameraTransform);

                RenderScene();

                Renderer2D::EndScene();
            }
        }
    }

    void Scene::OnUpdateEditor(UNUSED(Timestep ts), EditorCamera &camera)
    {
        Renderer2D::BeginScene(camera);

        RenderScene();

        Renderer2D::EndScene();
    }

    void Scene::OnViewportResize(uint32_t width, uint32_t height)
    {
        if (_ViewportWidth == width && _ViewportHeight == height)
            return;
        _ViewportWidth  = width;
        _ViewportHeight = height;

        _World->ForEach<CameraComponent>([&](Entity *entity, auto camera) {
            auto &cc = camera.Get();

            if (!cc.FixedAspectRatio) {
                cc.Camera.SetViewportSize(width, height);
            }
        });
    }

    void Scene::RegisterSystem(EntitySystem *system)
    {
        if (_IsRunning)
            _World->RegisterSystem(system);
        else
            _Systems.push_back(system);
    }

    void Scene::RenderScene()
    {
        if (RendererAPI::GetAPI() == RendererAPI::API::None)
            return;

        _World->LockMutex();
        _World->ForEach<TransformComponent, SpriteRendererComponent, IDComponent>([&](Entity *entity, auto transform, auto sprite, auto id) {
            auto &tc = transform.Get();
            auto &sc = sprite.Get();
            auto &ic = id.Get();

            Renderer2D::DrawSprite(tc.GetTransform(), sc, (int)ic.ID);
        });
        _World->UnlockMutex();

        /*_World->ForEach<TransformComponent, CircleRendererComponent, IDComponent>([&](Entity *entity, auto transform, auto circle, auto id) {
            auto &tc = transform.Get();
            auto &cc = circle.Get();
            auto &ic = id.Get();

            Renderer2D::DrawCircle(tc.GetTransform(), cc.Color, cc.Thickness, cc.Fade, (int)ic.ID);
        });*/

        // TODO: When text rendering will be implemented (in Renderer2D);
    }

    ///////////////////////
    // Getters & Setters //
    ///////////////////////

    const std::string &Scene::GetName() const
    {
        return _Name;
    }

    void Scene::SetName(const std::string &name)
    {
        _Name = name;
    }

    World &Scene::GetWorld() const
    {
        return *_World;
    }

    World *Scene::GetWorldPtr()
    {
        return _World;
    }

    Entity *Scene::GetPrimaryCamera()
    {
        Entity *primaryCamera = nullptr;

        _World->ForEach<CameraComponent>([&](Entity *entity, auto camera) {
            auto &cc = camera.Get();

            if (cc.Primary) {
                primaryCamera = entity;
                return;
            }
        });

        return primaryCamera;
    }

    Entity *Scene::GetEntityByName(const std::string &name)
    {
        Entity *entity = nullptr;

        _World->ForEach<TagComponent>([&](Entity *entt, auto tag) {
            auto &tc = tag.Get();

            if (tc.Tag == name) {
                entity = entt;
                return;
            }
        });

        return entity;
    }

    Entity *Scene::GetEntityByUUID(UUID uuid)
    {
        Entity *entity = nullptr;

        _World->ForEach<IDComponent>([&](Entity *entt, auto id) {
            auto &ic = id.Get();

            if (ic.ID == uuid) {
                entity = entt;
                return;
            }
        });

        return entity;
    }

    bool Scene::IsRunning() const
    {
        return _IsRunning;
    }

    bool Scene::IsPaused() const
    {
        return _IsPaused;
    }

    void Scene::SetPaused(bool paused)
    {
        _IsPaused = paused;
    }

    AssetType Scene::GetType() const
    {
        return AssetType::Scene;
    }
};
