/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** EntityEventSubscriber
*/

#include "EntityEventSubscriber.hpp"

namespace RType {

    using namespace Exodia;

    /////////////
    // Methods //
    /////////////

    void EntityEventSubscriber::Receive(UNUSED(World *world), const Events::OnEntityCreated &event) {
        for (auto *component : event.Entity->GetAllComponents()) {
            std::string name = component->GetTypeIndexOfComponent().name();
            std::string typeIndex = extractTypeName(name.c_str());


            if (typeIndex == "SpriteRendererComponent")
                continue;
            _Network.SendComponentOf(event.Entity, typeIndex);
        }
        if (event.Entity->GetComponent<SpriteRendererComponent>())
            _Network.SendComponentOf(event.Entity, "SpriteRendererComponent");
    }

    void EntityEventSubscriber::Receive(UNUSED(World *world), const Events::OnEntityDestroyed &event) {
        auto tag = event.Entity->GetComponent<TagComponent>();

        if (tag) {
            auto &tagValue = tag.Get();

            EXODIA_INFO("Entity destroyed '{0}'", tagValue.Tag);
        } else
            EXODIA_INFO("Entity destroyed");

        _Network.SendDeleteEntity(event.Entity);
    }
}; // namespace RType
