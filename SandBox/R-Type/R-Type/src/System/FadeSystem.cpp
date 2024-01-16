/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** FadeSystem
*/

// R-Type includes
#include "FadeSystem.hpp"
#include "Component/Fade.hpp"
#include "Event/FadeEvent.hpp"

// Exodia includes
#include "Exodia.hpp"

namespace RType {

    using namespace Exodia;

    /////////////
    // Methods //
    /////////////

    void FadeSystem::Update(World *world, Timestep ts) {
        world->ForEach<FadeComponent>([&](Entity *entity, ComponentHandle<FadeComponent> fade) {
            FadeComponent &fc = fade.Get(); // fc = Fade Component

            if (fc.ShouldFadeIn) {
                fc.Opacity += fc.FadeInSpeed * ts;

                if (fc.Opacity >= 1.0f) {
                    fc.Opacity = 1.0f;

                    if (!fc.Repeat) {
                        fc.ShouldFadeIn = false;
                        fc.ShouldFadeOut = false;
                    } else {
                        fc.ShouldFadeIn = false;
                        fc.ShouldFadeOut = true;
                    }
                }
            } else if (fc.ShouldFadeOut) {
                fc.Opacity -= fc.FadeOutSpeed * ts;

                if (fc.Opacity <= 0.0f) {
                    fc.Opacity = 0.0f;

                    if (!fc.Repeat) {
                        fc.ShouldFadeIn = false;
                        fc.ShouldFadeOut = false;

                        world->Emit<Events::FadeOutEndEvent>({entity});
                    } else {
                        fc.ShouldFadeOut = false;
                        fc.ShouldFadeIn = true;
                    }
                }
            }

            auto sprite = entity->GetComponent<SpriteRendererComponent>();
            auto circle = entity->GetComponent<CircleRendererComponent>();
            auto text = entity->GetComponent<TextRendererComponent>();

            if (sprite)
                sprite.Get().Color.w = fc.Opacity;
            if (circle)
                circle.Get().Color.w = fc.Opacity;
            if (text)
                text.Get().Color.w = fc.Opacity;
        });
    }
}; // namespace RType
