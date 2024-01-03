/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Buffer
*/

#include "Buffer.hpp"

namespace Exodia {

    //////////////////////////////
    // Constructor & Destructor //
    //////////////////////////////

    ScopedBuffer::ScopedBuffer(Buffer buffer) : _Buffer(buffer){};

    ScopedBuffer::ScopedBuffer(uint64_t size) : _Buffer(size){};

    ScopedBuffer::~ScopedBuffer() { _Buffer.Release(); }

    /////////////
    // Getters //
    /////////////

    uint8_t *ScopedBuffer::Data() { return _Buffer.Data; }

    uint64_t ScopedBuffer::Size() { return _Buffer.Size; }

    template <typename T> T *ScopedBuffer::As() { return _Buffer.As<T>(); }

    ///////////////
    // Operators //
    ///////////////

    ScopedBuffer::operator bool() const { return _Buffer; }
}; // namespace Exodia
