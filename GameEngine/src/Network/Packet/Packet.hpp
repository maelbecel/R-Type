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
                Packet() : _header(0, 0, 0, 0), _content(std::vector<char>()) {};


                ~Packet() = default;

                void setHeader(Header header) {
                    _header = header;
                }

                void setContent(std::vector<char> content) {
                    _content = content;
                }

                std::vector<char> getBuffer() const {
                    std::vector<char> buffer(Header::get_size() + _content.size());

                    _header.fillBuffer(buffer);
                    std::memcpy(buffer.data() + Header::get_size(), _content.data(), _content.size());
                    return buffer;
                }

                size_t get_size() {
                    return Header::get_size() + _content.size();
                }

            protected:
            private:
                Header _header;
                std::vector<char> _content;
        };
    };
};

#endif /* !PACKET_HPP_ */
