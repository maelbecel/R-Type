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

    inline static std::string KeyCodesToString(KeyCode key) {
        switch (key) {
        case SPACE:
            return "SPACE";
        case APOSTROPHE:
            return "APOSTROPHE";
        case COMMA:
            return "COMMA";
        case MINUS:
            return "MINUS";
        case PERIOD:
            return "PERIOD";
        case SLASH:
            return "SLASH";
        case D0:
            return "D0";
        case D1:
            return "D1";
        case D2:
            return "D2";
        case D3:
            return "D3";
        case D4:
            return "D4";
        case D5:
            return "D5";
        case D6:
            return "D6";
        case D7:
            return "D7";
        case D8:
            return "D8";
        case D9:
            return "D9";
        case SEMICOLON:
            return "SEMICOLON";
        case EQUAL:
            return "EQUAL";
        case A:
            return "A";
        case B:
            return "B";
        case C:
            return "C";
        case D:
            return "D";
        case E:
            return "E";
        case F:
            return "F";
        case G:
            return "G";
        case H:
            return "H";
        case I:
            return "I";
        case J:
            return "J";
        case K:
            return "K";
        case L:
            return "L";
        case M:
            return "M";
        case N:
            return "N";
        case O:
            return "O";
        case P:
            return "P";
        case Q:
            return "Q";
        case R:
            return "R";
        case S:
            return "S";
        case T:
            return "T";
        case U:
            return "U";
        case V:
            return "V";
        case W:
            return "W";
        case X:
            return "X";
        case Y:
            return "Y";
        case Z:
            return "Z";
        case LEFTBRACKET:
            return "LEFTBRACKET";
        case BACKSLASH:
            return "BACKSLASH";
        case RIGHTBRACKET:
            return "RIGHTBRACKET";
        case GRAVEACCENT:
            return "GRAVEACCENT";
        case WORLD1:
            return "WORLD1";
        case WORLD2:
            return "WORLD2";
        case ESCAPE:
            return "ESCAPE";
        case ENTER:
            return "ENTER";
        case TAB:
            return "TAB";
        case BACKSPACE:
            return "BACKSPACE";
        case INSERT:
            return "INSERT";
        case Delete:
            return "Delete";
        case RIGHT:
            return "RIGHT";
        case LEFT:
            return "LEFT";
        case DOWN:
            return "DOWN";
        case UP:
            return "UP";
        case PAGEUP:
            return "PAGEUP";
        case PAGEDOWN:
            return "PAGEDOWN";
        case HOME:
            return "HOME";
        case END:
            return "END";
        case CAPSLOCK:
            return "CAPSLOCK";
        case SCROLLLOCK:
            return "SCROLLLOCK";
        case NUMLOCK:
            return "NUMLOCK";
        case PRINTSCREEN:
            return "PRINTSCREEN";
        case PAUSE:
            return "PAUSE";
        case F1:
            return "F1";
        case F2:
            return "F2";
        case F3:
            return "F3";
        case F4:
            return "F4";
        case F5:
            return "F5";
        case F6:
            return "F6";
        case F7:
            return "F7";
        case F8:
            return "F8";
        case F9:
            return "F9";
        case F10:
            return "F10";
        case F11:
            return "F11";
        case F12:
            return "F12";
        case F13:
            return "F13";
        case F14:
            return "F14";
        case F15:
            return "F15";
        case F16:
            return "F16";
        case F17:
            return "F17";
        case F18:
            return "F18";
        case F19:
            return "F19";
        case F20:
            return "F20";
        case F21:
            return "F21";
        case F22:
            return "F22";
        case F23:
            return "F23";
        case F24:
            return "F24";
        case F25:
            return "F25";
        case KP0:
            return "KP0";
        case KP1:
            return "KP1";
        case KP2:
            return "KP2";
        case KP3:
            return "KP3";
        case KP4:
            return "KP4";
        case KP5:
            return "KP5";
        case KP6:
            return "KP6";
        case KP7:
            return "KP7";
        case KP8:
            return "KP8";
        case KP9:
            return "KP9";
        case KPDECIMAL:
            return "KPDECIMAL";
        case KPDIVIDE:
            return "KPDIVIDE";
        case KPMULTIPLY:
            return "KPMULTIPLY";
        case KPSUBSTRACT:
            return "KPSUBSTRACT";
        case KPADD:
            return "KPADD";
        case KPENTER:
            return "KPENTER";
        case KPEQUAL:
            return "KPEQUAL";
        case LEFTSHIFT:
            return "LEFTSHIFT";
        case LEFTCONTROL:
            return "LEFTCONTROL";
        case LEFTALT:
            return "LEFTALT";
        case LEFTSUPER:
            return "LEFTSUPER";
        case RIGHTSHIFT:
            return "RIGHTSHIFT";
        case RIGHTCONTROL:
            return "RIGHTCONTROL";
        case RIGHTALT:
            return "RIGHTALT";
        case RIGHTSUPER:
            return "RIGHTSUPER";
        case MENU:
            return "MENU";
        default:
            return "Unknown";
        }
    }

    inline static KeyCode StringToKeyCode(const std::string &key) {
        if (key == "SPACE")
            return SPACE;
        if (key == "APOSTROPHE")
            return APOSTROPHE;
        if (key == "COMMA")
            return COMMA;
        if (key == "MINUS")
            return MINUS;
        if (key == "PERIOD")
            return PERIOD;
        if (key == "SLASH")
            return SLASH;
        if (key == "D0")
            return D0;
        if (key == "D1")
            return D1;
        if (key == "D2")
            return D2;
        if (key == "D3")
            return D3;
        if (key == "D4")
            return D4;
        if (key == "D5")
            return D5;
        if (key == "D6")
            return D6;
        if (key == "D7")
            return D7;
        if (key == "D8")
            return D8;
        if (key == "D9")
            return D9;
        if (key == "SEMICOLON")
            return SEMICOLON;
        if (key == "EQUAL")
            return EQUAL;
        if (key == "A")
            return A;
        if (key == "B")
            return B;
        if (key == "C")
            return C;
        if (key == "D")
            return D;
        if (key == "E")
            return E;
        if (key == "F")
            return F;
        if (key == "G")
            return G;
        if (key == "H")
            return H;
        if (key == "I")
            return I;
        if (key == "J")
            return J;
        if (key == "K")
            return K;
        if (key == "L")
            return L;
        if (key == "M")
            return M;
        if (key == "N")
            return N;
        if (key == "O")
            return O;
        if (key == "P")
            return P;
        if (key == "Q")
            return Q;
        if (key == "R")
            return R;
        if (key == "S")
            return S;
        if (key == "T")
            return T;
        if (key == "U")
            return U;
        if (key == "V")
            return V;
        if (key == "W")
            return W;
        if (key == "X")
            return X;
        if (key == "Y")
            return Y;
        if (key == "Z")
            return Z;
        if (key == "LEFTBRACKET")
            return LEFTBRACKET;
        if (key == "BACKSLASH")
            return BACKSLASH;
        if (key == "RIGHTBRACKET")
            return RIGHTBRACKET;
        if (key == "GRAVEACCENT")
            return GRAVEACCENT;
        if (key == "WORLD1")
            return WORLD1;
        if (key == "WORLD2")
            return WORLD2;
        if (key == "ESCAPE")
            return ESCAPE;
        if (key == "ENTER")
            return ENTER;
        if (key == "TAB")
            return TAB;
        if (key == "BACKSPACE")
            return BACKSPACE;
        if (key == "INSERT")
            return INSERT;
        if (key == "Delete")
            return Delete;
        if (key == "RIGHT")
            return RIGHT;
        if (key == "LEFT")
            return LEFT;
        if (key == "DOWN")
            return DOWN;
        if (key == "UP")
            return UP;
        if (key == "PAGEUP")
            return PAGEUP;
        if (key == "PAGEDOWN")
            return PAGEDOWN;
        if (key == "HOME")
            return HOME;
        if (key == "END")
            return END;
        if (key == "CAPSLOCK")
            return CAPSLOCK;
        if (key == "SCROLLLOCK")
            return SCROLLLOCK;
        if (key == "NUMLOCK")
            return NUMLOCK;
        if (key == "PRINTSCREEN")
            return PRINTSCREEN;
        if (key == "PAUSE")
            return PAUSE;
        if (key == "F1")
            return F1;
        if (key == "F2")
            return F2;
        if (key == "F3")
            return F3;
        if (key == "F4")
            return F4;
        if (key == "F5")
            return F5;
        if (key == "F6")
            return F6;
        if (key == "F7")
            return F7;
        if (key == "F8")
            return F8;
        if (key == "F9")
            return F9;
        if (key == "F10")
            return F10;
        if (key == "F11")
            return F11;
        if (key == "F12")
            return F12;
        if (key == "F13")
            return F13;
        if (key == "F14")
            return F14;
        if (key == "F15")
            return F15;
        if (key == "F16")
            return F16;
        if (key == "F17")
            return F17;
        if (key == "F18")
            return F18;
        if (key == "F19")
            return F19;
        if (key == "F20")
            return F20;
        if (key == "F21")
            return F21;
        if (key == "F22")
            return F22;
        if (key == "F23")
            return F23;
        if (key == "F24")
            return F24;
        if (key == "F25")
            return F25;
        if (key == "KP0")
            return KP0;
        if (key == "KP1")
            return KP1;
        if (key == "KP2")
            return KP2;
        if (key == "KP3")
            return KP3;
        if (key == "KP4")
            return KP4;
        if (key == "KP5")
            return KP5;
        if (key == "KP6")
            return KP6;
        if (key == "KP7")
            return KP7;
        if (key == "KP8")
            return KP8;
        if (key == "KP9")
            return KP9;
        if (key == "KPDECIMAL")
            return KPDECIMAL;
        if (key == "KPDIVIDE")
            return KPDIVIDE;
        if (key == "KPMULTIPLY")
            return KPMULTIPLY;
        if (key == "KPSUBSTRACT")
            return KPSUBSTRACT;
        if (key == "KPADD")
            return KPADD;
        if (key == "KPENTER")
            return KPENTER;
        if (key == "KPEQUAL")
            return KPEQUAL;
        if (key == "LEFTSHIFT")
            return LEFTSHIFT;
        if (key == "LEFTCONTROL")
            return LEFTCONTROL;
        if (key == "LEFTALT")
            return LEFTALT;
        if (key == "LEFTSUPER")
            return LEFTSUPER;
        if (key == "RIGHTSHIFT")
            return RIGHTSHIFT;
        if (key == "RIGHTCONTROL")
            return RIGHTCONTROL;
        if (key == "RIGHTALT")
            return RIGHTALT;
        if (key == "RIGHTSUPER")
            return RIGHTSUPER;
        if (key == "MENU")
            return MENU;

        return Unknown;
    }
}; // namespace Exodia::Key

#endif /* !KEYCODES_HPP_ */
