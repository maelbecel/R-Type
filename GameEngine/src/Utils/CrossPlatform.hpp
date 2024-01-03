/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** Cross-Platform
*/

#ifndef CROSSPLATFORM_HPP_
#define CROSSPLATFORM_HPP_

#if defined(_WIN32) || defined(_WIN64)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#define EXODIA_EXPORT extern "C" __declspec(dllexport)
#else
#define EXODIA_EXPORT extern "C"
#endif

#endif /* !CROSSPLATFORM_HPP_ */
