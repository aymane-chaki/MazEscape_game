#include <SDL2/SDL.h>
#include "zombie.h"



extern int SCREEN_WIDTH;
extern int  SCREEN_HEIGHT;
extern SDL_Window *window;
extern SDL_Renderer *renderer;

zombie::zombie()
{
    posX = 0;
    posY = 0;
    velX = 0;
    velY = 0;
    clipC = 3;
    flip = SDL_FLIP_NONE;

    int x_passage = 0;

    for(int i = 0; i < 4; i++)
    {
        zombieSheet[i] = {x_passage, 0, 120, 126};
        x_passage += 120;
    }
}



zombie::zombie(int x, int y)
{
    posX = x;
    posY = y;
    velX = 0;
    velY = 0;
    clipC = 3;
    flip = SDL_FLIP_NONE;

    int x_passage = 0;

    for(int i = 0; i < 4; i++)
    {
        zombieSheet[i] = {x_passage, 0, 120, 126};
        x_passage += 120;
    }
}

void zombie::loadTexture()
{
    SDL_Surface *zombieSurface = NULL;

    zombieSurface = SDL_LoadBMP("resources/zombieSheet.bmp");

    SDL_SetColorKey(zombieSurface, SDL_TRUE, SDL_MapRGB(zombieSurface -> format, 255, 255, 255));
    zombieTexture = SDL_CreateTextureFromSurface(renderer, zombieSurface);

    SDL_FreeSurface(zombieSurface);
}

void zombie::move(int playerX, int playerY)
{
    
        

    if(playerX < posX)
    {
        posX -= ZOMBIE_VEL;
        flip = SDL_FLIP_NONE;
    }
        

    if(playerY < posY)
    {
        posY -= ZOMBIE_VEL;
        flip = SDL_FLIP_NONE;
    }
        

    if(playerY > posY)
    {
        posY += ZOMBIE_VEL;
        flip = SDL_FLIP_NONE;
    }

    if(playerX > posX)
    {
        posX += ZOMBIE_VEL;
        flip = SDL_FLIP_HORIZONTAL;

    }
        
}

void zombie::render()
{
    SDL_Rect zombieRect = {posX, posY, ZOMBIE_WIDTH, ZOMBIE_HEIGHT};

    SDL_RenderCopyEx(renderer, zombieTexture, &zombieSheet[clipC], &zombieRect, 0, NULL, flip);
}

