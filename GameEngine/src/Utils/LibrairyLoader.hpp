/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** LibrairyLoader
*/

#ifndef LIBRAIRYLOADER_HPP_
    #define LIBRAIRYLOADER_HPP_

    #include <string>

#ifdef _WIN32
    #define WIN32_LEAN_AND_MEAN
        #include <windows.h>
#else
    #include <dlfcn.h>
#endif

namespace Exodia {

    class LibraryLoader {

        /////////////
        // Methods //
        /////////////
        public:

            static void *Load(const std::string &path)
            {
            #ifdef _WIN32
                return LoadLibraryA(path.c_str());
            #else
                return dlopen(path.c_str(), RTLD_LAZY);
            #endif
            }

            static void *GetFunction(void *handle, const std::string &name)
            {
                if (handle == nullptr)
                    return nullptr;

            #ifdef _WIN32
                return GetProcAddress((HMODULE)handle, name.c_str());
            #else
                return dlsym(handle, name.c_str());
            #endif
            }

            static void Close(void *handle)
            {
                if (handle == nullptr)
                    return;
            #ifdef _WIN32
                FreeLibrary((HMODULE)handle);
            #else
                dlclose(handle);
            #endif
            }
    };
};

#endif /* !LIBRAIRYLOADER_HPP_ */
