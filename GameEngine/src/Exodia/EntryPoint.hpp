/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** EntryPoint
*/

#ifndef ENTRYPOINT_HPP_
#define ENTRYPOINT_HPP_

#include "Exodia.hpp"

extern Exodia::Application *Exodia::CreateApplication(ApplicationCommandLineArgs args);

int main(int ac, char **av) {
    Exodia::Log::Init("Exodia Application");

    EXODIA_PROFILE_BEGIN_SESSION("Startup", "ExodiaProfile-Startup.json");
    Exodia::Application *App = Exodia::CreateApplication({ac, av});
    EXODIA_PROFILE_END_SESSION();

    EXODIA_PROFILE_BEGIN_SESSION("Runtime", "ExodiaProfile-Runtime.json");
    App->Run();
    EXODIA_PROFILE_END_SESSION();

    EXODIA_PROFILE_BEGIN_SESSION("Shutdown", "ExodiaProfile-Shutdown.json");
    delete App;
    EXODIA_PROFILE_END_SESSION();

    return 0;
}

#endif /* !ENTRYPOINT_HPP_ */
