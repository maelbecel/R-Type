/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** Memory
*/

#ifndef MEMORY_HPP_
    #define MEMORY_HPP_

    #include <memory>
    #include <string.h>

    //////////////////////////////////////////////////////////////////
    // A bitshift operator that will shift the bit to the left by x //
    // Example: BIT(0) -> 0000 0001                                 //
    // Example: BIT(1) -> 0000 0010                                 //
    // Example: BIT(2) -> 0000 0100                                 //
    // Example: BIT(3) -> 0000 1000                                 //
    // Example: BIT(4) -> 0001 0000                                 //
    //////////////////////////////////////////////////////////////////
    #define BIT(x) (1 << x)

    #define UNUSED __attribute__((unused)) // For unused variables

    // Replace the std::shared_ptr into Ref
    template <typename T>
    using Ref = std::shared_ptr<T>;

    // Replace the std::make_shared into CreateRef
    template <typename T, typename... Args>
    constexpr Ref<T> CreateRef(Args &&... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

    // Replace the std::unique_ptr into Scope
    template <typename T>
    using Scope = std::unique_ptr<T>;

    // Replace the std::make_unique into CreateScope
    template <typename T, typename... Args>
    constexpr Scope<T> CreateScope(Args &&... args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

inline size_t Strlen(const char *str)
{
    return strlen(str);
}

inline size_t Wcslen(const wchar_t *s)
{
    return wcslen(s);
}

inline void *Memset(void *data, int c, size_t size)
{
    return memset(data, c, size);
}

inline void *Memcpy(void *dest, const void *src, size_t size)
{
    return memcpy(dest, src, size);
}

inline void *Strncpy(char *dest, size_t size, const char *src)
{
    return strncpy(dest, src, size);
}

#endif /* !MEMORY_HPP_ */
