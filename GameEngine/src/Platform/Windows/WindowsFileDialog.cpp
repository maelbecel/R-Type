/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** WindowsFileDialog
*/

// Exodia Platform
#include "Utils/PlatformUtils.hpp"

// Exodia Debug
#include "Exodia-Debug.hpp"

// Native File Dialog include
#include <nfd.h>

#ifdef _WIN32
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#else
#define GLFW_EXPOSE_NATIVE_X11
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#endif

// External includes
#include <glm/glm.hpp>
#include <cstdlib>

namespace Exodia {

    /////////////
    // Methods //
    /////////////

    std::string FileDialog::OpenFile(const char *filter) {
        std::string path;
        nfdchar_t *outPath = nullptr;
        nfdresult_t result = NFD_OpenDialog(filter, nullptr, &outPath);

        if (result == NFD_OKAY) {
            path = outPath;

            std::free(outPath);
        }

        if (path.empty())
            return "";

        try {
            std::string extension = path.substr(path.find_last_of(".") + 1);

            if (extension != std::string(filter)) {
                EXODIA_CORE_ERROR("The file extension is not valid (expected: {0}, got: {1})", filter, extension);

                return "";
            }
        } catch (std::exception &e) {
            EXODIA_CORE_WARN("An error occured while checking the file extension: {0}", e.what());

            return "";
        }
        return path;
    }

    std::string FileDialog::SaveFile(const char *filter) {
        std::string path;
        nfdchar_t *outPath = nullptr;
        nfdresult_t result = NFD_SaveDialog(filter, nullptr, &outPath);

        if (result == NFD_OKAY) {
            path = outPath;

            std::free(outPath);
            return path;
        }
        return "";
    }
}; // namespace Exodia
