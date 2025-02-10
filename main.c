// system includes
#include <stdio.h>
#include <stdbool.h>
#include "src/include/SDL2/SDL.h"
#include "src/include/SDL2/SDL_timer.h"
#include "src/include/SDL2/SDL_image.h"
#include "src/include/SDL2/SDL_mixer.h"

// my includes
#include "src/gameFiles/gameEntities.h"
#include "src/gameFiles/animations.h"
#include "src/gameFiles/audios.h"

// Constants
#define SCREEN_WIDTH 1020
#define SCREEN_HEIGHT 638
#define TARGET_FPS 60
#define FRAME_DELAY (1000 / TARGET_FPS) // 16.67ms per frame

// Animation pointers
Animation *player_run = NULL,
          *player_idle = NULL,
          *player_hit = NULL,
          *player_jump = NULL;
// charaters facing direction flag
FacingDirection player_facing = RIGHT; // initially player will face left

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

SDL_Texture *player_texture = NULL,
            *loadingScreen = NULL,
            *gameBackground = NULL,
            *collision_area_texture = NULL,
            *bg_parallax = NULL;

Mix_Music *bg_music = NULL;
Mix_Chunk *jump = NULL;

int main(int argc, char **argv)
{

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
    {
        printf("Error: SDL failed to initialize video and timer subsystems\nSDL Error: '%s'\n", SDL_GetError());
        return 1;
    }
    // Initialize SDL_image for png support
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        printf("Error: SDL_image failed to initialize\nSDL Error: '%s'\n", SDL_GetError());
        return 1;
    }
    if (SDL_Init(SDL_INIT_AUDIO) < 0)
    {
        printf("Error: SDL failed to initialize Audio subsystem\nSDL Error: '%s'\n", SDL_GetError());
        return 1;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return 1;
    }
    // Create a window
    window = SDL_CreateWindow(
        "Ninja-game-C",         // Window title
        SDL_WINDOWPOS_CENTERED, // X position
        SDL_WINDOWPOS_CENTERED, // Y position
        SCREEN_WIDTH,           // Width
        SCREEN_HEIGHT,          // Height
        0                       // Flags
    );

    if (!window)
    {
        printf("Error: Failed to open window\nSDL Error: '%s'\n", SDL_GetError());
        return 1;
    }

    // Create a renderer for the window
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer)
    {
        printf("Error: Failed to create renderer\nSDL_Error: '%s'\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Preloading textures
    loadingScreen = loadTexture("data/images/loadingScreen.png", renderer);
    gameBackground = loadTexture("data/images/backgrounds/dark_oakwood.png", renderer);
    bg_parallax = loadTexture("data/images/backgrounds/bg_parallaxLayer.png", renderer);

    // Preloading animations
    player_run = load_animation("entities/player/run/", renderer, 16);
    player_idle = load_animation("entities/player/idle/", renderer, 10);
    player_jump = load_animation("entities/player/jump/", renderer, 1);

    // Preloading audios
    bg_music = loadMusic("game_background");
    if (Mix_PlayMusic(bg_music, -1) == -1) {
        printf("Failed to play music! SDL_Mixer Error: %s\n", Mix_GetError());
        return -1;
    }
    Mix_VolumeMusic(MIX_MAX_VOLUME);  // Max = 128
    jump = loadSfx("jump");

    // Wall entities rects
    SDL_Rect window_rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_Rect parallax_rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_Rect rightWindow_wall = {SCREEN_WIDTH - 5, 0, WALL_THICKNESS, SCREEN_HEIGHT};
    SDL_Rect bottomWindow_wall = {0, SCREEN_HEIGHT - 5, SCREEN_WIDTH, WALL_THICKNESS};
    SDL_Rect leftWindow_wall = {-WALL_THICKNESS + 5, 0, WALL_THICKNESS, SCREEN_HEIGHT};
    SDL_Rect topWindow_wall = {0, -WALL_THICKNESS + 5, SCREEN_WIDTH, WALL_THICKNESS};
    // Player entity rect
    SDL_Rect player_hitbox = {PLAYER_POS_X, PLAYER_POS_Y, PLAYER_WIDTH, PLAYER_HEIGHT};

    // Collision detection rects
    SDL_Rect collision_area3 = {226, 170, 284, 16};
    SDL_Rect collision_area = {200, 569, 208, 69};
    SDL_Rect collision_area2 = {0, 397, 284, 21};
    SDL_Rect collision_area4 = {571, 563, 449, 75};
    SDL_Rect collision_area5 = {385, 430, 75, 13};
    SDL_Rect collision_area6 = {-37, 265, 75, 13};

    // Loading Screen or Game Menu
    bool loading = 0;
    bool running = 1;
    SDL_RenderCopy(renderer, loadingScreen, NULL, &window_rect);
    while (loading)
    {
        SDL_RenderPresent(renderer);
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                loading = 0;
                running = 0;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_e:
                {
                    loading = 0;
                }
                break;
                default:
                    break;
                }
                break;
            default:
                break;
            }
        }
    }

    Uint32 frameStartTime;
    int total_time_for_executing_currentFrame;
    bool movement[2] = {false, false};
    isJumping = false;

    // MAIN GAME LOOP

    // for tracking frames
    int i = 0;
    int seconds = 0;
    int frames_counter = 0;
    int frames_per_second = 0;
    // for displaying fps only once per second
    static int log_counter = 0;
    const int LOG_INTERVAL = 60;

    while (running)
    {
        i++;
        frames_counter++;
        if (i % TARGET_FPS == 0)
        {
            seconds++;
            frames_per_second = frames_counter;
            frames_counter = 0;
        }
        frameStartTime = SDL_GetTicks();

        SDL_SetRenderDrawColor(renderer, 225, 225, 225, 225); // Black Screen
        SDL_RenderClear(renderer);

        // Update Player position
        updatePlayer(&player_hitbox, movement[1] - movement[0], 0, &collision_area, &collision_area2, &collision_area3, &collision_area4, &collision_area5, &collision_area6, isJumping); // pasing y = 0 because this is a platformer, if rpg y pani pathauthyo
        isJumping = false;

        SDL_Event event;
        // Handle events
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                running = 0;
                break;
            // Player Movements
            case SDL_KEYDOWN:
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_UP:
                {
                    // printf("Up arrow key pressed\n");
                    isJumping = true;
                }
                break;
                case SDLK_DOWN:
                {
                    // printf("Down arrow key pressed\n");
                }
                break;
                case SDLK_LEFT:
                {
                    player_facing = LEFT;
                    // printf("Left arrow key pressed\n");
                    movement[0] = true;
                }
                break;
                case SDLK_RIGHT:
                {
                    player_facing = RIGHT;
                    // printf("Right arrow key pressed\n");
                    movement[1] = true;
                }
                break;
                case SDLK_f:
                {
                    fps_flag = !fps_flag;
                }
                default:
                    break;
                }
            }
            break;
            case SDL_KEYUP:
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_UP:
                    // printf("Up arrow key released\n");
                    break;
                case SDLK_DOWN:
                    // printf("Down arrow key released\n");
                    break;
                case SDLK_LEFT:
                {
                    // printf("Left arrow key released\n");
                    movement[0] = false;
                }
                break;
                case SDLK_RIGHT:
                {
                    // printf("Right arrow key released\n");
                    movement[1] = false;
                }
                break;
                default:
                    break;
                }
            }
            break;

            default:
                break;
            }
        }

        // Rendering
        SDL_RenderCopy(renderer, gameBackground, NULL, &window_rect);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(renderer, &leftWindow_wall);
        SDL_RenderFillRect(renderer, &bottomWindow_wall);
        SDL_RenderFillRect(renderer, &rightWindow_wall);
        SDL_RenderFillRect(renderer, &topWindow_wall);
        // if (collisionCheck(&player_hitbox, &collision_area))
        // {
        //     SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        // }
        // else
        // {
        //     SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        // }
        // SDL_RenderDrawRect(renderer, &collision_area);
        // SDL_RenderDrawRect(renderer, &collision_area2);
        // SDL_RenderDrawRect(renderer, &collision_area3);
        // SDL_RenderDrawRect(renderer, &collision_area4);
        // SDL_RenderDrawRect(renderer, &collision_area5);
        // SDL_RenderDrawRect(renderer, &collision_area6);
        renderPlayer(renderer, player_texture, &player_hitbox);

        SDL_RenderCopy(renderer, bg_parallax, NULL, &parallax_rect);
        SDL_RenderPresent(renderer);

        // Fixed Frame rate control
        if (fps_flag)
        {
            log_counter++;
            if (log_counter >= LOG_INTERVAL)
            {
                printf("Frame %d took %d ms\t Total time elapsed : %d s\t True FPS = %d\n", i, total_time_for_executing_currentFrame, seconds, frames_per_second);
                log_counter = 0; // Reset the counter
            }
        }
        total_time_for_executing_currentFrame = SDL_GetTicks() - frameStartTime;

        // printf("Time taken for current frame: %d\n", total_time_for_executing_currentFrame);
        if (total_time_for_executing_currentFrame < FRAME_DELAY)
        {
            SDL_Delay(FRAME_DELAY - total_time_for_executing_currentFrame);
        }
    }

    // Clean up
    cleanUp();
    return 0;
}
