/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** AnimationSystem
*/

#ifndef ANIMATIONSYSTEM_HPP_
    #define ANIMATIONSYSTEM_HPP_

    #include "Exodia.hpp"
    #include "ComponentExample.hpp"
    #include "Script/Player.hpp"
    #include "Script/Pata-pata.hpp"

namespace Exodia {

    class AnimationSystem : public EntitySystem {
        public:
            // Constructor && Destructor
            AnimationSystem() {
            };

            virtual ~AnimationSystem() {};

        public:
            // Methods
            virtual void Update(World *world, UNUSED Timestep ts) override
            {
                world->ForEach<SpriteRendererComponent, Animation>([&](Entity *entity, auto sprite, ComponentHandle<Animation> animation) {
                    // check if entity is player
                    if (entity->GetComponent<TagComponent>().Get().Tag == "Player") {
                        UpdateAnimation<Player>(entity, [&](UNUSED Player *player) {
                            switch (player->GetState()) {
                                case Player::State::MOVE_UP:
                                    animation.Get().MaxFrame = 4;
                                    break;
                                case Player::State::MOVE_DOWN:
                                    animation.Get().MaxFrame = 0;
                                    break;
                                case Player::State::IDLE:
                                    animation.Get().MaxFrame = 2;
                                    break;
                                default:
                                    break;
                            }
                            auto &anim = animation.Get();
                            // sprite.Get().Texture->SetCoords({ (float)anim.CurrentFrame, 4.0f });

                            anim.elapsedTime += ts.GetSeconds();

                            if (anim.elapsedTime >= 0.1f) {

                                if (anim.MaxFrame > anim.CurrentFrame) {
                                    anim.CurrentFrame += 1;

                                    if (anim.CurrentFrame >= anim.MaxFrame)
                                        anim.CurrentFrame = anim.MaxFrame;
                                } else {
                                    anim.CurrentFrame -= 1;

                                    if (anim.CurrentFrame <= anim.MaxFrame)
                                        anim.CurrentFrame = anim.MaxFrame;
                                }


                                sprite.Get().Texture->SetCoords({ anim.CurrentFrame, 4.0f });

                                anim.elapsedTime = 0.0f;
                            }
                        });
                    }
                    else if (entity->GetComponent<TagComponent>().Get().Tag == "Pata-pata") {
                        auto &anim = animation.Get();

                        // Incrémenter le compteur avec le temps écoulé depuis la dernière mise à jour
                        anim.elapsedTime += ts.GetSeconds();

                        // Vérifier si 0.5 seconde s'est écoulée
                        if (anim.elapsedTime >= 0.075f) {
                            anim.CurrentFrame += 1;

                            if (anim.CurrentFrame >= anim.MaxFrame)
                                anim.CurrentFrame = 0;

                            sprite.Get().Texture->SetCoords({ anim.CurrentFrame, 0.0f });

                            // Réinitialiser le compteur
                            anim.elapsedTime = 0.0f;
                        }
                    }
                });
            }

        private:
            template<typename T, typename F>
            void UpdateAnimation(Entity *entity, F &&func)
            {
                auto script = entity->GetComponent<ScriptComponent>();

                if (script) {
                    auto entity = reinterpret_cast<T *>(script.Get().Instance);

                    if (entity)
                        func(entity);
                }
            };
    };
};

#endif /* !ANIMATIONSYSTEM_HPP_ */
