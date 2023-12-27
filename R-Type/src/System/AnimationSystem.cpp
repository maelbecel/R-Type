/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** AnimationSystem
*/

#include "AnimationSystem.hpp"

using namespace Exodia;

namespace RType {


    void AnimationSystem::UpdatePlayer(Entity *entity, Exodia::ComponentHandle<SpriteRendererComponent> &sprite, Exodia::ComponentHandle<Animation> &animation, Timestep ts) {
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
    }

    void AnimationSystem::UpdatePataPata(Exodia::ComponentHandle<SpriteRendererComponent> &sprite, Exodia::ComponentHandle<Animation> &animation, Timestep ts) {
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
    }

    void AnimationSystem::UpdateBullet(Exodia::ComponentHandle<SpriteRendererComponent> &sprite, Exodia::ComponentHandle<Animation> &animation, Timestep ts) {
        auto &anim = animation.Get();

        // Incrémenter le compteur avec le temps écoulé depuis la dernière mise à jour
        anim.ElapsedTime += ts.GetSeconds();

        // Vérifier si 0.5 seconde s'est écoulée
        if (anim.ElapsedTime >= 0.05f) {
            anim.CurrentFrame += 1;

            if (anim.CurrentFrame >= anim.MaxFrame)
                anim.CurrentFrame = anim.MaxFrame;

            // WARNING: This is a temporary solution
            sprite.Get().Texture->SetCoords({ anim.CurrentFrame, 0.0f });

            // Réinitialiser le compteur
            anim.ElapsedTime = 0.0f;
        }
    }

    void AnimationSystem::Update(World *world, Timestep ts) {
        if (!world)
            return;
        world->LockMutex();
        // WARNING: This is a temporary solution
        world->ForEach<SpriteRendererComponent, Animation>([&](Entity *entity, auto sprite, auto animation) {
            if (entity->GetComponent<TagComponent>().Get().Tag.rfind("Player", 0) == 0) {
                UpdatePlayer(entity, sprite, animation, ts);
            } else if (entity->GetComponent<TagComponent>().Get().Tag == "Pata-pata") {
                UpdatePataPata(sprite, animation, ts);
            } else if (entity->GetComponent<TagComponent>().Get().Tag.rfind("Bullet", 0) == 0) {
                UpdateBullet(sprite, animation, ts);
            }
        });
        world->UnlockMutex();
    }

    template <typename T, typename F>
    void AnimationSystem::UpdateAnimation(Entity *entity, F &&func) {
        auto script = entity->GetComponent<ScriptComponent>();

        if (script) {
            auto instance = reinterpret_cast<T *>(script.Get().Instance);

            if (entity)
                func(instance);
        }
    };
}