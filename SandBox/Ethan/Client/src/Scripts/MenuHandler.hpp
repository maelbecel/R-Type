/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** MenuHandler
*/

#ifndef MENUHANDLER_HPP_
#define MENUHANDLER_HPP_

// Exodia includes
#include "Exodia.hpp"

namespace RType {

    class MenuHandler : public Exodia::ScriptableEntity {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
      public:
        MenuHandler() : _CurrentPages(0), _CurrentIndexMainMenu(0), _CurrentIndexOtherMenu(0), _CurrentColomn(0){};

        /////////////
        // Methods //
        /////////////
      public:
        void OnKeyPressed(int keycode) override;

        ////////////////
        // Attributes //
        ////////////////
      private:
        int _CurrentPages;
        int _CurrentIndexMainMenu;
        int _CurrentIndexOtherMenu;
        int _CurrentColomn;
    };
}; // namespace RType

#endif /* !MENUHANDLER_HPP_ */
