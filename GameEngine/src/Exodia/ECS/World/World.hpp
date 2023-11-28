/*
** EPITECH PROJECT, 2023
** ECS
** File description:
** World
*/

#ifndef WORLD_HPP_
    #define WORLD_HPP_

    // Exodia Core includes
    #include "Exodia/Core/Time/Timestep.hpp"

    // Exodia ECS Entity includes
    #include "Entity/Entity.hpp"
    #include "Entity/EntityComponentView.hpp"
    #include "Entity/EntityView.hpp"

    // Exodia ECS Interface includes
    #include "Interface/EntitySystem.hpp"
    #include "Interface/IEventSubscriber.hpp"
    #include "Interface/EventSubscriber.hpp"

    // Exodia Utils includes
    #include "Utils/CrossPlatform.hpp"

    // External includes
    #include <unordered_map>
    #include <functional>
    #include <cstdint>
    #include <vector>

namespace Exodia {

    class EXODIA_API World {

        /////////////
        // Defines //
        /////////////
        public:
            using WorldAllocator = std::allocator_traits<Allocator>::template rebind_alloc<World>;

            using SystemAllocator    = std::allocator_traits<Allocator>::template rebind_alloc<EntitySystem>;
            using SystemPtrAllocator = std::allocator_traits<Allocator>::template rebind_alloc<EntitySystem *>;

            using EntityAllocator    = std::allocator_traits<Allocator>::template rebind_alloc<Entity>;
            using EntityPtrAllocator = std::allocator_traits<Allocator>::template rebind_alloc<Entity *>;

            using SubscriberPtrAllocator  = std::allocator_traits<Allocator>::template rebind_alloc<IEventSubscriber *>;
            using SubscriberPairAllocator = std::allocator_traits<Allocator>::template rebind_alloc<std::pair<const TypeIndex, std::vector<IEventSubscriber *, SubscriberPtrAllocator>>>;
        
        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
        public:

            World(Allocator allocator);

            ~World();

        /////////////
        // Methods //
        /////////////
        public:

            static World *CreateWorld(Allocator allocator = Allocator());

            void DestroyWorld();

            Entity *CreateEntity();

            void DestroyEntity(Entity *entity, bool immediate = false);

            bool CleanUp();
            void Reset();

            EntitySystem *RegisterSystem(EntitySystem *system);
            void UnregisterSystem(EntitySystem *system);
            void EnableSystem(EntitySystem *system);
            void DisableSystem(EntitySystem *system);

            template<typename Event>
            void Subscribe(EventSubscriber<Event> *subscriber)
            {
                TypeIndex index = GetTypeIndex<Event>();

                auto found = _Subscribers.find(index);

                if (found == _Subscribers.end()) {
                    std::vector<IEventSubscriber *, SubscriberPtrAllocator> subscriberList(_EntityAllocator);

                    subscriberList.push_back(subscriber);

                    _Subscribers.insert({ index, subscriberList });
                    return;
                }
                found->second.push_back(subscriber);
            }

            template<typename Event>
            void Unsubscribe(EventSubscriber<Event> *subscriber)
            {
                auto found = _Subscribers.find(GetTypeIndex<Event>());

                if (found != _Subscribers.end()) {
                    found->second.erase(std::remove(found->second.begin(), found->second.end(), subscriber), found->second.end());

                    if (found->second.size() == 0)
                        _Subscribers.erase(found);
                }
            }

            void UnsubscribeAll(void *subscriber);

            template<typename Event>
            void Emit(const Event &event)
            {
                auto found = _Subscribers.find(GetTypeIndex<Event>());

                if (found != _Subscribers.end()) {
                    for (auto *base : found->second) {
                        auto *sub = reinterpret_cast<EventSubscriber<Event> *>(base);

                        sub->Receive(this, event);
                    }
                }
            }

            template<typename ...Entities>
            void ForEach(typename std::common_type<std::function<void(Entity*, ComponentHandle<Entities>...)>>::type function, bool includePendingDestroy = false)
            {
                for (auto *entity : View<Entities ...>(includePendingDestroy))
                    function(entity, entity->template GetComponent<Entities>()...);
            }

            void ForAll(std::function<void(Entity *)> function, bool includePendingDestroy = false);

            template<typename ...Components>
            EntityComponentView<Components ...> View(bool includePendingDestroy = false)
            {
                EntityComponentIterator<Components ...> first(this, 0, false, includePendingDestroy);
                EntityComponentIterator<Components ...> last(this, GetCount(), true, includePendingDestroy);

                return EntityComponentView<Components ...>(first, last);
            }

            EntityView AllEntities(bool includePendingDestroy = false);

            void Update(Timestep ts);

        ///////////////////////
        // Getters & Setters //
        ///////////////////////
        public:

            size_t GetCount() const;

            Entity *GetEntityByIndex(size_t index);

            Entity *GetEntityByID(uint64_t id) const;

            EntityAllocator &GetPrimaryAllocator();

        ////////////////
        // Attributes //
        ////////////////
        private:
            EntityAllocator _EntityAllocator;
            SystemAllocator _SystemAllocator;

            std::vector<Entity       *, EntityPtrAllocator> _Entities;
            std::vector<EntitySystem *, SystemPtrAllocator> _Systems;
            std::vector<EntitySystem *>                     _DisabledSystems;

            std::unordered_map<TypeIndex, std::vector<IEventSubscriber *, SubscriberPtrAllocator>, std::hash<TypeIndex>, std::equal_to<TypeIndex>, SubscriberPairAllocator> _Subscribers;

            uint64_t _LastEntityID;
    };

};

#endif /* !WORLD_HPP_ */
