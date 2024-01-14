/*
** EPITECH PROJECT, 2023
** $
** File description:
** BulletEnemy
*/

#include "BulletEnemy.hpp"

using namespace Exodia;

namespace RType {

    static float distanceBetweenEntities(const glm::vec3 &pos1, const glm::vec3 &pos2) {
        return glm::length(pos2 - pos1);
    }

    //////////////////////////////
    // Constructor & Destructor //
    //////////////////////////////

    void BulletEnemy::OnCreate() {
        // -- Instantiate Bullet Animations
        CreateAnimations();

        // -- Instantiate Bullet RigidBody
        Scene *scene = HandleEntity.GetScene();

        if (!scene)
            return;

        std::vector<Entity *> players;

        scene->ForEach<ScriptComponent>([&](Entity *entity, auto script) {
            if (script.Get().Name == "Player")
                players.push_back(entity);
        });

        auto &bulletRBC = GetComponent<RigidBody2DComponent>();
        auto &bulletTC = GetComponent<TransformComponent>();

        if (players.size() != 0) {
            TransformComponent nearTC;

            for (auto &player : players) {
                auto playerTC = player->GetComponent<TransformComponent>();

                if (!playerTC)
                    continue;

                float distance = distanceBetweenEntities(playerTC.Get().Translation, bulletTC.Translation);

                if (distance < distanceBetweenEntities(nearTC.Translation, bulletTC.Translation))
                    nearTC = playerTC.Get();
            }

            float delta_x = nearTC.Translation.x - bulletTC.Translation.x;
            float delta_y = nearTC.Translation.y - bulletTC.Translation.y;

            // Calcul of the velocity magnitude
            float velocityMagnitude = std::sqrt(delta_x * delta_x + delta_y * delta_y);

            // Calcul of the velocity vector
            if (velocityMagnitude > 0.0f) {
                bulletRBC.Velocity.x = (delta_x / velocityMagnitude) * _Speed;
                bulletRBC.Velocity.y = (delta_y / velocityMagnitude) * _Speed;
            }
        } else {
            bulletRBC.Velocity.x = -_Speed;
            bulletRBC.Velocity.y = 0.0f;
        }
    }

    /////////////
    // Methods //
    /////////////

    void BulletEnemy::OnUpdate(UNUSED(Timestep ts)) {
        Scene *scene = HandleEntity.GetScene();

        if (!scene)
            return;
        UpdateAnimations();

        GameObject camera = scene->GetPrimaryCamera();

        if (!camera.GetEntity())
            return;

        TransformComponent &cameraTC = camera.GetComponent<TransformComponent>();
        TransformComponent &tc = GetComponent<TransformComponent>();

        // -- Bullet out of screen (Destroy it)
        if (tc.Translation.x < cameraTC.Translation.x - 12.0f)
            scene->GetWorldPtr()->DestroyEntity(HandleEntity.GetEntity());
    }

    void BulletEnemy::CreateAnimations() {
        AnimationComponent anim;
        AnimationComponent destroy;

        std::vector<Ref<SubTexture2D>> framesIdle;
        std::vector<Ref<SubTexture2D>> framesDestroy;

        for (int i = 0; i < 4; i++)
            framesIdle.push_back(
                SubTexture2D::CreateFromCoords(BULLET, {8 + i, 9.0f}, {16.6666666667f, 17.0f}, {1.0f, 1.0f}));

        anim.Frames = framesIdle;
        anim.IsPlaying = true;
        anim.Repeat = true;
        anim.FrameRate = TimeBetweenAnimations;

        for (int i = 0; i < 5; i++)
            framesDestroy.push_back(
                SubTexture2D::CreateFromCoords(BULLET, {7 + i, 8.0f}, {16.6666666667f, 17.0f}, {1.0f, 1.0f}));

        destroy.Frames = framesDestroy;
        destroy.IsPlaying = false;
        destroy.Repeat = false;
        destroy.FrameRate = TimeBetweenAnimations;

        _Animations.push_back(anim);
        _Animations.push_back(destroy);
    }

    void BulletEnemy::UpdateAnimations() {
        SpriteRendererComponent &sprite = GetComponent<SpriteRendererComponent>();
        ComponentHandle<AnimationComponent> anim = HandleEntity.GetEntity()->GetComponent<AnimationComponent>();

        if (!anim) {
            _Animations[0].IsPlaying = true;
            _Animations[1].IsPlaying = false;

            anim = HandleEntity.GetEntity()->AddComponent<AnimationComponent>(_Animations[0]);

            sprite.Texture = anim.Get().Frames[0];
        } else {
            auto &ac = anim.Get();

            if (_IsColliding && _Animations[1].IsPlaying == false) {
                _Animations[0].IsPlaying = false;
                _Animations[1].IsPlaying = true;

                ac = _Animations[1];
                sprite.Texture = ac.Frames[0];
            }

            if (_IsColliding && ac.CurrentFrameIndex == ac.Frames.size() - 1 && _Animations[1].IsPlaying == true)
                HandleEntity.GetScene()->DestroyEntity(HandleEntity);
        }
    }

    void BulletEnemy::OnCollisionEnter(Entity *entity) {
        ComponentHandle<TagComponent> tag = entity->GetComponent<TagComponent>();

        if (!tag)
            return;
        auto &tagC = tag.Get();

        // -- If Obstacle is a Pata-Pata ignore collision
        if (tagC.Tag.rfind("Pata", 0) == 0)
            return;

        // -- If Entity have a life component, remove life
        // TODO: ...

        // -- Stop the bullet and launch the destroy animation
        RigidBody2DComponent &body = GetComponent<RigidBody2DComponent>();

        body.Velocity = {0.0f, 0.0f};
        _IsColliding = true;
    }
}; // namespace RType
