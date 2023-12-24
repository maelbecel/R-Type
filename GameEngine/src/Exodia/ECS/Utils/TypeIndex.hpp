/*
** EPITECH PROJECT, 2023
** ECS
** File description:
** TypeIndex
*/

#ifndef TYPEINDEX_HPP_
#define TYPEINDEX_HPP_

// External includes
#include <typeindex>
#include <typeinfo>
#include <memory>
#include <string>
#include <cstdlib>

#ifdef __GNUC__
#include <cxxabi.h>
#endif

namespace Exodia {

    class Entity;

    typedef std::allocator<Exodia::Entity> Allocator;
    typedef std::type_index TypeIndex;

    template <typename T> inline static TypeIndex GetTypeIndex() { return std::type_index(typeid(T)); }

    inline static std::string demangle(const char *name) {
#ifdef __GNUC__
        int status = 0;
        char *demangled = abi::__cxa_demangle(name, nullptr, nullptr, &status);

        if (status == 0) {
            std::string result(demangled);
            std::free(demangled);

            return result;
        }
#endif
        return name;
    }

    inline static std::string extractTypeName(const char *name) {
        std::string typeName = demangle(name);
        size_t colons = typeName.find_last_of(':');

        if (colons != std::string::npos)
            typeName.erase(0, colons + 1);
        return typeName;
    }

    template <typename T> inline static std::string GetTypeName() {
        std::string typeName = GetTypeIndex<T>().name();

        return extractTypeName(typeName.c_str());
    }
}; // namespace Exodia

#endif /* !TYPEINDEX_HPP_ */
