
#define PLAYER_POS_X 0
#define PLAYER_POS_Y 0
#define PLAYER_WIDTH 32
#define PLAYER_HEIGHT 32
#define GRAVITY 0.00
#define WALL_THICKNESS 150
#include "globals.h"
#include "gameRender.h"

float PLAYER_VELOCITY_X = 5;
float PLAYER_VELOCITY_Y = 5;

bool fps_flag = false;
// Physics Entities

// Function to check collision between two SDL_Rects
int top_collision(SDL_Rect, SDL_Rect);
int top_collision(SDL_Rect rect1, SDL_Rect rect2)
{
    if ((rect1.y < rect2.y + rect2.h && rect1.x + rect1.w > rect2.x) && (rect1.y < rect2.y + rect2.h && rect1.x < rect2.x + rect2.w))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int right_collision(SDL_Rect, SDL_Rect);
int right_collision(SDL_Rect rect1, SDL_Rect rect2)
{
    if ((rect1.x + rect1.w > rect2.x) && (rect1.x < rect2.x + rect2.w) && (rect1.y + rect1.h > rect2.y) && (rect1.y < rect2.y + rect2.h))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int left_collision(SDL_Rect, SDL_Rect);
int left_collision(SDL_Rect rect1, SDL_Rect rect2)
{
    if (rect1.x < rect2.x + rect2.w && rect1.y + rect1.h > rect2.y && rect1.y < rect2.y + rect2.h)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int bottom_collision(SDL_Rect, SDL_Rect);
int bottom_collision(SDL_Rect rect1, SDL_Rect rect2)
{
    if ((rect1.y + rect1.h > rect2.y) && (rect1.x + rect1.w > rect2.x) && (rect1.x < rect2.x + rect2.w))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int bottom_window_collision(SDL_Rect, SDL_Rect);
int bottom_window_collision(SDL_Rect rect1, SDL_Rect wrect)
{
    if ((rect1.y + rect1.h) > wrect.h + wrect.y)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int side_window_collision(SDL_Rect, SDL_Rect);
int side_window_collision(SDL_Rect rect1, SDL_Rect wrect)
{
    if ((rect1.x >= wrect.x) && (rect1.x + rect1.w <= wrect.x + wrect.w))
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

float get_dampness(float);
float get_dampness(float dampness)
{
    int dampness_switch = 0;
    if (dampness < GRAVITY)
    {
        dampness_switch = 1;
    }
    if (dampness_switch)
    {
        dampness += 1;
    }
    else
    {
        dampness = 0;
    }

    return dampness;
}