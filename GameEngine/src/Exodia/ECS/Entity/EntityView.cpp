/*
** EPITECH PROJECT, 2023
** ECS
** File description:
** EntityView
*/

#include "Entity/EntityView.hpp"
#include "ECS.hpp"

namespace Exodia
{

    /////////////////
    // Constructor //
    /////////////////

    EntityView::EntityView( const EntityIterator &first, const EntityIterator &last )
        : _FirstIterator( first ), _LastIterator( last )
    {
        if ( _FirstIterator.Get() == nullptr ||
             ( _FirstIterator.Get()->IsPendingDestroy() && !_FirstIterator.IncludePendingDestroy() ) )
            ++_FirstIterator;
    }

    /////////////
    // Methods //
    /////////////

    const EntityIterator &EntityView::begin() const { return _FirstIterator; }

    const EntityIterator &EntityView::end() const { return _LastIterator; }
}; // namespace Exodia
