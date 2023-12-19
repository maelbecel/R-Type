/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** TestScript
*/

#ifndef TESTSCRIPT_HPP_
    #define TESTSCRIPT_HPP_

    #include "Exodia.hpp"

namespace RType {

    class CameraController : public Exodia::ScriptableEntity {

        public:

            void OnCreate() override;

            void OnUpdate(Exodia::Timestep ts) override;
    };
};

#endif /* !TESTSCRIPT_HPP_ */
