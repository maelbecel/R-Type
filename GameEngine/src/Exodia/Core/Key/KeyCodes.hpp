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
    //   - Window : EXODIA_KEY_TAB  0x09            //
    //   - Linux  : EXODIA_KEY_TAB  258             //
    //////////////////////////////////////////////////

    // QWERTY Keyboard

    #define EXODIA_KEY_UNKNOWN            -1
    #define EXODIA_KEY_SPACE              32
    #define EXODIA_KEY_APOSTROPHE         39  /* ' */
    #define EXODIA_KEY_COMMA              44  /* , */
    #define EXODIA_KEY_MINUS              45  /* - */
    #define EXODIA_KEY_PERIOD             46  /* . */
    #define EXODIA_KEY_SLASH              47  /* / */
    #define EXODIA_KEY_0                  48
    #define EXODIA_KEY_1                  49
    #define EXODIA_KEY_2                  50
    #define EXODIA_KEY_3                  51
    #define EXODIA_KEY_4                  52
    #define EXODIA_KEY_5                  53
    #define EXODIA_KEY_6                  54
    #define EXODIA_KEY_7                  55
    #define EXODIA_KEY_8                  56
    #define EXODIA_KEY_9                  57
    #define EXODIA_KEY_SEMICOLON          59  /* ; */
    #define EXODIA_KEY_EQUAL              61  /* = */
    #define EXODIA_KEY_A                  65
    #define EXODIA_KEY_B                  66
    #define EXODIA_KEY_C                  67
    #define EXODIA_KEY_D                  68
    #define EXODIA_KEY_E                  69
    #define EXODIA_KEY_F                  70
    #define EXODIA_KEY_G                  71
    #define EXODIA_KEY_H                  72
    #define EXODIA_KEY_I                  73
    #define EXODIA_KEY_J                  74
    #define EXODIA_KEY_K                  75
    #define EXODIA_KEY_L                  76
    #define EXODIA_KEY_M                  77
    #define EXODIA_KEY_N                  78
    #define EXODIA_KEY_O                  79
    #define EXODIA_KEY_P                  80
    #define EXODIA_KEY_Q                  81
    #define EXODIA_KEY_R                  82
    #define EXODIA_KEY_S                  83
    #define EXODIA_KEY_T                  84
    #define EXODIA_KEY_U                  85
    #define EXODIA_KEY_V                  86
    #define EXODIA_KEY_W                  87
    #define EXODIA_KEY_X                  88
    #define EXODIA_KEY_Y                  89
    #define EXODIA_KEY_Z                  90
    #define EXODIA_KEY_LEFT_BRACKET       91  /* [ */
    #define EXODIA_KEY_BACKSLASH          92  /* \ */
    #define EXODIA_KEY_RIGHT_BRACKET      93  /* ] */
    #define EXODIA_KEY_GRAVE_ACCENT       96  /* ` */
    #define EXODIA_KEY_WORLD_1            161 /* non-US #1 */
    #define EXODIA_KEY_WORLD_2            162 /* non-US #2 */

        ///////////////////
        // Function keys //
        ///////////////////

    #define EXODIA_KEY_ESCAPE             256
    #define EXODIA_KEY_ENTER              257
    #define EXODIA_KEY_TAB                258
    #define EXODIA_KEY_BACKSPACE          259
    #define EXODIA_KEY_INSERT             260
    #define EXODIA_KEY_DELETE             261
    #define EXODIA_KEY_RIGHT              262
    #define EXODIA_KEY_LEFT               263
    #define EXODIA_KEY_DOWN               264
    #define EXODIA_KEY_UP                 265
    #define EXODIA_KEY_PAGE_UP            266
    #define EXODIA_KEY_PAGE_DOWN          267
    #define EXODIA_KEY_HOME               268
    #define EXODIA_KEY_END                269
    #define EXODIA_KEY_CAPS_LOCK          280
    #define EXODIA_KEY_SCROLL_LOCK        281
    #define EXODIA_KEY_NUM_LOCK           282
    #define EXODIA_KEY_PRINT_SCREEN       283
    #define EXODIA_KEY_PAUSE              284
    #define EXODIA_KEY_F1                 290
    #define EXODIA_KEY_F2                 291
    #define EXODIA_KEY_F3                 292
    #define EXODIA_KEY_F4                 293
    #define EXODIA_KEY_F5                 294
    #define EXODIA_KEY_F6                 295
    #define EXODIA_KEY_F7                 296
    #define EXODIA_KEY_F8                 297
    #define EXODIA_KEY_F9                 298
    #define EXODIA_KEY_F10                299
    #define EXODIA_KEY_F11                300
    #define EXODIA_KEY_F12                301
    #define EXODIA_KEY_F13                302
    #define EXODIA_KEY_F14                303
    #define EXODIA_KEY_F15                304
    #define EXODIA_KEY_F16                305
    #define EXODIA_KEY_F17                306
    #define EXODIA_KEY_F18                307
    #define EXODIA_KEY_F19                308
    #define EXODIA_KEY_F20                309
    #define EXODIA_KEY_F21                310
    #define EXODIA_KEY_F22                311
    #define EXODIA_KEY_F23                312
    #define EXODIA_KEY_F24                313
    #define EXODIA_KEY_F25                314
    #define EXODIA_KEY_KP_0               320
    #define EXODIA_KEY_KP_1               321
    #define EXODIA_KEY_KP_2               322
    #define EXODIA_KEY_KP_3               323
    #define EXODIA_KEY_KP_4               324
    #define EXODIA_KEY_KP_5               325
    #define EXODIA_KEY_KP_6               326
    #define EXODIA_KEY_KP_7               327
    #define EXODIA_KEY_KP_8               328
    #define EXODIA_KEY_KP_9               329
    #define EXODIA_KEY_KP_DECIMAL         330
    #define EXODIA_KEY_KP_DIVIDE          331
    #define EXODIA_KEY_KP_MULTIPLY        332
    #define EXODIA_KEY_KP_SUBTRACT        333
    #define EXODIA_KEY_KP_ADD             334
    #define EXODIA_KEY_KP_ENTER           335
    #define EXODIA_KEY_KP_EQUAL           336
    #define EXODIA_KEY_LEFT_SHIFT         340
    #define EXODIA_KEY_LEFT_CONTROL       341
    #define EXODIA_KEY_LEFT_ALT           342
    #define EXODIA_KEY_LEFT_SUPER         343
    #define EXODIA_KEY_RIGHT_SHIFT        344
    #define EXODIA_KEY_RIGHT_CONTROL      345
    #define EXODIA_KEY_RIGHT_ALT          346
    #define EXODIA_KEY_RIGHT_SUPER        347
    #define EXODIA_KEY_MENU               348
    #define EXODIA_KEY_LAST               EXODIA_KEY_MENU

#endif /* !KEYCODES_HPP_ */
