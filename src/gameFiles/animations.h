#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

// Animation State
extern bool IDLE, RUNNING, DEAD, ON_GROUND;

typedef enum
{
    LEFT = 0,
    RIGHT = 1
} FacingDirection;

extern FacingDirection player_facing;

typedef struct
{
    SDL_Texture **textureArr;
    int anim_duration;
    int anim_frame;
} Animation;

// functions declarations
Animation *load_animation(const char *path, SDL_Renderer *renderer, int total_frames);
SDL_Texture *loadTexture(const char *file, SDL_Renderer *renderer);

void render_animation(Animation *anim, SDL_Renderer *renderer, SDL_Rect *rect);
void free_animation(Animation* anim);

void initializeAnimations();
extern Animation *player_run, *player_idle, *player_hit, *player_jump;

#endif