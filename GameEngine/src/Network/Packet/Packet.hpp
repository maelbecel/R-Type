/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** Packet
*/

#ifndef PACKET_HPP_
#define PACKET_HPP_

#include "Network/Header/Header.hpp"

namespace Exodia {
    namespace Network {
        class Packet {
            public:
                Packet(uint8_t command) : _content(std::vector<char>())
                {
                    _header = std::make_unique<Header>(command);
                };

                Packet() : _content(std::vector<char>())
                {
                    _header = std::make_unique<Header>(0, 0, 0);
                };

                Packet(Header header, std::vector<char> content) : _content(content)
                {
                    _header = std::make_unique<Header>(header);
                    _header->setSize(_content.size());
                };

                Packet(const Packet &packet) : _content(packet._content)
                {
                    _header = std::make_unique<Header>(*packet._header);
                };

                ~Packet() = default;

                void SetHeader(Header header)
                {
                    _header = std::make_unique<Header>(header);
                    _header->setSize(_content.size());
                }

                void SetContent(std::vector<char> content)
                {
                    _content = content;
                }

                void Set(Header header, std::vector<char> content)
                {
                    _header = std::make_unique<Header>(header);
                    _content = content;
                    _header->setSize(_content.size());
                }

                std::vector<char> GetBuffer() const {
                    std::vector<char> buffer(Header::GetSize() + _content.size());

                    _header->fillBuffer(buffer);
                    std::memcpy(buffer.data() + Header::GetSize(), _content.data(), _content.size());
                    return buffer;
                }

                std::unique_ptr<Header> &GetHeader() {
                    return _header;
                }

                size_t GetSize() {
                    return Header::GetSize() + _content.size();
                }

                std::vector<char> GetContent() {
                    return _content;
                }

                Packet &operator=(const Packet &packet) {
                    _header = std::make_unique<Header>(*packet._header);
                    _content = packet._content;
                    return *this;
                }
            
            protected:
            private:
                std::unique_ptr<Header> _header;
                std::vector<char> _content;
        };
    };
};

#endif /* !PACKET_HPP_ */
