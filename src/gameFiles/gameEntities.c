#include "gameEntities.h"
#include <stdio.h>
// variable definations
float PLAYER_VELOCITY_X = 3.0f;
float PLAYER_VELOCITY_Y = 0;
bool fps_flag = false;
bool collision_flag[4] = {false, false, false, false};
const float TERMINAL_VELOCITY = 7.0f;
float GRAVITY_PULL = 0.21f;

// functions
float min(float a, float b)
{
    return (a < b) ? a : b;
}

void updatePlayer(SDL_Rect *player_hitbox, int movement_x, int movement_y, SDL_Rect *collision_area)
{
    bool collision_flag[4] = {false, false, false, false}; // resetting collision every frame

    if (collision(player_hitbox, collision_area))
    {
    }
    player_hitbox->x = player_hitbox->x + movement_x * PLAYER_VELOCITY_X;

    player_hitbox->y = player_hitbox->y + movement_y + PLAYER_VELOCITY_Y;

    PLAYER_VELOCITY_Y = min(TERMINAL_VELOCITY, PLAYER_VELOCITY_Y + GRAVITY_PULL);
}

void renderPlayer(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect *rect)
{
    SDL_RenderCopy(renderer, texture, NULL, rect);
}

bool collision(SDL_Rect *rect1, SDL_Rect *rect2)
{
    if ((rect1->x + rect1->w > rect2->x) && (rect1->x < rect2->x + rect2->w) && (rect1->y + rect1->h > rect2->y) && (rect1->y < rect2->y + rect2->h))
    {
        int bottom_overlap = rect2->y + rect2->h - rect1->y; // Top side of rect2 colliding with rect1
        int top_overlap = rect1->y + rect1->h - rect2->y;    // Bottom side of rect2 colliding with rect1
        int right_overlap = rect2->x + rect2->w - rect1->x;  // Left side of rect2 colliding with rect1
        int left_overlap = rect1->x + rect1->w - rect2->x;   // Right side of rect2 colliding with rect1

        // Determine the smallest overlap
        int min_overlap = top_overlap;

        if (bottom_overlap < min_overlap)
        {
            min_overlap = bottom_overlap;
            collision_flag[1] = true; // bottom
        }
        else if (left_overlap < min_overlap)
        {
            min_overlap = left_overlap;
            collision_flag[2] = true; // left
        }
        else if (right_overlap < min_overlap)
        {
            min_overlap = right_overlap;
            collision_flag[3] = true; // right
        }
        else
        {
            collision_flag[0] = true; // top
        }
        return 1;
    }
    else
    {
        return 0;
    }
}

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

int left_collision(SDL_Rect rect1, SDL_Rect rect2)
{
    if (rect1.x < rect2.x + rect2.w && rect1.y + rect1.h > rect2.y && rect1.y < rect2.y + rect2.h)
    {

        return 1;
        int bottom_overlap = rect2.y + rect2.h - rect1.y; // Top side of rect2 colliding with rect1
        int top_overlap = rect1.y + rect1.h - rect2.y;    // Bottom side of rect2 colliding with rect1
        int right_overlap = rect2.x + rect2.w - rect1.x;  // Left side of rect2 colliding with rect1
        int left_overlap = rect1.x + rect1.w - rect2.x;   // Right side of rect2 colliding with rect1

        // Determine the smallest overlap
        int min_overlap = top_overlap;

        if (bottom_overlap < min_overlap)
        {
            min_overlap = bottom_overlap;
        }

        if (left_overlap < min_overlap)
        {
            min_overlap = left_overlap;
        }

        if (right_overlap < min_overlap)
        {
            min_overlap = right_overlap;
        }
    }
    else
    {
        return 0;
    }
}

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