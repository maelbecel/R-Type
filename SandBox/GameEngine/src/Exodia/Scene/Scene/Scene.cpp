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

        for (auto &system : other->_Systems)
            copyScene->RegisterSystem(system.second);
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

    GameObject Scene::LoadPrefabs(const std::string &path, bool newPrefab) {
        /*if (_Prefabs.find(path) != _Prefabs.end())
            return _Prefabs[path].Duplicate(newPrefab);
        else {*/
        try {
            YAML::Node data = YAML::LoadFile(path);

            GameObject prefab = DeserializePrefab(data, newPrefab);

            //_Prefabs[path] = prefab;

            return prefab;
        } catch (const YAML::BadConversion &e) {
            EXODIA_CORE_ERROR("Failed to deserialize scene file '{0}':\n\t{1}", path, e.what());
        } catch (const YAML::Exception &e) {
            EXODIA_CORE_ERROR("Failed to deserialize scene file '{0}':\n\t{1}", path, e.what());
        }
        //}
        return {nullptr, this};
    }

    GameObject Scene::DeserializePrefab(YAML::Node &node, bool newPrefab) {
        GameObject newGameObject{nullptr, this};
        int i = 0;

        try {
            if (node["Entities"]) {
                auto entities = node["Entities"];

                for (YAML::detail::iterator_value entity : entities) {
                    if (i != 0)
                        break;
                    if (newPrefab)
                        newGameObject = CreateNewEntityWithUUID(UUID());
                    else
                        newGameObject = CreateEntityWithUUID(UUID());

                    for (YAML::detail::iterator_value component : entity) {
                        std::string componentType = component.first.as<std::string>();

                        if (componentType == "Entity" || componentType == "IDComponent" ||
                            componentType == "ParentComponent")
                            continue;
                        if (componentType == "ChildrenComponent") {
                            auto children = component.second["Children"];

                            for (auto child : children) {
                                auto &cc = newGameObject.AddComponent<ChildrenComponent>();

                                GameObject childObject = cc.AddChild(child, this);

                                childObject.GetComponent<ParentComponent>().Parent =
                                    newGameObject.GetComponent<IDComponent>().ID;
                            }
                            continue;
                        }

                        SceneSerializer::DeserializeComponent(componentType, entity, newGameObject);
                    }
                    i++;
                }
                return newGameObject;
            }
        } catch (const YAML::BadConversion &e) {
            EXODIA_CORE_ERROR("Failed to deserialize prefab file prefabs:\n\t{0}", e.what());
        } catch (const YAML::Exception &e) {
            EXODIA_CORE_ERROR("Failed to deserialize prefab file prefabs:\n\t{0}", e.what());
        }
        return newGameObject;
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

    void Scene::DestroyAllEntities() {
        _World->ForEach<IDComponent>([&](Entity *entity, auto id) {
            _World->DestroyEntity(entity);

            (void)id;
        });
    }

    void Scene::OnRuntimeStart() {
        if (_IsRunning)
            OnRuntimeStop();

        _IsRunning = true;

        for (auto &system : _Systems)
            _World->RegisterSystem(system.second);

        _World->AsyncForEach<CameraComponent>([&](Entity *entity, auto camera) {
            auto &cc = camera.Get();

            if (_ViewportWidth > 0 && _ViewportHeight > 0)
                cc.Camera.SetViewportSize(_ViewportWidth, _ViewportHeight);
        });

        _World->AsyncForEach<ScriptComponent>([&](Entity *entity, auto script) {
            auto &sc = script.Get();

            if (sc.Instance == nullptr && !sc.Name.empty() && sc.InstantiateScript) {
                sc.Instance = sc.InstantiateScript(sc.Name);

                if (sc.Instance != nullptr) {
                    sc.Instance->HandleEntity = GameObject(entity, this);
                    sc.Instance->OnCreate();
                }
            }
        });

        if (Renderer::GetAPI() == RendererAPI::API::None)
            return;

        _World->AsyncForEach<MusicComponent>([&](Entity *entity, ComponentHandle<MusicComponent> music) {
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
    }

    void Scene::OnRuntimeStop() {
        if (!_IsRunning)
            return;

        _IsRunning = false;

        for (auto &system : _Systems)
            _World->UnregisterSystem(system.second);

        _World->AsyncForEach<ScriptComponent>([&](Entity *entity, auto script) {
            auto &sc = script.Get();

            if (sc.Instance && !sc.Name.empty() && sc.DestroyScript) {
                sc.Instance->OnDestroy();
                sc.DestroyScript(&sc);
            }
        });

        if (Renderer::GetAPI() == RendererAPI::API::None)
            return;

        _World->AsyncForEach<MusicComponent>([&](Entity *entity, auto music) {
            auto &sc = music.Get();

            Ref<Sound2D> sound = AssetManager::GetAsset<Sound2D>(sc.Handle);

            if (sound == nullptr)
                return;
            if (sc.Play)
                sound->Pause();
        });
    }

    void Scene::OnUpdateRuntime(Timestep ts, bool showCollisions) {
        if (!_IsRunning || !_IsPaused) {

            // -- Update the Scripts -- //
            _World->AsyncForEach<ScriptComponent>([&](Entity *entity, auto script) {
                auto &sc = script.Get();

                if (sc.Instance == nullptr && !sc.Name.empty() && sc.InstantiateScript) {
                    sc.Instance = sc.InstantiateScript(sc.Name);

                    if (sc.Instance != nullptr) {
                        sc.Instance->HandleEntity = GameObject(entity, this);
                        sc.Instance->OnCreate();
                    }
                }

                if (sc.Instance != nullptr)
                    sc.Instance->OnUpdate(ts);
            });

            // -- Update the world -- //
            _World->Update(ts);

            // -- Get the main camera -- //
            Camera *mainCamera = nullptr;
            glm::mat4 cameraTransform;

            _World->AsyncForEach<TransformComponent, CameraComponent>([&](Entity *entity, auto transform, auto camera) {
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

                RenderScene(showCollisions);

                Renderer2D::EndScene();
            }
        }
    }

    void Scene::OnUpdateEditor(UNUSED(Timestep ts), EditorCamera &camera, bool showCollisions) {
        Renderer2D::BeginScene(camera);

        RenderScene(showCollisions);

        Renderer2D::EndScene();
    }

    void Scene::OnViewportResize(uint32_t width, uint32_t height) {
        if (_ViewportWidth == width && _ViewportHeight == height)
            return;
        _ViewportWidth = width;
        _ViewportHeight = height;

        _World->AsyncForEach<CameraComponent>(
            [&](Entity *entity, auto camera) {
                auto &cc = camera.Get();

                if (!cc.FixedAspectRatio) {
                    cc.Camera.SetViewportSize(width, height);
                }
            },
            false);
    }

    void Scene::RegisterSystem(EntitySystem *system) {
        if (_Systems.find(extractTypeName(typeid(*system).name())) != _Systems.end())
            return;
        _Systems[extractTypeName(typeid(*system).name())] = system;

        if (_IsRunning)
            _World->RegisterSystem(system);
    }

    void Scene::UnregisterSystem(const std::string &name) {
        if (_Systems.find(name) == _Systems.end())
            return;
        if (_IsRunning)
            _World->UnregisterSystem(_Systems[name]);
        _Systems.erase(name);
    }

    void Scene::RenderScene(bool showCollisions) {
        if (RendererAPI::GetAPI() == RendererAPI::API::None)
            return;

        _World->AsyncForEach<TransformComponent, SpriteRendererComponent, IDComponent>(
            [&](Entity *entity, auto transform, auto sprite, auto id) {
                auto &tc = transform.Get();
                auto &sc = sprite.Get();
                auto &ic = id.Get();

                Renderer2D::DrawSprite(tc.GetTransform(), sc, (int)ic.ID);
            });

        _World->AsyncForEach<TransformComponent, CircleRendererComponent, IDComponent>(
            [&](Entity *entity, auto transform, auto circle, auto id) {
                auto &tc = transform.Get();
                auto &cc = circle.Get();
                auto &ic = id.Get();

                Renderer2D::DrawCircle(tc.GetTransform(), cc.Color, cc.Thickness, cc.Fade, (int)ic.ID);
            });

        _World->AsyncForEach<TransformComponent, TextRendererComponent, IDComponent>(
            [&](Entity *entity, auto transform, auto text, auto id) {
                auto &tc = transform.Get();
                auto &txtc = text.Get();
                auto &ic = id.Get();

                Renderer2D::DrawText(tc.GetTransform(), txtc.Text, txtc, (int)ic.ID);
            });

        _World->AsyncForEach<SoundComponent>([&](Entity *entity, auto sound) {
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

        if (showCollisions)
            RenderDebugScene();
    }

    void Scene::RenderDebugScene() {
        _World->AsyncForEach<TransformComponent, BoxCollider2DComponent>(
            [&](Entity *entity, auto transform, auto collider) {
                auto &tc = transform.Get();
                auto &cc = collider.Get();

                glm::vec3 translation = tc.Translation + glm::vec3(cc.Offset, 0.001f);
                glm::vec3 scale = tc.Scale * glm::vec3(cc.Size * 2.0f, 1.0f);

                glm::mat4 transformMatrix = glm::translate(glm::mat4(1.0f), translation) *
                                            glm::rotate(glm::mat4(1.0f), tc.Rotation.z, glm::vec3(0.0f, 0.0f, 1.0f)) *
                                            glm::scale(glm::mat4(1.0f), scale);

                Renderer2D::DrawRect(transformMatrix, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));

                (void)entity;
            });

        _World->AsyncForEach<TransformComponent, CircleCollider2DComponent>(
            [&](Entity *entity, auto transform, auto collider) {
                auto &tc = transform.Get();
                auto &cc = collider.Get();

                glm::vec3 translation = tc.Translation + glm::vec3(cc.Offset, 0.001f);
                glm::vec3 scale = tc.Scale * glm::vec3(cc.Radius * 2.0f);

                glm::mat4 transformMatrix =
                    glm::translate(glm::mat4(1.0f), translation) * glm::scale(glm::mat4(1.0f), scale);

                Renderer2D::DrawCircle(transformMatrix, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), 0.05f);

                (void)entity;
            });
    }

    void Scene::OnKeyPressed(int key) {
        if (!_World || !_IsRunning)
            return;
        _World->AsyncForEach<ScriptComponent>([&](Entity *entity, auto script) {
            auto &sc = script.Get();

            if (sc.Instance != nullptr)
                sc.Instance->OnKeyPressed(key);

            (entity);
        });
    }

    void Scene::OnKeyReleased(int key) {
        if (!_World || !_IsRunning)
            return;
        _World->AsyncForEach<ScriptComponent>([&](Entity *entity, auto script) {
            auto &sc = script.Get();

            if (sc.Instance != nullptr)
                sc.Instance->OnKeyReleased(key);

            (entity);
        });
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

        _World->ForEach<CameraComponent>(
            [&](Entity *entity, auto camera) {
                auto &cc = camera.Get();

                if (cc.Primary)
                    primaryCamera = entity;
            },
            false);

        return GameObject(primaryCamera, this);
    }

    GameObject Scene::GetPrimaryCamera() const {
        Entity *primaryCamera = nullptr;

        _World->ForEach<CameraComponent>(
            [&](Entity *entity, auto camera) {
                auto &cc = camera.Get();

                if (cc.Primary)
                    primaryCamera = entity;
            },
            false);

        return GameObject(primaryCamera, nullptr);
    }

    bool Scene::HasSystems(const std::string &name) const { return _Systems.find(name) != _Systems.end(); }

    GameObject Scene::GetEntityByName(const std::string &name) {
        Entity *entity = nullptr;

        _World->ForEach<TagComponent>(
            [&](Entity *entt, auto tag) {
                auto &tc = tag.Get();

                if (tc.Tag == name)
                    entity = entt;
            },
            false);

        return GameObject(entity, this);
    }

    GameObject Scene::GetEntityByUUID(UUID uuid) {
        Entity *entity = nullptr;

        _World->ForEach<IDComponent>(
            [&](Entity *entt, auto id) {
                auto &ic = id.Get();

                if (ic.ID == uuid) {
                    entity = entt;
                    return;
                }
            },
            false);

        return GameObject(entity, this);
    }

    bool Scene::IsRunning() const { return _IsRunning; }

    bool Scene::IsPaused() const { return _IsPaused; }

    void Scene::SetPaused(bool paused) { _IsPaused = paused; }

    AssetType Scene::GetType() const { return AssetType::Scene; }
}; // namespace Exodia