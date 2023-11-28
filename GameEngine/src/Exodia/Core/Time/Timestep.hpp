/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** Timestep
*/

#ifndef TIMESTEP_HPP_
    #define TIMESTEP_HPP_

    // Exodia Utils includes
    #include "Utils/CrossPlatform.hpp"

namespace Exodia {

    /**
     * @brief The Timestep class represents a duration of time, typically used for frame timing.
     * It provides methods to retrieve the duration in seconds or milliseconds and supports conversion to float.
     */
    class EXODIA_API Timestep {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
        public:

            /**
             * @brief Construct a Timestep object with a given time.
             *
             * @param time (Type: float) The duration of time in seconds.
             */
            Timestep(float time = 0.0f);

            /**
             * @brief Default destructor for the Timestep class.
             */
            ~Timestep() = default;

        //////////////
        // Operator //
        //////////////
        public:

            /**
             * @brief Conversion operator to retrieve the duration in seconds as a float.
             *
             * @return (Type: float) The duration of the timestep in seconds.
             */
            operator float() const
            {
                return _Time;
            }

        ///////////////////////
        // Getters & Setters //
        ///////////////////////
        public:

            /**
             * @brief Get the duration of the timestep in seconds.
             *
             * @return (Type: float) The duration of the timestep in seconds.
             */
            float GetSeconds() const;

            /**
             * @brief Get the duration of the timestep in milliseconds.
             *
             * @return (Type: float) The duration of the timestep in milliseconds.
             */
            float GetMilliseconds() const;
 
        ////////////////
        // Attributes //
        ////////////////
        private:
            float _Time; /*!< The current time of the timestep */
    };
};

#endif /* !TIMESTEP_HPP_ */
