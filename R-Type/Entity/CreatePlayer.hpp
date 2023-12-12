/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Create player
*/

#ifndef CREATEPLAYER_HPP_
    #define CREATEPLAYER_HPP_

    #include "Exodia.hpp"
    #include "ComponentExample.hpp"
    #include "Script/Player/Player.hpp"

namespace Exodia {

    /**
     * @brief Create a Player object
     *
     * @param _World
     */
    void CreatePlayer(World *_World)
    {
        Entity *entity = _World->CreateEntity("Player");

        entity->AddComponent<Health>(1);
        entity->AddComponent<ScriptComponent>().Get().Bind<Player>();
        entity->AddComponent<Animation>(1.0f, 2.0f, 1.0f);
        entity->GetComponent<TransformComponent>().Get().Scale.y = 0.5f;
        entity->AddComponent<BoxCollider2DComponent>();
        auto sprite = entity->AddComponent<SpriteRendererComponent>();

        // Set entity sprite
        Ref<Texture2D> texture = TextureImporter::LoadTexture2D("Assets/Textures/Player.png");
        sprite.Get().Texture = SubTexture2D::CreateFromCoords(texture, { 2.0f, 4.0f }, { 33.2f, 17.2f }, { 1.0f, 1.0f });

        // Set entity rigidbody
        auto body = entity->AddComponent<RigidBody2DComponent>();

        body.Get().Type = RigidBody2DComponent::BodyType::Dynamic;
        body.Get().Mass = 0.0f;
        body.Get().GravityScale = 0.0f;
        body.Get().Velocity = glm::vec2{ 0.0f, 0.0f };
    };
};

#endif /* !CREATEPLAYER_HPP_ */
