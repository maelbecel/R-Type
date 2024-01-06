/*
** EXODIA PROJECT, 2023
** TryAGame
** File description:
** Level
*/

#ifndef LEVEL_HPP_
    #define LEVEL_HPP_

    #include "Exodia.hpp"

    #include "Entity/Player.hpp"

struct Obstacle {
    glm::vec3 PositionTop = { 0.0f, 10.0f, 0.0f };
    glm::vec2 TopScale = { 15.0f, 20.0f };

    glm::vec3 PositionBottom = { 10.0f, 10.0f, 0.0f };
    glm::vec2 BottomScale = { 15.0f, 20.0f };
};

class Level {

    // Constructor / Destructor (default)
    public:
        Level();
        ~Level() = default;

    // Methods
    public:
        void Init();
        void Reset();

        void OnUpdate(Exodia::Timestep ts);
        void OnRender();
        void OnImGuiRender();

        void CreateObstacle(int index, float offset);

    private:
        bool Collision();

    // Getters
    public:
        bool IsGameOver();
        Player &GetPlayer();

    // Attributes
    private:
        Player _Player;
        bool _GameOver;

        float _ObstacleTarget;
        int _ObstacleIndex;
        glm::vec3 _ObstacleHSV;

        std::vector<Obstacle> _Obstacles;

        Ref<Exodia::Texture2D> _ObstacleTexture;
};

#endif /* !LEVEL_HPP_ */
