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

SDL_Surface* surface_background = NULL;
SDL_Texture* texture_background = NULL;

SDL_Surface* image_Ruche = NULL;
SDL_Texture* texture_ruche = NULL;

SDL_Surface *BEE_surface = NULL;
SDL_Texture *BEE_texture = NULL;

SDL_Surface* surface_Timer = NULL;
SDL_Texture* texture_Timer = NULL;

extern SDL_Renderer* renderer;
extern SDL_Texture* texture_background;

#define WINDOW_WIDTH 510
#define WINDOW_HEIGHT 510

#define TAILLE_ABEILLE 100
#define NB_BEES 10

void SDL_ExitWithError(const char *message);
typedef struct Ruche {
    float W;    // Largeur
    float X;    // Postion X
    float Y;    // Position Y
    float Z;    // Hauteur
} Ruche;

typedef struct{
    const char* seasonName;
    const char* backgroundImagePath;
}Saison;

Saison seasons[] = {
    {"Spring", "Assets/back_spring.bmp"},  // Assurez-vous que ce chemin est correct
    {"Summer", "Assets/back_autumn.bmp"},  // et que l'image existe bien ici
    {"Autumn", "Assets/back_summer.bmp"},
    {"Winter", "Assets/back_winter.bmp"}
};

//Ruche ruches[BEES];
void load_bee_texture()
{
        SDL_Surface* BEE_surface = SDL_LoadBMP("Assets/Position_1.bmp");
        if (!BEE_surface) {
            printf("Failed to load bee frame! SDL Error: %s\n", SDL_GetError());
            exit(EXIT_FAILURE);
        }

        BEE_texture = SDL_CreateTextureFromSurface(renderer, BEE_surface);

        if (!BEE_texture) {
            printf("Failed to create texture for bee frame! SDL Error: %s\n", SDL_GetError());
            exit(EXIT_FAILURE);
        }
        SDL_FreeSurface(BEE_surface);
        //SDL_FreeTexture() ; 
}
void change_saisons(int seasonIndex, SDL_Texture **texture_background) {
    // Assurez-vous que l'index de saison est valide
    seasonIndex = seasonIndex % 4; // 4 saisons

    // Libère l'ancienne texture si elle existe
    if (*texture_background != NULL) {
        SDL_DestroyTexture(*texture_background);
    }

    // Charge l'image correspondante dans la texture
    SDL_Surface *tempSurface = SDL_LoadBMP(seasons[seasonIndex].backgroundImagePath);
    if (tempSurface == NULL) {
        printf("Could not load image: %s\n", SDL_GetError());
        return;
    }

    *texture_background = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);  // Libérer la surface temporaire après la création de la texture

    if (*texture_background == NULL) {
        printf("Could not create texture: %s\n", SDL_GetError());
    } else {
        printf("Season changed to: %s\n", seasons[seasonIndex].seasonName);
    }
}

/*
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

    sprintf(timeText, "Time: %.1f seconds", Temp_écoulé);

    SDL_Surface *surface_background = SDL_LoadBMP("Assets/back_winter.bmp");
    SDL_Surface *Ruche_surface = SDL_LoadBMP(HIVE_IMAGE);
    SDL_Surface* surface_Timer = TTF_RenderText_Solid(font, timeText, color);

    if(surface_background == NULL)
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Failed to load Backround image");
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
    if (SDL_RenderCopy(renderer,BEE_texture,NULL,&BEE_rect))
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window); 
        SDL_ExitWithError("Failed to render copy the BEE !");
    }
    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);
}
*/
void Display(float elapsed_time)
{
    // Charger la police et préparer le texte du timer
    TTF_Font* font = TTF_OpenFont("Config/Roboto-BlackItalic.ttf", 24);
    if (!font) {
        SDL_ExitWithError("Failed to load font");
    }

    char timeText[100];
    sprintf(timeText, "Time: %.1f seconds", elapsed_time);
    SDL_Color color = {0, 0, 0, 255}; // Couleur blanche pour la police
    SDL_Surface* surface_Timer = TTF_RenderText_Solid(font, timeText, color);
    if (!surface_Timer) {
        SDL_ExitWithError("Failed to create timer surface");
    }
    SDL_Texture* texture_Timer = SDL_CreateTextureFromSurface(renderer, surface_Timer);
    if (!texture_Timer) {
        SDL_ExitWithError("Failed to create timer texture");
    }
    SDL_FreeSurface(surface_Timer); // Libérer la surface car elle n'est plus nécessaire

    // Nettoyer l'écran avec une couleur de fond noire
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Dessiner la texture de fond
    SDL_Rect backgroundRect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT}; // Couvre toute la fenêtre
    if (texture_background != NULL) { // Assurez-vous qu'il y a une texture à dessiner
        if (SDL_RenderCopy(renderer, texture_background, NULL, &backgroundRect) != 0) {
            SDL_ExitWithError("Failed to render background texture");
        }
    } else {
        printf("No background texture to display.\n");
    }

    // Dessiner le timer
    SDL_Rect timerRect = {400, 0, 200, 50}; // Position et taille du timer
    if (SDL_RenderCopy(renderer, texture_Timer, NULL, &timerRect) != 0) {
        SDL_ExitWithError("Failed to render timer texture");
    }

    // Mettre à jour l'écran
    SDL_RenderPresent(renderer);

    // Libération des ressources
    SDL_DestroyTexture(texture_Timer); // Libérer la texture du timer
    TTF_CloseFont(font); // Fermer la police
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


void SDL_ExitWithError(const char *message){
    SDL_Log("ERREUR : %s > %s\n", message, SDL_GetError());
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    exit(EXIT_FAILURE);
}
 /*                        // Pour l'animation de l'abeille (pas opti vu que ça lag sa mère)
for(int i = 1; i<= 4;i++)
    {
        if(SDL_RenderCopy(renderer,BEE_texture[i],NULL,&BEE_rect))
        {
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_ExitWithError("Failed to render Copy the BEE");                               
        }
        SDL_RenderPresent(renderer);
        SDL_Delay(2000);
    }
*/
// gcc main.c -o SDL $(sdl2-config --cflags --libs)-
//gcc main.c -o SDL $(sdl2-config --cflags --libs) -lSDL2_ttf
