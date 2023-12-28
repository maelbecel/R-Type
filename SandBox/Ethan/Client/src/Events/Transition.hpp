/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Transition
*/

#ifndef TRANSITION_HPP_
    #define TRANSITION_HPP_

    // Exodia includes
    #include "Exodia.hpp"

    // R-Type includes
    #include "Events/FadeEvent.hpp"

namespace RType {

    class Transition : public Exodia::EventSubscriber<Events::FadeOutEndEvent> {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
        public:

            Transition() = default;
            ~Transition() = default;

        /////////////
        // Methods //
        /////////////
        public:

            void Receive(Exodia::World *world, const Events::FadeOutEndEvent &event) override;
    };
};

#endif /* !TRANSITION_HPP_ */
