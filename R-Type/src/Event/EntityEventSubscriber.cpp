/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** EntityEventSubscriber
*/

#include "EntityEventSubscriber.hpp"

namespace RType {

    /////////////
    // Methods //
    /////////////

    void EntityEventSubscriber::Receive(UNUSED(Exodia::World *world),
                                        UNUSED(const Exodia::Events::OnEntityCreated &event)) {
        // TODO: Send the entity to the server
        // TODO: Server must send the entity to all clients
        EXODIA_INFO("Entity created !");
    }

    void EntityEventSubscriber::Receive(UNUSED(Exodia::World *world), const Exodia::Events::OnEntityDestroyed &event) {
        EXODIA_INFO("Entity destroyed !");

        _Network.SendDeleteEntity(event.Entity);
    }
}; // namespace RType
