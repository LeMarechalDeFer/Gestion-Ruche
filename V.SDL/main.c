#include "game.c"


int main(int argc, char **argv)
{
    init_TTF();
    SDL_Window* window = initSDL();
    Uint32 Start_tick = SDL_GetTicks();                    // Chronomètre qui commence dès que le SDL init est en route
    Uint32 Start_tick_player = SDL_GetTicks();
    TTF_Font* font = TTF_OpenFont("Config/Roboto-BlackItalic.ttf", 24); // mettre le bon nom du fichier
    
    if (!window) {
        return 1;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    
    printf("Game's Loading...\n");
    
    SDL_bool program_launched = SDL_TRUE;              
    int seasonIndex  =0;


        // Initialisation de la texture de fond par défaut
    SDL_Surface* defaultSurface = SDL_LoadBMP("Assets/back_winter.bmp"); // Remplacez par votre chemin d'accès
    if (!defaultSurface) {
        printf("Unable to load default background image! SDL_Error: %s\n", SDL_GetError());
        // Gérez l'erreur comme vous préférez ici (par exemple, quitter le programme)
    }

    texture_background = SDL_CreateTextureFromSurface(renderer, defaultSurface);
    if (!texture_background) {
        printf("Unable to create texture from default background image! SDL_Error: %s\n", SDL_GetError());
        // Gérez l'erreur comme vous préférez ici
    }

    SDL_FreeSurface(defaultSurface); // Libérez la surface, elle n'est plus nécessaire

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
            
           // Make_Ruche();
        }
        // Vérifiez le temps écoulé et changez de saison toutes les 5 secondes en dehors de la boucle SDL_PollEvent
        Uint32 Differentiel_ticks = SDL_GetTicks() - Start_tick;
        Uint32 Differentiel_ticks_player = SDL_GetTicks() - Start_tick_player;
        float Temp_écoulé = Differentiel_ticks/1000.0f; // Seconde ;)
        float Temp_écoulé_player = Differentiel_ticks_player/1000.0f; //pour que le joueur continue a soir ce qui ce passe 
        if (Temp_écoulé >= 4)
        {
        change_saisons(seasonIndex , &texture_background); // Change la saison
        seasonIndex++;
        Start_tick = SDL_GetTicks(); // Réinitialise le chronomètre pour le prochain intervalle
        }
        Display(Temp_écoulé_player);
        
        
    }
    
    SDL_DestroyWindow(window);
    quit(window, renderer,font);
    return EXIT_SUCCESS;
}