# RType Game Engine Documentation

Welcome to the RType Game Engine documentation! RType is an exciting game engine project built with an Entity-Component-System (ECS) architecture. This documentation provides a comprehensive guide to help you understand and utilize the features of the RType game engine.

## Table of Contents

1. [Introduction](#introduction)
2. [What is RType?](#what-is-rtype)
3. [Getting Started](#getting-started)
    1. [Installation](#installation)
4. [Architecture](#architecture)
    1. [Entity-Component-System (ECS)](#entity-component-system-ecs)
    2. [Modules](#modules)
5. [Example](#example)

You can check [here](Game-Engine.md) for the Game Engine documentation.
You can check [here](Client.md) for the Client documentation.
You can check [here](Server.md) for the Server documentation.

## Introduction

RType is a game engine project that aims to provide game developers with a flexible and efficient framework for creating games. The engine is designed with scalability and performance in mind, making it suitable for a wide range of game development projects.

## What is RType?

![RType Logo](https://static.wikia.nocookie.net/shmup/images/d/d4/R-type_logo.png)

RType is a game engine that follows the Entity-Component-System (ECS) architectural pattern. This design promotes code reusability and maintainability by organizing game entities, components, and systems in a structured manner.


## Getting Started

### Installation

To start using RType, follow these installation steps:

```bash
git clone https://github.com/maelbecel/R-Type.git
cd rtype-game-engine
make install
```

## Architecture

### Entity-Component-System (ECS)

RType follows the ECS pattern, where:

- **Entity**: Represents an object in the game world.
- **Component**: Defines data or attributes attached to entities.
- **System**: Implements logic that operates on entities with specific components.

### Modules

RType is divided into various modules, including:

- **Core**: Contains fundamental components and systems.
- **Rendering**: Manages graphics rendering and shaders.
- **Physics**: Handles collision detection and rigid body dynamics.

## Example

There is a folder ```/Examples``` to check for example  

1. [Application](Application.md)
2. [Application with a sprite renderer](Application-with-a-sprite-renderer.md)
3. [Default System](Default-System.md)
4. [Entity Component System](Entity-Component-System.md)
5. [ImGui](ImGui.md)

Feel free to explore and learn more about each aspect of the RType game engine!

