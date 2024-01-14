# System

Each system have an `void Update(World *world, Timestep ts)` function that is called each frame.

The R-Type have two systems :


## Clock

The `Clock` system is used to update the clock of the game.

When it is update, it will add the time since the last frame to the clock.

```c++
        world->ForEach<Clock>([&](Entity *entity, auto clock) { clock->ElapsedTime += ts; });
```

## Animation

The `Animation` system is used to update the animations of the entities.

When it is update, it will update the animation of the entity.

If the animation is finished, it will emit an `AnimationEndingEvent`.

```c++
                    if (ac.Repeat == false && ac.CurrentFrameIndex == ac.Frames.size() - 1) {
                        ac.IsPlaying = false;

                        world->Emit<Events::AnimationEndingEvent>({entity});
                    }
```