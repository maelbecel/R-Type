/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Transition
*/

#include "Transition.hpp"
#include "GameScene/GameScene.hpp"
#include "Layer/GameLayer.hpp"

namespace RType {

    using namespace Exodia;

    /////////////
    // Methods //
    /////////////

    void Transition::Receive(UNUSED(World *world), UNUSED(const Events::FadeOutEndEvent &event)) {
        auto tag = event.Entity->GetComponent<TagComponent>();

        if (!tag)
            return;
        auto &tc = tag.Get(); // tc = Tag component

        if (tc.Tag == "LoadingBackground") {
            Ref<GameLayer> game = GameLayer::GetInstance();

            if (!game)
                return;

            game->SetScene(SceneType::MENU, true);
            return;
        }
    }
}; // namespace RType
