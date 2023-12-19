/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** TestScript
*/

#include "TestScript.hpp"
#include "iostream"

namespace RType {

    void CameraController::OnCreate()
    {
        //EXODIA_INFO("CameraController Created !");
        std::cout << "CameraController Created" << std::endl;
    }

    void CameraController::OnUpdate(Exodia::Timestep ts)
    {
        if (Exodia::Input::IsKeyPressed(Exodia::Key::A))
            EXODIA_TRACE("A key is pressed");
    }
};

EXODIA_EXPORT Exodia::ScriptableEntity *CreateScript()
{
    return new RType::CameraController();
}
