/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** MouseButtonCodes
*/

#ifndef MOUSEBUTTONCODES_HPP_
    #define MOUSEBUTTONCODES_HPP_

namespace Exodia::Mouse {

    using MouseCode = int;

    enum : MouseCode {
        BUTTON0      = 0,
        BUTTON1      = 1,
        BUTTON2      = 2,
        BUTTON3      = 3,
        BUTTON4      = 4,
        BUTTON5      = 5,
        BUTTON6      = 6,
        BUTTON7      = 7,

        BUTTONLAST   = BUTTON7,
        BUTTONLEFT   = BUTTON0,
        BUTTONRIGHT  = BUTTON1,
        BUTTONMIDDLE = BUTTON2
    };
};

#endif /* !MOUSEBUTTONCODES_HPP_ */
