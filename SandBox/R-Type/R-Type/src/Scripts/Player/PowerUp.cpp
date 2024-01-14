/*
** EPITECH PROJECT, 2023
** $
** File description:
** PowerUp
*/

#include "PowerUp.hpp"
#include "Event/TakeDamage.hpp"

using namespace Exodia;

namespace RType {

    void PowerUp::CreateAnimations() {
        AnimationComponent anim;

        std::vector<Ref<SubTexture2D>> framesIdle;

        for (int i = 0; i < 6; i++)
            framesIdle.push_back(
                SubTexture2D::CreateFromCoords(POWERUP, {120 + ((27 + 3) * i), 775.0f}, {1.0f, 1.0f}, {27.0f, 22.0f}));

        anim.Frames = framesIdle;
        anim.IsPlaying = true;
        anim.Repeat = true;
        anim.FrameRate = TimeBetweenAnimations;

        _Animations.push_back(anim);

        HandleEntity.AddComponent<AnimationComponent>(anim);
    }

    void PowerUp::OnCreate() {
        EXODIA_INFO("PowerUp created");
        HandleEntity.AddComponent<BoxCollider2DComponent>();

        RigidBody2DComponent &rb = HandleEntity.AddComponent<RigidBody2DComponent>();

        rb.Type = RigidBody2DComponent::BodyType::Dynamic;
        rb.Mass = 0.0f;
        rb.GravityScale = 0.0f;
        rb.Velocity.x = 0.0f;

        CreateAnimations();

        TransformComponent &tc = GetComponent<TransformComponent>();

        Scene *scene = HandleEntity.GetScene();

        if (!scene) {
            EXODIA_ERROR("No scene found");
            return;
        }
        GameObject camera = scene->GetPrimaryCamera();

        if (!camera) {
            EXODIA_ERROR("No camera found");
            return;
        }
        TransformComponent &cameraTC = camera.GetComponent<TransformComponent>();

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dis(0.0f, 1.0f);

        SpriteRendererComponent &sprite = HandleEntity.AddComponent<SpriteRendererComponent>();

        sprite.Texture = _Animations[0].Frames[0];

        // The module is created out of the camera's view, on the left
        tc.Translation.x = 5.0f;
        tc.Translation.y = dis(gen);

        tc.Scale.x = 0.5f;
        tc.Scale.y = 0.5f;

        EXODIA_INFO("PowerUp created at pos {0}, {1}", tc.Translation.x, tc.Translation.y);
    }

    void PowerUp::OnKeyPressed(int keycode) {
        // -- Simple Attack
        if (keycode == Key::SPACE && !_IsAttacking) {
            Shoot();
        }
    }

    void PowerUp::OnKeyReleased(int keycode) {
        if (keycode == Key::SPACE && _IsAttacking) {
            _IsAttacking = false;
        }
    }

    void PowerUp::OnUpdate(Timestep ts) { (void)ts; }

    void PowerUp::Shoot() {
        Scene *scene = HandleEntity.GetScene();

        if (!scene)
            return;
        GameObject bullet = scene->LoadPrefabs(
            (Project::GetActiveAssetDirectory() / "Prefabs/Bullets/BulletPlayer.prefab").string(), true);

        bullet.GetComponent<TagComponent>().Tag = "BP";
        auto &bulletID = bullet.GetComponent<IDComponent>();

        bullet.AddComponent<ParentComponent>().Parent = GetComponent<IDComponent>().ID;
        GetComponent<ChildrenComponent>().Children.push_back(bulletID.ID);

        auto &bulletTC = bullet.GetComponent<TransformComponent>();
        auto &tc = GetComponent<TransformComponent>();

        bulletTC.Translation.x = tc.Translation.x + 0.7f;
        bulletTC.Translation.y = tc.Translation.y - 0.05f;

        _IsAttacking = true;
    }

    void PowerUp::OnCollisionEnter(Entity *entity) {
        if (HandleEntity.HasComponent<ParentComponent>())
            return;
        if (entity->HasComponent<TagComponent>() &&
            entity->GetComponent<TagComponent>().Get().Tag.rfind("Player", 0) == 0) {
            EXODIA_INFO("PowerUp attached to player");
            if (entity->HasComponent<ParentComponent>()) {
                ParentComponent &PP = entity->GetComponent<ParentComponent>().Get();

                GameObject controller = HandleEntity.GetScene()->GetEntityByUUID(PP.Parent);
                if (!controller) {
                    EXODIA_ERROR("No controller found");
                    return;
                }

                if (controller.HasComponent<ChildrenComponent>()) {
                    auto &tc = GetComponent<TransformComponent>();
                    auto &playerTC = entity->GetComponent<TransformComponent>().Get();

                    tc.Translation.x = playerTC.Translation.x + 0.65f;
                    tc.Translation.y = playerTC.Translation.y;
                    ChildrenComponent &children = controller.GetComponent<ChildrenComponent>();

                    children.AddChild(HandleEntity.GetUUID());
                    auto &parent = GetComponent<ParentComponent>();
                    parent.Parent = controller.GetUUID();
                }
            }
        }
    }

} // namespace RType