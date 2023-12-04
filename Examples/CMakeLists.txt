cmake_minimum_required(VERSION 3.12)

project(examples)

file(GLOB SUBDIRECTORIES LIST_DIRECTORIES true ${CMAKE_SOURCE_DIR}/Examples/*)

add_subdirectory(Application)
add_subdirectory(Entity-Component-System)
add_subdirectory(ApplicationWithSpriteRenderer)
add_subdirectory(Script)
add_subdirectory(DefaultSystem)
