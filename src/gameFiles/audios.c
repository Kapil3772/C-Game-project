#include "audios.h"

Mix_Music *loadMusic(const char *path)
{
    char filePath[256];
    snprintf(filePath, sizeof(filePath), "%s%s.wav", BASE_AUDIO_PATH, path);
    Mix_Music *music = Mix_LoadMUS(filePath);
    if (music == NULL)
    {
        printf("Error: Failed to load music for '%s'\nSDL_mixer Error: '%s'\n", path, Mix_GetError());
        return NULL;
    }
    return music;
}

Mix_Chunk *loadSfx(const char *path)
{
    char filePath[256];
    snprintf(filePath, sizeof(filePath), "%s%s.wav", BASE_AUDIO_PATH, path);
    Mix_Chunk *sfx = Mix_LoadWAV(filePath);
    if (sfx == NULL)
    {
        printf("Error: Failed to load sfx for '%s'\nSDL_mixer Error: '%s'\n", path, Mix_GetError());
        return NULL;
    }
    return sfx;
}

void cleanUpAudio(void)
{
    Mix_FreeMusic(bg_music);
    bg_music = NULL;
    Mix_CloseAudio();
    Mix_Quit();
}