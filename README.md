# Platformer-In-C

A visually appealing and interactive platformer game built with SDL2 for a C class project.

## Features

- **Colorful and Animated Characters**: Vibrant colors and smooth animations
- **Platform Mechanics**: Jumping, moving platforms, and obstacles
- **User-Friendly Interface**: Clear and intuitive prompts and messages
- **Customizable Background**: Option to add background images
- **Welcome Screen**: Game title and controls instructions

## Getting Started

### Prerequisites

- SDL2: Simple DirectMedia Layer library
- SDL2_image: Image loading library for SDL2
- SDL2_mixer: Audio loading library for SDL2

### Installation

1. Clone the repository:
```sh
git clone https://github.com/Kapil3772/C-Game-project.git
cd C-Game-project
```

2. Ensure SDL2, SDL2_image, SDL2_mixer libraries are properly set up:
    - SDL2 directory: Contains SDL2, SDL2_image, SDL2_mixer header files
    - lib directory: Contains library files (libSDL2.a, libSDL2.dll, etc.)

3. Compile the project:
```sh
gcc -o build/game main.c src/gameFilesanimations.c src/gameFiles/gameEntities.c src/gameFiles/utils.c src/gameFiles/audios.c -I./src/include/SDL2 -L./src/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer
```

4. Run the game:
```sh
cd build
./game
```

## Usage

- **Welcome Screen**: Press "E" key to start
- **Controls**: 
  - Arrow keys to move and jump
- **Objective**: Navigate platforms and avoid obstacles
- **Game End**: Displays win/lose message based on outcome

## Contributing

Contributions are welcome! Please fork the repository and submit pull requests for improvements or bug fixes.

## License

This project is licensed under the MIT License. See the LICENSE file for details.

## Acknowledgements

- SDL2: Simple DirectMedia Layer
- SDL2_image: SDL_image Library

## Contact

For questions or suggestions, feel free to reach out.

Enjoy playing Platformer-SDL-C!