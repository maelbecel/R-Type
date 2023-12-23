/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Log
*/

#ifndef LOG_HPP_
#define LOG_HPP_

// Exodia Utils
#include "Utils/CrossPlatform.hpp"
#include "Utils/Memory.hpp"

// spdlog includes
#include <spdlog/fmt/ostr.h>
#include <spdlog/spdlog.h>

namespace Exodia
{

    /**
     * @brief Class that will be used for log
     */
    class Log
    {

        /////////////
        // Methods //
        /////////////
      public:
        /**
         * @brief Init the logger
         * Call this function for init the logger
         */
        static void Init( const std::string &appName = "Application" );

        ///////////////////////
        // Getters & Setters //
        ///////////////////////
      public:
        /**
         * @brief Get the Core Logger object
         * Call this function for get the core logger
         *
         * @return (Type: Ref<spdlog::logger> &) The core logger
         */
        inline static Ref<spdlog::logger> &GetCoreLogger() { return _CoreLogger; }

        /**
         * @brief Get the Client Logger object
         * Call this function for get the client logger
         *
         * @return (Type: Ref<spdlog::logger> &) The client logger
         */
        inline static Ref<spdlog::logger> &GetClientLogger() { return _ClientLogger; }

        ////////////////
        // Attributes //
        ////////////////
      private:
        static Ref<spdlog::logger> _CoreLogger;   /*!< The logger for the core */
        static Ref<spdlog::logger> _ClientLogger; /*!< The logger for the client */
    };
}; // namespace Exodia

#endif /* !LOG_HPP_ */
