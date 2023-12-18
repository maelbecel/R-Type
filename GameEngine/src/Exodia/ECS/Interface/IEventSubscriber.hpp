/*
** EPITECH PROJECT, 2023
** ECS
** File description:
** IEventSubscriber
*/

#ifndef IEVENTSUBSCRIBER_HPP_
    #define IEVENTSUBSCRIBER_HPP_

    // Exodia Utils includes
    #include "Utils/CrossPlatform.hpp"

namespace Exodia {

    class IEventSubscriber {

        ////////////////
        // Destructor //
        ////////////////
        public:
            virtual ~IEventSubscriber() = default;
    };
};

#endif /* !IEVENTSUBSCRIBER_HPP_ */
