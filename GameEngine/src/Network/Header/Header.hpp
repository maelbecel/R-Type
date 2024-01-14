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
        typedef enum {
            PACKET_INFO = 0x00,
            ACK = 0x01,
            CONNECT_ACCEPT = 0x02,
            CONNECT_REJECT = 0x03,
            SYSTEM_LOAD = 0x0b,
            COMPONENT_OF = 0x0c,
            GAME_EVENT = 0x0d,
            DELETE_ENTITY = 0x0e,
            DELETE_COMPONENT = 0x0f,
            IMPORTANT_EVENT = 0x10,
            CONNECT = 0x81,
            DISCONNECT = 0x82,
            EVENT = 0x8b
        } Command;
        class Header {
          public:
            Header(uint8_t command, bool isImportant)
                : _command(command), _timestamp(0), _id(0), _size(0), _isImportant(isImportant) {
                using MillisecondsType = std::chrono::milliseconds::rep;

                MillisecondsType timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(
                                                 std::chrono::system_clock::now().time_since_epoch())
                                                 .count();
                _timestamp = static_cast<double>(timestamp);
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
            Header(unsigned char command, unsigned long id, unsigned long size, bool isImportant)
                : _command(command), _id(id), _size(size), _isImportant(isImportant) {
                using MillisecondsType = std::chrono::milliseconds::rep;

                MillisecondsType timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(
                                                 std::chrono::system_clock::now().time_since_epoch())
                                                 .count();

                _timestamp = static_cast<double>(timestamp);
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

                double swappedTimestamp = swapEndianness(_timestamp);
                std::memcpy(buffer.data() + index, &swappedTimestamp, sizeof(double));
                index += sizeof(double);

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
                size_t index = 0;

                if (buffer.size() < GetSize())
                    return Header(0, 0, 0, 0);

                char swappedCommand;
                std::memcpy(&swappedCommand, buffer.data(), sizeof(char));
                index += sizeof(char);
                char command = swapEndianness(swappedCommand);

                double swappedTimestamp;
                std::memcpy(&swappedTimestamp, buffer.data() + index, sizeof(double));
                index += sizeof(double);
                double timestamp = swapEndianness(swappedTimestamp);

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

            uint64_t GetRealId() { return _id; }

            static unsigned long GetSize() { return 26; }

            void setSize(unsigned long size) { _size = size; }

            void SetId(unsigned long id) { _id = id; }

            void SetIsImportant(bool isImportant) { _isImportant = isImportant; }

            bool GetIsImportant() const { return _isImportant; }

            unsigned char getCommand() const { return _command; };
            double getTimestamp() const { return _timestamp; };
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

                commands[PACKET_INFO] = "Packet info";
                commands[ACK] = "Acknowledgement";
                commands[CONNECT_ACCEPT] = "Accept client connection";
                commands[CONNECT_REJECT] = "Reject client connection";
                commands[SYSTEM_LOAD] = "System load";
                commands[COMPONENT_OF] = "Create component";
                commands[GAME_EVENT] = "Game event";
                commands[DELETE_ENTITY] = "Delete entity";
                commands[DELETE_COMPONENT] = "Delete component";
                commands[IMPORTANT_EVENT] = "Important event";

                commands[CONNECT] = "Ask for connection";
                commands[DISCONNECT] = "Disconnect";
                commands[EVENT] = "Event";
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
                str += " Timestamp: " + std::to_string(_timestamp);

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
                _isImportant = header._isImportant;
                return *this;
            }

          private:
            unsigned char _command = 0x01;
            double _timestamp;
            unsigned long _id;
            unsigned long _size;
            bool _isImportant = false;
        };
    }; // namespace Network
};     // namespace Exodia

#endif /* !HEADER_HPP_ */
