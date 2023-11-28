/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** GravitySystem
*/

#ifndef GRAVITYSYSTEM_HPP_
    #define GRAVITYSYSTEM_HPP_

    #include "Exodia.hpp"
    #include "ComponentExample.hpp"

namespace Exodia {

    class GravitySystem : public EntitySystem {
        public:
            // Constructor && Destructor
            GravitySystem(float amount) : _GravityAmount(amount) {};
        
            virtual ~GravitySystem() {};
    
        public:
            // Methods
            virtual void Update(World *world, Timestep ts) override
            {
                world->ForEach<Transform>([&](UNUSED Entity *entity, ComponentHandle<Transform> transform) {
                    transform->Translation.y += _GravityAmount * ts;
                });
            }

        private:
            // Attributes
            float _GravityAmount;
    };
};

#endif /* !GRAVITYSYSTEM_HPP_ */
