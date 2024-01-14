/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Statistics
*/

#ifndef STATISTICS_HPP_
#define STATISTICS_HPP_

namespace Exodia {

    class StatistcsPanel {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
      public:
        StatistcsPanel() = default;
        ~StatistcsPanel() = default;

        /////////////
        // Methods //
        /////////////
      public:
        void OnImGuiRender();
    };
}; // namespace Exodia

#endif /* !STATISTICS_HPP_ */
