/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Log
*/

#include "Log.hpp"

namespace Exodia {

    ////////////////
    // Attributes //
    ////////////////

    Ref<Logger> Log::_CoreLogger;   /*!< The logger for the core */
    Ref<Logger> Log::_ClientLogger; /*!< The logger for the client */

    /////////////
    // Methods //
    /////////////

    void Log::Init(const std::string &logFile)
    {
        // -- Init the core logger ---------------------------------------------
        _CoreLogger = CreateRef<Logger>("Exodia");

        _CoreLogger->Init("Exodia.log");

        // -- Init the client logger -------------------------------------------
        _ClientLogger = CreateRef<Logger>(logFile);

        _ClientLogger->Init("R-Type.log");
    }
};
