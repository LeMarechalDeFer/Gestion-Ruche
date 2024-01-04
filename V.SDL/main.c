#include "game.c"


int main(int argc, char **argv)
{
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