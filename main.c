#include <stdio.h>
#include "src/include/SDL2/SDL.h"
#include "src/include/SDL2/SDL_timer.h"
#include "src/include/SDL2/SDL_image.h"
#include "src/gameFiles/gameEntities.h"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 720

int main(int argc, char **argv)
{

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
    {
        printf("Error: SDL failed to initialize\nSDL Error: '%s'\n", SDL_GetError());
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
        return 1;
    }

    // Player hitbox
    SDL_Rect player_hitbox = {PLAYER_POS_X, PLAYER_POS_Y, PLAYER_WIDTH, PLAYER_HEIGHT};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color
    SDL_RenderFillRect(renderer, &player_hitbox);

    SDL_RenderPresent(renderer);
    // Main loop flag
    int running = 1;

    while (running)
    {
        SDL_Event event;
        // Handle events
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                running = 0;
                break;
            case SDL_KEYDOWN:
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_UP:
                    printf("Up arrow key pressed\t Player POS:(%d, %d)\n", player_hitbox.x, player_hitbox.y);
                    player_hitbox.y -= PLAYER_VELOCITY_Y;
                    break;
                case SDLK_DOWN:
                    printf("Down arrow key pressed\t Player POS:(%d, %d)\n", player_hitbox.x, player_hitbox.y);
                    player_hitbox.y += PLAYER_VELOCITY_Y;
                    break;
                case SDLK_LEFT:
                    printf("Left arrow key pressed\t Player POS:(%d, %d)\n", player_hitbox.x, player_hitbox.y);
                    player_hitbox.x -= PLAYER_VELOCITY_X;
                    break;
                case SDLK_RIGHT:
                    printf("Right arrow key pressed\t Player POS:(%d, %d)\n", player_hitbox.x, player_hitbox.y);
                    player_hitbox.x += PLAYER_VELOCITY_X;
                default:
                    break;
                }
            }

            default:
                break;
            }

            // Set the draw color (RGB format: red, green, blue, alpha)
            SDL_SetRenderDrawColor(renderer, 0, 128, 255, 255); // Blue color
            SDL_RenderClear(renderer);
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color
            SDL_RenderFillRect(renderer, &player_hitbox);

            SDL_RenderPresent(renderer);
        }
    }

    return 0;
}
