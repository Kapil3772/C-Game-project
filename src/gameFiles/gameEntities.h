
#define PLAYER_POS_X 100
#define PLAYER_POS_Y 100
#define PLAYER_WIDTH 50
#define PLAYER_HEIGHT 75
#define GRAVITY 3

float PLAYER_VELOCITY_X = 50;
float PLAYER_VELOCITY_Y = 140;
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

int rside_window_collision(SDL_Rect, SDL_Rect);
int rside_window_collision(SDL_Rect rect1, SDL_Rect wrect)
{
    if ((rect1.x < wrect.x) || (rect1.x + rect1.w > wrect.x + wrect.w))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}