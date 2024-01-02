/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** MenuScene
*/

#ifndef MENUSCENE_HPP_
#define MENUSCENE_HPP_

// Exodia includes
#include "Exodia.hpp"

// R-Type includes
#include "GameScene/GameScene.hpp"

namespace RType {

    class MenuScene : public GameScene {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
      public:
        MenuScene() = default;
        ~MenuScene() override = default;

        /////////////
        // Methods //
        /////////////
      public:
        void OnCreate() override;
        void OnDestroy() override;

        void OnUpdate(Exodia::Timestep ts) override;
        void OnEvent(Exodia::Event &event) override;

      private:
        void GiveFadeEffect(bool in = true);

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
}; // namespace RType

#endif /* !MENUSCENE_HPP_ */
