# ScriptSystem

## Description

The ScriptSystem is a system that handles scripts. It contains the scripts' data.

## Methods

### Update
```c++
void Update(World *world, Timestep ts)
```

It takes the following parameters:

- `World *world` : A pointer to the world.
- `Timestep ts` : The timestep.

The Update method is called every frame. It updates the scripts' data.

## Usage

### Create a ScriptSystem

To create a ScriptSystem, you can use the following code:

```c++
World->RegisterSystem(new ScriptSystem());
```

