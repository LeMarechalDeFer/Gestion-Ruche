/*
    SDL_RENDERER_SOFTWARE (procésseur)
    SDL_RENDERER_ACCELERATED (accelaration materielle carte graphique)
    SDL_RENDERER_PRESENTVSYNC (synchronisation verticale)
    SDL_RENDERER_TARGETTEXTURE (rendu selon texture)

*/

#include "SDL.h"
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define TAILLE_ABEILLE 100
#define BEES 100

typedef struct Ruche {
    float W;    // Largeur
    float X;    // Postion X
    float Y;    // Position Y
    float Z;    // Hauteur
} Ruche;

Ruche ruches[BEES];

typedef struct Abeille
{
    float X;    // Postion X
    float Y;    // Position Y
    int taille;
    float Vitesse_sur_X;
    float Vitesse_sur_Y;
} Abeille;

Abeille abeille;

Abeille MAKE_ABEILLE()
{
    const float Vitesse_sur_X = 120;
    const float Vitesse_sur_Y = 120;

    Abeille abeille = {
        .X = (WINDOW_WIDTH - TAILLE_ABEILLE) /2,
        .Y = (WINDOW_HEIGHT - TAILLE_ABEILLE) /2,
        .taille = TAILLE_ABEILLE,
    };
    return abeille;
}

void render_Abeille(Abeille *abeille)
{
    int size = abeille->taille;

    SDL_Rect abeille_rect = {
        .x = abeille->X,
        .y = abeille->Y,
        .w = abeille->taille,
        .h = abeille->taille
    };
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderFillRect(renderer,&abeille_rect);
    SDL_RenderPresent(renderer);

}

void update(float Temp_écoulé)
{
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderClear(renderer);
    render_Abeille(&abeille);
    SDL_RenderPresent(renderer);
}

SDL_Window* initSDL()
{                         // Initialisation et création de fenêtre
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Raté ...  %s\n", SDL_GetError());
        return NULL;
    }


    window = SDL_CreateWindow("Hive Simulator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Raté...  %s\n", SDL_GetError());
        SDL_Quit();
        return NULL;
    }

    return window;
}

void SDL_ExitWithError(const char *message){
    SDL_Log("ERREUR : %s > %s\n", message, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv){

    SDL_Window* window = initSDL();
    
    if (!window) {
        return 1;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    printf("Game's Loading...\n");

    Uint32 Dernier_Tick = SDL_GetTicks();                    // Chronomètre qui commence dès que le SDL init est en route
    bool Quitter = false;                   
    SDL_Event action_utilisateur;
    while (!Quitter)
    {
        while (SDL_PollEvent(&action_utilisateur))
        {
            switch (action_utilisateur.type)
            {
                case SDL_QUIT:                                              // Quitter quand on clique sur la croix
                    Quitter = true;                                     
                break;
                case SDL_KEYDOWN:
                    if (action_utilisateur.key.keysym.sym == SDLK_ESCAPE); // Quitter quand on appuie sur ECHAP
                    Quitter = true;
                break;
            }
            Uint32 Tick_Actuel = SDL_GetTicks();
            Uint32 Differentiel_ticks = Tick_Actuel - Dernier_Tick;
            float Temp_écoulé = Differentiel_ticks / 1000.0f; // Seconde ;)
            update(Temp_écoulé);
            Dernier_Tick = Tick_Actuel;
        }
        
    }
    
    SDL_DestroyWindow(window);
    SDL_Quit() ;
    return EXIT_SUCCESS;
}
/*void shutdown(void) {
    if(renderer){
        SDL_DestroyRenderer(renderer);
    }
    if(window){
    SDL_DestroyWindow(window);                      SEGMENTATION FAULT WHENEVER UTILIZED IDK WHY ^^'
    }              
    SDL_Quit();
}*/

// gcc main.c -o prog $(sdl2-config --cflags --libs)
