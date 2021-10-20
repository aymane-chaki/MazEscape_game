#ifndef PLAYER_H
#define PLAYER_H

class player
{
    public:
        static const int PLAYER_WIDTH = 50;
        static const int PLAYER_HEIGHT = 50;
        static const int PLAYER_VEL = 10;

        player();
        void loadTexture();
        void handleEvent(SDL_Event *e);
        void move();
        void test_V_obstacles();
        void test_H_obstacles();
        void render();

    public:
        int posX;
        int posY;
        int velX;
        int velY;

        SDL_Texture *playerTexture;
        SDL_Rect playerSheet[4][4];
        int clipL;
        int clipC;

        bool isMoving;
        
};

#endif