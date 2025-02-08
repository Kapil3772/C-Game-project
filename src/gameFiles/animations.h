#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

// Animation State
extern bool IDLE, RUNNING, DEAD, ON_GROUND;

typedef struct
{
    SDL_Texture **texture;
    int anim_duration;
    int anim_frame;
} Animation;

// functions declarations
Animation load_image(const char *path, SDL_Renderer *renderer);
SDL_Texture *loadTexture(const char *file, SDL_Renderer *renderer);
void show_animation(SDL_Renderer *, SDL_Texture *, SDL_Rect *);

#endif