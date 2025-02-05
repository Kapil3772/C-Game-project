#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "gameEntities.h"

typedef struct
{
    SDL_Texture **texture;
    int anim_duration;
    int anim_frame;
} Animation;



// functions declarations
Animation load_image(const char *path, SDL_Renderer *renderer);
SDL_Texture *loadTexture(const char *file, SDL_Renderer *renderer);



#endif