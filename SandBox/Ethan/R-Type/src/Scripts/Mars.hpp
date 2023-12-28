/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Mars
*/

#ifndef MARS_HPP_
    #define MARS_HPP_

    // Exodia includes
    #include "Exodia.hpp"

namespace RType {

    class Mars : public Exodia::ScriptableEntity {

        /////////////
        // Methods //
        /////////////
        public:

            void OnCreate() override;
    };
};

#endif /* !MARS_HPP_ */
