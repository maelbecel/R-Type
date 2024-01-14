/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Console
*/

#ifndef CONSOLE_HPP_
#define CONSOLE_HPP_

// External includes
#include <vector>
#include <string>

namespace Exodia {

    class Console {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
      public:
        Console() = default;
        ~Console() = default;

        /////////////
        // Methods //
        /////////////
      public:
        void OnImGuiRender();

        ///////////////////////
        // Getters & Setters //
        ///////////////////////
      private:
        std::vector<std::string> GetLogs();
    };
}; // namespace Exodia

#endif /* !CONSOLE_HPP_ */
