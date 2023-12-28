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
        // Defines //
        /////////////
        private:

            static const uint64_t MARS = 8452581520512152;

        /////////////
        // Methods //
        /////////////
        public:

            void OnCreate() override;

        private:

            void GenerateDebris(Exodia::World *world);
    };
};

#endif /* !MARS_HPP_ */
