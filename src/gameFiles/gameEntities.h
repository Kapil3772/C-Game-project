#ifndef GAME_ENTITIES_H

#define PLAYER_POS_X 0
#define PLAYER_POS_Y 0
#define PLAYER_WIDTH 32
#define PLAYER_HEIGHT 32
#define GRAVITY 0.00
#define WALL_THICKNESS 150

#include <stdbool.h>
#include "SDL2/SDL.h"

extern float PLAYER_VELOCITY_X;
extern float PLAYER_VELOCITY_Y;

extern bool fps_flag;

// Physics Entities
extern bool collision_flag[4];

typedef struct
{
    float x, y;
    const char type;
    float w, h;
    float velocity_x, velocity_y;
} PhysicsEntity;

void updateEntity(PhysicsEntity *entity, bool movement[4]);
void renderEntity(SDL_Renderer *renderer, PhysicsEntity *entity);

// Function to check collision between two SDL_Rects
int top_collision(SDL_Rect, SDL_Rect);
int right_collision(SDL_Rect, SDL_Rect);
int left_collision(SDL_Rect, SDL_Rect);
int bottom_collision(SDL_Rect, SDL_Rect);
int bottom_window_collision(SDL_Rect, SDL_Rect);
int side_window_collision(SDL_Rect, SDL_Rect);

#endif