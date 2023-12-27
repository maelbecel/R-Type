/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** EditorLayer
*/

#ifndef GAMEENGINE_HPP_
#define GAMEENGINE_HPP_

// Exodia includes
#include "Exodia.hpp"

// Panel includes
#include "Panel/ContentBrowser/ContentBrowser.hpp"
#include "Panel/SceneHierarchy/SceneHierarchy.hpp"

namespace Exodia {

    class EditorLayer : public Exodia::Layer {

        //////////
        // Enum //
        //////////
      public:
        enum class SceneState { Edit = 0, Play = 1 };

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
      public:
        EditorLayer();
        ~EditorLayer() = default;

        /////////////
        // Methods //
        /////////////
      public:
        void OnAttach() override;
        void OnDetach() override;
        void OnUpdate(Timestep ts) override;
        void OnImGUIRender() override;
        void OnEvent(Event &event) override;

        /////////////////////
        // Project Methods //
        /////////////////////
      private:
        void NewProject();
        bool OpenProject();
        void OpenProject(const std::filesystem::path &path);

        ///////////////////
        // Scene Methods //
        ///////////////////
      private:
        void NewScene();
        void OpenScene(AssetHandle handle);
        void SaveScene();
        void SaveSceneAs();
        void OnSceneStart();
        void OnSceneStop();

        ///////////
        // ImGui //
        ///////////
      private:
        void ToolBarRendering();
        void OnOverlayRender();

        ////////////////
        // Attributes //
        ////////////////
      private:
        // Framebuffer
        Ref<Framebuffer> _Framebuffer;

        // Scene
        EditorCamera _EditorCamera;
        Ref<Scene> _EditorScene;
        Ref<Scene> _ActiveScene;
        std::filesystem::path _EditorScenePath;
        SceneState _SceneState;

        // Panels
        Scope<ContentBrowser> _ContentBrowser;
        SceneHierarchy _SceneHierarchy;

        // Entity
        Entity _HoveredEntity;

        // Viewport
        glm::vec2 _ViewportBounds[2];
        glm::vec2 _ViewportSize;
        bool _ViewportHovered;

        // ImGuizmo
        int _GuizmoType;

        // Icon
        Ref<Texture2D> _PlayButton;
        Ref<Texture2D> _PauseButton;
        Ref<Texture2D> _StopButton;
    };
}; // namespace Exodia

#endif /* !GAMEENGINE_HPP_ */
