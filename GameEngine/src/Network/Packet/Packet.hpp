/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** Packet
*/

#ifndef PACKET_HPP_
#define PACKET_HPP_

#include "Network/Header/Header.hpp"
#include "Utils/Memory.hpp"
#include "Core/Buffer/Buffer.hpp"

namespace Exodia {
    namespace Network {
        class Packet {
          public:
            Packet(uint8_t command, bool isImportant = false) : _content(std::vector<char>()) {
                _header = std::make_unique<Header>(command, isImportant);
            };

            Packet() : _content(std::vector<char>()) { _header = CreateScope<Header>(0, 0, 0); };

            Packet(Header header, std::vector<char> content) : _content(content) {
                _header = CreateScope<Header>(header);
                _header->setSize((unsigned long)_content.size());
            };

            Packet(const Packet &packet) : _content(packet._content) {
                _header = CreateScope<Header>(*packet._header);
            };

            ~Packet() = default;

            void SetHeader(Header header) {
                _header = CreateScope<Header>(header);
                _header->setSize((unsigned long)_content.size());
            }

            void SetContent(std::vector<char> content) { _content = content; }

            void SetContent(Exodia::Buffer buffer) { _content = buffer.ToVector(); }

            void Set(Header header, std::vector<char> content) {
                _header = CreateScope<Header>(header);
                _content = content;
                _header->setSize((unsigned long)_content.size());
            }

            std::vector<char> GetBuffer() const {
                std::vector<char> buffer(Header::GetSize() + _content.size());

                _header->fillBuffer(buffer);
                std::memcpy(buffer.data() + Header::GetSize(), _content.data(), _content.size());
                return buffer;
            }

            std::unique_ptr<Header> &GetHeader() { return _header; }

            size_t GetSize() { return Header::GetSize() + _content.size(); }

            std::vector<char> GetContent() { return _content; }

            Packet &operator=(const Packet &packet) {
                _header = std::make_unique<Header>(*packet._header);
                _content = packet._content;
                return *this;
            }

          protected:
          private:
            Scope<Header> _header;
            std::vector<char> _content;
        };
    }; // namespace Network
};     // namespace Exodia

#endif /* !PACKET_HPP_ */
