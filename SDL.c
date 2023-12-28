#include "SDL.h"



/*
    SDL_RENDERER_SOFTWARE (procésseur)
    SDL_RENDERER_ACCELERATED (accelaration materielle carte graphique)
    SDL_RENDERER_PRESENTVSYNC (synchronisation verticale)
    SDL_RENDERER_TARGETTEXTURE (rendu selon texture)

*/


void SDL_ExitWithError(const char *message);

int main(int argc, char **argv){
    SDL_version nb ;
    SDL_VERSION(&nb);
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    printf("SDL %d.%d.%d !\n", nb.major, nb.minor, nb.patch);


    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        SDL_ExitWithError("Initialisation SDL");
    }

    if(SDL_CreateWindowAndRenderer(800, 600, 0, &window, &renderer) != 0){
        SDL_ExitWithError("Impossible de creer la fenetre et le rendu");
    }

    // window = SDL_CreateWindow("Première fenêtre SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    // if(window == NULL){
    //     SDL_ExitWithError("Creation fenetre echouee");
    // }

    // renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    // if(renderer == NULL){
    //     SDL_ExitWithError("Creation rendu echouee");
    // }

    if(SDL_SetRenderDrawColor(renderer, 112, 168, 237, SDL_ALPHA_OPAQUE) != 0){
        SDL_ExitWithError("Impossible de changer la couleur pour le rendu");
    }


    if(SDL_RenderDrawPoint(renderer, 100, 450) != 0){
        SDL_ExitWithError("Impossible de dessiner un point");
    }

    if(SDL_RenderDrawLine(renderer, 50, 50, 500, 500) != 0){
        SDL_ExitWithError("Impossible de dessiner une ligne");
    }

    SDL_Rect rectangle ;
    rectangle.x = 400;
    rectangle.y = 300;
    rectangle.w = 200;
    rectangle.h = 100;


    if(SDL_RenderDrawRect(renderer, &rectangle) != 0){
        SDL_ExitWithError("Impossible de dessiner une ligne");
    }

    SDL_RenderPresent(renderer);
    SDL_Delay(3000);

    if(SDL_RenderClear(renderer) != 0){
        SDL_ExitWithError("Effacement rendu echouee");
    }
 
    SDL_DestroyWindow(window);
    SDL_Quit() ;
    return EXIT_SUCCESS;
}

// gcc main.c -o prog $(sdl2-config --cflags --libs)

void SDL_ExitWithError(const char *message){
    SDL_Log("ERREUR : %s > %s\n", message, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}