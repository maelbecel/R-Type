/*
** EXODIA PROJECT, 2023
** ExodiaGameEngine
** File description:
** Timer
*/

#ifndef TIMER_HPP_
#define TIMER_HPP_

// External includes
#include <chrono>

namespace Exodia {

    class Timer {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
      public:
        Timer() { Reset(); }

        ~Timer() = default;

        /////////////
        // Methods //
        /////////////
      public:
        void Reset() { _Start = std::chrono::high_resolution_clock::now(); }

        float Elapsed() {
            return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() -
                                                                        _Start)
                       .count() *
                   0.001f * 0.001f * 0.001f;
        }

        float ElapsedMillis() { return Elapsed() * 1000.0f; }

        ////////////////
        // Attributes //
        ////////////////
      private:
        std::chrono::time_point<std::chrono::high_resolution_clock> _Start; /*!< The start timepoint */
    };
}; // namespace Exodia

#endif /* !TIMER_HPP_ */
