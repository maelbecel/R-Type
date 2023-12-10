/*
** EPITECH PROJECT, 2023
** ECS
** File description:
** Entity
*/

#include "Entity.hpp"
#include "World/World.hpp"

namespace Exodia {

    //////////////////////////////
    // Constructor & Destructor //
    //////////////////////////////

    Entity::Entity() : _World(nullptr), _ID(0), _PendingDestroy(false) {};

    Entity::Entity(World *world, uint64_t id) : _World(world), _ID(id), _PendingDestroy(false) {};

    Entity::~Entity()
    {
        RemoveAllComponents();
    }

    /////////////
    // Methods //
    /////////////

    void Entity::RemoveAllComponents()
    {
        for (auto pair : _Components) {
            pair.second->Removed(this);
            //pair.second->Destroy(_World);
        }

        _Components.clear();
    }

    Entity *Entity::Duplicate(World *world, UUID uuid, const std::string &name)
    {
        Entity *entity = world->CreateEntity(uuid, name);

        for (auto pair : _Components)
            entity->_Components[pair.first] = pair.second;
        return entity;
    }

    ///////////////////////
    // Getters & Setters //
    ///////////////////////

    World *Entity::GetWorld() const
    {
        return _World;
    }

    void Entity::SetWorld(World *world)
    {
        _World = world;
    }

    uint64_t Entity::GetEntityID() const
    {
        return _ID;
    }

    bool Entity::IsPendingDestroy() const
    {
        return _PendingDestroy;
    }

    void Entity::SetPendingDestroy(bool pendingDestroy)
    {
        _PendingDestroy = pendingDestroy;
    }

    /////////////////
    // Comparators //
    /////////////////

    bool Entity::operator==(const Entity &other) const
    {
        return _ID == other._ID;
    }

    bool Entity::operator!=(const Entity &other) const
    {
        return !(other == *this);
    }
    
};
