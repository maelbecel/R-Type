/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** R-Type
*/

#ifndef R_TYPE_HPP_
    #define R_TYPE_HPP_

    ///////////////////////////////////////////////
    // Main include file for R-Type              //
    // Include this file to use the R-Type logic //
    // And create your own R-Type game           //
    ///////////////////////////////////////////////

    // -- Game Engine includes -------------------------------------------------

    #include "Exodia.hpp"

    // -- R-Type Settings includes ---------------------------------------------

    #include "Settings/Config.hpp"

namespace RType {

    inline static void EntryPoint()
    {
        // -- Init the R-Type Project ------------------------------------------
        Ref<Exodia::Project> project = Exodia::Project::Load("Assets/R-Type.proj");

        // -- Register R-Type Components ---------------------------------------

        // -- Register R-Type Scripts ------------------------------------------

        // -- Register R-Type Systems ------------------------------------------
    }
};

#endif /* !R_TYPE_HPP_ */
