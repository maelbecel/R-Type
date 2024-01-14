/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Log
*/

// Exodia Debug
#include "Log.hpp"

// spdlog includes
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

// External includes
#include <vector>

namespace Exodia {

    ////////////////
    // Attributes //
    ////////////////

    Ref<spdlog::logger> Log::_CoreLogger;   /*!< The logger for the core */
    Ref<spdlog::logger> Log::_ClientLogger; /*!< The logger for the client */

    /////////////
    // Methods //
    /////////////

    void Log::Init(const std::string &appName) {
        // -- Init spdlog ------------------------------------------------------
        std::vector<spdlog::sink_ptr> logSinks;

        logSinks.emplace_back(CreateRef<spdlog::sinks::stdout_color_sink_mt>());
        logSinks.emplace_back(CreateRef<spdlog::sinks::basic_file_sink_mt>("Exodia.log", true));

        logSinks[0]->set_pattern("%^[%T] %n: %v%$");
        logSinks[1]->set_pattern("[%T] [%l] %n: %v");

        // -- Init the core logger ---------------------------------------------
        _CoreLogger = CreateRef<spdlog::logger>("EXODIA", begin(logSinks), end(logSinks));

        _CoreLogger->set_level(spdlog::level::trace);
        _CoreLogger->flush_on(spdlog::level::trace);

        spdlog::register_logger(_CoreLogger);

        // -- Init the client logger -------------------------------------------
        _ClientLogger = CreateRef<spdlog::logger>(appName, begin(logSinks), end(logSinks));

        _ClientLogger->set_level(spdlog::level::trace);
        _ClientLogger->flush_on(spdlog::level::trace);

        spdlog::register_logger(_ClientLogger);
    }

    ///////////////////////
    // Getters & Setters //
    ///////////////////////

    LogHistory Log::GetCoreLoggerHistory() {
        LogHistory history;

        for (const auto &sink : _CoreLogger->sinks()) {
            if (auto file_sink = std::dynamic_pointer_cast<spdlog::sinks::basic_file_sink_mt>(sink))
                history.AddLog(file_sink->filename());
        }
        return history;
    }

    LogHistory Log::GetClientLoggerHistory() {
        LogHistory history;

        for (const auto &sink : _ClientLogger->sinks()) {
            if (auto file_sink = std::dynamic_pointer_cast<spdlog::sinks::basic_file_sink_mt>(sink))
                history.AddLog(file_sink->filename());
        }

        return history;
    }
}; // namespace Exodia
