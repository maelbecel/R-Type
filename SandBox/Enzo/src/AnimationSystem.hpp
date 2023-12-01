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
                        auto script = entity->GetComponent<ScriptComponent>();
                        if (script) {
                            auto player = reinterpret_cast<Player *>(script.Get().Instance);

                            if (player) {
                                switch (player->GetState()) {
                                    case Player::State::MOVE_UP:
                                        animation.Get().CurrentFrame = 3;
                                        animation.Get().MaxFrame = 4;
                                        animation.Get().FrameTime = 0.0f;
                                        break;
                                    case Player::State::MOVE_DOWN:
                                        animation.Get().CurrentFrame = 1;
                                        animation.Get().MaxFrame = 0;
                                        animation.Get().FrameTime = 0.0f;
                                        break;
                                    case Player::State::IDLE:
                                        animation.Get().CurrentFrame = 2;
                                        animation.Get().MaxFrame = 2;
                                        animation.Get().FrameTime = 0.0f;
                                        break;
                                    default:
                                        break;
                               }
                            }
                        }
                        auto &anim = animation.Get();
                        sprite.Get().Texture->SetCoords({ (float)anim.CurrentFrame, 4.0f });
                    }
                });
            }

        private:
            // Attributes
    };
};

#endif /* !ANIMATIONSYSTEM_HPP_ */
