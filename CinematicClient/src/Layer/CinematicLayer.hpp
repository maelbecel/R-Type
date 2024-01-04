/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** CinematicLayer
*/

#ifndef CINEMATICLAYER_HPP_
#define CINEMATICLAYER_HPP_

#include "Exodia.hpp"

using namespace Exodia;

namespace Cinematic {

    class CinematicLayer : public Exodia::Layer {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
      public:
        CinematicLayer();
        ~CinematicLayer() = default;

        /////////////
        // Methods //
        /////////////
      public:
        void OnAttach() override;
        void OnDetach() override;
        void OnUpdate(Timestep ts) override;
        void OnImGUIRender() override;
        void OnEvent(Event &event) override;

        ////////////////
        // Attributes //
        ////////////////
      private:
        // TODO: WARNING: This is a temporary solution
        World *_World;
    };
}; // namespace Cinematic

#endif /* !RTYPELAYER_HPP_ */
