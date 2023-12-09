/*
** EPITECH PROJECT, 2023
** ECS
** File description:
** Entity
*/

#include "Entity.hpp"

namespace Exodia {

    //////////////////////////////
    // Constructor & Destructor //
    //////////////////////////////

    Entity::Entity() {};

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
            pair.second->Destroy(_World);
        }

        _Components.clear();
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
