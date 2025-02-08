#include "gameEntities.h"
#include <stdio.h>
// variable definations
float PLAYER_VELOCITY_X = 3.0f;
float PLAYER_VELOCITY_Y = 0;
bool fps_flag = false;
bool collision_flag[4] = {false, false, false, false};
const float TERMINAL_VELOCITY = 10.0f;
float GRAVITY_PULL = 0.25f;
bool isJumping;
bool IDLE = true, RUNNING = false, DEAD = false, ON_GROUND = false;

SDL_Rect *colliding_rect;
// functions
float min(float a, float b)
{
    return (a < b) ? a : b;
}

void updatePlayer(SDL_Rect *player_hitbox, int movement_x, int movement_y, SDL_Rect *collision_area, SDL_Rect *collision_area2, bool isJumping)
{
    if (movement_x != 0)
    {
        IDLE = false;
        RUNNING = true;
    }
    else
    {
        IDLE = true;
        RUNNING = false;
    }
    CollisionSide collision = (CollisionSide)((collisionCheck(player_hitbox, collision_area) | collisionCheck(player_hitbox, collision_area2)));
    if (collision & COLLISION_LEFT)
    {
        player_hitbox->x = colliding_rect->x - player_hitbox->w; // clamping player to the left of the platform
    }
    if (collision & COLLISION_RIGHT)
    {
        player_hitbox->x = colliding_rect->x + colliding_rect->w; // clamping player to the right of the platform
    }
    player_hitbox->x = player_hitbox->x + movement_x * PLAYER_VELOCITY_X;

    if (collision & COLLISION_TOP)
    {
        ON_GROUND = true;
        player_hitbox->y = colliding_rect->y - player_hitbox->h; // clamping player to the top of the platform
        PLAYER_VELOCITY_Y = 0;
    }
    if (isJumping)
    {
        ON_GROUND = false;
        PLAYER_VELOCITY_Y = -5.0f;
    }
    if (collision & COLLISION_BOTTOM)
    {
        PLAYER_VELOCITY_Y = 0.5;
        player_hitbox->y = colliding_rect->y + colliding_rect->h + 1; // clamping player to the bottom of the platform
    }

    player_hitbox->y = player_hitbox->y + movement_y + PLAYER_VELOCITY_Y;

    PLAYER_VELOCITY_Y = min(TERMINAL_VELOCITY, PLAYER_VELOCITY_Y + GRAVITY_PULL);
}

void renderPlayer(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect *rect)
{
    if (ON_GROUND)
    {
        if (RUNNING)
        {
            render_animation("running", renderer, rect);
            SDL_SetRenderDrawColor(renderer, 225, 0, 0, 255);
            SDL_RenderDrawRect(renderer, rect);
        }
    }
    else
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 225, 255);
        SDL_RenderDrawRect(renderer, rect);
    }
    SDL_RenderCopy(renderer, texture, NULL, rect);
}

CollisionSide collisionCheck(SDL_Rect *rect1, SDL_Rect *rect2)
{
    CollisionSide collision = NO_COLLISION;

    if ((rect1->x + rect1->w >= rect2->x) && (rect1->x <= rect2->x + rect2->w) && (rect1->y + rect1->h >= rect2->y) && (rect1->y <= rect2->y + rect2->h))
    {

        colliding_rect = rect2;

        int bottom_overlap = rect2->y + rect2->h - rect1->y;
        int top_overlap = rect1->y + rect1->h - rect2->y;
        int left_overlap = rect1->x + rect1->w - rect2->x;
        int right_overlap = rect2->x + rect2->w - rect1->x;

        int min_overlap = bottom_overlap;

        if (top_overlap < min_overlap)
        {
            min_overlap = top_overlap;
        }

        if (left_overlap < min_overlap)
        {
            min_overlap = left_overlap;
        }

        if (right_overlap < min_overlap)
        {
            min_overlap = right_overlap;
        }

        if (min_overlap == bottom_overlap)
        {
            collision = (CollisionSide)(collision | COLLISION_BOTTOM);
        }
        if (min_overlap == top_overlap)
        {
            collision = (CollisionSide)(collision | COLLISION_TOP);
        }
        if (min_overlap == left_overlap)
        {
            collision = (CollisionSide)(collision | COLLISION_LEFT);
        }
        if (min_overlap == right_overlap)
        {
            collision = (CollisionSide)(collision | COLLISION_RIGHT);
        }
    }

    return collision;
}

void render_animation(const char *animation, SDL_Renderer *renderer, SDL_Rect *rect)
{
    
}