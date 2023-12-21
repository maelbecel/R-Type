# EPITECH Project - R-Type

Replicate of the `rtype` game.

## Usage & Examples

### VCPKG

- Install VCPKG.

After the installation done, on Linux :

```bash
./vcpkg/bootstrap-vcpkg.sh

code ~/.bashrc
```

On the file opened, add this line at the end :

```bash
export VCPKG_ROOT=/path/vcpkg
```

Save and close the file.

```bash
source ~/.bashrc
```

## Windows

Please install `Visual Studio 17 2022`

```bash
mkdir build
cd build
cmake .. -G "Visual Studio 17 2022" -DCMAKE_TOOLCHAIN_FILE=\path\vcpkg\scripts\buildsystems\vcpkg.cmake -D_WIN32_WINNT=0x0601
cmake --build . --config Release
```

## Linux

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