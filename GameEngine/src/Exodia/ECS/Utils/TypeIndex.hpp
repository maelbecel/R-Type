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

namespace Exodia {

    class Entity;

    typedef std::allocator<Exodia::Entity> Allocator;
    typedef std::type_index                TypeIndex;

    template<typename T>
    TypeIndex GetTypeIndex()
    {
        return std::type_index(typeid(T));
    }
};

#endif /* !TYPEINDEX_HPP_ */
