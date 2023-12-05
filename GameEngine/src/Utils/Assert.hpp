/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** Assert
*/

#ifndef ASSERT_HPP_
    #define ASSERT_HPP_

    #include "Debug/Logs.hpp"

#if defined(_MSC_VER)
    #define EXODIA_DEBUGBREAK() __debugbreak()
#elif defined(__GNUC__) || defined(__clang__)
    #define EXODIA_DEBUGBREAK() __builtin_trap()
#else
    #error "Unsupported compiler"
#endif

#ifndef EXODIA_DEBUG
    #define EXODIA_ENABLE_ASSERTS
#endif

#ifndef EXODIA_ENABLE_ASSERTS
    #define EXODIA_ASSERT(x, ...) \
            {                     \
                if (!(x)) {                 \
                    EXODIA_ERROR("Assertion Failed: ", __VA_ARGS__); \
                    EXODIA_DEBUGBREAK();    \
                }                           \
            }

    #define EXODIA_CORE_ASSERT(x, ...) \
            {                          \
                if (!(x)) {                \
                    EXODIA_CORE_ERROR("Assertion Failed: ", __VA_ARGS__); \
                    EXODIA_DEBUGBREAK();   \
                }                          \
            }
#else
    #define EXODIA_ASSERT(x, ...)
    #define EXODIA_CORE_ASSERT(x, ...)
#endif

#endif /* !ASSERT_HPP_ */
