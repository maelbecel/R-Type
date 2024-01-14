/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Console
*/

#include "Console.hpp"
#include "Exodia.hpp"

namespace Exodia {

    /////////////
    // Methods //
    /////////////

    void Console::OnImGuiRender() {
        ImGui::Begin("Console");

        for (std::string &log : GetLogs())
            ImGui::Text("%s", log.c_str());

        ImGui::End();
    }

    ///////////////////////
    // Getters & Setters //
    ///////////////////////

    std::vector<std::string> Console::GetLogs() {
        LogHistory coreHistory = Log::GetCoreLoggerHistory();
        std::vector<std::string> logs;

        for (const std::string &logFileName : coreHistory.GetLogs()) {
            std::ifstream logFile(logFileName);

            if (logFile.is_open()) {
                std::string line;

                while (std::getline(logFile, line))
                    logs.push_back(line);
                logFile.close();
            }
        }

        return logs;
    }
}; // namespace Exodia
