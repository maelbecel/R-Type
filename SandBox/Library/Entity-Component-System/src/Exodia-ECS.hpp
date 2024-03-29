/*
** EPITECH PROJECT, 2023
** ECS
** File description:
** ECS
*/

#ifndef EXODIA_ECS_HPP_
#define EXODIA_ECS_HPP_

// -- Exodia ECS Component -------------------------------------------------

#include "Component/ComponentHandle.hpp"
#include "Component/ComponentContainer.hpp"

// -- Exodia ECS Entity ----------------------------------------------------

#include "Entity/EntityIterator.hpp"
#include "Entity/EntityView.hpp"
#include "Entity/EntityComponentView.hpp"
#include "Entity/EntityComponentIterator.hpp"
#include "Entity/Entity.hpp"

// -- Exodia ECS World -----------------------------------------------------

#include "World/World.hpp"

// -- Exodia ECS Events ----------------------------------------------------

#include "Events/Events.hpp"

// -- Exodia ECS Interface -------------------------------------------------

#include "Interface/IComponentContainer.hpp"
#include "Interface/IEventSubscriber.hpp"
#include "Interface/EventSubscriber.hpp"
#include "Interface/EntitySystem.hpp"

// -- Exodia ECS Utils -----------------------------------------------------

#include "Utils/TypeIndex.hpp"

// -------------------------------------------------------------------------

#include "Exodia-Debug.hpp"

#include <iostream>

namespace Exodia {

    /////////////////////////////////////////////////////////////////////////////////
    // ----- This part is the implementation of the templates declared above ----- //
    //      ---- It's here because that cause a lot of errors if it's not ----     //
    /////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////////
    // -- Exodia ECS Entity CPP ------------------------------------------------ //
    ///////////////////////////////////////////////////////////////////////////////

    template <typename Component, typename... Args> ComponentHandle<Component> Entity::AddComponent(Args &&...args) {
        using ComponentAllocator =
            std::allocator_traits<World::EntityAllocator>::template rebind_alloc<ComponentContainer<Component>>;

        auto found = _Components.find(GetTypeName<Component>());

        if (found != _Components.end()) {
            ComponentContainer<Component> *container = reinterpret_cast<ComponentContainer<Component> *>(found->second);

            container->Data = Component(args...);

            auto handle = ComponentHandle<Component>(&container->Data);

            _World->Emit<Events::OnComponentAdded<Component>>({this, handle});

            return handle;
        } else {
            ComponentAllocator allocator(_World->GetPrimaryAllocator());

            ComponentContainer<Component> *container =
                std::allocator_traits<ComponentAllocator>::allocate(allocator, 1);

            std::allocator_traits<ComponentAllocator>::construct(allocator, container, Component(args...));

            _Components.insert({GetTypeName<Component>(), container});

            auto handle = ComponentHandle<Component>(&container->Data);

            _World->Emit<Events::OnComponentAdded<Component>>({this, handle});

            return handle;
        }
    }

    template <typename Component> ComponentHandle<Component> Entity::GetComponent() {
        auto found = _Components.find(GetTypeName<Component>());

        if (found == _Components.end() || found->second == nullptr)
            return ComponentHandle<Component>();
        return ComponentHandle<Component>(&reinterpret_cast<ComponentContainer<Component> *>(found->second)->Data);
    }

    ///////////////////////////////////////////////////////////////////////////////
    // -- Exodia Entity Component Iterator CPP --------------------------------- //
    ///////////////////////////////////////////////////////////////////////////////

    template <typename... Components>
    EntityComponentIterator<Components...>::EntityComponentIterator(World *world, size_t index, bool isEnd,
                                                                    bool includePendingDestroy)
        : _World(world), _Index(index), _IsEnd(isEnd), _IncludePendingDestroy(includePendingDestroy) {
        if (_Index >= _World->GetCount())
            this->_IsEnd = true;
    }

    template <typename... Components> bool EntityComponentIterator<Components...>::IsEnd() const {
        return _IsEnd || _Index >= _World->GetCount();
    }

    template <typename... Components> Entity *EntityComponentIterator<Components...>::Get() const {
        if (IsEnd())
            return nullptr;
        return _World->GetEntityByIndex(_Index);
    }

    template <typename... Components>
    EntityComponentIterator<Components...> &EntityComponentIterator<Components...>::operator++() {
        _Index++;

        for (; _Index < _World->GetCount() && (Get() == nullptr || !Get()->template HasComponent<Components...>() ||
                                               (Get()->IsPendingDestroy() && !_IncludePendingDestroy));
             _Index++)
            ;

        if (_Index >= _World->GetCount())
            _IsEnd = true;
        return *this;
    }
}; // namespace Exodia

#endif /* !EXODIA_ECS_HPP_ */
