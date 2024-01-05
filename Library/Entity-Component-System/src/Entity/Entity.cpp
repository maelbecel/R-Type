/*
** EPITECH PROJECT, 2023
** ECS
** File description:
** Entity
*/

#include "Entity.hpp"
#include "World/World.hpp"
#include "Events/Events.hpp"

namespace Exodia {

    //////////////////////////////
    // Constructor & Destructor //
    //////////////////////////////

    Entity::Entity() : _World(nullptr), _ID(0), _PendingDestroy(false){};

    Entity::Entity(World *world, uint64_t id) : _World(world), _ID(id), _PendingDestroy(false){};

    Entity::~Entity() { RemoveAllComponents(); }

    /////////////
    // Methods //
    /////////////

    void Entity::RemoveAllComponents() {
        for (auto pair : _Components) {
            pair.second->Removed(this);
            // pair.second->Destroy(_World);
        }

        _Components.clear();
    }

    Entity *Entity::Duplicate(World *world, UUID uuid, const std::string &name) {
        Entity *entity = world->CreateEntity(uuid, name);

        for (auto pair : _Components)
            entity->_Components[pair.first] = pair.second;
        return entity;
    }

    void Entity::AddComponent(IComponentContainer *component) {
        std::string name = component->GetTypeIndexOfComponent().name();
        std::string typeIndex = extractTypeName(name.c_str());

        _Components[typeIndex] = component;

        _World->Emit<Events::OnComponentAddedNoTemplate>({this, typeIndex});
    }

    bool Entity::RemoveComponent(IComponentContainer *component) {
        std::string name = component->GetTypeIndexOfComponent().name();
        std::string typeIndex = extractTypeName(name.c_str());

        auto found = _Components.find(typeIndex);

        if (found == _Components.end())
            return false;
        found->second->Removed(this);
        found->second->Destroy(_World);
        _Components.erase(found);
        return true;
    }

    ///////////////////////
    // Getters & Setters //
    ///////////////////////

    World *Entity::GetWorld() const { return _World; }

    void Entity::SetWorld(World *world) { _World = world; }

    uint64_t Entity::GetEntityID() const { return _ID; }

    bool Entity::IsPendingDestroy() const { return _PendingDestroy; }

    void Entity::SetPendingDestroy(bool pendingDestroy) { _PendingDestroy = pendingDestroy; }

    std::vector<IComponentContainer *> Entity::GetAllComponents() {
        std::vector<IComponentContainer *> components;

        for (auto pair : _Components)
            components.push_back(pair.second);
        return components;
    }

    void Entity::SetComponent(const std::string &index, IComponentContainer *component) {
        auto found = _Components.find(index);

        if (found != _Components.end()) {
            found->second->Removed(this);
            found->second->Destroy(_World);
        }

        _Components[index] = component;
    }

    IComponentContainer *Entity::GetComponent(const std::string &index) {
        auto found = _Components.find(index);

        if (found == _Components.end())
            return nullptr;
        return found->second;
    }

    /////////////////
    // Comparators //
    /////////////////

    bool Entity::operator==(const Entity &other) const { return _ID == other._ID; }

    bool Entity::operator!=(const Entity &other) const { return !(other == *this); }

    Entity::operator bool() const { return _ID != 0; }
}; // namespace Exodia
