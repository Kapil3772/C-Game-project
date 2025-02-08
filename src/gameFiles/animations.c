#include "gameEntities.h"
#include "animations.h"
#include "utils.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <stdio.h>

// functions

// for loading all texture for a particular animation animation

Animation *load_animation(const char *folderPath, SDL_Renderer *renderer, int total_frames)
{
    Animation *anim = (Animation *)malloc(sizeof(Animation));
    if (anim == NULL)
    {
        printf("Error: Failed to allocate memory for ANIMATION STRUCT for %s\n", folderPath);
        return NULL;
    }
    anim->anim_frame = total_frames;
    anim->anim_duration = 1000 / total_frames; // for now
    anim->textureArr = (SDL_Texture **)malloc(sizeof(SDL_Texture *) * total_frames);
    if (anim->textureArr == NULL)
    {
        printf("Error: Failed to allocate memory for TEXTURE ARRAY for %s\n", folderPath);
        free(anim);
        return NULL;
    }
    else
    {
        for (int i = 0; i < anim->anim_frame; i++)
        {
            char filePath[256];
            if (i < 10)
            {
                snprintf(filePath, sizeof(filePath), "%s%s0%d.png", BASE_IMG_PATH, folderPath, i);
            }
            else
            {
                snprintf(filePath, sizeof(filePath), "%s%s%d.png", BASE_IMG_PATH, folderPath, i);
            }
            anim->textureArr[i] = loadTexture(filePath, renderer); // here anim->textureArr[i] = pointer to single texture in a textureArr array.
            if (anim->textureArr[i] == NULL)
            {
                printf("Error: Failed to load texture for frame %d of %s\n", i, folderPath);
                for (int j = 0; j < i; j++)
                {
                    SDL_DestroyTexture(anim->textureArr[j]);
                }
                free(anim->textureArr);
                free(anim);
                return NULL;
            }
        }
        return anim;
    }
}

// for loading a single texture
SDL_Texture *loadTexture(const char *filePath, SDL_Renderer *renderer)
{
    SDL_Texture *texture = NULL;
    // load image into memory
    SDL_Surface *anim_surface = IMG_Load(filePath);
    if (!anim_surface)
    {
        printf("Error: Failed to load surface for %s\nSDL_Error: '%s'\n", filePath, SDL_GetError());
        return NULL;
    }
    else
    {
        // load image into graphics hardware
        texture = SDL_CreateTextureFromSurface(renderer, anim_surface);
        if (!texture)
        {
            printf("Error: Failed to create texture for %s\nSDL_Error: '%s'\n", filePath, SDL_GetError());
            return NULL;
        }
    }
    SDL_FreeSurface(anim_surface);
    return texture;
}

// rendering animation by name
void render_animation(Animation *anim, SDL_Renderer *renderer, SDL_Rect *rect)
{
    int frames = anim->anim_frame;
    int duration = anim->anim_duration;
    int current_frame = (SDL_GetTicks() / duration) % frames;
    if (SDL_RenderCopy(renderer, anim->textureArr[current_frame], NULL, rect) != 0)
    {
        printf("Error: Failed to render texture for frame %d\n", current_frame);
    }
}

// cleanup function for animation
void free_animation(Animation *anim)
{
    if (anim != NULL)
    {
        if (anim->textureArr != NULL)
        {
            for (int i = 0; i < anim->anim_frame; i++)
            {
                if (anim->textureArr[i] != NULL)
                {
                    SDL_DestroyTexture(anim->textureArr[i]);
                }
            }
            free(anim->textureArr);
        }
        free(anim);
    }
}
