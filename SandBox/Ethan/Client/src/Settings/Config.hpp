/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Config
*/

#ifndef CONFIG_HPP_
    #define CONFIG_HPP_

namespace RType {

    class Config {

        /////////////
        // Methods //
        /////////////
        public:

            static void Init();
            static bool Read();
            static bool Write();
    };
};

#endif /* !CONFIG_HPP_ */
