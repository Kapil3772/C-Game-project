#ifndef GAME_ENTITIES_H

#include <stdbool.h>
#include <stdbool.h>
#include "SDL2/SDL.h"

// Game fundamentals Constants
#define PLAYER_POS_X 0
#define PLAYER_POS_Y 0
#define PLAYER_WIDTH 32
#define PLAYER_HEIGHT 32
#define GRAVITY 0.00
#define WALL_THICKNESS 150

// Game fundamentals Flags
extern bool fps_flag;
extern bool running, loading;

extern const float TERMINAL_VELOCITY;

// Renderer pointers
extern SDL_Renderer *renderer;
extern SDL_Rect *colliding_rect;
extern SDL_Texture *player_texture, *loadingScreen, *gameBackground, *collision_area_texture;

extern int player_movement[2];

// Physics Entities
extern bool collision_flag[4];
extern bool movement[2];
extern bool isJumping;

extern float GRAVITY_PULL;
extern float PLAYER_VELOCITY_X;
extern float PLAYER_VELOCITY_Y;

extern SDL_Texture tex[];
typedef enum
{
    NO_COLLISION = 0,
    COLLISION_TOP = 1 << 0,
    COLLISION_BOTTOM = 1 << 1,
    COLLISION_LEFT = 1 << 2,
    COLLISION_RIGHT = 1 << 3
} CollisionSide;

// Function to check collision between two SDL_Rects
CollisionSide collisionCheck(SDL_Rect *, SDL_Rect *);

// Maths Functions
float min(float, float);

// Functions to update and render player
void updatePlayer(SDL_Rect *, int movement_x, int movement_y, SDL_Rect *collision_area, SDL_Rect *collision_area2, bool isJumping);
void renderPlayer(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect *rect);

#endif