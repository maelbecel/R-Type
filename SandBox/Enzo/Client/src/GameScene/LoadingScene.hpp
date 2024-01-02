/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** LoadingScene
*/

#ifndef LOADINGSCENE_HPP_
    #define LOADINGSCENE_HPP_

    // R-Type includes
    #include "GameScene/GameScene.hpp"

namespace RType {

    class LoadingScene : public GameScene {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
        public:

            LoadingScene() = default;
            ~LoadingScene() override = default;

        /////////////
        // Methods //
        /////////////
        public:

            void OnCreate() override;
            void OnDestroy() override;

            void OnUpdate(Exodia::Timestep ts) override;
            void OnEvent(Exodia::Event &event) override;

        ////////////
        // Events //
        ////////////
        private:

            bool OnKeyPressedEvent(Exodia::KeyPressedEvent &event);

        ////////////////
        // Attributes //
        ////////////////
        private:

            Ref<Exodia::Scene> _Scene;
    };
};

#endif /* !LOADINGSCENE_HPP_ */
