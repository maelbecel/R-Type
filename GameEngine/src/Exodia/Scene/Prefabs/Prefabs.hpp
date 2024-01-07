/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Prefabs
*/

#ifndef PREFABS_HPP_
#define PREFABS_HPP_

// Exodia Asset includes
#include "Asset/Asset.hpp"

// Exodia ECS includes
#include "Scene/GameObject/GameObject.hpp"
#include "Scene/Components/Components.hpp"

// External includes
#include <vector>
#include <yaml-cpp/yaml.h>

namespace Exodia {

    class Prefabs : public Asset {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
      public:
        Prefabs(const std::string &name = "Untitled Prefabs");
        ~Prefabs();

        /////////////
        // Methods //
        /////////////
      public:
        static Ref<Prefabs> Copy(Ref<Prefabs> other);

        void Save(const std::string &path);
        void Serialize(YAML::Emitter &out);

        Ref<Prefabs> AddPrefab(Ref<Prefabs> prefab);
        bool RemovePrefab(const std::string &name);

        void AddEntity(GameObject gameObject);
        bool RemoveEntity(GameObject gameObject);

        // -- Update -------------------------------------------------------
        void OnRuntimeStart();
        void OnRuntimeStop();

        ///////////////////////
        // Getters & Setters //
        ///////////////////////
      public:
        TransformComponent &GetTransform();
        const std::string &GetName() const;

        void SetName(const std::string &name);
        void SetTransform(const TransformComponent &transform);

        virtual AssetType GetType() const override;

        ////////////////
        // Attributes //
        ////////////////
      private:
        TagComponent _Tag;
        TransformComponent _Transform;

        std::vector<GameObject> _Entities;
        std::vector<Ref<Prefabs>> _Prefabs;
    };
}; // namespace Exodia

#endif /* !PREFABS_HPP_ */
