#ifndef AUDIO_H
#define AUDIO_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "SDL2/SDL_mixer.h"

#include "utils.h"

Mix_Music * loadMusic(const char *path);
Mix_Chunk * loadSfx(const char *path);
extern Mix_Music *bg_music;
extern Mix_Chunk *jump;
void cleanUpAudio(void);

#endif