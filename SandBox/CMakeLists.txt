cmake_minimum_required(VERSION 3.12)

project(sandbox)

file(GLOB SUBDIRECTORIES LIST_DIRECTORIES true ${CMAKE_SOURCE_DIR}/SandBox/*)

#[[foreach(SUBDIR ${SUBDIRECTORIES})
    if(${SUBDIR} STREQUAL ${CMAKE_SOURCE_DIR}/SandBox/bin)
        continue()
    endif()

    if(IS_DIRECTORY ${SUBDIR})
        add_subdirectory(${SUBDIR})
    endif()
endforeach()]]

add_subdirectory(Ethan)
