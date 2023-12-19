/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Profiling
*/

#ifndef PROFILING_HPP_
    #define PROFILING_HPP_

    /////////////////////////////////////////////////
    // Main include file for Exodia Profiling      //
    // Include this file to use debug instrumentor //
    // It will allow you to profile your code      //
    /////////////////////////////////////////////////

    // -- Profiling ------------------------------------------------------------

    #include "Exodia/Debug/Profiling/InstrumentorTimer.hpp"
    #include "Exodia/Debug/Profiling/Instrumentor.hpp"

    // -- Macros ---------------------------------------------------------------

    #if EXODIA_DEBUG
        #define EXODIA_PROFILE_BEGIN_SESSION(name, filepath) ::Exodia::Instrumentor::Get().BeginSession(name, filepath)
        #define EXODIA_PROFILE_END_SESSION()                 ::Exodia::Instrumentor::Get().EndSession()
        #define EXODIA_PROFILE_SCOPE(name)                   ::Exodia::InstrumentationTimer timer##__LINE__(name)
        #define EXODIA_PROFILE_FUNCTION()                    EXODIA_PROFILE_SCOPE(EXODIA_FUNC_SIG)
    #else
        #define EXODIA_PROFILE_BEGIN_SESSION(name, filepath);
        #define EXODIA_PROFILE_END_SESSION();
        #define EXODIA_PROFILE_SCOPE(name);
        #define EXODIA_PROFILE_FUNCTION();
    #endif

#endif /* !PROFILING_HPP_ */
