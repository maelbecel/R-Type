/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Log
*/

#ifndef LOG_HPP_
    #define LOG_HPP_

    // Exodia Debug Logger
    #include "Debug/Logger/Logger.hpp"

    // Exodia Utils
    #include "Utils/Memory.hpp"

namespace Exodia {

    /**
     * @brief Class that will be used for log
     */
    class EXODIA_API Log {

        /////////////
        // Methods //
        /////////////
        public:

            /**
             * @brief Init the logger
             * Call this function for init the logger
             */
            static void Init(const std::string &logFile = "Client.log");

        ///////////////////////
        // Getters & Setters //
        ///////////////////////
        public:

            /**
             * @brief Get the Core Logger object
             * Call this function for get the core logger
             *
             * @return (Type: Ref<Logger> &) The core logger
             */
            inline static Ref<Logger> &GetCoreLogger()
            {
                return _CoreLogger;
            }

            /**
             * @brief Get the Client Logger object
             * Call this function for get the client logger
             *
             * @return (Type: Ref<Logger> &) The client logger
             */
            inline static Ref<Logger> &GetClientLogger()
            {
                return _ClientLogger;
            }

        ////////////////
        // Attributes //
        ////////////////
        private:
            static Ref<Logger> _CoreLogger;   /*!< The logger for the core */
            static Ref<Logger> _ClientLogger; /*!< The logger for the client */
    };
};

#endif /* !LOG_HPP_ */
