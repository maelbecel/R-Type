/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** FadeSystem
*/

// R-Type includes
#include "FadeSystem.hpp"
#include "Components/Fade.hpp"
#include "Components/Clock.hpp"

// Exodia includes
#include "Exodia.hpp"

namespace RType {

    using namespace Exodia;

    /////////////
    // Methods //
    /////////////

    void FadeSystem::Update(Exodia::World *world, Exodia::Timestep ts) {
        world->ForEach<FadeComponent>([&](Entity *entity, ComponentHandle<FadeComponent> fade) {
            FadeComponent &fc = fade.Get(); // fc = Fade Component

            if (fc.shouldFadeIn) {
                fc.Opacity += fc.FadeInSpeed * ts;

                if (fc.Opacity >= 1.0f) {
                    fc.Opacity = 1.0f;

                    fc.shouldFadeIn = false;
                    fc.shouldFadeOut = true;
                }
            } else if (fc.shouldFadeOut) {
                fc.Opacity -= fc.FadeOutSpeed * ts;

                if (fc.Opacity <= 0.0f) {
                    fc.Opacity = 0.0f;

                    fc.shouldFadeOut = false;
                    fc.shouldFadeIn = true;
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
