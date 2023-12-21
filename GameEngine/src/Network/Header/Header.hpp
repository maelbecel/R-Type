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
#include <ctime>
#include <arpa/inet.h>
#include <iomanip>


template <typename T>
T swapEndianness(T value) {
    std::reverse(reinterpret_cast<char*>(&value), reinterpret_cast<char*>(&value) + sizeof(T));
    return value;
}

namespace Exodia {
    namespace Network {
        class Header {
            public:

                Header(uint8_t command) : _command(command), _timestamp(0), _id(0), _size(0)
                {
                    _timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
                };
                /**
                 * @brief Construct a new Header object
                 * Construct a new Header object with the given command, id and size
                 *
                 * @param command (Type: char ) The command of the header
                 * @param id (Type: unsigned long) The id of the header
                 * @param size (Type: unsigned long) The size of the packet
                 */
                Header(char command, unsigned long id, unsigned long size) : _command(command), _id(id), _size(size)
                {
                    _timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
                };

                Header(const Header &header) : _command(header._command), _timestamp(header._timestamp), _id(header._id), _size(header._size)
                {
                };

                ~Header() = default;

                void fillBuffer(std::vector<char>& buffer) const {
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

                    unsigned long swappedSize = swapEndianness(_size);
                    std::memcpy(buffer.data() + index, &swappedSize, sizeof(unsigned long));
                }

                // Static function to fill a Header from a buffer
                static Header fillHeader(const std::vector<char> buffer) {
                    size_t index = 0;

                    if (buffer.size() < 22)
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

                    unsigned long swappedSize;
                    std::memcpy(&swappedSize, buffer.data() + index, sizeof(unsigned long));
                    unsigned long size = swapEndianness(swappedSize);

                    Header header(command, id, size);
                    header._timestamp = timestamp;

                    return header;
                }

                static size_t GetSize()
                {
                    return 22;
                }

                void setSize(unsigned long size) {
                    _size = size;
                }

                void SetId(unsigned long id) {
                    _id = id;
                }

                char getCommand() const { return _command; };
                float getTimestamp() const { return _timestamp; };
                unsigned long getId() const { return _id; };
                unsigned long getSize() const { return _size; };


                /**
                 * @brief Return string representation of a command
                 *
                 * @param header (Type: Exodia::Network::Header) The header of the command
                 *
                 * @return std::string String representation of the command
                */
                static std::string VerbaliseCommand(const Header &header)
                {
                    std::string command;
                    std::unordered_map<char, std::string> commands;
                    commands[0x00] = "Packet info";
                    commands[0x01] = "Acknowledgement";
                    commands[0x02] = "Accept client connection";
                    commands[0x81] = "Ask for connection";
                    commands[0x82] = "New Event";
                    commands[0x0c] = "Create component";
                    command = commands[header.getCommand()];
                    if (command.empty())
                        command = "Unknown command";
                    return command;
                }

                static std::string toStr(const Header &header) {
                    std::string str;
                    str += "Command: '" + VerbaliseCommand(header) + "'";
                    std::time_t timestampAsTimeT = static_cast<std::time_t>(header._timestamp);
                    std::tm* timeInfo = std::gmtime(&timestampAsTimeT);
                    char buffer[80];
                    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeInfo);
                    str += " Timestamp: " + std::string(buffer);
                    str += " ID: " + std::to_string(header._id);
                    str += " Size: " + std::to_string(header._size);
                    return str;
                }

                friend std::ostream& operator<<(std::ostream& os, const Header& header) {
                    os << toStr(header);
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
                char _command;
                float _timestamp;
                unsigned long _id;
                unsigned long _size;
        };
    };
};


#endif /* !HEADER_HPP_ */
