/*
** EXODIA PROJECT, 2023
** ExodiaGameEngine
** File description:
** Buffer
*/

#ifndef BUFFER_HPP_
    #define BUFFER_HPP_

    // Exodia Utils
    #include "Utils/Memory.hpp"

    // External include
    #include <cstdint>

namespace Exodia {

    struct Buffer {
        uint8_t  *Data = nullptr;
        uint64_t  Size = 0;

        Buffer(uint64_t size = 0)
        {
            Allocate(size);
        }

        Buffer(const void *data, uint64_t size) : Data((uint8_t *)data), Size(size) {};

        Buffer(const Buffer &other) = default;

        static Buffer Copy(Buffer other)
        {
            Buffer buffer(other.Size);

            Memcpy(buffer.Data, other.Data, other.Size);
            return buffer;
        }

        void Allocate(uint64_t size)
        {
            Release();

            Data = (uint8_t *)Malloc(size);
            Size = size;
        }

        void Release()
        {
            if (Data) {
                delete[] Data;
                Data = nullptr;
            }

            Size = 0;
        }

        template<typename T>
        T *As()
        {
            return (T *)Data;
        }

        operator bool() const
        {
            return (bool)Data;
        }
    };

    class ScopedBuffer {
        public:

            //////////////////////////////
            // Constructor & Destructor //
            //////////////////////////////

            ScopedBuffer(Buffer buffer) : _Buffer(buffer) {};
            ScopedBuffer(uint64_t size) : _Buffer(size) {};
            ~ScopedBuffer()
            {
                _Buffer.Release();
            }

            /////////////
            // Getters //
            /////////////

            uint8_t *Data()
            {
                return _Buffer.Data;
            }

            uint64_t Size()
            {
                return _Buffer.Size;
            }

            template<typename T>
            T *As()
            {
                return _Buffer.As<T>();
            }

            operator bool() const
            {
                return _Buffer;
            }

        ////////////////
        // Attributes //
        ////////////////
        private:
            Buffer _Buffer;
    };
};

#endif /* !BUFFER_HPP_ */
