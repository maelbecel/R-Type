/*
** EPITECH PROJECT, 2023
** $
** File description:
** Module
*/

#include "Module.hpp"
#include "Event/TakeDamage.hpp"

using namespace Exodia;

namespace RType {

    void Module::CreateAnimations() {
        AnimationComponent anim;

        std::vector<Ref<SubTexture2D>> framesIdle;

        for (int i = 0; i < 6; i++)
            framesIdle.push_back(
                SubTexture2D::CreateFromCoords(MODULE, {159 + (24 * i), 815.0f}, {1.0f, 1.0f}, {20.0f, 16.0f}));

        anim.Frames = framesIdle;
        anim.IsPlaying = true;
        anim.Repeat = true;
        anim.FrameRate = TimeBetweenAnimations;

        _Animations.push_back(anim);

        HandleEntity.AddComponent<AnimationComponent>(anim);
    }

    void Module::OnCreate() {
        HandleEntity.AddComponent<BoxCollider2DComponent>();

        RigidBody2DComponent &rb = HandleEntity.AddComponent<RigidBody2DComponent>();

        rb.Type = RigidBody2DComponent::BodyType::Dynamic;
        rb.Mass = 0.0f;
        rb.GravityScale = 0.0f;
        rb.Velocity.x = 0.0f;

        CreateAnimations();

        TransformComponent &tc = GetComponent<TransformComponent>();

        Scene *scene = HandleEntity.GetScene();

        if (!scene)
            return;
        GameObject camera = scene->GetPrimaryCamera();

        if (!camera)
            return;
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

        EXODIA_INFO("Module created at pos {0}, {1}", tc.Translation.x, tc.Translation.y);
    }

    void Module::OnKeyPressed(int keycode) {
        // -- Simple Attack
        if (keycode == Key::SPACE && !_IsAttacking) {
            Shoot();
        }
    }

    void Module::OnKeyReleased(int keycode) {
        if (keycode == Key::SPACE && _IsAttacking) {
            _IsAttacking = false;
        }
    }

    void Module::OnUpdate(Timestep ts) { (void)ts; }

    void Module::Shoot() {
        Scene *scene = HandleEntity.GetScene();

        if (!scene)
            return;
        GameObject bullet = scene->LoadPrefabs(
            (Project::GetActiveAssetDirectory() / "Prefabs/Bullets/BulletModule.prefab").string(), true);

        bullet.GetComponent<TagComponent>().Tag = "BP";
        auto &bulletID = bullet.GetComponent<IDComponent>();

        bullet.AddComponent<ParentComponent>().Parent = GetComponent<IDComponent>().ID;
        GetComponent<ChildrenComponent>().Children.push_back(bulletID.ID);

        auto &bulletTC = bullet.GetComponent<TransformComponent>();
        auto &tc = GetComponent<TransformComponent>();

        bullet.AddComponent<Health>(1);

        bulletTC.Translation.x = tc.Translation.x + 0.7f;
        bulletTC.Translation.y = tc.Translation.y - 0.05f;

        _IsAttacking = true;
    }

    void Module::OnCollisionEnter(Entity *entity) {
        if (HandleEntity.HasComponent<ParentComponent>())
            return;
        if (entity->HasComponent<TagComponent>() &&
            entity->GetComponent<TagComponent>().Get().Tag.rfind("Player", 0) == 0) {
            EXODIA_INFO("Module attached to player");
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