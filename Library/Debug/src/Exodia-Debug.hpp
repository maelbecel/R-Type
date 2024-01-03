/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Exodia-Debug
*/

#ifndef EXODIA_DEBUG_HPP_
    #define EXODIA_DEBUG_HPP_

    //////////////////////////////////////////////////////////////
    // Include this file for use Exodia Debug Profiling and Log //
    //////////////////////////////////////////////////////////////

    // -- Exodia Debug Profiling -----------------------------------------------

    #include "Profiling/Instrumentor.hpp"
    #include "Profiling/InstrumentorTimer.hpp"
    #include "Profiling/InstrumentorTools.hpp"

    // -- Exodia Debug Log -----------------------------------------------------

    #include "Logger/Log.hpp"

    // -- Exodia Debug Assert --------------------------------------------------

    #include "Assert/Assert.hpp"

    // -------------------------------------------------------------------------

#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__) // If the compiler is GCC, or a GCC-compatible compiler
    #define EXODIA_FUNC_SIG __PRETTY_FUNCTION__
#elif defined(__DMC__) && (__DMC__ >= 0x810) // If this is the Digital Mars compiler
    #define EXODIA_FUNC_SIG __PRETTY_FUNCTION__
#elif (defined(__FUNCSIG__) || (_MSC_VER)) // If this is Visual Studio
    #define EXODIA_FUNC_SIG __FUNCSIG__
#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500)) // If this is the Intel or IBM compilers
    #define EXODIA_FUNC_SIG __FUNCTION__
#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550) // If this is the Borland compilers
    #define EXODIA_FUNC_SIG __FUNC__
#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901) // If this is a C99 compliant compiler
    #define EXODIA_FUNC_SIG __func__
#elif defined(__cplusplus) && (__cplusplus >= 201103) // If this is a C++11 compliant compiler
    #define EXODIA_FUNC_SIG __func__
#else
    #define EXODIA_FUNC_SIG "EXODIA_FUNC_SIG unknown!"
#endif

// -- *Core* Logger Macros -----------------------------------------------------
    #define EXODIA_CORE_TRACE(...) ::Exodia::Log::GetCoreLogger()->trace(__VA_ARGS__)
    #define EXODIA_CORE_INFO(...) ::Exodia::Log::GetCoreLogger()->info(__VA_ARGS__)
    #define EXODIA_CORE_WARN(...) ::Exodia::Log::GetCoreLogger()->warn(__VA_ARGS__)
    #define EXODIA_CORE_ERROR(...) ::Exodia::Log::GetCoreLogger()->error(__VA_ARGS__)
    #define EXODIA_CORE_FATAL(...) ::Exodia::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// -- *Client* Logger Macros ---------------------------------------------------
    #define EXODIA_TRACE(...) ::Exodia::Log::GetClientLogger()->trace(__VA_ARGS__)
    #define EXODIA_INFO(...) ::Exodia::Log::GetClientLogger()->info(__VA_ARGS__)
    #define EXODIA_WARN(...) ::Exodia::Log::GetClientLogger()->warn(__VA_ARGS__)
    #define EXODIA_ERROR(...) ::Exodia::Log::GetClientLogger()->error(__VA_ARGS__)
    #define EXODIA_FATAL(...) ::Exodia::Log::GetClientLogger()->fatal(__VA_ARGS__)

// -- Profiling Macros ---------------------------------------------------------
#if EXODIA_DEBUG
    #define EXODIA_PROFILE_BEGIN_SESSION(name, filepath) ::Exodia::Instrumentor::Get().BeginSession(name, filepath)
    #define EXODIA_PROFILE_END_SESSION() ::Exodia::Instrumentor::Get().EndSession()
    #define EXODIA_PROFILE_SCOPE(name) ::Exodia::InstrumentationTimer timer##__LINE__(name)
    #define EXODIA_PROFILE_FUNCTION() EXODIA_PROFILE_SCOPE(EXODIA_FUNC_SIG)
#else
    #define EXODIA_PROFILE_BEGIN_SESSION(name, filepath);
    #define EXODIA_PROFILE_END_SESSION();
    #define EXODIA_PROFILE_SCOPE(name);
    #define EXODIA_PROFILE_FUNCTION();
#endif

#endif /*  EXODIA_DEBUG_HPP_ */
