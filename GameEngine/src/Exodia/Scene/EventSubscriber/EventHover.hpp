/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** EventHover
*/

#ifndef EVENTHOVER_HPP_
#define EVENTHOVER_HPP_

// Exodia ECS includes
#include "Exodia-ECS.hpp"

namespace Exodia {

    class EventHover : public EventSubscriber<Events::OnHoveredEnter>,
                       public EventSubscriber<Events::OnHoveredExit>,
                       public EventSubscriber<Events::OnClick> {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
      public:
        EventHover() = default;
        ~EventHover() = default;

        /////////////
        // Methods //
        /////////////
      public:
        virtual void Receive(World *world, const Events::OnHoveredEnter &event) override;
        virtual void Receive(World *world, const Events::OnHoveredExit &event) override;
        virtual void Receive(World *world, const Events::OnClick &event) override;
    };
}; // namespace Exodia

#endif /* !EVENTHOVER_HPP_ */
