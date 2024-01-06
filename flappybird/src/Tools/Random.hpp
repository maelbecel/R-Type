/*
** EXODIA PROJECT, 2023
** TryAGame
** File description:
** Random
*/

#ifndef RANDOM_HPP_
#define RANDOM_HPP_

#include <random>

class Random {

    // Methods
  public:
    static void Init() { _Engine.seed(std::random_device()()); }

    static float Float() { return (float)_Distribution(_Engine); }

    // Attributes
  private:
    static std::mt19937 _Engine;
    static std::uniform_real_distribution<float> _Distribution;
};

#endif /* !RANDOM_HPP_ */
