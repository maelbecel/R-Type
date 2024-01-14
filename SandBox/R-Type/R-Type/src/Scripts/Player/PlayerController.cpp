/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** PlayerController
*/

#include "PlayerController.hpp"
#include "Scripts/Player/Player.hpp"

namespace RType {

    using namespace Exodia;

    /////////////
    // Methods //
    /////////////

    void PlayerController::OnUpdate(Timestep ts) {
        if (GetPlayerState() == PlayerState::DEAD) {
            for (auto &children : GetComponent<ChildrenComponent>().Children) {
                auto child = HandleEntity.GetScene()->GetEntityByUUID(children);

                if (!child.GetEntity())
                    continue;
                auto &childRBC = child.GetComponent<RigidBody2DComponent>();

                childRBC.Velocity.x = 0.0f;
                childRBC.Velocity.y = 0.0f;

                auto script = child.GetEntity()->GetComponent<ScriptComponent>();

                if (script && script.Get().Name == "Player")
                    continue;
                HandleEntity.GetScene()->DestroyEntity(child);
            }
        } else {
            for (auto &children : GetComponent<ChildrenComponent>().Children) {
                auto child = HandleEntity.GetScene()->GetEntityByUUID(children);
                if (child.GetComponent<TagComponent>().Tag == "Module" && !_IsAttached) {
                    _IsAttached = true;
                }
            }
        }
    }

    void PlayerController::OnKeyPressed(int keycode) {
        for (auto &children : GetComponent<ChildrenComponent>().Children) {
            auto child = HandleEntity.GetScene()->GetEntityByUUID(children);

            if (!child.GetEntity())
                continue;
            auto &childRBC = child.GetComponent<RigidBody2DComponent>();

            if (keycode == Key::A)
                childRBC.Velocity.x = -_Speed;
            else if (keycode == Key::D)
                childRBC.Velocity.x = _Speed;
            else if (keycode == Key::W) {
                childRBC.Velocity.y = _Speed;

                SetPlayerState(child, PlayerState::MOVE_UP);
            } else if (keycode == Key::S) {
                childRBC.Velocity.y = -_Speed;

                SetPlayerState(child, PlayerState::MOVE_DOWN);
            } else if (keycode == Key::E) {
                if (_IsAttached) {
                    if (child.GetComponent<TagComponent>().Tag == "Module") {
                        child.RemoveComponent<ParentComponent>();

                        GetComponent<ChildrenComponent>().Children.erase(
                            std::remove(GetComponent<ChildrenComponent>().Children.begin(),
                                        GetComponent<ChildrenComponent>().Children.end(),
                                        child.GetEntity()->GetEntityID()),
                            GetComponent<ChildrenComponent>().Children.end());
                        _IsAttached = false;
                    }
                }
            }
        }
    }

    void PlayerController::OnKeyReleased(int keycode) {
        for (auto &children : GetComponent<ChildrenComponent>().Children) {
            auto child = HandleEntity.GetScene()->GetEntityByUUID(children);

            if (!child.GetEntity())
                continue;
            auto &childRBC = child.GetComponent<RigidBody2DComponent>();

            if (keycode == Key::A || keycode == Key::D)
                childRBC.Velocity.x = 0.0f;
            if (keycode == Key::W || keycode == Key::S) {
                childRBC.Velocity.y = 0.0f;

                SetPlayerState(child, PlayerState::IDLE);
            }
        }
    }

    ///////////////////////
    // Getters & Setters //
    ///////////////////////

    void PlayerController::SetPlayerState(GameObject player, PlayerState state) {
        // Check if the player have a script component
        auto script = player.GetEntity()->GetComponent<ScriptComponent>();

        if (!script)
            return;
        auto &sc = script.Get();

        // Check if the script is a Player
        if (sc.Name == "Player" && sc.Instance) {
            auto *player = dynamic_cast<Player *>(sc.Instance);

            if (player)
                player->SetState(state);
        }
    }

    PlayerState PlayerController::GetPlayerState() {
        for (auto &children : GetComponent<ChildrenComponent>().Children) {
            auto child = HandleEntity.GetScene()->GetEntityByUUID(children);

            if (!child.GetEntity())
                continue;
            auto script = child.GetEntity()->GetComponent<ScriptComponent>();

            if (!script)
                continue;
            auto &sc = script.Get();

            if (sc.Name == "Player" && sc.Instance) {
                auto *player = dynamic_cast<Player *>(sc.Instance);

                if (player)
                    return player->GetState();
            }
        }

        return PlayerState::DEAD;
    }
}; // namespace RType
