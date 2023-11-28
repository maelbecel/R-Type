/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Logger
*/

#ifndef LOGGER_HPP_
    #define LOGGER_HPP_

    // Exodia Utils
    #include "Utils/CrossPlatform.hpp"

    // External includes
    #include <iostream>
    #include <iomanip>
    #include <fstream>
    #include <memory>
    #include <vector>
    #include <chrono>

namespace Exodia {

    enum class LogLevel {
        TRACE, // When you want to trace a function
        INFO,  // When you want to log something
        WARN,  // When you want to log a warning
        ERROR, // When you want to log an error
        FATAL, // When you want to log a fatal error
        NONE
    };

    class EXODIA_API Logger {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
        public:

            Logger(const std::string &name);
            ~Logger() = default;

        /////////////
        // Methods //
        /////////////
        public:

            void Init(const std::string &logFile);

            template<typename ...Args>
            void Log(LogLevel level, Args && ...args)
            {
                if (level == LogLevel::NONE)
                    return;

                auto now = std::chrono::system_clock::now();
                std::time_t now_c = std::chrono::system_clock::to_time_t(now);
                std::string logLevelStr;
                std::string colorCode;

                switch (level) {
                    case LogLevel::TRACE:
                        logLevelStr = "TRACE";
                        colorCode = "\033[1;37m"; // White
                        break;
                    case LogLevel::INFO:
                        logLevelStr = "INFO";
                        colorCode = "\033[1;32m"; // Green
                        break;
                    case LogLevel::WARN:
                        logLevelStr = "WARNING";
                        colorCode = "\033[1;33m"; // Yellow
                        break;
                    case LogLevel::ERROR:
                        logLevelStr = "ERROR";
                        colorCode = "\033[1;31m"; // Red
                        break;
                    case LogLevel::FATAL:
                        logLevelStr = "FATAL";
                        colorCode = "\033[1;31m"; // Red
                        break;
                    default:
                        logLevelStr = "UNKNOWN";
                        colorCode = "";
                        break;
                }

                // Log to console with color
                std::ostringstream messageStream;

                printArgs(messageStream, std::forward<Args>(args)...);

                std::string message = messageStream.str();

                std::cout << colorCode << "[" << std::put_time(std::localtime(&now_c), "%T") << "][" << _Name << " " << logLevelStr << "] " << message << "\033[0m" << std::endl;

                // Log to file
                if (_LogFile.is_open())
                    _LogFile << "[" << std::put_time(std::localtime(&now_c), "%T") << "][" << _Name << " " << logLevelStr << "] " << message << std::endl;
            }

        private:

            /**
             * @brief End point of the recursive variadic template 'printArgs'
             */
            template<typename T>
            void printArgs(std::ostringstream &stream, T && arg)
            {
                stream << std::forward<T>(arg);
            };

            template<typename T, typename ...Args>
            void printArgs(std::ostringstream &stream, T && arg, Args && ...args)
            {
                stream << std::forward<T>(arg);

                printArgs(stream, std::forward<Args>(args)...);
            }

        ///////////////////////
        // Setters & Getters //
        ///////////////////////
        public:

            void SetFilePattern(const std::string &pattern);

        ////////////////
        // Attributes //
        ////////////////
        private:

            std::string   _Name;
            std::ofstream _LogFile;
            std::string   _FilePattern;
    };
};

#endif /* !LOGGER_HPP_ */
