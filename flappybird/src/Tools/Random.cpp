/*
** EXODIA PROJECT, 2023
** TryAGame
** File description:
** Random
*/

#include "Random.hpp"

std::mt19937 Random::_Engine;
std::uniform_real_distribution<float> Random::_Distribution(0.0f, 1.0f);
