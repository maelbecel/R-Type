/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** Instrumentor
*/

// Exodia Debug
#include "Instrumentor.hpp"

namespace Exodia {

    //////////////////////////////
    // Constructor & Destructor //
    //////////////////////////////
    
    Instrumentor::Instrumentor() : _CurrentSession(nullptr), _ProfileCount(0) {};

    /////////////
    // Methods //
    /////////////

    void Instrumentor::BeginSession(const std::string &name, const std::string &filepath)
    {
        // If a session is already running, then close it before starting a new one
        if (_CurrentSession != nullptr)
            EndSession();

        _OutputStream.open(filepath);

        WriteHeader();

        _CurrentSession = new InstrumentationSession({ name });
    }

    void Instrumentor::EndSession()
    {
        WriteFooter();

        _OutputStream.close();

        if (_CurrentSession != nullptr) {
            delete _CurrentSession;
            _CurrentSession = nullptr;
        }

        _ProfileCount = 0;
    }

    void Instrumentor::WriteProfile(const ProfileResult &result)
    {
        // If a session is not running, then don't write profile results
        if (_CurrentSession == nullptr)
            return;

        // If this is not the first profile result, then add a comma to separate the results
        if (_ProfileCount++ > 0)
            _OutputStream << ",";

        // Write the profile result to the output stream
        std::string name = result.Name;
        std::replace(name.begin(), name.end(), '"', '\'');

        _OutputStream << "{";                                              // Start of the profile result
        _OutputStream << "\"cat\":\"function\",";                          // Event category
        _OutputStream << "\"dur\":" << (result.End - result.Start) << ','; // Duration in microseconds
        _OutputStream << "\"name\":\"" << name << "\",";                   // Name of the profile result
        _OutputStream << "\"ph\":\"X\",";                                  // Event type
        _OutputStream << "\"pid\":0,";                                     // Process ID
        _OutputStream << "\"tid\":" << result.ThreadID << ",";             // Thread ID
        _OutputStream << "\"ts\":" << result.Start;                        // Start time of the profile result
        _OutputStream << "}";                                              // End of the profile result

        _OutputStream.flush();
    }

    void Instrumentor::WriteHeader()
    {
        // Write the header of the profile data
        _OutputStream << "{\"otherData\": {},\"traceEvents\":[";
        _OutputStream.flush();
    }

    void Instrumentor::WriteFooter()
    {
        // Write the footer of the profile data
        _OutputStream << "]}";
        _OutputStream.flush();
    }
};
