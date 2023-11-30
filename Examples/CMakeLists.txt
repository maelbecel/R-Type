cmake_minimum_required(VERSION 3.12)

project(examples)

file(GLOB SUBDIRECTORIES LIST_DIRECTORIES true ${CMAKE_SOURCE_DIR}/Examples/*)

foreach(SUBDIR ${SUBDIRECTORIES})
    if(IS_DIRECTORY ${SUBDIR})
        add_subdirectory(${SUBDIR})
    endif()
endforeach()
