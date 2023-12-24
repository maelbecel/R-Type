/*
** EPITECH PROJECT, 2023
** ECS
** File description:
** EntityIterator
*/

#include "EntityIterator.hpp"
#include "ECS.hpp"

namespace Exodia {

    /////////////////
    // Constructor //
    /////////////////

    EntityIterator::EntityIterator(class World *world, size_t index, bool isEnd, bool includePendingDestroy)
        : _World(world), _Index(index), _IsEnd(isEnd), _IncludePendingDestroy(includePendingDestroy) {
        if (_Index >= _World->GetCount())
            this->_IsEnd = true;
    }

    ///////////////////////
    // Getters & Setters //
    ///////////////////////

    bool EntityIterator::IsEnd() const { return _IsEnd || _Index >= _World->GetCount(); }

    Entity *EntityIterator::Get() const {
        if (IsEnd())
            return nullptr;
        return _World->GetEntityByIndex(_Index);
    }

    size_t EntityIterator::GetIndex() const { return _Index; }

    bool EntityIterator::IncludePendingDestroy() const { return _IncludePendingDestroy; }

    World *EntityIterator::GetWorld() const { return _World; }

    ///////////////
    // Operators //
    ///////////////

    Entity *EntityIterator::operator*() const { return Get(); }

    EntityIterator &EntityIterator::operator++() {
        _Index++;

        for (; _Index < _World->GetCount() &&
               (Get() == nullptr || (Get()->IsPendingDestroy() && !_IncludePendingDestroy));
             _Index++)
            ;

        if (_Index >= _World->GetCount())
            _IsEnd = true;
        return *this;
    }

    /////////////////
    // Comparators //
    /////////////////

    bool EntityIterator::operator==(const EntityIterator &other) const {
        return _World == other._World && IsEnd() == other.IsEnd() && _Index == other._Index;
    }

    bool EntityIterator::operator!=(const EntityIterator &other) const { return !(*this == other); }
}; // namespace Exodia
