/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** Header
*/

#ifndef HEADER_HPP_
#define HEADER_HPP_

#include <iostream>
#include <vector>
#include <cstring>
#include <iomanip>
#define _CRT_SECURE_NO_WARNINGS
#include <ctime>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <arpa/inet.h>
#endif

template <typename T> T swapEndianness(T value) {
    std::reverse(reinterpret_cast<char *>(&value), reinterpret_cast<char *>(&value) + sizeof(T));
    return value;
}

namespace Exodia {
    namespace Network {
        class Header {
          public:
            Header(uint8_t command, bool isImportant)
                : _command(command), _timestamp(0), _id(0), _size(0), _isImportant(isImportant) {
                using MillisecondsType = std::chrono::milliseconds::rep;

                MillisecondsType timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(
                                                 std::chrono::system_clock::now().time_since_epoch())
                                                 .count();

                _timestamp = static_cast<float>(timestamp);
            };
            /**
             * @brief Construct a new Header object
             * Construct a new Header object with the given command, id and size
             *
             * @param command (Type: char ) The command of the header
             * @param id (Type: unsigned long) The id of the header
             * @param size (Type: unsigned long) The size of the packet
             * @param isImportant (Type: bool) If the packet is important or not
             */
            Header(unsigned char command, unsigned long id, unsigned long size, bool isImportant = false)
                : _command(command), _id(id), _size(size), _isImportant(isImportant) {
                using MillisecondsType = std::chrono::milliseconds::rep;

                MillisecondsType timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(
                                                 std::chrono::system_clock::now().time_since_epoch())
                                                 .count();

                _timestamp = static_cast<float>(timestamp);
            }

            Header(const Header &header)
                : _command(header._command), _timestamp(header._timestamp), _id(header._id), _size(header._size),
                  _isImportant(header._isImportant) {}

            ~Header() = default;

            void fillBuffer(std::vector<char> &buffer) const {
                size_t index = 0;

                char swappedCommand = swapEndianness(_command);
                std::memcpy(buffer.data(), &swappedCommand, sizeof(char));
                index += sizeof(char);

                float swappedTimestamp = swapEndianness(_timestamp);
                std::memcpy(buffer.data() + index, &swappedTimestamp, sizeof(float));
                index += sizeof(float);

                unsigned long swappedId = swapEndianness(_id);
                std::memcpy(buffer.data() + index, &swappedId, sizeof(unsigned long));
                index += sizeof(unsigned long);

                std::memcpy(buffer.data() + index, &_isImportant, sizeof(bool));
                index += sizeof(bool);

                unsigned long swappedSize = swapEndianness(_size);
                std::memcpy(buffer.data() + index, &swappedSize, sizeof(unsigned long));
            }

            // Static function to fill a Header from a buffer
            static Header fillHeader(const std::vector<char> buffer) {
                std::cout << "Size: " << buffer.size() << std::endl;
                size_t index = 0;

                if (buffer.size() < GetSize())
                    return Header(0, 0, 0);

                char swappedCommand;
                std::memcpy(&swappedCommand, buffer.data(), sizeof(char));
                index += sizeof(char);
                char command = swapEndianness(swappedCommand);

                float swappedTimestamp;
                std::memcpy(&swappedTimestamp, buffer.data() + index, sizeof(float));
                index += sizeof(float);
                float timestamp = swapEndianness(swappedTimestamp);

                unsigned long swappedId;
                std::memcpy(&swappedId, buffer.data() + index, sizeof(unsigned long));
                index += sizeof(unsigned long);
                unsigned long id = swapEndianness(swappedId);

                bool isImportant;
                std::memcpy(&isImportant, buffer.data() + index, sizeof(bool));
                index += sizeof(bool);

                unsigned long swappedSize;
                std::memcpy(&swappedSize, buffer.data() + index, sizeof(unsigned long));
                unsigned long size = swapEndianness(swappedSize);

                Header header(command, id, size, isImportant);
                header._timestamp = timestamp;

                return header;
            }

            uint64_t GetId() const { return _id; }

            static unsigned long GetSize() { return 22; }

            void setSize(unsigned long size) { _size = size; }

            void SetId(unsigned long id) { _id = id; }

            void SetIsImportant(bool isImportant) { _isImportant = isImportant; }

            bool GetIsImportant() const { return _isImportant; }

            unsigned char getCommand() const { return _command; };
            float getTimestamp() const { return _timestamp; };
            unsigned long getId() const { return _id; };
            unsigned long getSize() const { return _size; };

            /**
             * @brief Return string representation of a command
             *
             * @return std::string String representation of the command
             */
            std::string VerbaliseCommand() const {
                std::unordered_map<unsigned char, std::string> commands;
                std::string command;

                commands[0x00] = "Packet info";
                commands[0x01] = "Acknowledgement";
                commands[0x02] = "Accept client connection";
                commands[0x03] = "Reject client connection";
                commands[0x0b] = "System load";
                commands[0x0c] = "Create component";
                commands[0x0d] = "Game event";
                commands[0x0e] = "Delete entity";
                commands[0x0f] = "Delete component";
                commands[0x10] = "Important event";

                commands[0x81] = "Ask for connection";
                commands[0x82] = "Disconnect";
                commands[0x8b] = "Event";
                command = commands[getCommand()];

                if (command.empty())
                    command = "Unknown command";

                return command;
            }

            std::string toString() {
                std::string str;

                str += "Header: ";
                str += "'" + VerbaliseCommand() + "'";
                str += " ID: " + std::to_string(_id);
                str += " Size: " + std::to_string(_size);
                str += " Is important: " + std::to_string(_isImportant);

                return str;
            }

            friend std::ostream &operator<<(std::ostream &os, const Header &header) {
                os << "Header: ";
                os << "Command: '" << header.VerbaliseCommand() << "'";
                os << " ID: " << header._id;
                os << " Size: " << header._size;
                os << " Is important: " << header._isImportant;

                return os;
            }

            Header &operator=(const Header &header) {
                _command = header._command;
                _timestamp = header._timestamp;
                _id = header._id;
                _size = header._size;
                return *this;
            }

          private:
            unsigned char _command;
            float _timestamp;
            unsigned long _id;
            unsigned long _size;
            bool _isImportant;
        };
    }; // namespace Network
};     // namespace Exodia

#endif /* !HEADER_HPP_ */
