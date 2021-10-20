#include <SDL2/SDL.h>
#include "player.h"
#include "InitialisationJeu.h"

//extern int SCREEN_WIDTH;
//extern int  SCREEN_HEIGHT;
extern SDL_Window *window;
extern SDL_Renderer *renderer;

extern std::list<std::list<int>> V_Obstacles;
extern std::list<std::list<int>> H_Obstacles;

player::player()
{
    /*Initialize the player's position*/
    posX = 0;
    posY = 0;
    
    /*Initialize the player's velocity*/
    velX = 0;
    velY = 0;

    /*Initialize the player's texture*/
    playerTexture = NULL;

    /*clip initialisation*/
    clipL = 0;
    clipC = 0;
    
    /*reading the sprite sheet of the player*/
    int x_passage = 44;
    int y_passage = 0;
     

    for(int i = 0; i < 4; i++)
    {
        int x_passage = 0; 
        for(int j = 0; j < 4; j++)
        {
            playerSheet[i][j] = {x_passage, y_passage, 44, 66};
            x_passage += 44;
        }
        y_passage += 66;
        
    }
}

void player::loadTexture()
{
    SDL_Surface *playerSurface = NULL;

    playerSurface = SDL_LoadBMP("resources/spriteSheet.bmp");

    SDL_SetColorKey(playerSurface, SDL_TRUE, SDL_MapRGB(playerSurface -> format, 255, 255, 255));

    playerTexture = SDL_CreateTextureFromSurface(renderer, playerSurface);


}

void player::handleEvent(SDL_Event *e)
{
    if (e -> type == SDL_KEYDOWN && e -> key.repeat == 0)
    {
            switch(e -> key.keysym.sym)
            {
                case SDLK_UP : velY -= PLAYER_VEL;
                           clipL = 3;
                           
                           break;
                case SDLK_DOWN : velY += PLAYER_VEL;
                             clipL = 0;
                             break;
                case SDLK_RIGHT : velX += PLAYER_VEL;
                              clipL = 2;
                              break;
                case SDLK_LEFT : velX -= PLAYER_VEL;
                             clipL = 1;
                             break;
            }
    }

    else if (e -> type == SDL_KEYUP && e -> key.repeat == 0)
    {
        switch(e ->key.keysym.sym)
        {
            case SDLK_UP : velY += PLAYER_VEL;
                           break;
            case SDLK_DOWN : velY -= PLAYER_VEL;
                              break;
            case SDLK_RIGHT : velX -= PLAYER_VEL;
                              break;
            case SDLK_LEFT : velX += PLAYER_VEL;
                             break;
        }       
    }
}

void player::move()
{
    

    int cell_width;
    int column_pos;
    int line_pos;

    int left_obstacle = 0;
    int right_obstacle = WINDOW_WIDTH;
    int top_obstacle = 0;
    int bottom_obstacle = WINDOW_HEIGHT;

    posX += velX;

    //si le joueur est au niveau du labyrinthe
    if ( (posX >= MAZE_X && posX+PLAYER_WIDTH <= MAZE_X+MAZE_WIDTH) || (posY >= MAZE_Y && posY+PLAYER_HEIGHT <= MAZE_Y+MAZE_HEIGHT) ){

        //test_V_obstacles();
        std::list<int> row_obstacles = {};  //obstacles contenus dans la ligne ou le joueur est situé
        std::list<int> col_obstacles = {};

        //std::list<std::list<int>>::iterator it = V_Obstacles.begin();
        int cell_width = MAZE_WIDTH/10 ;
        int column_pos;  //determiner la colonne dans laquelle le joueur est situé
        int line_pos;   //determiner la ligne dans laquelle le joueur est situé

        cell_width = MAZE_WIDTH/10 ;
        
        
        //printf("player positionned in column : %d , line : %d\n", column_pos, line_pos); 

        
        if (posY >= MAZE_Y && posY+PLAYER_HEIGHT <= MAZE_Y+MAZE_HEIGHT){
            line_pos = (int) (((posY-MAZE_Y)/cell_width)+0.5);
            //detection des obstacles verticaux dans la ligne
            int row_counter = 0;
            for (std::list<int> l : V_Obstacles) {
                if (row_counter == line_pos){
                    row_obstacles = l;
                    break;
                }
                row_counter++;
            }
            //tester la detection des obstacles verticaux
            /* std::cout << "Obstacles in line : " << line_pos << " are : \n";
            for (int x : row_obstacles){
                std::cout << x << '\n';
            } */
            //detection des obstacles vertivaux entourant le joueur de la droite et gauche
            for (int obstacle : row_obstacles){
                if (posX >= obstacle && left_obstacle < obstacle){
                    left_obstacle = obstacle;
                }
                if (posX < obstacle && right_obstacle > obstacle){
                    right_obstacle = obstacle;
                }
            }
            //test des resultats
            //std::cout << "Obstacle a droite : " << right_obstacle << "\n";
            //std::cout << "Obstacle a gauche : " << left_obstacle << "\n";
        }

        if (posX >= MAZE_X && posX+PLAYER_WIDTH <= MAZE_X+MAZE_WIDTH){
            column_pos = (int) (((posX-MAZE_X)/cell_width)+0.5);
            //detection des obstacles horizontaux dans la colonne
            int col_counter = 0;
            for (std::list<int> l : H_Obstacles) {
                if (col_counter == column_pos){
                    col_obstacles = l;
                    break;
                }
                col_counter++;
            }
            //tester la detection des obstacles horizontaux
            /* std::cout << "Obstacles in column : " << column_pos << " are : \n";
            for (int x : col_obstacles){
                std::cout << x << '\n';
            } */
            for (int obstacle : col_obstacles){
                if (posY >= obstacle && top_obstacle < obstacle){
                    top_obstacle = obstacle;
                }
                if (posY < obstacle && bottom_obstacle > obstacle){
                    bottom_obstacle = obstacle;
                }
            }
            //test des resultats
            //std::cout << "Obstacle en haut : " << top_obstacle << "\n";
            //std::cout << "Obstacle en bas : " << bottom_obstacle << "\n";
        }
        

    }

    if(posX < left_obstacle || posX + PLAYER_WIDTH > right_obstacle)
    {
        posX -= velX;
    }

    posY += velY;

    if(posY < top_obstacle || posY + PLAYER_HEIGHT > bottom_obstacle)
    {
        posY -= velY;
    }
    
}

void player::render()
{
    SDL_Rect playerClip = {posX, posY, PLAYER_WIDTH, PLAYER_HEIGHT};    
    SDL_RenderCopy(renderer, playerTexture, &playerSheet[clipL][clipC], &playerClip);
}

void player::test_V_obstacles()
{
    std::list<int> row_obstacles = {};  //obstacles contenus dans la ligne ou le joueur est situé
    std::list<int> col_obstacles = {};

    //std::list<std::list<int>>::iterator it = V_Obstacles.begin();
    int cell_width = MAZE_WIDTH/10 ;
    int column_pos;  //determiner la colonne dans laquelle le joueur est situé
    int line_pos;   //determiner la ligne dans laquelle le joueur est situé

    cell_width = MAZE_WIDTH/10 ;
    column_pos = (int) (((posX-MAZE_X)/cell_width)+0.5);
    line_pos = (int) (((posY-MAZE_Y)/cell_width)+0.5);
    //printf("player positionned in column : %d , line : %d\n", column_pos, line_pos); 

    //detection des obstacles verticaux dans la ligne
    int row_counter = 0;
    for (std::list<int> l : V_Obstacles) {
        if (row_counter == line_pos){
            row_obstacles = l;
            break;
        }
        row_counter++;
	}
    //tester la detection des obstacles verticaux
    /* std::cout << "Obstacles in line : " << line_pos << " are : \n";
    for (int x : row_obstacles){
		std::cout << x << '\n';
    } */

    //detection des obstacles horizontaux dans la colonne
    int col_counter = 0;
    for (std::list<int> l : H_Obstacles) {
        if (col_counter == column_pos){
            col_obstacles = l;
            break;
        }
        col_counter++;
	}
    //tester la detection des obstacles horizontaux
    /* std::cout << "Obstacles in column : " << column_pos << " are : \n";
    for (int x : col_obstacles){
		std::cout << x << '\n';
    } */

    //detection des obstacles vertivaux entourant le joueur de la droite et gauche
    int left_obstacle = 0;
    int right_obstacle = WINDOW_WIDTH;
    for (int obstacle : row_obstacles){
        if (posX >= obstacle && left_obstacle < obstacle){
            left_obstacle = obstacle;
        }
        if (posX < obstacle && right_obstacle > obstacle){
            right_obstacle = obstacle;
        }
    }
    std::cout << "Obstacle a droite : " << right_obstacle << "\n";
    std::cout << "Obstacle a gauche : " << left_obstacle << "\n";

}