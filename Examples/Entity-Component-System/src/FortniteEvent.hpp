/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** FortniteEvent
*/

#ifndef FORTNITEEVENT_HPP_
    #define FORTNITEEVENT_HPP_

    #include "GravitySystem.hpp"

namespace Exodia {

    struct TakeDamageEvent {
        int Damage;
    };

    class TakeDamageSubscriber : public EventSubscriber<TakeDamageEvent> {
        public:
            // Constructor && Destructor
            TakeDamageSubscriber() = default;
            virtual ~TakeDamageSubscriber() {};

        public:
            // Methods
            virtual void Receive(World *world, const TakeDamageEvent &event) override
            {
                world->ForEach<Health>([&](UNUSED Entity *entity, ComponentHandle<Health> health) {
                    std::cout << "I took " << event.Damage << " damage !" << std::endl;

                    health->CurrentHealth -= event.Damage;
                });
            }
    };

    class FortniteZone : public EntitySystem, public EventSubscriber<TakeDamageEvent> {
        public:
            // Constructor && Destructor
            FortniteZone(float damagePerSecond) : _DamagePerSecond(damagePerSecond) {};
        
            virtual ~FortniteZone() {};

        public:
            // Methods
            virtual void Update(World *world, Timestep ts) override
            {
                world->ForEach<Health>([&](UNUSED Entity *entity, ComponentHandle<Health> health) {
                    health->CurrentHealth -= _DamagePerSecond * ts;
                });
            }

            virtual void Configure(World *world) override
            {
                world->Subscribe<TakeDamageEvent>(this);
            }
        
            virtual void Unconfigure(World *world) override
            {
                // world->Unsubscribe<TakeDamageEvent>(this);
                world->UnsubscribeAll(this);

                // You may also unsubscribe from specific events with world->Unsubscribe<TakeDamageEvent>(this), but
                // when unconfigure is called you usually want to unsubscribe from all events.
            }

        private:
            // Attributes
            float _DamagePerSecond;
    };
};

#endif /* !FORTNITEEVENT_HPP_ */

