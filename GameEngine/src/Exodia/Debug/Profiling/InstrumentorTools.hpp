/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** InstrumentorTools
*/

#ifndef INSTRUMENTORTOOLS_HPP_
#define INSTRUMENTORTOOLS_HPP_

// External includes
#include <cstdint>
#include <string>

namespace Exodia
{

    /**
     * @brief The ProfileResult struct represents a profiling result for an instrumented code block.
     * It stores the name of the block, start and end times, and the thread ID.
     */
    struct ProfileResult
    {
        std::string Name;     /*!< Name of the instrumented code block. */
        long long   Start;    /*!< Start time of the profile in microseconds. */
        long long   End;      /*!< End time of the profile in microseconds. */
        uint32_t    ThreadID; /*!< ID of the thread in which profiling was performed. */
    };

    /**
     * @brief The InstrumentationSession struct represents a profiling session.
     * It stores the name of the session.
     */
    struct InstrumentationSession
    {
        std::string Name; /*!< Name of the profiling session. */
    };
}; // namespace Exodia

#endif /* !INSTRUMENTORTOOLS_HPP_ */
