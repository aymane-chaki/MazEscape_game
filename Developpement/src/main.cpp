#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <conio.h>

#include "InitialisationJeu.h"
#include "timer.h"
#include "player.h"
//#include "zombie.h"


//int SCREEN_WIDTH =  800;
//int  SCREEN_HEIGHT = 640;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
std::list<std::list<int>> V_Obstacles = {};
std::list<std::list<int>> H_Obstacles = {};


int main(int argc, char *argv[])
{
    SDL_bool programLaunched = SDL_TRUE;

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("MazEscape", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    determinerObstacles_Facile(&renderer, window, V_Matrix_easy, H_Matrix_easy);
    
    
    //tester si les listes sont bien remplies
    /* for (std::list<int> l : V_Obstacles) {
        int col = 0;
        for (int x : l){
		    std::cout << 'V' << col << ':' << x << '\n';
            col++;
        }
	}
    for (std::list<int> l : H_Obstacles) {
        int line = 0;
        for (int x : l){
		    std::cout << 'H' << line << ':' << x << '\n';
            line++;
        }
	} */


    if(SDL_RenderClear(renderer) != 0 )
	{
		SDL_ExitWithError(renderer, window, "Impossible de vider le rendu");
	}
    
    SDL_RenderPresent(renderer);
    player p = player();
    p.loadTexture();
    //zombie z = zombie();
    //z.loadTexture();

    int FPS = 10;
    float frameTicks = (float)1000 / (float)FPS;
    timer capTimer; 
    int timeticks = 0;
    SDL_Event Event;
    //la partie est gagnee si le joueur entrer au labyrinthe et sort : true & true
    bool entrer_labyrinthe = false;
    bool sortie_labyrinthe = false;
    chrono::steady_clock sc;   // create an object of `steady_clock` class
    auto start = sc.now();    
    int previous_second = 0;
    bool counter_started = false;
    bool stop_counter = false; 
    while(programLaunched)
    {   
        capTimer.start();
        while(SDL_PollEvent(&Event))
        {   
            
            p.handleEvent(&Event);
            if(Event.type == SDL_QUIT)
            {
                programLaunched = SDL_FALSE;
                break;
            }
        }           

        /*Very Important*/
        const Uint8 *state = SDL_GetKeyboardState(NULL);
        if(state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_DOWN] || state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_LEFT])
            p.clipC = (p.clipC + 1) % 4;

        //z.clipC = + (z.clipC + 1) % 4;
            
        p.move();
        //joueur entre en labyrinthe
        if ( (p.posX >= MAZE_X && p.posX+p.PLAYER_WIDTH <= MAZE_X+MAZE_WIDTH) && (p.posY >= MAZE_Y && p.posY+p.PLAYER_HEIGHT <= MAZE_Y+MAZE_HEIGHT) ){
            entrer_labyrinthe = true;
            if(!counter_started){
                //lancer le compteur
                start = sc.now();     // start timer
                counter_started = true;
            }
     
        }
        else {
            if (entrer_labyrinthe){
                sortie_labyrinthe = true;
                //arreter compteur
                stop_counter = true;
                std::cout << "Congratulations!!! You Won :) " << "\n";
                entrer_labyrinthe = false;
                sortie_labyrinthe = false;
            }                
        }
        //z.move(p.posX, p.posY);
          
        SDL_RenderClear(renderer);
        RemplirArrierePlan(&renderer, window);
        CreerLabyrinthe_Facile(&renderer, window, V_Matrix_easy, H_Matrix_easy);  
        p.render();
        //z.render();
        SDL_RenderPresent(renderer);

        timeticks = capTimer.getTicks();

        if(timeticks < frameTicks)
        {
            SDL_Delay(frameTicks - timeticks);
        }
        auto end = sc.now();       // end timer (starting & ending is done by measuring the time at the moment the process started & ended respectively)
        auto time_span = static_cast<chrono::duration<double>>(end - start); 

      
        
        //clear screen
        if ( previous_second != (int)time_span.count() && counter_started && !stop_counter){
            system("cls");
            cout<<(((int)time_span.count())/60)<<" : "<<(((int)time_span.count())%60)<<" \n";
        }
        previous_second = (int)time_span.count();
    }
    return 0;
}