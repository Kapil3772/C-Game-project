#include <stdio.h>
#include "src/include/SDL2/SDL.h"
#include "src/include/SDL2/SDL_timer.h"
#include "src/include/SDL2/SDL_image.h"
#include "src/gameFiles/gameEntities.h"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 720
float dampness = 0.0f;
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
    SDL_Surface *surface = IMG_Load("C:/Users/Lenovo/Desktop/C-game-pro/C-Game-project/data/images/entities/player.png");
    if (!surface)
    {
        printf("Error: Failed to load image\nSDL_Error: '%s'\n", SDL_GetError());
        // return 1;
    }

    // load image into graphics hardware
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (!texture)
    {
        printf("Error: Failed to create texture\nSDL_Error: '%s'\n", SDL_GetError());
        // return 1;
    }

    SDL_Surface *background = IMG_Load("C:/Users/Lenovo/Desktop/C-game-pro/C-Game-project/data/images/backgrounds/space.jpg");
    if (!background)
    {
        printf("Error: Failed to load image\nSDL_Error: '%s'\n", SDL_GetError());
        // return 1;
    }

    SDL_Texture *bg_texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (!bg_texture)
    {
        printf("Error: Failed to create texture\nSDL_Error: '%s'\n", SDL_GetError());
        // return 1;
    }
    // Player hitbox
    SDL_Rect window_rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_Rect rightWindow_wall = {SCREEN_WIDTH, 0, 100, WALL_THICKNESS};
    SDL_Rect bottomWindow_wall = {0, SCREEN_HEIGHT, SCREEN_WIDTH, WALL_THICKNESS};
    SDL_Rect leftWindow_wall = {-WALL_THICKNESS, 0, WALL_THICKNESS, SCREEN_HEIGHT};

    SDL_Rect player_hitbox = {PLAYER_POS_X, PLAYER_POS_Y, PLAYER_WIDTH, PLAYER_HEIGHT};

    SDL_Rect Wall_hitbox = {SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, PLAYER_WIDTH, PLAYER_HEIGHT};

    Uint32 lastTime = SDL_GetTicks();
    Uint32 currentTime;
    float deltaTime;
    // Main loop flag
    int running = 1;

    while (running)
    {
        currentTime = SDL_GetTicks();
        deltaTime = (currentTime - lastTime) / 1000.0f; // Convert milliseconds to seconds
        lastTime = currentTime;

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
                    printf("Up arrow key pressed\t Player POS:(%d, %d)\n", player_hitbox.x, player_hitbox.y);
                    if (top_collision(player_hitbox, Wall_hitbox))
                    {
                        printf("Upward collision detected\n");
                    }
                    else
                    {
                        printf("Player Jumped\n");
                        player_hitbox.y -= PLAYER_VELOCITY_Y;
                    }
                    break;
                case SDLK_DOWN:
                    printf("Down arrow key pressed\t Player POS:(%d, %d)\n", player_hitbox.x, player_hitbox.y);
                    if (bottom_collision(player_hitbox, Wall_hitbox) || bottom_window_collision(player_hitbox, bottomWindow_wall))
                    {
                        printf("Downward collision detected\n");
                    }
                    else
                    {
                        player_hitbox.y += PLAYER_VELOCITY_Y;
                    }

                    break;
                case SDLK_LEFT:
                    printf("Left arrow key pressed\t Player POS:(%d, %d)\n", player_hitbox.x, player_hitbox.y);
                    if (left_collision(player_hitbox, Wall_hitbox) || left_collision(player_hitbox, leftWindow_wall))
                    {
                        printf("Left Side Collision Detected\n");
                    }
                    else
                    {
                        player_hitbox.x -= PLAYER_VELOCITY_X;
                    }
                    break;
                case SDLK_RIGHT:
                    printf("Right arrow key pressed\t Player POS:(%d, %d)\n", player_hitbox.x, player_hitbox.y);

                    if (right_collision(player_hitbox, Wall_hitbox) || right_collision(player_hitbox, rightWindow_wall))
                    {
                        printf("Right Side Collision Detected\n");
                        player_hitbox.x = window_rect.x + window_rect.w - PLAYER_WIDTH;
                    }
                    else
                    {
                        player_hitbox.x += PLAYER_VELOCITY_X;
                    }
                default:
                    break;
                }
            }

            default:
                break;
            }

            // Update Gravity

            // Set the draw color (RGB format: red, green, blue, alpha)
            // SDL_SetRenderDrawColor(renderer, 0, 128, 255, 255); // Blue color
            // SDL_RenderClear(renderer);
            // SDL_SetRenderDrawColor(renderer, 0, 0, 220, 255); // Green color
            // SDL_RenderFillRect(renderer, &Wall_hitbox);
            // SDL_RenderPresent(renderer);
        }
        if (bottom_window_collision(player_hitbox, window_rect))
        {
            printf("Bottom window collision detected\n");
        }
        else
        {
            player_hitbox.y += ((int)(GRAVITY * deltaTime * 100));
        }

        SDL_SetRenderDrawColor(renderer, 225, 225, 225, 225); // Black
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 199, 128, 255, 255);
        SDL_RenderFillRect(renderer, &leftWindow_wall);
        SDL_RenderFillRect(renderer, &bottomWindow_wall);
        SDL_RenderFillRect(renderer, &rightWindow_wall);

        SDL_RenderCopy(renderer, texture, NULL, &player_hitbox);
        SDL_SetRenderDrawColor(renderer, 0, 0, 220, 255); // Green color
        SDL_RenderFillRect(renderer, &Wall_hitbox);
        SDL_RenderPresent(renderer);
    }

    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(texture);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
