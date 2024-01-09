/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** InstrumentorTimer
*/

#ifndef INSTRUMENTORTIMER_HPP_
#define INSTRUMENTORTIMER_HPP_

// External includes
#include <chrono>

namespace Exodia {

    /**
     * @brief The InstrumentationTimer class provides a mechanism to measure the duration of code execution for
     * profiling.
     */
    class InstrumentationTimer {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
      public:
        /**
         * @brief Construct an InstrumentationTimer object.
         *
         * @param name (Type: const char *) The name of the instrumented code block.
         */
        InstrumentationTimer(const char *name);

        /**
         * @brief Destroy the InstrumentationTimer object.
         *
         * @note If the timer is not explicitly stopped, it will be stopped upon destruction.
         */
        ~InstrumentationTimer();

        /////////////
        // Methods //
        /////////////
      public:
        /**
         * @brief Stop the timer and record the profile result.
         */
        void Stop();

        ////////////////
        // Attributes //
        ////////////////
      private:
        const char *_Name;                                                  /*!< Name of the instrumented code block. */
        std::chrono::time_point<std::chrono::steady_clock> _StartTimePoint; /*!< Start time point of the timer. */
        bool _Stopped; /*!< Flag indicating whether the timer has been stopped. */
    };
}; // namespace Exodia

#endif /* !INSTRUMENTORTIMER_HPP_ */
