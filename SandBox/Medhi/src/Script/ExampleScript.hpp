/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** ExampleScript
*/

#ifndef EXAMPLESCRIPT_HPP_
    #define EXAMPLESCRIPT_HPP_

    #include "Exodia.hpp"

namespace Exodia {

    class ExampleScript : public ScriptableEntity {

        public:

            void OnCreate() override
            {
                std::cout << "Hello world !" << std::endl;
            }
    };
};

#endif /* !EXAMPLESCRIPT_HPP_ */
