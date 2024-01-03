/*
    SDL_RENDERER_SOFTWARE (procésseur)
    SDL_RENDERER_ACCELERATED (accelaration materielle carte graphique)
    SDL_RENDERER_PRESENTVSYNC (synchronisation verticale)
    SDL_RENDERER_TARGETTEXTURE (rendu selon texture)

*/
/* gcc main.c -o SDL -I/usr/include/SDL2 -I/usr/include/SDL2_image -I/usr/include/SDL2_ttf -L/usr/lib -lSDL2 -lSDL2_ima
ge -lSDL2_ttf */


#include "Config/SDL.h"
#include "Config/Constantes.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;


SDL_Surface* image_background = NULL;
SDL_Texture* texture_background = NULL;

SDL_Surface* image_Ruche = NULL;
SDL_Texture* texture_ruche = NULL;

SDL_Surface *BEE_surface = NULL;
SDL_Texture *BEE_texture[4];

SDL_Surface* surface_Timer = NULL;
SDL_Texture* texture_Timer = NULL;


#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define TAILLE_ABEILLE 100
#define NB_BEES 10

void SDL_ExitWithError(const char *message);
typedef struct Ruche {
    float W;    // Largeur
    float X;    // Postion X
    float Y;    // Position Y
    float Z;    // Hauteur
} Ruche;

//Ruche ruches[BEES];
void load_bee_texture()
{
        for (int i = 1; i <= 4; ++i) {
        char filePath[50];
        snprintf(filePath, sizeof(filePath), "Assets/Position_%d.bmp", i);

        SDL_Surface* BEE_surface = SDL_LoadBMP(filePath);
        if (!BEE_surface) {
            printf("Failed to load bee frame %d! SDL Error: %s\n", i, SDL_GetError());
            exit(EXIT_FAILURE);
        }

        BEE_texture[i] = SDL_CreateTextureFromSurface(renderer, BEE_surface);

        if (!BEE_texture[i]) {
            printf("Failed to create texture for bee frame %d! SDL Error: %s\n", i, SDL_GetError());
            exit(EXIT_FAILURE);
        }
        SDL_FreeSurface(BEE_surface);
    }
}
/*void MAKE_ABEILLE(float Temp_écoulé)
{ 
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderClear(renderer);
    for(int i = 0; i<NB_BEES; i++)
    {

        SDL_Surface *Abeille_SPRITE = IMG_LoadGIF_RW("Assets/Abeille_Anime.gif");
        if(Abeille_SPRITE == NULL)
        {
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_ExitWithError("Failed to load Bee image");
        }
        SDL_Texture *BEE_texture = SDL_CreateTextureFromSurface(renderer, Abeille_SPRITE);
        SDL_FreeSurface(Abeille_SPRITE);
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
        BEE_position.x = BEE_position.x + 5;
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
}*/
/*void Make_Ruche()
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
*/
void Display(float Temp_écoulé)
{
    TTF_Font* font = TTF_OpenFont("Config/Roboto-BlackItalic.ttf", 24);
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderClear(renderer);

    int Current_frame = 1;

    if (!font) {
        printf("Failed to load font: %s\n", TTF_GetError());
        exit (-1);
    }

    SDL_Color color = {255, 255, 255, 255}; // White color for the font
    SDL_RenderClear(renderer);
    char timeText[1000];

    sprintf(timeText, "Time: %f seconds", Temp_écoulé);

    SDL_Surface *surface_background = SDL_LoadBMP(BACKGROUND_IMAGE);
    SDL_Surface *Ruche_surface = SDL_LoadBMP(HIVE_IMAGE);
    SDL_Surface* surface_Timer = TTF_RenderText_Solid(font, timeText, color);

    if(surface_background == NULL)
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Failed to load image");
    }

    SDL_Texture *texture_background = SDL_CreateTextureFromSurface(renderer, surface_background);
    SDL_Texture *Ruche_texture = SDL_CreateTextureFromSurface(renderer, Ruche_surface);
    SDL_Texture *texture_Timer = SDL_CreateTextureFromSurface(renderer, surface_Timer);


    SDL_FreeSurface(surface_background);
    SDL_FreeSurface(Ruche_surface);
    SDL_FreeSurface(surface_Timer);


    if(texture_background == NULL)
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Failed to create texture");
    }
    SDL_Rect Background;
    if (SDL_QueryTexture(texture_background, NULL,NULL,&Background.w, &Background.h)!= 0)
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Failed to load texture");
    }
    Background.x = (WINDOW_WIDTH - Background.w)/2;
    Background.y = (WINDOW_HEIGHT - Background.h)/2;

    SDL_Rect ruche_position;
    if (SDL_QueryTexture(Ruche_texture, NULL,NULL,&ruche_position.w, &ruche_position.h)!= 0)
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Failed to load Hive texture");
    }
    ruche_position.x = 20;
    ruche_position.y = 240;
    load_bee_texture();

    if(SDL_RenderCopy(renderer,texture_background,NULL,&Background))
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

    SDL_Rect timer_position = { 400, 0, 200, 50 };
    if(SDL_RenderCopy(renderer, texture_Timer, NULL, &timer_position))
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Failed to render Copy the Timer");
    }
    SDL_Rect BEE_rect = { 100, 100, 50, 50 };
    for(int i = 1; i<= 4;i++)
    {
        if(SDL_RenderCopy(renderer,BEE_texture[i],NULL,&BEE_rect))
        {
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_ExitWithError("Failed to render Copy the BEE");
        }
        SDL_RenderPresent(renderer);
        SDL_Delay(200);
    }
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




////////////////////////////////////////////////////////////////////////////////////////////



// Initialize SDL and TTF
void init_TTF() {
    SDL_Init(SDL_INIT_TIMER);
    TTF_Init();
}

// Clean up SDL and TTF
void quit(SDL_Window* window, SDL_Renderer* renderer, TTF_Font* font) {
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

int main(int argc, char **argv){
    init_TTF();
    SDL_Window* window = initSDL();
    Uint32 Start_tick = SDL_GetTicks();                    // Chronomètre qui commence dès que le SDL init est en route
    TTF_Font* font = TTF_OpenFont("Config/Roboto-BlackItalic.ttf", 24); // mettre le bon nom du fichier
    
    if (!window) {
        return 1;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    
    printf("Game's Loading...\n");
    
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
            Uint32 Differentiel_ticks = SDL_GetTicks() - Start_tick;
            float Temp_écoulé = Differentiel_ticks/1000.0f; // Seconde ;)
            Display(Temp_écoulé);
           // Make_Ruche();
        }
    }
    
    SDL_DestroyWindow(window);
    quit(window, renderer,font);
    return EXIT_SUCCESS;
}

void SDL_ExitWithError(const char *message){
    SDL_Log("ERREUR : %s > %s\n", message, SDL_GetError());
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
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

// gcc main.c -o SDL $(sdl2-config --cflags --libs)-
//gcc main.c -o SDL $(sdl2-config --cflags --libs) -lSDL2_ttf
