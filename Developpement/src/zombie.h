#ifndef ZOMBIE_H
#define ZOMBIE_H

class zombie
{
    public:
        static const int ZOMBIE_WIDTH = 50;
        static const int ZOMBIE_HEIGHT = 50;
        static const int ZOMBIE_VEL = 5;
        zombie();
        zombie(int x, int y);
        void loadTexture();
        void move(int playerX, int playerY);
        void render();
        bool hasIntersectHuman(SDL_Rect *Player);

        SDL_Texture *zombieTexture;
        SDL_Rect zombieSheet[4];
        int posX;
        int posY;
        int velX;
        int velY;
        int clipC;
        SDL_RendererFlip flip;
};


#endif