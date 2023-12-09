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

namespace Exodia {

    class EditorLayer : public Exodia::Layer {

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

            void OnAttach()            override;
            void OnDetach()            override;
            void OnUpdate(Timestep ts) override;
            void OnImGUIRender()       override;
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
            void OpenScene();
            void OpenScene(AssetHandle handle);
            void SaveScene();
            void SaveSceneAs();

        ////////////////
        // Attributes //
        ////////////////
        private:

            Scope<ContentBrowser> _ContentBrowser;
            //Ref<Texture2D>         _Texture;
    };
};

#endif /* !GAMEENGINE_HPP_ */
