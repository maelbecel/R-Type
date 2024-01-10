/*
** EXODIA PROJECT, 2023
** TryAGame
** File description:
** Level
*/

#ifndef LEVEL_HPP_
#define LEVEL_HPP_

#include "Exodia.hpp"

using namespace Exodia;

namespace FlappyBird {

    class Level : public Exodia::EventSubscriber<Exodia::Events::OnEntityDestroyed> {

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

        int GetScore() const { return score; };

        void Receive(UNUSED(World *world), const Events::OnEntityDestroyed &event) override {
            auto tag = event.Entity->GetComponent<TagComponent>();

            if (!tag) {
                EXODIA_WARN("Entity destroyed without tag");
                return;
            }

            auto &tg = tag.Get();

            if (tg.Tag.find("Particle") != std::string::npos)
                return;

            if (tg.Tag.find("SpaceShip") != std::string::npos)
                _GameOver = true;
            else
                EXODIA_INFO("Entity destroyed: {0}", tg.Tag);
        }

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
        Ref<Exodia::Prefabs> _PrefabObstacle;
        bool _GameOver = false;
        float _mytime = 0.0f;

        int score = 0;

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
