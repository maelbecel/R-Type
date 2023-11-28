/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** Cross-Platform
*/

#ifndef CROSSPLATFORM_HPP_
    #define CROSSPLATFORM_HPP_

#if defined(_WIN32) || defined(_WIN64)
    #ifndef ENGINE_EXPORT
        #define EXODIA_API __declspec(dllexport)
    #else
        #define EXODIA_API __declspec(dllimport)
    #endif
#elif defined(__APPLE__)
    #define EXODIA_API __attribute__((visibility("default")))
#else
    #define EXODIA_API
#endif

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

#endif /* !CROSSPLATFORM_HPP_ */
