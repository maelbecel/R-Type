/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** GameObject
*/

#include "GameObject.hpp"
#include "Scene/Components/Components.hpp"

namespace Exodia {

    //////////////////////////////
    // Constructor & Destructor //
    //////////////////////////////

    GameObject::GameObject(Entity handle, Scene *scene) : _EntityHandle(handle), _Scene(scene) {};

    ///////////////////////
    // Getters & Setters //
    ///////////////////////

    UUID GameObject::GetUUID()
    {
        return GetComponent<IDComponent>().ID;
    }

    const std::string &GameObject::GetName()
    {
        return GetComponent<TagComponent>().Tag;
    }

    ///////////////
    // Operators //
    ///////////////

    GameObject::operator bool() const
    {
        return _EntityHandle != Entity::InvalidEntityID;
    }

    GameObject::operator uint32_t() const
    {
        return (uint32_t)_EntityHandle;
    }

    GameObject::operator Entity() const
    {
        return _EntityHandle;
    }

    bool GameObject::operator==(const GameObject &other) const
    {
        return _EntityHandle == other._EntityHandle && _Scene == other._Scene;
    }

    bool GameObject::operator!=(const GameObject &other) const
    {
        return !(*this == other);
    }
};
