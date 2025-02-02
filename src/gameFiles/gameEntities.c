#include "gameEntities.h"
#include <stdio.h>

float PLAYER_VELOCITY_X = 5;
float PLAYER_VELOCITY_Y = 5;
bool fps_flag = false;
bool collision_flag[4] = {false, false, false, false};

void updatePlayer(SDL_Rect *player_hitbox, bool movement[4])
{
    player_hitbox->y = player_hitbox->y + ((int)(movement[1]) - (int)(movement[0])) * PLAYER_VELOCITY_Y;
    player_hitbox->x = player_hitbox->x + ((int)(movement[2]) - (int)(movement[3])) * PLAYER_VELOCITY_X;
}

void renderPlayer(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect *rect)
{
    SDL_RenderCopy(renderer, texture, NULL, rect);
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

int right_collision(SDL_Rect rect1, SDL_Rect rect2)
{
    if ((rect1.x + rect1.w >= rect2.x) && (rect1.x <= rect2.x + rect2.w) && (rect1.y + rect1.h >= rect2.y) && (rect1.y <= rect2.y + rect2.h))
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
        int top_overlap = rect2.y + rect2.h - rect1.y;    // Top side of rect2 colliding with rect1
        int bottom_overlap = rect1.y + rect1.h - rect2.y; // Bottom side of rect2 colliding with rect1
        int left_overlap = rect2.x + rect2.w - rect1.x;   // Left side of rect2 colliding with rect1
        int right_overlap = rect1.x + rect1.w - rect2.x;  // Right side of rect2 colliding with rect1

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