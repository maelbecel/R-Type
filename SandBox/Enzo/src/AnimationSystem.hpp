/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** AnimationSystem
*/

#ifndef ANIMATIONSYSTEM_HPP_
#define ANIMATIONSYSTEM_HPP_

#include "ComponentExample.hpp"
#include "Exodia.hpp"
#include "Script/Pata-pata.hpp"
#include "Script/Player.hpp"

namespace Exodia
{

    class AnimationSystem : public EntitySystem
    {
      public:
        // Constructor && Destructor
        AnimationSystem(){};

        virtual ~AnimationSystem(){};

      public:
        // Methods
        virtual void Update( World *world, Timestep ts ) override
        {
            world->ForEach<SpriteRendererComponent, Animation>(
                [ & ]( Entity *entity, auto sprite, ComponentHandle<Animation> animation ) {
                    // check if entity is player
                    if ( entity->GetComponent<TagComponent>().Get().Tag == "Player" )
                    {
                        UpdateAnimation<Player>( entity, [ & ]( Player *player ) {
                            switch ( player->GetState() )
                            {
                            case Player::State::MOVE_UP:
                                animation.Get().CurrentFrame = 3;
                                animation.Get().MaxFrame     = 4;
                                animation.Get().FrameTime    = 0.0f;
                                break;
                            case Player::State::MOVE_DOWN:
                                animation.Get().CurrentFrame = 1;
                                animation.Get().MaxFrame     = 0;
                                animation.Get().FrameTime    = 0.0f;
                                break;
                            case Player::State::IDLE:
                                animation.Get().CurrentFrame = 2;
                                animation.Get().MaxFrame     = 2;
                                animation.Get().FrameTime    = 0.0f;
                                break;
                            default:
                                break;
                            }
                            auto &anim = animation.Get();
                            sprite.Get().Texture->SetCoords( { (float) anim.CurrentFrame, 4.0f } );
                        } );
                    }
                    else if ( entity->GetComponent<TagComponent>().Get().Tag == "Pata-pata" )
                    {
                        auto &anim = animation.Get();

                        // Incrémenter le compteur avec le temps écoulé depuis la dernière mise à jour
                        anim.elapsedTime += ts.GetSeconds();

                        // Vérifier si 0.5 seconde s'est écoulée
                        if ( anim.elapsedTime >= 0.075f )
                        {
                            anim.CurrentFrame += 1;

                            if ( anim.CurrentFrame >= anim.MaxFrame )
                                anim.CurrentFrame = 0;

                            sprite.Get().Texture->SetCoords( { anim.CurrentFrame, 0.0f } );

                            // Réinitialiser le compteur
                            anim.elapsedTime = 0.0f;
                        }
                    }
                } );
        }

      private:
        template <typename T, typename F> void UpdateAnimation( Entity *entity, F &&func )
        {
            auto script = entity->GetComponent<ScriptComponent>();

            if ( script )
            {
                auto entity = reinterpret_cast<T *>( script.Get().Instance );

                if ( entity )
                    func( entity );
            }
        };
    };
}; // namespace Exodia

#endif /* !ANIMATIONSYSTEM_HPP_ */
