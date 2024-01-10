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

// Exodia Scene includes
#include "Scene/GameObject/GameObject.hpp"
#include "Scene/Prefabs/Prefabs.hpp"

// External includes
#include <unordered_map>

namespace Exodia {

    class GameObject;
    class Prefabs;

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

        GameObject DuplicateEntity(GameObject gameObject);

        void DestroyEntity(GameObject gameObject);
        void DestroyAllEntities();

        // -- Runtime ------------------------------------------------------

        void OnRuntimeStart();
        void OnRuntimeStop();
        void OnUpdateRuntime(Timestep ts);

        // -- Editor -------------------------------------------------------

        void OnUpdateEditor(Timestep ts, EditorCamera &camera);

        // -- Viewport -----------------------------------------------------

        void OnViewportResize(uint32_t width, uint32_t height);

        // -- World --------------------------------------------------------

        template <typename... Components>
        void
        ForEach(typename std::common_type<std::function<void(Entity *, ComponentHandle<Components>...)>>::type function,
                bool includePendingDestroy = false) {
            if (_World)
                _World->ForEach<Components...>(function, includePendingDestroy);
        }

        void RegisterSystem(EntitySystem *system);

        template <typename Event> void Subscribe(EventSubscriber<Event> *subscriber) {
            _World->Subscribe<Event>(subscriber);
        }

        void AddPrefab(Ref<Prefabs> prefab);
        bool RemovePrefab(const std::string &name);

        // -- Key Events ---------------------------------------------------

        void OnKeyPressedEvent(int keyCode);
        void OnKeyReleasedEvent(int keyCode);

      private:
        void RenderScene();
        void RenderDebugScene();

        ///////////////////////
        // Getters & Setters //
        ///////////////////////
      public:
        const std::string &GetName() const;
        void SetName(const std::string &name);

        World &GetWorld() const;

        World *GetWorldPtr();

        GameObject GetPrimaryCamera();
        GameObject GetEntityByName(const std::string &name);
        GameObject GetEntityByUUID(UUID uuid);

        bool IsRunning() const;
        bool IsPaused() const;

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

        std::vector<EntitySystem *> _Systems;

        std::vector<Ref<Prefabs>> _Prefabs;

        std::unordered_map<UUID, Entity *> _EntityMap;

        friend class GameObject;
        friend class SceneSerializer;
    };
}; // namespace Exodia

#endif /* !SCENE_HPP_ */
