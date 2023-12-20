# Game Engine

## Introduction

The Game Engine is the core of the project. It is the part that will be used by the client and the server to create the game.
It Works using an ECS (Entity-Component-System) architecture.

### What is an ECS ?

Entity-Component-System (ECS) is an architectural pattern commonly used in game development. It provides a simple and efficient way to structure game logic and manage game entities. ECS is designed to facilitate better separation of concerns and to make entities more modular and reusable.

Here's a brief explanation of each part of ECS:

- **Entity**: An entity is a general-purpose object, typically represented by a unique identifier. It doesn't contain any logic or data by itself. Instead, it serves as a container for components.

- **Component**: A component is a data container. It holds the attributes and state of an entity. For example, a "Transform" component might contain the position, rotation, and scale of an entity. Components do not contain any logic; they are purely data.

- **System**: A system contains the game logic that operates on entities. Each system works on a specific set of components. For example, a "MovementSystem" might work on all entities with "Transform" and "Velocity" components. It reads the "Velocity" component to update the "Transform" component of each entity.

The ECS pattern promotes decoupling of data and logic, making your code more modular and easier to maintain and reuse. It also helps to improve performance by enabling efficient batch processing of entities based on their components, which can be beneficial for cache coherence.

Here's a simple example of how ECS might work in a game:

1. Entities are created, such as a player entity and enemy entities.
2. Components are added to these entities. The player entity might have components like "Transform", "Health", and "InputControl". An enemy entity might have "Transform", "Health", and "AIControl".
3. Systems are created that operate on these components. For example, a "MovementSystem" that updates "Transform" based on "InputControl" or "AIControl", and a "RenderSystem" that draws entities with a "Transform" and "Sprite" component.
4. In the game loop, each system is updated in turn. The systems only operate on entities that have the required components.

This is a high-level overview of ECS. The actual implementation can vary based on the specific requirements of your game.
The entity component system provides a flexible and efficient way to represent and manage complex objects in software. Its modularity, reusability, and performance benefits make it a valuable tool for game developers and beyond.


## Architecture

The Game Engine has 3 main parts :

- **Exodia** : The core of the Game Engine. It contains the ECS and the main classes of the Game Engine.
- **Network** : The network part of the Game Engine. It contains the classes that will be used to communicate with the server.
- [**Platform**](Platform.md) : The platform part of the Game Engine. It contains the classes that will be used to communicate with the client.

There is also a [**Utils**](Utils.md) part that contains some useful classes.

## Usage

### Default Components

The Game Engine comes with a set of default components that can be used to create a game.
YOu can check it [here](Components.md)

### Default Systems

The Game Engine comes with a set of default systems that can be used to create a game.
You can check it [here](Systems.md)
