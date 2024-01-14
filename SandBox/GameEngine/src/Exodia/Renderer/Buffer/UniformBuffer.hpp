/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** UniformBuffer
*/

#ifndef UNIFORMBUFFER_HPP_
#define UNIFORMBUFFER_HPP_

// Exodia Utils includes
#include "Exodia-Utils.hpp"

namespace Exodia {

    class UniformBuffer {

        /////////////
        // Factory //
        /////////////
      public:
        static Ref<UniformBuffer> Create(uint32_t size, uint32_t binding);

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
      public:
        virtual ~UniformBuffer() = default;

        ///////////////////////
        // Getters & Setters //
        ///////////////////////
      public:
        virtual void SetData(const void *data, uint32_t size, uint32_t offset = 0) = 0;
    };
}; // namespace Exodia

#endif /* !UNIFORMBUFFER_HPP_ */
