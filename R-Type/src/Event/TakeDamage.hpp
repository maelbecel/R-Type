/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** TakeDamage
*/

#ifndef TAKEDAMAGE_HPP_
#define TAKEDAMAGE_HPP_

// Exodia includes
#include "Exodia.hpp"

// RType includes
#include "Component/Health.hpp"

namespace RType {

    namespace Events {

        struct TakeDamage {
            Exodia::Entity *Entity;

            int Damage;
        };
    }; // namespace Events

    class TakeDamageSubscriber : public Exodia::EventSubscriber<Events::TakeDamage> {
      public:
        void Receive(Exodia::World *world, const Events::TakeDamage &event) override {
            auto health = event.Entity->GetComponent<Exodia::Health>();

            if (!health)
                return;
            auto &hc = health.Get();

            hc.CurrentHealth -= event.Damage;

            if (hc.CurrentHealth <= 0)
                world->DestroyEntity(event.Entity);
        }
    };
}; // namespace RType

#endif /* !TAKEDAMAGE_HPP_ */
