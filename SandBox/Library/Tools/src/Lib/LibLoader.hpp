/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** LibrairyLoader
*/

#ifndef LIBRAIRYLOADER_HPP_
#define LIBRAIRYLOADER_HPP_

#if defined(_WIN32) || defined(_WIN64)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#define EXODIA_EXPORT extern "C" __declspec(dllexport)
#else
#include <dlfcn.h>

#define EXODIA_EXPORT extern "C"
#endif

#include <string>

namespace Exodia {

    class LibraryLoader {

        /////////////
        // Methods //
        /////////////
      public:
        static void *Load(const std::string &path) {
#ifdef _WIN32
            return LoadLibraryA(path.c_str());
#else
            return dlopen(path.c_str(), RTLD_LAZY);
#endif
        }

        static void *GetFunction(void *handle, const std::string &name) {
            if (handle == nullptr)
                return nullptr;

#ifdef _WIN32
            return GetProcAddress((HMODULE)handle, name.c_str());
#else
            return dlsym(handle, name.c_str());
#endif
        }

        static void Close(void *handle) {
            if (handle == nullptr)
                return;

#ifdef _WIN32
            FreeLibrary((HMODULE)handle);
#else
            dlclose(handle);
#endif
        }
    };
}; // namespace Exodia

#endif /* !LIBRAIRYLOADER_HPP_ */
