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

namespace RType {

    class EntityEventSubscriber : public Exodia::EventSubscriber<Exodia::Events::OnEntityCreated>, public Exodia::EventSubscriber<Exodia::Events::OnEntityDestroyed> {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
        public:

            EntityEventSubscriber(const Exodia::Network::Network &network) : _Network(network) {};

            virtual ~EntityEventSubscriber() override = default;

        /////////////
        // Methods //
        /////////////
        public:

            virtual void Receive(Exodia::World *world, const Exodia::Events::OnEntityCreated   &event) override;
            virtual void Receive(Exodia::World *world, const Exodia::Events::OnEntityDestroyed &event) override;

        ////////////////
        // Attributes //
        ////////////////
        private:
            const Exodia::Network::Network &_Network;
    };
};

#endif /* !ENTITYEVENTSUBSCRIBER_HPP_ */

