# EPITECH Project - R-Type

<a href="https://img.shields.io/badge/MADE%20WITH-C%2B%2B-015482" alt="C++">
    <img src="https://img.shields.io/badge/MADE%20WITH-C%2B%2B-015482" />
</a>
<a href="https://img.shields.io/badge/MADE%20WITH-OpenGL-63809f" alt="OpenGL">
    <img src="https://img.shields.io/badge/MADE%20WITH-OpenGL-63809f">
</a>
<a href="https://img.shields.io/badge/MADE%20WITH-VCPKG-f9c438" alt="Vcpkg">
    <img src="https://img.shields.io/badge/MADE%20WITH-VCPKG-f9c438" />
</a>
<a href="https://img.shields.io/badge/MADE%20WITH-CMAKE-CB2030" alt="Cmake">
    <img src="https://img.shields.io/badge/MADE%20WITH-CMAKE-CB2030" />
</a>

![Alt text](doc/RType.png)

> This project of the Advanced C++ knowledge unit will introduce you to networked video game development, and will give you the opportunity to explore advanced development techniques as well as to learn good software engineering practices.
The goal is to implement a multithreaded server and a graphical client for a well-known legacy video game called 'R-Type', using a game engine of your own design.

## Table of Contents

1. [Usage & Examples](#usage--examples)
    1. [VCPKG](#vcpkg)
    2. [Windows](#windows)
    3. [Linux](#linux)
2. [UML](#uml)
3. [Contact](#contact)
4. [Documentation](#documentation)

## Usage & Examples

### VCPKG

- Install VCPKG.

After the installation done, on Linux :

```bash
git clone git@github.com:microsoft/vcpkg.git
```

### Linux
```bash
./vcpkg/bootstrap-vcpkg.sh
export VCPKG_ROOT=/path/vcpkg
source ~./bashrc
```
```bash
mkdir build
cd build
```

If you have ninja:
```
cmake .. -G Ninja
ninja
```
else:
```bash
cmake ..
cmake --build .
```

### Windows :
```bash
./vcpkg/bootstrap-vcpkg.bat
```
- In advanced parameters system, add the environnement variable : `VCPKG_ROOT`, that contain the `/path/vcpkg`.
- When it's done, restart your computer.

```bash
cmake ..
cmake --build .
```

### Flags :

- `-DCOMPILE_DEBUG=ON`: Compile the project in debug mode.
- `-DCOMPILE_EXAMPLES=ON`: Compile the examples.
- `-DCOMPILE_FLAPPYBIRD=ON`: Compile the flappy bird game.
- `-DCOMPILE_SOLORTYPE=ON`: Compile the solo r-type game.
- `-DCOMPILE_EDITOR=ON`: Compile the editor.
All the flags can be combined.
For found executable, just go into the `Release` folder. They are classified by folder.

## Usage & Examples

**Products to be delivered**
`r-type_server` `r-type_client` # They are all located in the Release folder

**In Terminal**
```bash
./r-type_server
```

**In another terminal**
```bash
./r-type_client [PORT] [IP SERVER] [PORT]
```

## UML
![GameEngine](doc/GameEngine.jpeg)

## Contact

If you have any questions or concerns, please feel free to contact us :

- Game Engine
    - [PharaEthan](https://github.com/PharaEthan) ethan.hernou@epitech.eu

- Client
    - [maelbecel](https://github.com/maelbecel) mael1.becel@epitech.eu
    - [EnzoGrn](https://github.com/EnzoGrn) enzo.garnier@epitech.eu

- Server
    - [RoheeAxel](https://github.com/RoheeAxel) axel.rohee@epitech.eu
    - [Chocofraise](https://github.com/thomasjuin1) thomas.juin@epitech.eu

## Documentation

You can read the full documentation [here](http://etipech.me)
