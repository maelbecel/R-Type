/*
** EXODIA PROJECT, 2023
** TryAGame
** File description:
** Level
*/

#ifndef LEVEL_HPP_
#define LEVEL_HPP_

#include "Exodia.hpp"

namespace FlappyBird {

    class Level {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
      public:
        Level();
        ~Level() = default;

        /////////////
        // Methods //
        /////////////
      public:
        void OnUpdate(Exodia::Timestep ts);
        void OnRender(Exodia::Timestep ts);

        void Init();
        void Reset();

        void Play();

        void OnKeyPressed(int keyCode);

        ///////////////////////
        // Getters & Setters //
        ///////////////////////
      public:
        bool IsGameOver();

        ////////////////
        // Attributes //
        ////////////////
      private:
        Ref<Exodia::Scene> _Scene;
        bool _GameOver;

        Exodia::EditorCamera _EditorCamera;

        /*public:
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
          static const uint64_t PLAYER = 14815285158415;

          // Attributes
        private:
          Player _Player;
          bool _GameOver;

          float _ObstacleTarget;
          int _ObstacleIndex;
          glm::vec3 _ObstacleHSV;

          std::vector<Obstacle> _Obstacles;

          Ref<Exodia::Texture2D> _ObstacleTexture;*/
    };

} // namespace FlappyBird

#endif /* !LEVEL_HPP_ */
