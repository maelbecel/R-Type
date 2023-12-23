/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** Memory
*/

#ifndef MEMORY_HPP_
#define MEMORY_HPP_

#include <memory>
#include <stdlib.h>
#include <string.h>

//////////////////////////////////////////////////////////////////
// A bitshift operator that will shift the bit to the left by x //
// Example: BIT(0) -> 0000 0001                                 //
// Example: BIT(1) -> 0000 0010                                 //
// Example: BIT(2) -> 0000 0100                                 //
// Example: BIT(3) -> 0000 1000                                 //
// Example: BIT(4) -> 0001 0000                                 //
//////////////////////////////////////////////////////////////////
#define BIT( x ) ( 1 << x )

#ifdef _MSC_VER // MSVC (Microsoft Visual C++)
#define UNUSED( x ) __pragma( warning( suppress : 4100 ) ) x
#else
#define UNUSED( x ) __attribute__( ( unused ) ) x
#endif

// Replace the std::shared_ptr into Ref
template <typename T> using Ref = std::shared_ptr<T>;

// Replace the std::make_shared into CreateRef
template <typename T, typename... Args> constexpr Ref<T> CreateRef( Args &&...args )
{
    return std::make_shared<T>( std::forward<Args>( args )... );
}

// Replace the std::unique_ptr into Scope
template <typename T> using Scope = std::unique_ptr<T>;

// Replace the std::make_unique into CreateScope
template <typename T, typename... Args> constexpr Scope<T> CreateScope( Args &&...args )
{
    return std::make_unique<T>( std::forward<Args>( args )... );
}

inline static void *Memcopy( void *dest, const void *src, size_t n ) { return memcpy( dest, src, n ); }

#endif /* !MEMORY_HPP_ */
