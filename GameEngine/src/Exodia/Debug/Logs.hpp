/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Log
*/

#ifndef LOGS_HPP_
    #define LOGS_HPP_

    /////////////////////////////////////////////////
    // Main include file for Exodia Logger         //
    // Include this file to debug your application //
    // It will allow you to log messages           //
    /////////////////////////////////////////////////

    // -- Logger ---------------------------------------------------------------

    #include "Exodia/Debug/Logger/Logger.hpp"
    #include "Exodia/Debug/Logger/Log.hpp"

    // -- Macros ---------------------------------------------------------------

        // -- *Core* Logger Macros ---------------------------------------------
    #define EXODIA_CORE_TRACE(...) ::Exodia::Log::GetCoreLogger()->Log(Exodia::LogLevel::TRACE, __VA_ARGS__)
    #define EXODIA_CORE_INFO(...)  ::Exodia::Log::GetCoreLogger()->Log(Exodia::LogLevel::INFO, __VA_ARGS__)
    #define EXODIA_CORE_WARN(...)  ::Exodia::Log::GetCoreLogger()->Log(Exodia::LogLevel::WARN, __VA_ARGS__)
    #define EXODIA_CORE_ERROR(...) ::Exodia::Log::GetCoreLogger()->Log(Exodia::LogLevel::ERROR, __VA_ARGS__)
    #define EXODIA_CORE_FATAL(...) ::Exodia::Log::GetCoreLogger()->Log(Exodia::LogLevel::FATAL, __VA_ARGS__)

        // -- *Client* Logger Macros -------------------------------------------
    #define EXODIA_TRACE(...) ::Exodia::Log::GetClientLogger()->Log(Exodia::LogLevel::TRACE, __VA_ARGS__)
    #define EXODIA_INFO(...)  ::Exodia::Log::GetClientLogger()->Log(Exodia::LogLevel::INFO, __VA_ARGS__)
    #define EXODIA_WARN(...)  ::Exodia::Log::GetClientLogger()->Log(Exodia::LogLevel::WARN, __VA_ARGS__)
    #define EXODIA_ERROR(...) ::Exodia::Log::GetClientLogger()->Log(Exodia::LogLevel::ERROR, __VA_ARGS__)
    #define EXODIA_FATAL(...) ::Exodia::Log::GetClientLogger()->Log(Exodia::LogLevel::FATAL, __VA_ARGS__)

#endif /* !LOGS_HPP_ */
