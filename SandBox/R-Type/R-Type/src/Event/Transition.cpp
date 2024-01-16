/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Transition
*/

#include "Transition.hpp"

namespace RType {

    using namespace Exodia;

    /////////////
    // Methods //
    /////////////

    void Transition::Receive(UNUSED(World *world), UNUSED(const Events::FadeOutEndEvent &event))
    {
        auto tag = event.Entity->GetComponent<TagComponent>();

        if (!tag)
            return;
        auto &tc = tag.Get(); // tc = Tag component

        if (tc.Tag == "LoadingBackground") {};
    }
};
