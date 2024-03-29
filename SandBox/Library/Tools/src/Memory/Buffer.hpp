/*
** EXODIA PROJECT, 2023
** ExodiaGameEngine
** File description:
** Buffer
*/

#ifndef BUFFER_HPP_
#define BUFFER_HPP_

// Exodia Utils
#include "Memory/Memory.hpp"

// External include
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <vector>

namespace Exodia {

    struct Buffer {

        uint8_t *Data = nullptr;
        uint64_t Size = 0;
        uint64_t Offset = 0;

        Buffer() = default;

        Buffer(uint64_t size) { Allocate(size); }

        Buffer(uint64_t size, uint8_t value) {
            Allocate(size);

            std::memset(Data, value, size);
        }

        Buffer(const void *data, uint64_t size) : Data((uint8_t *)data), Size(size){};

        Buffer(const Buffer &other) = default;

        static Buffer Copy(Buffer other) {
            Buffer buffer(other.Size);

            std::memcpy(buffer.Data, other.Data, other.Size);

            return buffer;
        }

        bool Write(const void *data, uint64_t size) {
            if (Offset + size > Size)
                Resize(Offset + size);

            std::memcpy(Data + Offset, data, size);

            Offset += size;

            return true;
        }

        void Allocate(uint64_t size) {
            Release();

            Data = (uint8_t *)std::malloc(size);
            Size = size;
        }

        void Resize(uint64_t size) {
            if (size == Size)
                return;
            uint8_t *newData = (uint8_t *)std::malloc(size);

            if (Data != nullptr) {
                uint64_t minSize = size < Size ? size : Size;

                std::memcpy(newData, Data, minSize);
                std::free(Data);
            }

            Data = newData;
            Size = size;
        }

        void Release() {
            if (Data != nullptr) {
                std::free(Data);
                Data = nullptr;
            }

            Size = 0;
        }

        std::vector<char> ToVector() {
            std::vector<char> vector(Size);

            std::memcpy(vector.data(), Data, Size);
            return vector;
        }

        template <typename T> T *As() { return (T *)Data; }

        operator bool() const { return (bool)Data; }
    };

    class ScopedBuffer {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
      public:
        ScopedBuffer(Buffer buffer);
        ScopedBuffer(uint64_t size);

        ~ScopedBuffer();

        /////////////
        // Getters //
        /////////////
      public:
        uint8_t *Data();
        uint64_t Size();
        template <typename T> T *As();

        ///////////////
        // Operators //
        ///////////////
      public:
        operator bool() const;

        ////////////////
        // Attributes //
        ////////////////
      private:
        Buffer _Buffer;
    };
}; // namespace Exodia

#endif /* !BUFFER_HPP_ */
