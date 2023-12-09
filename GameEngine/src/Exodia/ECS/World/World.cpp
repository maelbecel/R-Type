/*
** EPITECH PROJECT, 2023
** ECS
** File description:
** World
*/

#include "ECS.hpp"
#include "Exodia/Debug/Logs.hpp"

namespace Exodia {

    //////////////////////////////
    // Constructor & Destructor //
    //////////////////////////////

    World::World(Allocator allocator) : _EntityAllocator(allocator), _SystemAllocator(allocator), _Entities({}, EntityPtrAllocator(allocator)), _Systems({}, SystemPtrAllocator(allocator)), _Subscribers({}, 0, std::hash<TypeIndex>(), std::equal_to<TypeIndex>(), SubscriberPtrAllocator(allocator)) {};

    World::~World()
    {
        for (auto *system : _Systems)
            system->Unconfigure(this);

        for (auto *entity : _Entities) {
            if (!entity->IsPendingDestroy()) {
                entity->SetPendingDestroy(true);

                Emit<Events::OnEntityDestroyed>({ entity });
            }

            std::allocator_traits<EntityAllocator>::destroy(_EntityAllocator, entity);
            std::allocator_traits<EntityAllocator>::deallocate(_EntityAllocator, entity, 1);
        }

        _IndexToUUIDMap.clear();

        for (auto *system : _Systems) {
            std::allocator_traits<SystemAllocator>::destroy(_SystemAllocator, system);
            std::allocator_traits<SystemAllocator>::deallocate(_SystemAllocator, system, 1);
        }
    }

    /////////////
    // Methods //
    /////////////

    World *World::CreateWorld(Allocator allocator)
    {
        WorldAllocator worldAllocator(allocator);

        World *world = std::allocator_traits<WorldAllocator>::allocate(worldAllocator, 1);

        std::allocator_traits<WorldAllocator>::construct(worldAllocator, world, allocator);

        return world;
    }

    void World::DestroyWorld()
    {
        WorldAllocator allocator(_EntityAllocator);

        std::allocator_traits<WorldAllocator>::destroy(allocator, this);
        std::allocator_traits<WorldAllocator>::deallocate(allocator, this, 1);
    }

    Entity *World::CreateNewEntity(const std::string &name)
    {
        Entity *entity = std::allocator_traits<EntityAllocator>::allocate(_EntityAllocator, 1);
        UUID entityID = UUID();

        std::allocator_traits<EntityAllocator>::construct(_EntityAllocator, entity, this, entityID);

        _IndexToUUIDMap[GetCount() + _MergedEntities.size()] = entityID;

        entity->AddComponent<IDComponent>(entityID);
        entity->AddComponent<TransformComponent>();
        auto tag = entity->AddComponent<TagComponent>();

        tag.Get().Tag = name.empty() ? "Entity" : name;

        _MergedEntities.push_back(entity);

        Emit<Events::OnEntityCreated>({ entity });

        return entity;
    }

    Entity *World::CreateNewEntity(const UUID &uuid, const std::string &name)
    {
        Entity *entity = std::allocator_traits<EntityAllocator>::allocate(_EntityAllocator, 1);

        std::allocator_traits<EntityAllocator>::construct(_EntityAllocator, entity, this, uuid);

        _IndexToUUIDMap[GetCount() + _MergedEntities.size()] = uuid;

        entity->AddComponent<IDComponent>(uuid);
        entity->AddComponent<TransformComponent>();
        auto tag = entity->AddComponent<TagComponent>();

        tag.Get().Tag = name.empty() ? "Entity" : name;

        _MergedEntities.push_back(entity);

        Emit<Events::OnEntityCreated>({ entity });

        return entity;
    }

    Entity *World::CreateEntity(const std::string &name)
    {
        Entity *entity = std::allocator_traits<EntityAllocator>::allocate(_EntityAllocator, 1);
        UUID entityID = UUID();

        std::allocator_traits<EntityAllocator>::construct(_EntityAllocator, entity, this, entityID);

        _IndexToUUIDMap[GetCount()] = entityID;

        entity->AddComponent<IDComponent>(entityID);
        entity->AddComponent<TransformComponent>();
        auto tag = entity->AddComponent<TagComponent>();

        tag.Get().Tag = name.empty() ? "Entity" : name;

        _Entities.push_back(entity);

        Emit<Events::OnEntityCreated>({ entity });

        return entity;
    }

    Entity *World::CreateEntity(const UUID &uuid, const std::string &name)
    {
        Entity *entity = std::allocator_traits<EntityAllocator>::allocate(_EntityAllocator, 1);

        std::allocator_traits<EntityAllocator>::construct(_EntityAllocator, entity, this, uuid);

        _IndexToUUIDMap[GetCount()] = uuid;

        entity->AddComponent<IDComponent>(uuid);
        entity->AddComponent<TransformComponent>();
        auto tag = entity->AddComponent<TagComponent>();

        tag.Get().Tag = name.empty() ? "Entity" : name;

        _Entities.push_back(entity);

        Emit<Events::OnEntityCreated>({ entity });

        return entity;
    }

    void World::DestroyEntity(Entity *entity, bool immediate)
    {
        if (entity == nullptr)
            return;

        if (entity->IsPendingDestroy()) {
            if (immediate) {
                _Entities.erase(std::remove(_Entities.begin(), _Entities.end(), entity), _Entities.end());

                _IndexToUUIDMap.erase(_IndexToUUIDMap.find(entity->GetEntityID()));

                SortUUIDMap();

                std::allocator_traits<EntityAllocator>::destroy(_EntityAllocator, entity);
                std::allocator_traits<EntityAllocator>::deallocate(_EntityAllocator, entity, 1);
            }
            return;
        }
        entity->SetPendingDestroy(true);

        Emit<Events::OnEntityDestroyed>({ entity });

        if (immediate) {
            _Entities.erase(std::remove(_Entities.begin(), _Entities.end(), entity), _Entities.end());

            _IndexToUUIDMap.erase(_IndexToUUIDMap.find(entity->GetEntityID()));

            SortUUIDMap();

            std::allocator_traits<EntityAllocator>::destroy(_EntityAllocator, entity);
            std::allocator_traits<EntityAllocator>::deallocate(_EntityAllocator, entity, 1);
        }
    }

    bool World::CleanUp()
    {
        uint64_t count = 0;

        _Entities.erase(std::remove_if(_Entities.begin(), _Entities.end(), [&, this](Entity *entity) {
            if (entity->IsPendingDestroy()) {
                _IndexToUUIDMap.erase(_IndexToUUIDMap.find(entity->GetEntityID()));

                SortUUIDMap();

                std::allocator_traits<EntityAllocator>::destroy(_EntityAllocator, entity);
                std::allocator_traits<EntityAllocator>::deallocate(_EntityAllocator, entity, 1);

                count++;

                return true;
            }
            return false;
        }), _Entities.end());

        return count > 0;
    }

    void World::Reset()
    {
        for (auto *entity : _Entities) {
            if (!entity->IsPendingDestroy()) {
                entity->SetPendingDestroy(true);

                Emit<Events::OnEntityDestroyed>({ entity });
            }
            _IndexToUUIDMap.erase(_IndexToUUIDMap.find(entity->GetEntityID()));

            SortUUIDMap();

            std::allocator_traits<EntityAllocator>::destroy(_EntityAllocator, entity);
            std::allocator_traits<EntityAllocator>::deallocate(_EntityAllocator, entity, 1);
        }
        _Entities.clear();
    }

    EntitySystem *World::RegisterSystem(EntitySystem *system)
    {
        _Systems.push_back(system);
        
        system->Configure(this);

        return system;
    }

    void World::UnregisterSystem(EntitySystem *system)
    {
        _Systems.erase(std::remove(_Systems.begin(), _Systems.end(), system), _Systems.end());

        system->Unconfigure(this);
    }

    void World::EnableSystem(EntitySystem *system)
    {
        auto it = std::find(_DisabledSystems.begin(), _DisabledSystems.end(), system);

        if (it != _DisabledSystems.end()) {
            _DisabledSystems.erase(it);

            _Systems.push_back(system);
        }
    }

    void World::DisableSystem(EntitySystem *system)
    {
        auto it = std::find(_Systems.begin(), _Systems.end(), system);

        if (it != _Systems.end()) {
            _Systems.erase(it);

            _DisabledSystems.push_back(system);
        }
    }

    void World::UnsubscribeAll(void *subscriber)
    {
        for (auto sub : _Subscribers) {
            sub.second.erase(std::remove(sub.second.begin(), sub.second.end(), subscriber), sub.second.end());

            if (sub.second.size() == 0)
                _Subscribers.erase(sub.first);
        }
    }

    void World::ForAll(std::function<void(Entity *)> function, bool includePendingDestroy)
    {
        for (auto *entity : AllEntities(includePendingDestroy))
            function(entity);
    }

    EntityView World::AllEntities(bool includePendingDestroy)
    {
        EntityIterator first(this, 0, false, includePendingDestroy);
        EntityIterator last(this, GetCount(), true, includePendingDestroy);

        return EntityView(first, last);
    }

    void World::Update(Timestep ts)
    {
        CleanUp();

        for (auto *system : _Systems)
            system->Update(this, ts);
    }

    void World::MergeEntities()
    {
        for (auto *entity : _MergedEntities)
            _Entities.push_back(entity);
        _MergedEntities.clear();
    }

    void World::SortUUIDMap()
    {
        std::unordered_map<uint64_t, uint64_t> newMap;
        uint64_t index = 0;

        for (auto &pair : _IndexToUUIDMap) {
            newMap[index] = pair.second;
            index++;
        }
        _IndexToUUIDMap = newMap;
    }

    ///////////////////////
    // Getters & Setters //
    ///////////////////////

    uint64_t World::GetCount() const
    {
        return _Entities.size();
    }

    Entity *World::GetEntityByIndex(uint64_t index)
    {
        auto it = _IndexToUUIDMap.find(index);

        EXODIA_ASSERT(it != _IndexToUUIDMap.end(), "Entity not found for the given index");

        return GetEntityByID(it->second);
    }

    Entity *World::GetEntityByID(uint64_t id) const
    {
        if (id == Entity::InvalidEntityID)
            return nullptr;
        for (auto *entity : _Entities)
            if (entity->GetEntityID() == id)
                return entity;
        return nullptr;
    }

    Entity *World::GetEntityByTag(const std::string &name) const
    {
        for (auto *entity : _Entities) {
            auto tag = entity->GetComponent<TagComponent>();

            if (tag && tag.Get().Tag == name)
                return entity;
        }
        return nullptr;
    }

    World::EntityAllocator &World::GetPrimaryAllocator()
    {
        return _EntityAllocator;
    }
};
