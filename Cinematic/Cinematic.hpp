/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** R-Type
*/

#ifndef CINEMATIC_HPP_
#define CINEMATIC_HPP_

#include "Exodia.hpp"
#include "Scripts/Train.hpp"

namespace Cinematic {

    inline static void InitCinematic() {
        // -- Init the Cinematic project ------------------------------------------
#ifdef _WIN32
        Ref<Exodia::Project> project = Exodia::Project::Load("../CinematicClient/Cinematic.proj");
#else
        Ref<Exodia::Project> project = Exodia::Project::Load("./CinematicClient/Cinematic.proj");
#endif

        project->RegisterScript("Train", []() -> Exodia::ScriptableEntity * { return new Cinematic::Train(); });

    }
}; // namespace Cinematic

#endif /* !CINEMATIC_HPP_ */