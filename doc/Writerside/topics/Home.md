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
6. [Contributing](#contributing)
7. [Contact](#contact)

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

- First, you need to install VCPKG
   - On linux :
     ```bash
      git clone https://github.com/microsoft/vcpkg.git
      cd vcpkg
      ./bootstrap-vcpkg.sh
      export VCPKG_ROOT=$(pwd)
     ```
   - On windows :
     ```bash
       git clone https://github.com/microsoft/vcpkg.git
       ./vcpkg/bootstrap-vcpkg.bat
     ```
     Go on Advanced parameters for setup VCPKG_ROOT environment variable :
     `VCPKG_ROOT`: `/path/vcpkg`

- Then, you can get the project
   ```bash
   git clone https://github.com/maelbecel/R-Type.git
   cd R-Type
   git submodule update --init --recursive
   ```

- Finally, you can build the project
  - On linux :
    You can use the bash script `make.sh` if you want to try.
   
    First at all, you will have this menu when you launch the script. Here you can choose which command execute.
   
    ```bash
    Menu Make:
    1. make
    2. make re
    3. make clean
    4. make fclean
    5. Examples
    6. Sandbox
    0. Quitter
    Choisissez une option (0-6):
    ```
    
    If you choose 'Examples' (5) or 'Sandbox' (6), a new menu will be opened.
   
    ```bash
    Choisissez une option (0-6): 5
    Menu Examples:
    1. make
    2. make re
    3. make clean
    4. make fclean
    0. Retour au menu principal
    00. Quitter
    Choisissez une option (0-4):
    ```
   
    The 'Examples' section is for compiling Game-Engine examples. The goal is to try features from our Game-Engine.
   
    The 'Sandbox' section is our laboratory where we try out all the things we need or want to implement.
  
  - On windows :
   
   ```bash
   mkdir build
   cd build
   cmake ..
   cmake --build .
   ```

## Architecture

![Architechture.png](Architechture.png)

### Entity-Component-System (ECS)

RType follows the ECS pattern, where:

- **Entity**: Represents an object in the game world.
- **Component**: Defines data or attributes attached to entities.
- **System**: Implements logic that operates on entities with specific components.

ECS offers several advantages for game development:

- **Code Reusability**: Components can be reused across multiple entities, reducing code duplication and improving maintainability.
- **Modular Design**: Systems are independent of each other, allowing for flexible and extensible code.
- **Performance Efficiency**: ECS can improve performance by reducing memory access and calculations.

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

## Contributing

If you are interested in contributing to the RType game engine, please read our [contributing guidelines](CONTRIBUTING.md) for more information.

## Contact

If you have any questions or concerns, please feel free to contact us :

- Game Engine
    - [PharaEthan](https://github.com/PharaEthan)

- Client
    - [maelbecel](https://github.com/maelbecel)
    - [EnzoGrn](https://github.com/EnzoGrn)

- Server
    - [RoheeAxel](https://github.com/RoheeAxel)
    - [Chocofraise](https://github.com/thomasjuin1)