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

    #include "Exodia/Debug/Logger/Log.hpp"

    // -- Macros ---------------------------------------------------------------

        // -- *Core* Logger Macros ---------------------------------------------
    #define EXODIA_CORE_TRACE(...) ::Exodia::Log::GetCoreLogger()->trace(__VA_ARGS__)
    #define EXODIA_CORE_INFO(...)  ::Exodia::Log::GetCoreLogger()->info(__VA_ARGS__)
    #define EXODIA_CORE_WARN(...)  ::Exodia::Log::GetCoreLogger()->warn(__VA_ARGS__)
    #define EXODIA_CORE_ERROR(...) ::Exodia::Log::GetCoreLogger()->error(__VA_ARGS__)
    #define EXODIA_CORE_FATAL(...) ::Exodia::Log::GetCoreLogger()->fatal(__VA_ARGS__)

        // -- *Client* Logger Macros -------------------------------------------
    #define EXODIA_TRACE(...) ::Exodia::Log::GetClientLogger()->trace(__VA_ARGS__)
    #define EXODIA_INFO(...)  ::Exodia::Log::GetClientLogger()->info(__VA_ARGS__)
    #define EXODIA_WARN(...)  ::Exodia::Log::GetClientLogger()->warn(__VA_ARGS__)
    #define EXODIA_ERROR(...) ::Exodia::Log::GetClientLogger()->error(__VA_ARGS__)
    #define EXODIA_FATAL(...) ::Exodia::Log::GetClientLogger()->fatal(__VA_ARGS__)

#endif /* !LOGS_HPP_ */
