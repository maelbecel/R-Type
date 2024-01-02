/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Intro
*/

#ifndef INTRO_HPP_
    #define INTRO_HPP_

    // Exodia includes
    #include "Exodia.hpp"

    // R-Type Components includes
    #include "R-Type.hpp"

namespace RType {

    class Intro : public Exodia::ScriptableEntity {

        /////////////
        // Defines //
        /////////////
        private:

            static const uint64_t LIFTIN  = 51584511521211;
            static const uint64_t LIFTOUT = 120584531521562;
            static const uint64_t CLASSIC = 45121874124124;

            const float TimeBetweenAnimations = 5.0f;

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
        public:

            Intro() : _Time(0.0f), _IsLiftIn(true), _IsLoad(false) {};

        /////////////
        // Methods //
        /////////////
        public:

            /**
             * @brief OnCreate function of the Intro script that will be called when the entity is created.
             * 
             * In this script we will create the animations LiftIn and LiftOut.
             */
            void OnCreate() override;

            /**
             * @brief OnUpdate function of the Intro script that will be called when the entity is updated.
             * 
             * In this script we will update the animations LiftIn and LiftOut. Every 5 seconds we will switch between the two animations.
             * 
             * @param ts Delta time between two frames.
             */
            void OnUpdate(Exodia::Timestep ts) override;

            void OnKeyPressed(int keycode) override;

        private:

            void PressStartFactory();

        ////////////////
        // Attributes //
        ////////////////
        private:

            float _Time;
            bool  _IsLiftIn;

            bool _IsLoad;

            std::vector<AnimationComponent> _Animations;
    };
};

#endif /* !INTRO_HPP_ */
