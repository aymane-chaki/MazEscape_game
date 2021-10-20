#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<stdlib.h>
#include<list> 
#include <iostream>
#include"InitialisationJeu.h"

extern std::list<std::list<int>> V_Obstacles;
extern std::list<std::list<int>> H_Obstacles;

void SDL_ExitWithError( SDL_Renderer * renderer, SDL_Window * window, const char *ErrorText)
{
	SDL_Log("Erreur : %s > %s\n",ErrorText,SDL_GetError());
	if(renderer)
		SDL_DestroyRenderer(renderer);
	if(window)
		SDL_DestroyWindow(window);
	SDL_Quit();
	exit(EXIT_FAILURE);
}

void RemplirArrierePlan(SDL_Renderer ** rendererPtr, SDL_Window * window)
{
    
    SDL_Rect arriere_plan;

    arriere_plan.x = 0 ;
	arriere_plan.y = 0;
	arriere_plan.w = WINDOW_WIDTH ;
	arriere_plan.h = WINDOW_HEIGHT;

    if(SDL_SetRenderDrawColor(*rendererPtr,248,212,147,SDL_ALPHA_OPAQUE) !=0)
	{
		SDL_ExitWithError(*rendererPtr, window, "Definition de la couleur echouee");
	}
    SDL_RenderClear(*rendererPtr);
    /* if(SDL_RenderFillRect(*rendererPtr,&arriere_plan) != 0)
	{
		SDL_ExitWithError(*rendererPtr, window, "Remplissage impossible");
	}
    SDL_RenderClear(*rendererPtr); */
}

void determinerObstacles_Facile(SDL_Renderer ** rendererPtr, SDL_Window * window, const int (*V_Matrix)[12], const int (*H_Matrix)[12])
{
    
    std::list<int> row_obstacles = {};
    std::list<int> column_obstacles = {};


    //subdiviser la fenetre en cellules selon la taille de la fenetre
    int cell_width = MAZE_WIDTH / 10;

    
	//tracage des murs verticaux du labyrinthe
	
    int j = 0; // colonne de la matrice
    int X = MAZE_X; //positionnement horizontal

    int i = 1; // ligne de la matrice
    int Y = MAZE_Y; //positionnement vertival

    while (i<11 && Y<MAZE_Y+MAZE_HEIGHT) 
	{
        j = 0;
        X = MAZE_X;
        while(j<11 && X<=MAZE_X+MAZE_WIDTH)
        {
            if (V_Matrix[i][j] != V_Matrix[i][j+1])
            {
                row_obstacles.push_back(X);
            }
            j++;
            X+=cell_width;
        }
        V_Obstacles.push_back(row_obstacles);
        /* for (int x : row_obstacles) {
		    std::cout << 'V' << ':' << x << '\n';
	    } */
        row_obstacles = {};
        i++;
        Y+=cell_width;
	}
    

    j = 1;
    X = MAZE_X;

    // for ( int j=1; j<11 ; j++) 
    while (j<11 && X<MAZE_X+MAZE_WIDTH)
	{
        i = 0;
        Y = MAZE_Y;
        //for ( int i=0; i<11 ; i++)
        while(i<11 && Y<=MAZE_Y+MAZE_HEIGHT)
        {
            if (H_Matrix[i][j] != H_Matrix[i+1][j])
            {
                column_obstacles.push_back(Y);
            }
            i++;
            Y+=cell_width;
        }
        H_Obstacles.push_back(column_obstacles);
        column_obstacles = {};
        j++;
        X+=cell_width;
	}
    
}

void CreerLabyrinthe_Facile(SDL_Renderer ** rendererPtr, SDL_Window * window, const int (*V_Matrix)[12], const int (*H_Matrix)[12])
{
   /*  std::list<std::list<int>> V_Obstacles = {};
    std::list<int> row_obstacles = {};

    std::list<std::list<int>> H_Obstacles = {};
    std::list<int> column_obstacles = {}; */


    //subdiviser la fenetre en cellules selon la taille de la fenetre
    int cell_width = MAZE_WIDTH / 10;

    
	//tracage des murs verticaux du labyrinthe
	if(SDL_SetRenderDrawColor(*rendererPtr,0,0,0,SDL_ALPHA_OPAQUE) !=0) //Couleur de la ligne
	{
		SDL_ExitWithError(*rendererPtr, window, "Definition de la couleur echouee");
	}
    int j = 0; // colonne de la matrice
    int X = MAZE_X; //positionnement horizontal

    int i = 1; // ligne de la matrice
    int Y = MAZE_Y; //positionnement vertival

    while (i<11 && Y<MAZE_Y+MAZE_HEIGHT) 
	{
        j = 0;
        X = MAZE_X;
        while(j<11 && X<=MAZE_X+MAZE_WIDTH)
        {
            if (V_Matrix[i][j] != V_Matrix[i][j+1])
            {
                //on dessine une ligne verticale
                if(SDL_RenderDrawLine(*rendererPtr, X, Y, X, Y+cell_width)!= 0) 
                {
                    SDL_ExitWithError(*rendererPtr, window, "Impossible de dessiner la ligne");
                }
                //row_obstacles.push_back(X);
            }
            j++;
            X+=cell_width;
        }
        //V_Obstacles.push_back(row_obstacles);
        /* for (int x : row_obstacles) {
		    std::cout << x << '\n';
	    } */
        //row_obstacles = {};
        i++;
        Y+=cell_width;
	}
    j = 1;
    X = MAZE_X;

    // for ( int j=1; j<11 ; j++) 
    while (j<11 && X<MAZE_X+MAZE_WIDTH)
	{
        i = 0;
        Y = MAZE_Y;
        //for ( int i=0; i<11 ; i++)
        while(i<11 && Y<=MAZE_Y+MAZE_HEIGHT)
        {
            
            if (H_Matrix[i][j] != H_Matrix[i+1][j])
            {
                //on dessine une ligne horizontale
                if(SDL_RenderDrawLine(*rendererPtr, X, Y, X+cell_width, Y)!= 0) 
                {
                    SDL_ExitWithError(*rendererPtr, window, "Impossible de dessiner la ligne");
                }
            }
            i++;
            Y+=cell_width;
        }
        j++;
        X+=cell_width;
	}
}


//void CreerLabyrintheMoyen(SDL_Renderer ** rendererPtr, SDL_Window * window, const int (*V_Matrix)[17], const int (*H_Matrix)[17])
