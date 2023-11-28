/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Logger
*/

#include "Logger.hpp"

namespace Exodia {

    //////////////////////////////
    // Constructor & Destructor //
    //////////////////////////////

    Logger::Logger(const std::string &name) : _Name(name), _FilePattern("[%T] [%l] %v") {};

    /////////////
    // Methods //
    /////////////

    void Logger::Init(const std::string &logFile)
    {
        _LogFile.open(logFile);

        if (!_LogFile.is_open())
            std::cerr << "Failed to open log file: " << logFile << std::endl;
    }

    ///////////////////////
    // Setters & Getters //
    ///////////////////////

    void Logger::SetFilePattern(const std::string &pattern)
    {
        _FilePattern = pattern;
    }
};
