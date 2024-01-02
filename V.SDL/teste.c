
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>


SDL_Renderer* SDL_CreateRenderer(SDL_Window* window,
                                 int         index,
                                 Uint32      flags); // permet de dessiner dans la fenetre 

SDL_Window* SDL_CreateWindow(const char* title,
                             int         x,
                             int         y,
                             int         w,
                             int         h,
                             Uint32      flags);

int SDL_CreateWindowAndRenderer(int            width,
                                int            height,
                                Uint32         window_flags,
                                SDL_Window**   window,
                                SDL_Renderer** renderer);   //permet de créer window et rendered en meme temps
void SDL_Quit(void);
const char* SDL_GetError(void);
void SDL_Delay(Uint32 ms);
void SDL_DestroyWindow(SDL_Window* window);

const char* SDL_GetWindowTitle(SDL_Window* window);
void SDL_SetWindowTitle(SDL_Window* window,const char* title);


void SDL_GetWindowPosition(SDL_Window* window,
                           int*        x,
                           int*        y);

void SDL_SetWindowPosition(SDL_Window* window,
                           int         x,
                           int         y);

/*//changer les taille 
void SDL_MaximizeWindow(SDL_Window* window); 
void SDL_MinimizeWindow(SDL_Window* window); 
void SDL_RestoreWindow(SDL_Window* window);

int SDL_SetWindowFullscreen(SDL_Window* window,
                            Uint32 flags);*/
int main(int argc, char *argv[])
{
    SDL_Window *window =NULL; //ini pointeur (c'est lui qu'on va modifier pour modifier la fenetre)
    SDL_Renderer *renderer = NULL; //ini rendered (c'est lui qui comunique avec l'ordi pour modifier ce qui se passe dans la fenetre )
    int statut = EXIT_FAILURE;
    if(0 != SDL_Init(SDL_INIT_VIDEO))//*
    {
        fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
        goto Quit;
    }
 
    window = SDL_CreateWindow(
        "LA RUCHE DES MILLES ET UNE ABEILLES",                  // window title
        SDL_WINDOWPOS_CENTERED,  // initial x position
        SDL_WINDOWPOS_CENTERED,  // initial y position
        800,                     // width, in pixels
        600,                     // height, in pixels
        SDL_WINDOW_SHOWN         // flags - see below
    ); //**
    //SDL_SetWindowTitle(window, "LA RUCHE DES MILLES ET UNE ABEILLES2"); 
    //SDL_SetWindowPosition(window,5000 ,SDL_WINDOWPOS_CENTERED);
    if(NULL == window)
    {
        fprintf(stderr, "Erreur SDL_CreateWindow : %s", SDL_GetError());
        goto Quit;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(NULL == renderer)
    {
        fprintf(stderr, "Erreur SDL_CreateRenderer : %s", SDL_GetError());
        goto Quit;
    }
   // SDL_SetWindowFullscreen(window,SDL_WINDOW_FULLSCREEN );
    statut =EXIT_SUCCESS;
    SDL_Delay(3000);// nombre de temps que s'affiche la fenetre

   
Quit:                                 //goto code (permet de sauter )
    if(NULL != renderer)
        SDL_DestroyRenderer(renderer);
    if(NULL != window)
        SDL_DestroyWindow(window);
    SDL_Quit();
    return statut;
    return EXIT_SUCCESS;
}

//*
/*Drapeaux
SDL_INIT_TIMER
Initialise le système de gestion du temps
SDL_INIT_AUDIO
Initialise le système de gestion de l’audio
SDL_INIT_VIDEO
Initialise le système de gestion de rendu
SDL_INIT_JOYSTICK
Initialise le système de gestion des joysticks
SDL_INIT_GAMECONTROLLER
Initialise le système de gestion des contrôleurs de jeux
SDL_INIT_EVENTS
Initialise le système de gestion des évènements
SDL_INIT_EVERYTHING
Permet de tout initialiser
*/

//**
/*Drapeaux
SDL_WINDOW_FULLSCREEN
Crée une fenêtre en plein écran
SDL_WINDOW_FULLSCREEN_DESKTOP
Crée une fenêtre en plein écran à la résolution du bureau
SDL_WINDOW_SHOWN
Crée une fenêtre visible
SDL_WINDOW_HIDDEN
Crée une fenêtre non visible
SDL_WINDOW_BORDERLESS
Crée une fenêtre sans bordures
SDL_WINDOW_RESIZABLE
Crée une fenêtre redimensionnable
SDL_WINDOW_MINIMIZED
Crée une fenêtre minimisée
SDL_WINDOW_MAXIMIZED
Crée une fenêtre maximisée
*/

//***
/*
SDL_RENDERER_SOFTWARE
Le renderer est logiciel, le rendu sera effectué par le CPU et les données seront stockées en mémoire vive.
SDL_RENDERER_ACCELERATED
Le renderer utilise l’accélération matérielle. Les données sont en mémoire vidéo, plus rapide que la mémoire vive.
SDL_RENDERER_PRESENTVSYNC
La mise à jour de la fenêtre de rendu est synchronisé avec la fréquence de rafraîchissement de l’écran.*/