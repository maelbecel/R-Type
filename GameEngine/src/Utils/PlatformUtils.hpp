/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** PlatformUtils
*/

#ifndef PLATFORMUTILS_HPP_
#define PLATFORMUTILS_HPP_

// External include
#include <string>

namespace Exodia {

    class FileDialog {

        /////////////
        // Methods //
        /////////////
      public:
        static std::string OpenFile(const char *filter);
        static std::string SaveFile(const char *filter);
    };

    class Time {

        ///////////////////////
        // Getters & Setters //
        ///////////////////////
      public:
        static float GetTime();
    };
}; // namespace Exodia

#endif /* !PLATFORMUTILS_HPP_ */
