# Pata-pata

The Pata-pata is a mob that move in a sinusoidal way.

## CreateAnimations

```c++
void PataPata::CreateAnimations()
```

The `CreateAnimations` function create the animations of the pata-pata.

## OnCreate

```c++
void PataPata::OnCreate()
```

The `OnCreate` function is called when the entity is created.

It set all the components that the entity need.

Then it start the animation.

```c++
CreateAnimations();
```

And finally it emit an `OnEntityCreated` event.

## UpdateAnimations

```c++
void PataPata::UpdateAnimations()
```

The `UpdateAnimations` function update the animations of the pata-pata.


## OnUpdate

```c++
void PataPata::OnUpdate(Timestep ts)
```

The `OnUpdate` function is called when the entity is updated.

He will check if the entity is dead.

```c++
IsDead();
```

Then update the animation.

```c++
UpdateAnimations();
```

Then make a sinusoidal movement.

```c++
SinusoidalMovement(ts);
```

And finally shoot a bullet.

```c++
Shoot();
```

## OnCollisonEnter

```c++
void PataPata::OnCollisionEnter(Entity *entity)
```

The `OnCollisionEnter` function is called when the entity collide with another entity.

If it's a bullet, it will emit a `TakeDamage` event.

```c++
            HandleEntity->GetWorld()->Emit<Events::TakeDamage>({HandleEntity, 1});
```

## Shoot

```c++
void PataPata::Shoot()
```

The `Shoot` function shoot a bullet.

It will check the attack cooldown and if it's under it, it will create a new entity `BulletEnnemy`.


## SinusoidalMovement

```c++
void PataPata::SinusoidalMovement(Timestep ts)
```

The `SinusoidalMovement` function make a sinusoidal movement.

```c++
        double amplitude = 5.0f; // Amplitude of the sinusoidal movement
        double frequency = 1.0f; // Frequency of the sinusoidal movement
        float &mytime = clock.Get().ElapsedTime;

        if (_State == State::ALIVE) {
            body.Get().Velocity.y = (float)(amplitude * sin(frequency * mytime * PI));
        }
```

## IsDead

```c++
void PataPata::IsDead()
```

The `IsDead` function check if the entity is dead.

It will check if the entity `HealthComponent` component is under 0.