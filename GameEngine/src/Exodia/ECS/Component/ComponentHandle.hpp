/*
** EPITECH PROJECT, 2023
** ECS
** File description:
** ComponentHandle
*/

#ifndef COMPONENTHANDLE_HPP_
#define COMPONENTHANDLE_HPP_

// Exodia Utils includes
#include "Utils/CrossPlatform.hpp"

namespace Exodia {

    template <typename Component> class ComponentHandle {

        /////////////////
        // Constructor //
        /////////////////
      public:
        ComponentHandle(Component *component = nullptr) : _Component(component){};

        ///////////////////////
        // Getters & Setters //
        ///////////////////////
      public:
        Component &Get() { return *_Component; }

        bool IsValid() const { return _Component != nullptr; }

        ///////////////
        // Operators //
        ///////////////
      public:
        Component *operator->() const { return _Component; }

        operator bool() const { return IsValid(); }

        ////////////////
        // Attributes //
        ////////////////
      private:
        Component *_Component;
    };
}; // namespace Exodia

#endif /* !COMPONENTHANDLE_HPP_ */
