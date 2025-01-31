// system includes
#include <stdio.h>
#include <stdbool.h>
#include "src/include/SDL2/SDL.h"
#include "src/include/SDL2/SDL_timer.h"
#include "src/include/SDL2/SDL_image.h"

// my includes
#include "src/gameFiles/gameEntities.h"

// Constants
#define SCREEN_WIDTH 816
#define SCREEN_HEIGHT 384
#define TARGET_FPS 60
#define FRAME_DELAY (1000 / TARGET_FPS) // 16.67ms per frame

int main(int argc, char **argv)
{

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
    {
        printf("Error: SDL failed to initialize\nSDL Error: '%s'\n", SDL_GetError());
        return 1;
    }
    // Initialize SDL_image for png support
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        printf("Error: SDL_image failed to initialize\nSDL Error: '%s'\n", SDL_GetError());
        return 1;
    }
    // Create a window
    SDL_Window *window = SDL_CreateWindow(
        "Game",                 // Window title
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
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer)
    {
        printf("Error: Failed to create renderer\nSDL_Error: '%s'\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // load image into memory
    SDL_Surface *surface = IMG_Load("C:/Users/Lenovo/Desktop/C-game-pro/C-Game-project/data/images/entities/Actor1_1.png");
    if (!surface)
    {
        printf("Error: Failed to load image\nSDL_Error: '%s'\n", SDL_GetError());
        return 1;
    }

    // load image into graphics hardware
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (!texture)
    {
        printf("Error: Failed to create texture\nSDL_Error: '%s'\n", SDL_GetError());
        return 1;
    }

    // Wall entities rects
    SDL_Rect window_rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_Rect rightWindow_wall = {SCREEN_WIDTH - 5, 0, WALL_THICKNESS, SCREEN_HEIGHT};
    SDL_Rect bottomWindow_wall = {0, SCREEN_HEIGHT - 5, SCREEN_WIDTH, WALL_THICKNESS};
    SDL_Rect leftWindow_wall = {-WALL_THICKNESS + 5, 0, WALL_THICKNESS, SCREEN_HEIGHT};
    SDL_Rect topWindow_wall = {0, -WALL_THICKNESS + 5, SCREEN_WIDTH, WALL_THICKNESS};
    // Player entity rect
    SDL_Rect player_hitbox = {PLAYER_POS_X, PLAYER_POS_Y, PLAYER_WIDTH, PLAYER_HEIGHT};

    // Collision detection rects
    SDL_Rect collision_area = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 100, 150};

    Uint32 lastTime = SDL_GetTicks();
    Uint32 frameStartTime;
    int total_time_for_executing_currentFrame;

    bool movement[4] = {false, false, false, false};

    // MAIN GAME LOOP
    bool running = 1;

    // for tracking frames
    int i = 0;
    int seconds = 0;
    int frames_counter = 0;
    int frames_per_second = 0;

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

        SDL_SetRenderDrawColor(renderer, 225, 225, 225, 225); // Black
        SDL_RenderClear(renderer);

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
                    printf("Up arrow key pressed\n");
                    movement[0] = true;
                }
                break;
                case SDLK_DOWN:
                {
                    printf("Down arrow key pressed\n");
                    movement[1] = true;
                }
                break;
                case SDLK_RIGHT:
                {
                    printf("Right arrow key pressed\n");
                    movement[2] = true;
                }
                break;
                case SDLK_LEFT:
                {
                    printf("Left arrow key pressed\n");
                    movement[3] = true;
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
                    printf("Up arrow key released\n");
                    movement[0] = false;
                    break;
                case SDLK_DOWN:
                    printf("Down arrow key released\n");
                    movement[1] = false;
                    break;
                case SDLK_RIGHT:
                {
                    printf("Right arrow key released\n");
                    movement[2] = false;
                }
                break;
                case SDLK_LEFT:
                {
                    printf("Left arrow key released\n");
                    movement[3] = false;
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
        // Update Player position
        player_hitbox.y = player_hitbox.y + ((int)(movement[1]) - (int)(movement[0])) * PLAYER_VELOCITY_Y;
        player_hitbox.x = player_hitbox.x + ((int)(movement[2]) - (int)(movement[3])) * PLAYER_VELOCITY_X;

        // Rendering
        SDL_SetRenderDrawColor(renderer, 199, 128, 255, 255);
        SDL_RenderFillRect(renderer, &leftWindow_wall);
        SDL_RenderFillRect(renderer, &bottomWindow_wall);
        SDL_RenderFillRect(renderer, &rightWindow_wall);
        SDL_RenderFillRect(renderer, &topWindow_wall);
        SDL_RenderCopy(renderer, texture, NULL, &player_hitbox);
        SDL_RenderDrawRect(renderer, &collision_area);
        SDL_RenderPresent(renderer);

        // Fixed Frame rate control
        total_time_for_executing_currentFrame = SDL_GetTicks() - frameStartTime;
        // printf("Time taken for current frame: %d\n", total_time_for_executing_currentFrame);
        if (total_time_for_executing_currentFrame < FRAME_DELAY)
        {
            SDL_Delay(FRAME_DELAY - total_time_for_executing_currentFrame);
            if (fps_flag)
            {
                printf("Frame %d took %d ms\t Total time elapsed : %d s\t True FPS = %d\n", i, total_time_for_executing_currentFrame, seconds, frames_per_second);
            }
        }
    }

    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(texture);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
