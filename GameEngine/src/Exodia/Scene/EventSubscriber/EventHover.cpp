/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** EventHover
*/

#include "EventHover.hpp"
#include "Scene/Components/Components.hpp"

namespace Exodia {

    /////////////
    // Methods //
    /////////////

    void EventHover::Receive(World *world, const Events::OnHoveredEnter &event) {
        if (event.Entity->HasComponent<ScriptComponent>()) {
            auto &script = event.Entity->GetComponent<ScriptComponent>().Get();

            if (script.Instance != nullptr)
                script.Instance->OnHoveredEnter();
        }
    }

    void EventHover::Receive(World *world, const Events::OnHoveredExit &event) {
        if (event.Entity->HasComponent<ScriptComponent>()) {
            auto &script = event.Entity->GetComponent<ScriptComponent>().Get();

            if (script.Instance != nullptr)
                script.Instance->OnHoveredExit();
        }
    }

    void EventHover::Receive(World *world, const Events::OnClick &event) {
        if (event.Entity->HasComponent<ScriptComponent>()) {
            auto &script = event.Entity->GetComponent<ScriptComponent>().Get();

            if (script.Instance != nullptr)
                script.Instance->OnClick();
        }
    }
}; // namespace Exodia
