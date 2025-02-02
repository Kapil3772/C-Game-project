# C-Game-project

This is a space to learn game development in C Language

## How to build(Compile) the main.c file

Step1: **cd C-Game-project** Go to the clonewd directory
Step 2: **g++ -Isrc/include -Lsrc/lib -o build/game main.c -lmingw32 -lSDL2main -lSDL2** Paste this command
Step 3: **cd build** go to the build directory where the executable is bulded...
Step 4: **./game** or **./game.exe** to run the executable file...

## Directory Structure

**This is the directory structure for this project**
C-game-project/
├── build/ # Build output folder
│ |── game.exe # Compiled executable
│ └── SDL2.dll # SDL2 DLL for runtime
├── src/  
│ |── include/SDL2 # SDL2 include files (SDL.h, etc.)
├── └──lib/ # SDL2 and other library binaries
│  
├── .vscode/ # VS Code configuration files
│ └── tasks.json # Task configuration for building the project(NOT IMPLEMENTED RN)
├── Rawfile.md # Brainstorming ideas and notes for the project
└── README.md # Project documentation
