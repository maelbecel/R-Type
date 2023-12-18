/*
** EPITECH PROJECT, 2023
** $
** File description:
** Player
*/

#ifndef PATAPATA_HPP_
    #define PATAPATA_HPP_

    // Exodia includes
    #include "Exodia.hpp"
    #include "ComponentExample.hpp"
    #include "BulletEnnemy.hpp"

    #include <cmath>

namespace Exodia {

    const double PI = 3.14159265358979323846;

    class PataPata : public ScriptableEntity {

        /////////////
        //  enum   //
        /////////////
        public:
            enum class State {
                ALIVE,
                DEAD
            };

        /////////////
        // Methods //
        /////////////
        public:

            void CreateBullet(TransformComponent &tc) {
                EXODIA_INFO("Ennemy attack");

                Entity *bullet = HandleEntity->GetWorld()->CreateNewEntity("BE" + std::to_string(HandleEntity->GetWorld()->GetCount()));

                TransformComponent &bullet_tc = bullet->GetComponent<TransformComponent>().Get();
                bullet_tc.Translation.x = tc.Translation.x;
                bullet_tc.Translation.y = tc.Translation.y - 1.0f;
                auto sprite = bullet->AddComponent<SpriteRendererComponent>();
                bullet->AddComponent<ScriptComponent>().Get().Bind<BulletEnnemy>();
                bullet->AddComponent<Animation>(0.0f, 2.0f, 1.0f);
                bullet->AddComponent<BoxCollider2DComponent>();
                bullet->AddComponent<ParentComponent>().Get().Parent = GetComponent<IDComponent>().Get().ID;

                auto player = HandleEntity->GetWorld()->GetEntityByTag("Player")->GetComponent<TransformComponent>();
                auto body_bullet = bullet->AddComponent<RigidBody2DComponent>();

                body_bullet.Get().Type = RigidBody2DComponent::BodyType::Dynamic;
                body_bullet.Get().Mass = 0.0f;
                body_bullet.Get().GravityScale = 0.0f;
                body_bullet.Get().Velocity.x = player.Get().Translation.x - tc.Translation.x;
                body_bullet.Get().Velocity.y = player.Get().Translation.y - tc.Translation.y;

                Ref<Texture2D> texture = TextureImporter::LoadTexture2D("Assets/Textures/Missile.png");
                sprite.Get().Texture = SubTexture2D::CreateFromCoords(texture, { 0.0f, 0.0f }, { 17.33f, 14.0f }, { 1.0f, 1.0f });

                // Ref<Texture2D> texture = TextureImporter::LoadTexture2D("Assets/Textures/Explosion.png");
                // sprite.Get().Texture = SubTexture2D::CreateFromCoords(texture, { 4.0f, 9.0f }, { 16.6666666667f, 17.0f }, { 1.0f, 1.0f });
            }

            void OnCreate() override
            {
                auto transform = GetComponent<TransformComponent>();
                auto camera = HandleEntity->GetWorld()->GetEntityByTag("Camera")->GetComponent<TransformComponent>();

                _State = State::ALIVE;
                std::cout << "PataPata created" << std::endl;
                transform.Get().Translation.x = camera.Get().Translation.x + 20.0f;
                transform.Get().Translation.y = 0.0f - random() % 5;
                EXODIA_INFO("PataPata created at pos {0}, {1}", transform.Get().Translation.x, transform.Get().Translation.y);
            }

            void OnUpdate(Timestep ts) override
            {
                auto transform = GetComponent<TransformComponent>();
                auto &mytime = GetComponent<Clock>().Get().ElapsedTime;
                auto body = GetComponent<RigidBody2DComponent>();
                auto camera = HandleEntity->GetWorld()->GetEntityByTag("Camera")->GetComponent<TransformComponent>();

                // Paramètres de la fonction sinus
                double amplitude = 5.0f;  // Amplitude de la sinusoïde
                double frequency = 1.0f;  // Fréquence de la sinusoïde en Hz

                _AttackTimer += ts.GetSeconds();
                if (transform && _State == State::ALIVE) {
                    // auto &tc = transform.Get();
                    // Mise à jour de la position en fonction du temps et du mouvement sinusoidal
                    mytime += ts.GetSeconds();
                    body.Get().Velocity.y = amplitude * sin(frequency * mytime * PI);

                    // Affichage des coordonnées

                    if (transform.Get().Translation.x < camera.Get().Translation.x - 20.0f)
                        transform.Get().Translation.x = camera.Get().Translation.x + 20.0f;
                }

                if (GetComponent<Health>().Get().CurrentHealth == 0 && _State == State::ALIVE) {
                    auto animation = GetComponent<Animation>();
                    auto sprite = GetComponent<SpriteRendererComponent>();

                    animation.Get().CurrentFrame = 0;
                    animation.Get().MaxFrame = 7;
                    animation.Get().FrameTime = 0.095f;

                    // Set entity sprite
                    Ref<Texture2D> texture = TextureImporter::LoadTexture2D("Assets/Textures/Simple_Explosion.png");
                    sprite.Get().Texture = SubTexture2D::CreateFromCoords(texture, { 0.0f, 0.0f }, { 32.0f, 34.0f }, { 1.0f, 1.0f });
                    _State = State::DEAD;
                    GetComponent<RigidBody2DComponent>().Get().Velocity = { 0.0f, 0.0f };
                }
                if (_State == State::DEAD && GetComponent<Animation>().Get().CurrentFrame == 6) {
                    HandleEntity->GetWorld()->DestroyEntity(HandleEntity);
                }
                if (_AttackTimer > 5.0f) {
                    CreateBullet(transform.Get());
                    _AttackTimer = 0.0f;
                }
            }

            void OnCollisionEnter(Entity *entity) override
            {
                if (entity->GetComponent<TagComponent>().Get().Tag.rfind("Bullet", 0) == 0) {
                    EXODIA_INFO("Bullet {0} hit", entity->GetComponent<TagComponent>().Get().Tag);
                    GetComponent<Health>().Get().CurrentHealth -= 1;
                }
            }

            State GetState() const { return _State; }

        ////////////////
        // Attributes //
        ////////////////
        private:
            State _State;
            float _AttackTimer;
    };
};

#endif /* !PATAPATA_HPP_ */

