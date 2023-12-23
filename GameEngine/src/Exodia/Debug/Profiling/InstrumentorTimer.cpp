/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** InstrumentorTimer
*/

// Exodia Debug Profiling
#include "InstrumentorTimer.hpp"
#include "Debug/Profiling/Instrumentor.hpp"

// External includes
#include <thread>

namespace Exodia
{

    //////////////////////////////
    // Constructor & Destructor //
    //////////////////////////////

    InstrumentationTimer::InstrumentationTimer( const char *name ) : _Name( name ), _Stopped( false )
    {
        _StartTimePoint = std::chrono::steady_clock::now();
    }

    InstrumentationTimer::~InstrumentationTimer()
    {
        if ( !_Stopped )
            Stop();
    }

    /////////////
    // Methods //
    /////////////

    void InstrumentationTimer::Stop()
    {
        auto endTimePoint = std::chrono::high_resolution_clock::now();

        long long start =
            std::chrono::time_point_cast<std::chrono::microseconds>( _StartTimePoint ).time_since_epoch().count();
        long long end =
            std::chrono::time_point_cast<std::chrono::microseconds>( endTimePoint ).time_since_epoch().count();

        uint32_t threadID = (uint32_t) ( std::hash<std::thread::id>{}( std::this_thread::get_id() ) );

        Instrumentor::Get().WriteProfile( { _Name, start, end, threadID } );

        _Stopped = true;
    }
}; // namespace Exodia
