/*
** EPITECH PROJECT, 2023
** ECS
** File description:
** Entity
*/

#ifndef ENTITY_HPP_
    #define ENTITY_HPP_

    // Exodia Core includes
    #include "Core/ID/UUID.hpp"

    // Exodia ECS Component includes
    #include "Component/ComponentHandle.hpp"

    // Exodia ECS Internal includes
    #include "Interface/IComponentContainer.hpp"

    // Exodia ECS Utils includes
    #include "Utils/TypeIndex.hpp"

    // Exodia Utils includes
    #include "Utils/CrossPlatform.hpp"
    #include "Utils/Memory.hpp"

    // External includes
    #include <unordered_map>
    #include <functional>
    #include <cstdint>

namespace Exodia {

    class World;

    class EXODIA_API Entity {

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

            template<typename Component, typename ...Args>
            ComponentHandle<Component> AddComponent(Args && ...args);

            template<typename Component>
            bool RemoveComponent()
            {
                auto found = _Components.find(GetTypeIndex<Component>());

                if (found != _Components.end()) {
                    found->second->Removed(this);
                    found->second->Destroy(_World);

                    _Components.erase(found);

                    return true;
                }
                return false;
            }

            void RemoveAllComponents();

            template<typename ...Components>
            bool CallFunctionWithComponents(typename std::common_type<std::function<void(ComponentHandle<Components>...)>>::type view)
            {
                if (!HasComponent<Components ...>())
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

            template<typename Component>
            bool HasComponent() const
            {
                TypeIndex index = GetTypeIndex<Component>();

                return _Components.find(index) != _Components.end();
            }

            template<typename Required, typename Additional, typename... Remaining>
            bool HasComponent() const
            {
                return HasComponent<Required>() && HasComponent<Additional, Remaining...>();
            }

            template<typename Component>
            ComponentHandle<Component> GetComponent();

            std::vector<IComponentContainer *> GetAllComponents();

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
            uint64_t   _ID;
            bool       _PendingDestroy;

            std::unordered_map<TypeIndex, IComponentContainer *> _Components;

        /////////////
        // Friends //
        /////////////

        friend class World;
    };
};

#endif /* !ENTITY_HPP_ */
