/*
** EPITECH PROJECT, 2023
** ECS
** File description:
** Entity
*/

#ifndef ENTITY_HPP_
#define ENTITY_HPP_

// Exodia ECS Component includes
#include "Component/ComponentHandle.hpp"

// Exodia ECS Internal includes
#include "Interface/IComponentContainer.hpp"

// Exodia ECS Utils includes
#include "Utils/TypeIndex.hpp"

// Exodia Utils includes
#include "Exodia-Utils.hpp"

// External includes
#include <unordered_map>
#include <functional>
#include <cstdint>

namespace Exodia {

    class World;

    class Entity {

        /////////////
        // Defines //
        /////////////
      public:
        const static uint64_t InvalidEntityID = 0;

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
      public:
        Entity();
        Entity(World *world, uint64_t id = UUID());

        ~Entity();

        /////////////
        // Methods //
        /////////////
      public:
        template <typename Component, typename... Args> ComponentHandle<Component> AddComponent(Args &&...args);

        void AddComponent(IComponentContainer *component);

        template <typename Component> bool RemoveComponent() {
            auto found = _Components.find(GetTypeName<Component>());

            if (found != _Components.end()) {
                found->second->Removed(this);
                found->second->Destroy(_World);

                _Components.erase(found);

                return true;
            }
            return false;
        }

        bool RemoveComponent(IComponentContainer *component);

        void RemoveAllComponents();

        template <typename... Components>
        bool CallFunctionWithComponents(
            typename std::common_type<std::function<void(ComponentHandle<Components>...)>>::type view) {
            if (!HasComponent<Components...>())
                return false;

            view(GetComponent<Components>()...);
            return true;
        }

        Entity *Duplicate(World *world, UUID uuid, const std::string &name);

        ///////////////////////
        // Getters & Setters //
        ///////////////////////
      public:
        World *GetWorld() const;
        void SetWorld(World *world);

        template <typename Component> bool HasComponent() const {
            std::string index = GetTypeName<Component>();

            return _Components.find(index) != _Components.end();
        }

        template <typename Required, typename Additional, typename... Remaining> bool HasComponent() const {
            return HasComponent<Required>() && HasComponent<Additional, Remaining...>();
        }

        template <typename Component> ComponentHandle<Component> GetComponent();

        IComponentContainer *GetComponent(const std::string &index);

        std::vector<IComponentContainer *> GetAllComponents();

        void SetComponent(const std::string &index, IComponentContainer *component);

        uint64_t GetEntityID() const;

        bool IsPendingDestroy() const;

        void SetPendingDestroy(bool pendingDestroy);

        /////////////////
        // Comparators //
        /////////////////
      public:
        bool operator==(const Entity &other) const;
        bool operator!=(const Entity &other) const;
        operator bool() const;

        ////////////////
        // Attributes //
        ////////////////
      private:
        World *_World;
        uint64_t _ID;
        bool _PendingDestroy;

        std::unordered_map<std::string, IComponentContainer *> _Components;

        /////////////
        // Friends //
        /////////////

        friend class World;
    };
}; // namespace Exodia

#endif /* !ENTITY_HPP_ */
