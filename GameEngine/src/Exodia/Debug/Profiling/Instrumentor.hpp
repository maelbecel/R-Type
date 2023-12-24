/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** Instrumentor
*/

#ifndef INSTRUMENTOR_HPP_
#define INSTRUMENTOR_HPP_

// Exodia Debug Profiling includes
#include "Debug/Profiling/InstrumentorTools.hpp"

// Exodia Tools
#include "Utils/CrossPlatform.hpp"

// External includes
#include <algorithm>
#include <fstream>

namespace Exodia {

    /**
     * @brief The Instrumentor class provides functionality for instrumenting code for profiling.
     * It allows starting and ending profiling sessions, writing profile results to an output stream, and managing
     * timers.
     */
    class Instrumentor {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
      public:
        Instrumentor();

        /////////////
        // Methods //
        /////////////
      public:
        /**
         * @brief Begin a new profiling session.
         *
         * @param name     (Type: const std::string &) The name of the profiling session.
         * @param filepath (Type: const std::string &) The path to the output file for profile results.
         */
        void BeginSession(const std::string &name, const std::string &filepath = "results.json");

        /**
         * @brief End the current profiling session.
         */
        void EndSession();

        /**
         * @brief Write a profile result to the output stream.
         *
         * @param result (Type: const ProfileResult &) The profile result to write.
         */
        void WriteProfile(const ProfileResult &result);

        /**
         * @brief Write the header of the profile data.
         */
        void WriteHeader();

        /**
         * @brief Write the footer of the profile data.
         */
        void WriteFooter();

        //////////////////////
        // Getter & Setters //
        //////////////////////
      public:
        /**
         * @brief Get the instance of the Instrumentor class.
         *
         * @return (Type: Instrumentor &) A reference to the Instrumentor instance.
         */
        static Instrumentor &Get() {
            static Instrumentor instance;

            return instance;
        }

        ////////////////
        // Attributes //
        ////////////////
      private:
        InstrumentationSession *_CurrentSession; /*!< Pointer to the current profiling session. */
        std::ofstream _OutputStream;             /*!< Output stream for profile results. */
        int _ProfileCount;                       /*!< Count of profile results. */
    };
}; // namespace Exodia

#endif /* !INSTRUMENTOR_HPP_ */
