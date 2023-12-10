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
    #include "ECS/World/World.hpp"

    // Exodia Renderer includes
    #include "Renderer/Camera/EditorCamera.hpp"

namespace Exodia {

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

            Entity *CreateEntity(const std::string &name = std::string());
            Entity *CreateEntityWithUUID(UUID uuid, const std::string &name = std::string());
            Entity *DuplicateEntity(Entity *entity);
            void DestroyEntity(Entity *entity);

            // -- Runtime ------------------------------------------------------

            void OnRuntimeStart();
            void OnRuntimeStop();
            void OnUpdataRuntime(Timestep ts);

            // -- Editor -------------------------------------------------------

            void OnUpdateEditor(Timestep ts, EditorCamera &camera);

            // -- Viewport -----------------------------------------------------

            void OnViewportResize(uint32_t width, uint32_t height);

            // -- World --------------------------------------------------------

            template<typename ...Components>
            void ForEach(typename std::common_type<std::function<void(Entity *, ComponentHandle<Components>...)>>::type function, bool includePendingDestroy = false)
            {
                _World->ForEach<Components...>(function, includePendingDestroy);
            }

        private:
            
            void RenderScene();

        ///////////////////////
        // Getters & Setters //
        ///////////////////////
        public:

            const std::string &GetName() const;

            World &GetWorld() const;

            Entity *GetPrimaryCamera();
            Entity *GetEntityByName(const std::string &name);
            Entity *GetEntityByUUID(UUID uuid);

            bool IsRunning() const;
            bool IsPaused() const;

            void SetPaused(bool paused);

            virtual AssetType GetType() const override;

        ////////////////
        // Attributes //
        ////////////////
        private:

            std::string _Name;
            uint32_t    _ViewportWidth;
            uint32_t    _ViewportHeight;
            World      *_World;

            bool _IsRunning;
            bool _IsPaused;
    };
};

#endif /* !SCENE_HPP_ */
