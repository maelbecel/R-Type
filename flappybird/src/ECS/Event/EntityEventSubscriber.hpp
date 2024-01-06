/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** EntityEventSubscriber
*/

#ifndef ENTITYEVENTSUBSCRIBER_HPP_
#define ENTITYEVENTSUBSCRIBER_HPP_

// Exodia include
#include "Exodia.hpp"

namespace FlappyBird {

    class EntityEventSubscriber : public Exodia::EventSubscriber<Exodia::Events::OnEntityCreated>,
                                  public Exodia::EventSubscriber<Exodia::Events::OnEntityDestroyed> {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
      public:
        EntityEventSubscriber(Exodia::Network::Network &network) : _Network(network){};

        virtual ~EntityEventSubscriber() override = default;

        /////////////
        // Methods //
        /////////////
      public:
        virtual void Receive(Exodia::World *world, const Exodia::Events::OnEntityCreated &event) override;
        virtual void Receive(Exodia::World *world, const Exodia::Events::OnEntityDestroyed &event) override;

        ////////////////
        // Attributes //
        ////////////////
      private:
        Exodia::Network::Network &_Network;
    };
}; // namespace RType

#endif /* !ENTITYEVENTSUBSCRIBER_HPP_ */
