/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Scene
*/

#ifndef SCENE_HPP_
#define SCENE_HPP_

// Exodia Asset includes
#include "Asset/Asset.hpp"

// Exodia ECS includes
#include "Exodia-ECS.hpp"

// Exodia Renderer includes
#include "Renderer/Camera/EditorCamera.hpp"
#include "Scene/GameObject/GameObject.hpp"

// External includes
#include <unordered_map>

namespace Exodia {

    class GameObject;

    class Scene : public Asset {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
      public:
        Scene(const std::string &name = "Untitled Scene");
        ~Scene();

        /////////////
        // Methods //
        /////////////
      public:
        static Ref<Scene> Copy(Ref<Scene> other);

        // -- Entity -------------------------------------------------------

        GameObject CreateEntity(const std::string &name = std::string());
        GameObject CreateEntityWithUUID(UUID uuid, const std::string &name = std::string());
        GameObject CreateNewEntity(const std::string &name = std::string());
        GameObject CreateNewEntityWithUUID(UUID uuid, const std::string &name = std::string());
        GameObject LoadPrefabs(const std::string &path, bool newPrefab = false);

        GameObject DuplicateEntity(GameObject gameObject);

        void DestroyEntity(GameObject gameObject);
        void DestroyAllEntities();

        // -- Runtime ------------------------------------------------------

        void OnRuntimeStart();
        void OnRuntimeStop();
        void OnUpdateRuntime(Timestep ts, bool showCollisions = false);

        // -- Editor -------------------------------------------------------

        void OnUpdateEditor(Timestep ts, EditorCamera &camera, bool showCollisions = false);

        // -- Viewport -----------------------------------------------------

        void OnViewportResize(uint32_t width, uint32_t height);

        // -- World --------------------------------------------------------

        template <typename... Components>
        void
        ForEach(typename std::common_type<std::function<void(Entity *, ComponentHandle<Components>...)>>::type function,
                bool mergeEntities = true, bool includePendingDestroy = false) {
            if (_World)
                _World->ForEach<Components...>(function, mergeEntities, includePendingDestroy);
        }

        void RegisterSystem(EntitySystem *system);
        void UnregisterSystem(const std::string &name);

        template <typename Event> void Subscribe(EventSubscriber<Event> *subscriber) {
            _World->Subscribe<Event>(subscriber);
        }

        template <typename Event> void Emit(const Event &event) { _World->Emit<Event>(event); }

        // -- Scene Events -------------------------------------------------

        void OnKeyPressed(int key);
        void OnKeyReleased(int key);

        // -- Key Events ---------------------------------------------------

        void OnKeyPressedEvent(int keyCode);
        void OnKeyReleasedEvent(int keyCode);

      private:
        void RenderScene(bool showCollisions = false);
        void RenderDebugScene();

        GameObject DeserializePrefab(YAML::Node &node, bool newPrefab);

        ///////////////////////
        // Getters & Setters //
        ///////////////////////
      public:
        const std::string &GetName() const;
        void SetName(const std::string &name);

        World &GetWorld() const;

        World *GetWorldPtr();

        GameObject GetPrimaryCamera();
        GameObject GetPrimaryCamera() const;
        GameObject GetEntityByName(const std::string &name);
        GameObject GetEntityByUUID(UUID uuid);

        bool IsRunning() const;
        bool IsPaused() const;
        bool HasSystems(const std::string &name) const;

        void SetPaused(bool paused);

        virtual AssetType GetType() const override;

        ////////////////
        // Attributes //
        ////////////////
      private:
        std::string _Name;
        uint32_t _ViewportWidth;
        uint32_t _ViewportHeight;
        World *_World;

        bool _IsRunning;
        bool _IsPaused;

        std::unordered_map<std::string, EntitySystem *> _Systems;

        std::unordered_map<std::string, GameObject> _Prefabs;

        std::unordered_map<UUID, Entity *> _EntityMap;

        friend class GameObject;
        friend class SceneSerializer;
    };
}; // namespace Exodia

#endif /* !SCENE_HPP_ */
