/*
    SDL_RENDERER_SOFTWARE (procésseur)
    SDL_RENDERER_ACCELERATED (accelaration materielle carte graphique)
    SDL_RENDERER_PRESENTVSYNC (synchronisation verticale)
    SDL_RENDERER_TARGETTEXTURE (rendu selon texture)

*/
#include "SDL.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Surface* image_background = NULL;
SDL_Surface* image_Ruche = NULL;
SDL_Texture* texture_background = NULL;
SDL_Texture* texture_ruche = NULL;

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define BACKGROUND_IMAGE "BackGroundd.bmp"
#define HIVE_IMAGE "Hive.bmp"

//#define BEES_IMAGE[4] ""

#define TAILLE_BLOC 34                  // 34 pixel pour les personnages

#define TAILLE_ABEILLE 100
#define NB_BEES 100

void SDL_ExitWithError(const char *message);
typedef struct Ruche {
    float W;    // Largeur
    float X;    // Postion X
    float Y;    // Position Y
    float Z;    // Hauteur
} Ruche;

//Ruche ruches[BEES];



void MAKE_ABEILLE(float Temp_écoulé)
{   for(int i = 0; i<NB_BEES; i++)
    {
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);

        SDL_Surface *BEE_surface = SDL_LoadBMP(HIVE_IMAGE);
        if(BEE_surface == NULL)
        {
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_ExitWithError("Failed to load Bee image");
        }
        SDL_Texture *BEE_texture = SDL_CreateTextureFromSurface(renderer, BEE_surface);
        SDL_FreeSurface(BEE_surface);
        if(BEE_texture == NULL)
        {
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_ExitWithError("Failed to create BEE texture");
        }
        SDL_Rect BEE_position;
        if (SDL_QueryTexture(BEE_texture, NULL,NULL,&BEE_position.w, &BEE_position.h)!= 0)
        {
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_ExitWithError("Failed to load BEE texture");
        }
        BEE_position.x = 25;
        BEE_position.y = 20;

        if(SDL_RenderCopy(renderer,BEE_texture,NULL,&BEE_position))
        {
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_ExitWithError("Failed to render Copy the BEE");
        }
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
    }

}
void Make_Ruche()
{
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderClear(renderer);

    SDL_Surface *Ruche_surface = SDL_LoadBMP(HIVE_IMAGE);
    if(Ruche_surface == NULL)
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Failed to load Hive image");
    }
    SDL_Texture *Ruche_texture = SDL_CreateTextureFromSurface(renderer, Ruche_surface);
    SDL_FreeSurface(Ruche_surface);
    if(Ruche_texture == NULL)
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Failed to create Hive texture");
    }
    SDL_Rect ruche_position;
    if (SDL_QueryTexture(Ruche_texture, NULL,NULL,&ruche_position.w, &ruche_position.h)!= 0)
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Failed to load Hive texture");
    }
    ruche_position.x = 20;
    ruche_position.y = 20;

    if(SDL_RenderCopy(renderer,Ruche_texture,NULL,&ruche_position))
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Failed to render Copy the Hive");
    }
    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);

}
void Display(float Temp_écoulé)
{
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderClear(renderer);

    SDL_Surface *surface_background = SDL_LoadBMP(BACKGROUND_IMAGE);
    SDL_Surface *Ruche_surface = SDL_LoadBMP(HIVE_IMAGE);
    if(surface_background == NULL)
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Failed to load image");
    }

    SDL_Texture *texture_background = SDL_CreateTextureFromSurface(renderer, surface_background);
    SDL_Texture *Ruche_texture = SDL_CreateTextureFromSurface(renderer, Ruche_surface);
    SDL_FreeSurface(surface_background);
    SDL_FreeSurface(Ruche_surface);

    if(texture_background == NULL)
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Failed to create texture");
    }
    SDL_Rect rectangle;
    if (SDL_QueryTexture(texture_background, NULL,NULL,&rectangle.w, &rectangle.h)!= 0)
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Failed to load texture");
    }
    rectangle.x = (WINDOW_WIDTH - rectangle.w)/2;
    rectangle.y = (WINDOW_HEIGHT - rectangle.h)/2;

    SDL_Rect ruche_position;
    if (SDL_QueryTexture(Ruche_texture, NULL,NULL,&ruche_position.w, &ruche_position.h)!= 0)
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Failed to load Hive texture");
    }
    ruche_position.x = 20;
    ruche_position.y = 240;


    if(SDL_RenderCopy(renderer,texture_background,NULL,&rectangle))
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Failed to render Copy");
    }
    if(SDL_RenderCopy(renderer,Ruche_texture,NULL,&ruche_position))
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Failed to render Copy the Hive");
    }
    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);
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

int main(int argc, char **argv){

    SDL_Window* window = initSDL();

    
    if (!window) {
        return 1;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    printf("Game's Loading...\n");
    
    Uint32 Dernier_Tick = SDL_GetTicks();                    // Chronomètre qui commence dès que le SDL init est en route

    SDL_bool program_launched = SDL_TRUE;              


    while (program_launched)
    {
        SDL_Event action_utilisateur;
        while (SDL_PollEvent(&action_utilisateur))
        {
            switch (action_utilisateur.type)
            {
                case SDL_QUIT:                                              // Quitter quand on clique sur la croix
                    program_launched = SDL_FALSE;                                     
                break;
                case SDL_KEYDOWN:
                    if (action_utilisateur.key.keysym.sym == SDLK_ESCAPE)    // Quitter quand on appuie sur ECHAP
                    {
                        program_launched = SDL_FALSE;   
                        break;
                    }
                    else
                        continue;
            }
            Uint32 Tick_Actuel = SDL_GetTicks();
            Uint32 Differentiel_ticks = Tick_Actuel - Dernier_Tick;
            float Temp_écoulé = Differentiel_ticks / 1000.0f; // Seconde ;)
            Display(Temp_écoulé);
           // Make_Ruche();
            Dernier_Tick = Tick_Actuel;
        }
    }
    
    SDL_DestroyWindow(window);
    SDL_Quit() ;
    return EXIT_SUCCESS;
}

void SDL_ExitWithError(const char *message){
    SDL_Log("ERREUR : %s > %s\n", message, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
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

// gcc main.c -o SDL $(sdl2-config --cflags --libs)
