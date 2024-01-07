/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Prefabs
*/

#include "Prefabs.hpp"
#include "Scene/Serializer/SceneSerializer.hpp"

namespace Exodia {

    //////////////////////////////
    // Constructor & Destructor //
    //////////////////////////////

    Prefabs::Prefabs(const std::string &name) : _Tag(name){};

    Prefabs::~Prefabs(){};

    /////////////
    // Methods //
    /////////////

    Ref<Prefabs> Prefabs::Copy(Ref<Prefabs> other) {
        if (!other)
            return nullptr;
        Ref<Prefabs> copy = CreateRef<Prefabs>(other->GetName());

        for (auto &prefab : other->_Prefabs)
            copy->AddPrefab(Prefabs::Copy(prefab));
        for (auto &entity : other->_Entities)
            copy->AddEntity(entity.Duplicate());

        copy->SetName(other->GetName());
        copy->SetTransform(other->GetTransform());

        return copy;
    }

    void Prefabs::Save(const std::string &path) {
        YAML::Emitter out;

        Serialize(out);

        std::ofstream fout(path);

        fout << out.c_str();
    }

    void Prefabs::Serialize(YAML::Emitter &out) {
        out << YAML::BeginMap;
        out << YAML::Key << "Prefab" << YAML::Value << _Tag.Tag;

        _Transform.Serialize(out);

        out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;
        {
            for (auto &entity : _Entities) {
                out << YAML::BeginMap;
                out << YAML::Key << "Entity" << YAML::Value << entity.GetComponent<IDComponent>().ID;
                { SceneSerializer::SerializeEntity(out, entity.GetEntity()); }
                out << YAML::EndMap;
            }

            for (auto &prefab : _Prefabs)
                prefab->Serialize(out);
        }
        out << YAML::EndSeq;
        out << YAML::EndMap;
    }

    Ref<Prefabs> Prefabs::AddPrefab(Ref<Prefabs> prefab) {
        _Prefabs.push_back(prefab);

        return prefab;
    }

    bool Prefabs::RemovePrefab(const std::string &name) {
        for (auto it = _Prefabs.begin(); it != _Prefabs.end(); it++) {
            if ((*it)->_Tag.Tag == name) {
                _Prefabs.erase(it);

                return true;
            }
        }

        return false;
    }

    void Prefabs::AddEntity(GameObject gameObject) { _Entities.push_back(gameObject); }

    bool Prefabs::RemoveEntity(GameObject gameObject) {
        for (auto it = _Entities.begin(); it != _Entities.end(); it++) {
            if ((*it) == gameObject) {
                _Entities.erase(it);

                return true;
            }
        }

        return false;
    }

    void Prefabs::OnRuntimeStart() {
        for (auto &entity : _Entities) {
            if (!entity.GetEntity())
                continue;
            auto &transform = entity.GetComponent<TransformComponent>();

            transform.Translation += _Transform.Translation;
            transform.Rotation += _Transform.Rotation;
            transform.Scale *= _Transform.Scale;
        }

        for (auto &prefab : _Prefabs) {
            if (!prefab)
                continue;
            auto &transform = prefab->GetTransform();

            transform.Translation += _Transform.Translation;
            transform.Rotation += _Transform.Rotation;
            transform.Scale *= _Transform.Scale;

            prefab->OnRuntimeStart();
        }
    }

    void Prefabs::OnRuntimeStop() {
        for (auto &entity : _Entities) {
            if (!entity.GetEntity())
                continue;
            auto &transform = entity.GetComponent<TransformComponent>();

            transform.Translation -= _Transform.Translation;
            transform.Rotation -= _Transform.Rotation;
            transform.Scale /= _Transform.Scale;
        }

        for (auto &prefab : _Prefabs) {
            if (!prefab)
                continue;
            auto &transform = prefab->GetTransform();

            transform.Translation -= _Transform.Translation;
            transform.Rotation -= _Transform.Rotation;
            transform.Scale /= _Transform.Scale;

            prefab->OnRuntimeStop();
        }
    }

    ///////////////////////
    // Getters & Setters //
    ///////////////////////

    TransformComponent &Prefabs::GetTransform() { return _Transform; }

    const std::string &Prefabs::GetName() const { return _Tag.Tag; }

    void Prefabs::SetName(const std::string &name) { _Tag.Tag = name; }

    void Prefabs::SetTransform(const TransformComponent &transform) { _Transform = transform; }

    AssetType Prefabs::GetType() const { return AssetType::Prefabs; }
}; // namespace Exodia
