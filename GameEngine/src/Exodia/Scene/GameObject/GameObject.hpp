/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** GameObject
*/

#ifndef GAMEOBJECT_HPP_
#define GAMEOBJECT_HPP_

#include "ECS/ECS.hpp"
#include "Scene/Scene/Scene.hpp"

namespace Exodia {

    class GameObject {
        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
      public:
        GameObject(Entity handle = Entity(), Scene *scene = nullptr);
        GameObject(const GameObject &other) = default;

        ///////////////////////
        // Getters & Setters //
        ///////////////////////
      public:
        template <typename T, typename... Args> T &AddComponent(Args &&...args) {
            if (HasComponent<T>()) {
                EXODIA_CORE_WARN("Entity already has component !");

                return GetComponent<T>();
            }

            return _EntityHandle.AddComponent<T>(std::forward<Args>(args)...).Get();
        }

        template <typename T, typename... Args> T &AddOrReplaceComponent(Args &&...args) {
            if (HasComponent<T>())
                RemoveComponent<T>();
            return AddComponent<T>(std::forward<Args>(args)...);
        }

        template <typename T> void RemoveComponent() {
            if (!(_EntityHandle.RemoveComponent<T>()))
                EXODIA_CORE_WARN("Entity does not have component !");
        }

        template <typename T> T &GetComponent() {
            ComponentHandle<T> component = _EntityHandle.GetComponent<T>();

            if (!component)
                return AddComponent<T>();
            return component.Get();
        }

        template <typename T> bool HasComponent() { return _EntityHandle.HasComponent<T>(); }

        UUID GetUUID();

        const std::string &GetName();

        ///////////////
        // Operators //
        ///////////////
      public:
        operator bool() const;
        operator uint32_t() const;
        operator Entity() const;

        bool operator==(const GameObject &other) const;
        bool operator!=(const GameObject &other) const;

        ////////////////
        // Attributes //
        ////////////////
      private:
        Entity _EntityHandle; /* !< The entity handle */
        Scene *_Scene;        /* !< The scene where the entity is (it's a 12 bytes memory address) */
    };
}; // namespace Exodia

#endif /* !GAMEOBJECT_HPP_ */
