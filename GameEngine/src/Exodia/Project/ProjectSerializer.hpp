/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** ProjectSerializer
*/

#ifndef PROJECTSERIALIZER_HPP_
    #define PROJECTSERIALIZER_HPP_

    // Exodia Project includes
    #include "Project/Project.hpp"

namespace Exodia {

    class ProjectSerializer {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
        public:

            ProjectSerializer(Ref<Project> project);
            ~ProjectSerializer() = default;
        
        /////////////
        // Methods //
        /////////////
        public:

            bool Serialize(const std::filesystem::path &path);
            bool Deserialize(const std::filesystem::path &path);

        ////////////////
        // Attributes //
        ////////////////
        private:

            Ref<Project> _Project;
    };
};

#endif /* !PROJECTSERIALIZER_HPP_ */
