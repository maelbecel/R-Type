/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** GameLayer
*/

#ifndef GAMELAYER_HPP_
    #define GAMELAYER_HPP_

    // Exodia includes
    #include "Exodia.hpp"

    // R-Type Games includes
    #include "R-Type.hpp"

    // R-Type Client includes
    #include "GameScene/GameScene.hpp"

namespace RType {

    enum SceneType {
        LOADING,
        MENU,
        GAME,
        NONE
    };

    class GameLayer : public Exodia::Layer {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
        public:

            GameLayer();
            ~GameLayer() = default;

        /////////////
        // Methods //
        /////////////
        public:

            static Ref<GameLayer> New()
            {
                _Instance = CreateRef<GameLayer>();

                return _Instance;
            }

            void OnAttach() override;
            void OnUpdate(Exodia::Timestep ts) override;
            void OnEvent(Exodia::Event &event) override;
        
        private:
            
            void InitGame();

        ///////////////////////
        // Getters & Setters //
        ///////////////////////
        public:

            static Ref<GameLayer> GetInstance()
            {
                return _Instance;
            }

            /**
             * @brief Set the Scene object
             *
             * @param scene   The scene to set
             * @param destroy If true, the current scene will be destroyed
             */
            void SetScene(SceneType scene, bool destroy = false);

        ////////////////
        // Attributes //
        ////////////////
        private:

            std::map<SceneType, Ref<GameScene>> _Scenes;
            SceneType _CurrentScene;
        
        private:
            inline static Ref<GameLayer> _Instance;
    };
};

#endif /* !GAMELAYER_HPP_ */
