/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** KeyCodes
*/

#ifndef KEYCODES_HPP_
#define KEYCODES_HPP_

//////////////////////////////////////////////////
// TODO: Change this define for Windows version //
// Compatible only with Linux and MacOS now     //
// Windows version will be added soon           //
// Example :                                    //
//   - Window : Exodia::Key::TAB  0x09          //
//   - Linux  : Exodia::Key::TAB  258           //
//////////////////////////////////////////////////

namespace Exodia::Key {

    using KeyCode = int;

    // QWERTY Keyboard (From glfw3.h)
    enum : KeyCode {
        Unknown = -1,
        SPACE = 32,
        APOSTROPHE = 39, /* ' */
        COMMA = 44,      /* , */
        MINUS = 45,      /* - */
        PERIOD = 46,     /* . */
        SLASH = 47,      /* / */

        D0 = 48, /* 0 */
        D1 = 49, /* 1 */
        D2 = 50, /* 2 */
        D3 = 51, /* 3 */
        D4 = 52, /* 4 */
        D5 = 53, /* 5 */
        D6 = 54, /* 6 */
        D7 = 55, /* 7 */
        D8 = 56, /* 8 */
        D9 = 57, /* 9 */

        SEMICOLON = 59, /* ; */
        EQUAL = 61,     /* = */

        A = 65,
        B = 66,
        C = 67,
        D = 68,
        E = 69,
        F = 70,
        G = 71,
        H = 72,
        I = 73,
        J = 74,
        K = 75,
        L = 76,
        M = 77,
        N = 78,
        O = 79,
        P = 80,
        Q = 81,
        R = 82,
        S = 83,
        T = 84,
        U = 85,
        V = 86,
        W = 87,
        X = 88,
        Y = 89,
        Z = 90,

        LEFTBRACKET = 91,  /* [ */
        BACKSLASH = 92,    /* \ */
        RIGHTBRACKET = 93, /* ] */
        GRAVEACCENT = 96,  /* ` */

        WORLD1 = 161, /* non-US #1 */
        WORLD2 = 162, /* non-US #2 */

        ///////////////////
        // Function keys //
        ///////////////////
        ESCAPE = 256,
        ENTER = 257,
        TAB = 258,
        BACKSPACE = 259,
        INSERT = 260,
        Delete = 261, // DELETE Already defined in windows.h
        RIGHT = 262,
        LEFT = 263,
        DOWN = 264,
        UP = 265,
        PAGEUP = 266,
        PAGEDOWN = 267,
        HOME = 268,
        END = 269,
        CAPSLOCK = 280,
        SCROLLLOCK = 281,
        NUMLOCK = 282,
        PRINTSCREEN = 283,
        PAUSE = 284,
        F1 = 290,
        F2 = 291,
        F3 = 292,
        F4 = 293,
        F5 = 294,
        F6 = 295,
        F7 = 296,
        F8 = 297,
        F9 = 298,
        F10 = 299,
        F11 = 300,
        F12 = 301,
        F13 = 302,
        F14 = 303,
        F15 = 304,
        F16 = 305,
        F17 = 306,
        F18 = 307,
        F19 = 308,
        F20 = 309,
        F21 = 310,
        F22 = 311,
        F23 = 312,
        F24 = 313,
        F25 = 314,

        ////////////
        // Keypad //
        ////////////
        KP0 = 320,
        KP1 = 321,
        KP2 = 322,
        KP3 = 323,
        KP4 = 324,
        KP5 = 325,
        KP6 = 326,
        KP7 = 327,
        KP8 = 328,
        KP9 = 329,
        KPDECIMAL = 330,
        KPDIVIDE = 331,
        KPMULTIPLY = 332,
        KPSUBSTRACT = 333,
        KPADD = 334,
        KPENTER = 335,
        KPEQUAL = 336,

        LEFTSHIFT = 340,
        LEFTCONTROL = 341,
        LEFTALT = 342,
        LEFTSUPER = 343,
        RIGHTSHIFT = 344,
        RIGHTCONTROL = 345,
        RIGHTALT = 346,
        RIGHTSUPER = 347,
        MENU = 348,
        LAST = MENU
    };
}; // namespace Exodia::Key

#endif /* !KEYCODES_HPP_ */
