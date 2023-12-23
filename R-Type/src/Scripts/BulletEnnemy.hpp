/*
** EPITECH PROJECT, 2023
** $
** File description:
** Player
*/

#ifndef BULLETENNEMY_HPP_
#define BULLETENNEMY_HPP_

// Exodia includes
#include "Component/Animation.hpp"
#include "Exodia.hpp"

#include <cmath>

namespace Exodia
{

    class BulletEnnemy : public ScriptableEntity
    {

        /////////////
        // Methods //
        /////////////
      public:
        void OnCreate() override
        {
            _Speed = 5.0f;

            std::cout << "Bullet created" << std::endl;
        }

        void OnUpdate( Timestep ts ) override
        {
            auto transform = GetComponent<TransformComponent>();
            auto animation = GetComponent<Animation>();
            auto parent    = GetComponent<ParentComponent>();
            auto camera    = HandleEntity->GetWorld()->GetEntityByTag( "Camera" )->GetComponent<TransformComponent>();

            Entity *entity = HandleEntity->GetWorld()->GetEntityByID( parent.Get().Parent );

            if ( !entity )
            {
                std::cout << "Entity not found " << parent.Get().Parent << std::endl;
            }

            // Paramètres de la fonction sinus

            if ( transform && animation )
            {
                auto &tc = transform.Get();
                // Mise à jour de la position en fonction du temps et du mouvement sinusoidal
                if ( animation.Get().CurrentFrame == animation.Get().MaxFrame )
                {
                    tc.Translation.x -= _Speed * ts;
                }
            }

            // Remove bullet if out of screen
            if ( transform.Get().Translation.x > camera.Get().Translation.x + 20.0f )
            {
                EXODIA_INFO( "Bullet {0} destroyed", HandleEntity->GetComponent<TagComponent>().Get().Tag );
                HandleEntity->GetWorld()->DestroyEntity( HandleEntity );
            }
        }

        ////////////////
        // Attributes //
        ////////////////
      private:
        float _Speed;
    };
}; // namespace Exodia

#endif /* !BULLETENNEMY_HPP_ */
