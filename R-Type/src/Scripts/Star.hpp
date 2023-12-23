/*
** EPITECH PROJECT, 2023
** $
** File description:
** Player
*/

#ifndef STAR_HPP_
#define STAR_HPP_

// Exodia includes
#include "Component/Clock.hpp"
#include "Exodia.hpp"
#include <random>

namespace Exodia
{

    class Star : public ScriptableEntity
    {

        /////////////
        // Methods //
        /////////////
      public:
        enum class State
        {
            GROWING = 0,
            SHRINKING,
        };

        void OnCreate() override
        {
            std::mt19937                          gen( std::random_device{}() );
            std::uniform_real_distribution<float> sizeDist( 0.01f, 0.09f );
            std::uniform_int_distribution<int>    intensityDist( 1, 255 );
            std::uniform_int_distribution<int>    stateDist( 0, 1 );

            auto camera = HandleEntity->GetWorld()->GetEntityByTag( "Camera" )->GetComponent<TransformComponent>();

            float max_height = 20.0f;
            int   height     = 40;

            _size      = sizeDist( gen );
            _intensity = intensityDist( gen ) / 255.0f;
            _State     = stateDist( gen ) ? State::GROWING : State::SHRINKING;

            auto  transform = GetComponent<TransformComponent>();
            auto &tc        = transform.Get();
            tc.Translation.x =
                (float) ( 10 + std::uniform_int_distribution<int>( 0, 19 )( gen ) ) + camera.Get().Translation.x;
            tc.Translation.y = max_height - (float) ( std::uniform_int_distribution<int>( 0, height )( gen ) );
            tc.Scale.x       = _size;
            tc.Scale.y       = _size;
        }

        void OnUpdate( Timestep ts ) override
        {
            auto &mytime    = GetComponent<Clock>().Get().ElapsedTime;
            auto  transform = GetComponent<TransformComponent>();
            auto  circle    = GetComponent<CircleRendererComponent>();
            auto  camera    = HandleEntity->GetWorld()->GetEntityByTag( "Camera" )->GetComponent<TransformComponent>();

            mytime += ts.GetMilliseconds();

            if ( circle )
            {
                auto &cc = circle.Get();

                _intensity += ( _State == State::GROWING ) ? (float) ( ts.GetSeconds() * 0.1 )
                                                           : (float) ( ts.GetSeconds() * 0.1 * -1 );

                if ( _intensity <= 0.01f )
                    _State = State::GROWING;
                else if ( _intensity >= 0.99f )
                    _State = State::SHRINKING;
                cc.Color.a = _intensity;
            }

            if ( transform.Get().Translation.x < camera.Get().Translation.x - 12 )
            {
                std::mt19937                       gen( std::random_device{}() );
                std::uniform_int_distribution<int> xDist( 10, 19 );
                std::uniform_int_distribution<int> yDist( -5, 5 );

                transform.Get().Translation.x = (float) ( xDist( gen ) ) + camera.Get().Translation.x;
                transform.Get().Translation.y = (float) ( yDist( gen ) );
            }
        }

        ////////////////
        // Attributes //
        ////////////////
      private:
        float _intensity;
        State _State;
        float _size;
    };
}; // namespace Exodia

#endif /* !STAR_HPP_ */
