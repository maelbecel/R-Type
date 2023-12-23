/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** Header
*/

#ifndef HEADER_HPP_
#define HEADER_HPP_

#include <cstring>
#include <ctime>
#include <iostream>
#include <vector>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <arpa/inet.h>
#endif

template <typename T> T swapEndianness( T value )
{
    std::reverse( reinterpret_cast<char *>( &value ), reinterpret_cast<char *>( &value ) + sizeof( T ) );
    return value;
}

namespace Exodia
{
    namespace Network
    {
        class Header
        {
          public:
            /**
             * @brief Construct a new Header object
             * Construct a new Header object with the given command, id and size
             *
             * @param command (Type: char ) The command of the header
             * @param id (Type: unsigned long) The id of the header
             * @param size (Type: unsigned long) The size of the packet
             */
            Header( unsigned char command, unsigned long id, unsigned long size )
                : _command( command ), _id( id ), _size( size )
            {
                using MillisecondsType = std::chrono::milliseconds::rep;

                MillisecondsType timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(
                                                 std::chrono::system_clock::now().time_since_epoch() )
                                                 .count();

                _timestamp = static_cast<float>( timestamp );
            }

            Header( const Header &header )
                : _command( header._command ), _timestamp( header._timestamp ), _id( header._id ),
                  _size( header._size ){};

            ~Header() = default;

            void fillBuffer( std::vector<char> &buffer ) const
            {
                size_t index = 0;

                char swappedCommand = swapEndianness( _command );
                std::memcpy( buffer.data(), &swappedCommand, sizeof( char ) );
                index += sizeof( char );

                float swappedTimestamp = swapEndianness( _timestamp );
                std::memcpy( buffer.data() + index, &swappedTimestamp, sizeof( float ) );
                index += sizeof( float );

                unsigned long swappedId = swapEndianness( _id );
                std::memcpy( buffer.data() + index, &swappedId, sizeof( unsigned long ) );
                index += sizeof( unsigned long );

                unsigned long swappedSize = swapEndianness( _size );
                std::memcpy( buffer.data() + index, &swappedSize, sizeof( unsigned long ) );
            }

            // Static function to fill a Header from a buffer
            static Header fillHeader( const std::vector<char> buffer )
            {
                size_t index = 0;

                if ( buffer.size() < 22 )
                    return Header( 0, 0, 0 );

                char swappedCommand;
                std::memcpy( &swappedCommand, buffer.data(), sizeof( char ) );
                index += sizeof( char );
                char command = swapEndianness( swappedCommand );

                float swappedTimestamp;
                std::memcpy( &swappedTimestamp, buffer.data() + index, sizeof( float ) );
                index += sizeof( float );
                float timestamp = swapEndianness( swappedTimestamp );

                unsigned long swappedId;
                std::memcpy( &swappedId, buffer.data() + index, sizeof( unsigned long ) );
                index += sizeof( unsigned long );
                unsigned long id = swapEndianness( swappedId );

                unsigned long swappedSize;
                std::memcpy( &swappedSize, buffer.data() + index, sizeof( unsigned long ) );
                unsigned long size = swapEndianness( swappedSize );

                Header header( command, id, size );
                header._timestamp = timestamp;

                return header;
            }

            static size_t GetSize() { return 22; }

            void setSize( unsigned long size ) { _size = size; }

            void SetId( unsigned long id ) { _id = id; }

            unsigned char getCommand() const { return _command; };
            float         getTimestamp() const { return _timestamp; };
            unsigned long getId() const { return _id; };
            unsigned long getSize() const { return _size; };

            friend std::ostream &operator<<( std::ostream &os, const Header &header )
            {
                os << "Command: " << header._command << std::endl;
                os << "Timestamp: " << header._timestamp << std::endl;
                os << "ID: " << header._id << std::endl;
                os << "Size: " << header._size << std::endl;
                return os;
            }

            Header &operator=( const Header &header )
            {
                _command   = header._command;
                _timestamp = header._timestamp;
                _id        = header._id;
                _size      = header._size;
                return *this;
            }

          private:
            unsigned char _command;
            float         _timestamp;
            unsigned long _id;
            unsigned long _size;
        };
    }; // namespace Network
};     // namespace Exodia

#endif /* !HEADER_HPP_ */
