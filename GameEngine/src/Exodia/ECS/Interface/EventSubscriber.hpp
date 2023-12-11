/*
** EPITECH PROJECT, 2023
** ECS
** File description:
** EventSubscriber
*/

#ifndef EVENTSUBSCRIBER_HPP_
    #define EVENTSUBSCRIBER_HPP_

    // Exodia ECS Interface includes
    #include "Interface/IEventSubscriber.hpp"

    // Exodia Utils includes
    #include "Utils/CrossPlatform.hpp"

namespace Exodia {

    class World;

    template<typename Event>
    class EXODIA_API EventSubscriber : public IEventSubscriber {

        ////////////////
        // Destructor //
        ////////////////
        public:

            virtual ~EventSubscriber() = default;

        /////////////
        // Methods //
        /////////////
        public:

            virtual void Receive(World *world, const Event &event) = 0;
    };
};

#endif /* !EVENTSUBSCRIBER_HPP_ */

