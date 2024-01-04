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

    GameObject::GameObject(Entity *handle, Scene *scene) : _EntityHandle(handle), _Scene(scene) {};

    /////////////
    // Methods //
    /////////////

    void GameObject::AddComponent(IComponentContainer *component)
    {
        _EntityHandle->AddComponent(component);
    }

    ///////////////////////
    // Getters & Setters //
    ///////////////////////

    UUID GameObject::GetUUID() { return GetComponent<IDComponent>().ID; }

    const std::string &GameObject::GetName() { return GetComponent<TagComponent>().Tag; }

    Entity *GameObject::GetEntity() const
    {
        return _EntityHandle;
    }

    Scene *GameObject::GetScene() const
    {
        return _Scene;
    }

    ///////////////
    // Operators //
    ///////////////

    GameObject::operator bool() const
    {
        return (bool)_EntityHandle;
    }

    GameObject::operator uint32_t() const
    {
        return (uint32_t)_EntityHandle->GetEntityID();
    }

    bool GameObject::operator==(const GameObject &other) const {
        return _EntityHandle == other._EntityHandle && _Scene == other._Scene;
    }

    bool GameObject::operator!=(const GameObject &other) const { return !(*this == other); }
}; // namespace Exodia
