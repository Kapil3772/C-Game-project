#ifndef GAME_ENTITIES_H

#include <stdbool.h>
extern bool running, loading;

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
extern bool movement[4];
extern bool fps_flag;
extern SDL_Rect player_hitbox, collision_area;
extern SDL_Texture *player_texture;
extern int player_movement[2];
extern const float TERMINAL_VELOCITY;
// Physics Entities
extern bool collision_flag[4];

typedef struct
{
    int x, y;
    int w, h;
} PhysicsEntity;

float min(float, float);

void updatePlayer(SDL_Rect *, int movement_x, int movement_y);
void renderPlayer(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect *rect);

// Function to check collision between two SDL_Rects
int top_collision(SDL_Rect, SDL_Rect);
int right_collision(SDL_Rect, SDL_Rect);
int left_collision(SDL_Rect, SDL_Rect);
int bottom_collision(SDL_Rect, SDL_Rect);
int bottom_window_collision(SDL_Rect, SDL_Rect);
int side_window_collision(SDL_Rect, SDL_Rect);

#endif