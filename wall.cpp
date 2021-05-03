#include"header.h"
void wall(SDL_Renderer* renderer, SDL_Rect wall)
{
    wall.w=20;
    wall.h=20;
    for(int i=60;i<250;i+=20)
    {
        wall.x=i;
        wall.y=60;
        SDL_SetRenderDrawColor(renderer, 102, 51, 0, 255);
        SDL_RenderFillRect(renderer, &wall);
    }
    for(int i=60;i<250;i+=20)
    {
        wall.x=i;
        wall.y=560;
        SDL_SetRenderDrawColor(renderer, 102, 51, 0, 255);
        SDL_RenderFillRect(renderer, &wall);
    }
    for(int i=60;i<250;i+=20)
    {
        wall.x=60;
        wall.y=i;
        SDL_SetRenderDrawColor(renderer, 102, 51, 0, 255);
        SDL_RenderFillRect(renderer, &wall);
    }
    for(int i=60;i<250;i+=20)
    {
        wall.x=600;
        wall.y=i;
        SDL_SetRenderDrawColor(renderer, 102, 51, 0, 255);
        SDL_RenderFillRect(renderer, &wall);
    }
    for(int i=600;i>400;i-=20)
    {
        wall.x=i;
        wall.y=60;
        SDL_SetRenderDrawColor(renderer, 102, 51, 0, 255);
        SDL_RenderFillRect(renderer, &wall);
    }
    for(int i=600;i>400;i-=20)
    {
        wall.x=i;
        wall.y=560;
        SDL_SetRenderDrawColor(renderer, 102, 51, 0, 255);
        SDL_RenderFillRect(renderer, &wall);
    }
    for(int i=560;i>360;i-=20)
    {
        wall.x=60;
        wall.y=i;
        SDL_SetRenderDrawColor(renderer, 102, 51, 0, 255);
        SDL_RenderFillRect(renderer, &wall);
    }
    for(int i=560;i>360;i-=20)
    {
        wall.x=600;
        wall.y=i;
        SDL_SetRenderDrawColor(renderer, 102, 51, 0, 255);
        SDL_RenderFillRect(renderer, &wall);
    }
}
