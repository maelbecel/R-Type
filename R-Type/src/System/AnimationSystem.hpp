/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** AnimationSystem
*/

#ifndef ANIMATIONSYSTEM_HPP_
    #define ANIMATIONSYSTEM_HPP_

    #include "Exodia.hpp"
    #include "Component/Animation.hpp"
    #include "Scripts/Player/Player.hpp"
    #include "Scripts/Pata-pata.hpp"

namespace Exodia {

    class AnimationSystem : public EntitySystem {
        public:
            // Constructor && Destructor
            AnimationSystem() {};

            virtual ~AnimationSystem() {};

        public:
            // Methods
            virtual void Update(World *world, Timestep ts) override
            {
                // WARNING: This is a temporary solution
                // world->ForEach<SpriteRendererComponent, Animation>([&](Entity *entity, auto sprite, auto animation) {
                world->ForEach<Animation>([&](Entity *entity, ComponentHandle<Animation> animation) {
                    // check if entity is player
                    if (entity->GetComponent<TagComponent>().Get().Tag.rfind("Player", 0) == 0) {
                        UpdateAnimation<Player>(entity, [&](Player *player) {
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

                            anim.ElapsedTime += ts.GetSeconds();

                            if (anim.ElapsedTime >= 0.1f) {

                                if (anim.MaxFrame > anim.CurrentFrame) {
                                    anim.CurrentFrame += 1;

                                    if (anim.CurrentFrame >= anim.MaxFrame)
                                        anim.CurrentFrame = anim.MaxFrame;
                                } else {
                                    anim.CurrentFrame -= 1;

                                    if (anim.CurrentFrame <= anim.MaxFrame)
                                        anim.CurrentFrame = anim.MaxFrame;
                                }

                                // WARNING: This is a temporary solution
                                // sprite.Get().Texture->SetCoords({ anim.CurrentFrame, 4.0f });

                                anim.ElapsedTime = 0.0f;
                            }
                        });
                    } else if (entity->GetComponent<TagComponent>().Get().Tag == "Pata-pata") {
                        auto &anim = animation.Get();

                        // Incrémenter le compteur avec le temps écoulé depuis la dernière mise à jour
                        anim.ElapsedTime += ts.GetSeconds();

                        // Vérifier si 0.5 seconde s'est écoulée
                        if (anim.ElapsedTime >= anim.FrameTime) {
                            anim.CurrentFrame += 1;

                            if (anim.CurrentFrame >= anim.MaxFrame)
                                anim.CurrentFrame = 0;

                            // WARNING: This is a temporary solution
                            // sprite.Get().Texture->SetCoords({ anim.CurrentFrame, 4.0f });

                            // Réinitialiser le compteur
                            anim.ElapsedTime = 0.0f;
                        }
                    } else if (entity->GetComponent<TagComponent>().Get().Tag.rfind("Bullet", 0) == 0) {
                        auto &anim = animation.Get();

                        // Incrémenter le compteur avec le temps écoulé depuis la dernière mise à jour
                        anim.ElapsedTime += ts.GetSeconds();

                        // Vérifier si 0.5 seconde s'est écoulée
                        if (anim.ElapsedTime >= 0.075f) {
                            anim.CurrentFrame += 1;

                            if (anim.CurrentFrame >= anim.MaxFrame)
                                anim.CurrentFrame = anim.MaxFrame;

                            // WARNING: This is a temporary solution
                            // sprite.Get().Texture->SetCoords({ anim.CurrentFrame, 0.0f });

                            // Réinitialiser le compteur
                            anim.ElapsedTime = 0.0f;
                        }
                    }
                });
            }

        //    virtual void OnCollisionEnter(Entity *entity) override
        //    {

        //    }


        private:
            template<typename T, typename F>
            void UpdateAnimation(Entity *entity, F &&func)
            {
                auto script = entity->GetComponent<ScriptComponent>();

                if (script) {
                    auto instance = reinterpret_cast<T *>(script.Get().Instance);

                    if (entity)
                        func(instance);
                }
            };
    };
};

#endif /* !ANIMATIONSYSTEM_HPP_ */
