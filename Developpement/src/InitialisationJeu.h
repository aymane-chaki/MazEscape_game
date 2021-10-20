#ifndef INITIALISATIONJEU_H_INCLUDED
#define INITIALISATIONJEU_H_INCLUDED
    #include<SDL2/SDL.h>
    //#include<SDL2/SDL_ttf.h>
    #include<stdio.h>
    #include<stdlib.h>
    #include<string.h>
    #include<list>
    #include<iostream>
    #include <chrono>
    using namespace std;

    //Ajouter la possibilite de redimensionner la fenetre
    #define MAZE_WIDTH 600	
    #define MAZE_HEIGHT 600
    #define WINDOW_WIDTH 900	
    #define WINDOW_HEIGHT 800
    #define MAZE_X 150
    #define MAZE_Y 100

    

    const int V_Matrix_easy[12][12] =
    {
        { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
        { 0 , 1 , 1 , 1 , 0 , 0 , 1 , 1 , 0 , 0 , 0 , 0 },
        { 0 , 1 , 0 , 1 , 1 , 0 , 0 , 1 , 1 , 1 , 1 , 0 },
        { 0 , 1 , 0 , 0 , 1 , 1 , 0 , 0 , 1 , 1 , 0 , 1 },
        { 0 , 1 , 1 , 0 , 0 , 0 , 1 , 0 , 0 , 1 , 1 , 0 },
        { 0 , 1 , 0 , 0 , 0 , 1 , 1 , 0 , 1 , 1 , 1 , 0 },
        { 0 , 1 , 0 , 0 , 1 , 0 , 0 , 0 , 1 , 0 , 1 , 0 },
        { 0 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 0 , 1 , 0 },
        { 0 , 1 , 1 , 1 , 0 , 1 , 0 , 1 , 1 , 1 , 1 , 0 },
        { 0 , 1 , 0 , 0 , 0 , 1 , 1 , 1 , 0 , 1 , 1 , 0 },
        { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 1 , 0 , 1 },
        { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 }
    };

    const int H_Matrix_easy[12][12] =
    {
        { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
        { 0 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 0 },
        { 0 , 0 , 1 , 1 , 0 , 1 , 1 , 1 , 0 , 0 , 1 , 0 },
        { 0 , 0 , 1 , 0 , 0 , 1 , 0 , 0 , 1 , 0 , 0 , 0 },
        { 0 , 0 , 0 , 0 , 1 , 0 , 0 , 1 , 0 , 1 , 0 , 0 },
        { 0 , 0 , 1 , 1 , 1 , 1 , 0 , 1 , 0 , 0 , 0 , 0 },
        { 0 , 0 , 1 , 0 , 0 , 1 , 1 , 1 , 0 , 0 , 1 , 0 },
        { 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 1 , 0 },
        { 0 , 1 , 1 , 0 , 0 , 1 , 1 , 1 , 1 , 0 , 1 , 0 },
        { 0 , 1 , 0 , 0 , 0 , 1 , 1 , 1 , 1 , 1 , 0 , 0 },
        { 0 , 1 , 1 , 1 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 0 },
        { 0 , 0 , 0 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 1 , 0 } 
    };

    /* const int MV_Debut[7][8] =
    {
        { -2 , -2 , -2 , -2 , -2 , -2 , -2 , -2},
        { -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1},
        {  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0},
        {  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0},
        {  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0},
        {  1 ,  1 ,  1 ,  1 ,  1 ,  1 ,  1 ,  1},
        {  2 ,  2 ,  2 ,  2 ,  2 ,  2 ,  2 ,  2}
    };
    const int MH_Debut[8][7] =
    {
        {  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0},
        { -1 , -1 , -1 , -1 , -1 , -1 , -1},
        {  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0},
        {  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0},
        {  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0},
        {  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0},
        {  1 ,  1 ,  1 ,  1 ,  1 ,  1 ,  1},
        {  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0}
    };

    int MR[7][7] =
    {
        { 0 , 0 , 0 ,-3 , 0 , 0 , 0},
        { 0 , 0 , 0 , 0 , 0 , 0 , 0},
        { 0 , 0 , 0 , 0 , 0 , 0 , 0},
        { 0 , 0 , 0 , 0 , 0 , 0 , 0},
        { 0 , 0 , 0 , 0 , 0 , 0 , 0},
        { 0 , 0 , 0 , 0 , 0 , 0 , 0},
        { 0 , 0 , 0 , 3 , 0 , 0 , 0}
    };
    int MV[7][8] =
    {
        { -2 , -2 , -2 , -2 , -2 , -2 , -2 , -2},
        { -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1},
        {  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0},
        {  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0},
        {  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0},
        {  1 ,  1 ,  1 ,  1 ,  1 ,  1 ,  1 ,  1},
        {  2 ,  2 ,  2 ,  2 ,  2 ,  2 ,  2 ,  2}
    };
    int MH[8][7] =
    {
        {  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0},
        { -1 , -1 , -1 , -1 , -1 , -1 , -1},
        {  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0},
        {  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0},
        {  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0},
        {  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0},
        {  1 ,  1 ,  1 ,  1 ,  1 ,  1 ,  1},
        {  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0}
    };
    
    int MR_Copy[7][7];
    int MH_Copy[8][7];
    int MV_Copy[7][8]; */


    void SDL_ExitWithError( SDL_Renderer * renderer, SDL_Window * window, const char *ErrorText);

    void RemplirArrierePlan(SDL_Renderer ** rendererPtr, SDL_Window * window);

    void CreerLabyrinthe_Facile(SDL_Renderer ** renderer, SDL_Window * window, const int (*V_Matrix)[12], const int (*H_Matrix)[12]);
    void determinerObstacles_Facile(SDL_Renderer ** renderer, SDL_Window * window, const int (*V_Matrix)[12], const int (*H_Matrix)[12]);

    
    
#endif