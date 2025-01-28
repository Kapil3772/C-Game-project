#ifndef GLOBALS_H
#define GLOBALS_H

#include <SDL2/SDL.h>

// Declare shared variables
extern SDL_Renderer *renderer;
extern SDL_Texture *texture;
extern SDL_Rect leftWindow_wall, bottomWindow_wall, rightWindow_wall, player_hitbox, Wall_hitbox;

#endif