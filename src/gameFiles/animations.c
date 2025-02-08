#include "gameEntities.h"
#include "animations.h"
#include "utils.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <stdio.h>

// functions

// for loading all texture for a particular animation animation
Animation load_image(const char *folderPath, SDL_Renderer *renderer)
{
    Animation anim;
    anim.anim_frame = 0;
    anim.anim_duration = 0;
    anim.texture = (SDL_Texture **)malloc(sizeof(SDL_Texture *) * 4);
    for (int i = 0; i < 4; i++)
    {
        anim.texture[i] = loadTexture(folderPath, renderer);
    }
    return anim;
}

// for loading a single texture
SDL_Texture *loadTexture(const char *file, SDL_Renderer *renderer)
{
    SDL_Texture *texture = NULL;
    SDL_Surface *anim_surface = IMG_Load(file);
    if (!anim_surface)
    {
        printf("Error: Failed to load image\nSDL_Error: '%s'\n", SDL_GetError());
        return NULL;
    }
    else
    {
        texture = SDL_CreateTextureFromSurface(renderer, anim_surface);
        if (!texture)
        {
            printf("Error: Failed to create texture\nSDL_Error: '%s'\n", SDL_GetError());
            return NULL;
        }
    }
    SDL_FreeSurface(anim_surface);
    return texture;
}

// for showing the animation
void show_animation(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect *rect)
{
    SDL_RenderCopy(renderer, texture, NULL, rect);
}