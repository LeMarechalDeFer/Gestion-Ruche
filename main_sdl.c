#include "V.SDL/game.c"
#include "abeille.h"


int main()
{
    srand(time(NULL));
    unsigned int *jourNumero = malloc(sizeof(unsigned int));
    *jourNumero = 0;


    RuchePtr maRuche = initialisationRuche();
    ListeInsectes mesInsectes = new_list();
    print_list(mesInsectes);

    mesInsectes = initialisationEssaim(mesInsectes, 20);
    maRuche = initialisationRuche(maRuche);

    /*
    int NBR_DE_TOURS =45; //choisir le nombre de jours
    for(int i=0;i<NBR_DE_TOURS;i++){
        mesInsectes = tourDeSimulation(mesInsectes, maRuche, jourNumero);
        if(mesInsectes  == NULL)
        {
        printf("Toute la colonie est morte\n");
        printf("_______________________________________________________________________________________________________\n");
        break;
        }
        delay(1000)
    }
    //print_list(mesInsectes);
    mesInsectes = clear_list(mesInsectes);  
    print_list(mesInsectes);
    free(jourNumero);*/
    // ///////////////////////////////////////////////////////////////////////////////////////////////////
    init_TTF();
    SDL_Window* window = initSDL();
    //Uint32 Start_tick = SDL_GetTicks();                    // Chronomètre qui commence dès que le SDL init est en route
    Uint32 Start_tick_player = SDL_GetTicks();
    TTF_Font* font = TTF_OpenFont("V.SDL/Assets/Roboto-BlackItalic.ttf", 24); // mettre le bon nom du fichier
    
    if (!window) {
        return 1;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    
    printf("Game's Loading...\n");
    
    SDL_bool program_launched = SDL_TRUE;              
    


        // Initialisation de la texture de fond par défaut
    SDL_Surface* defaultSurface = SDL_LoadBMP("V.SDL/Assets/back_spring.bmp"); // Remplacez par votre chemin d'accès
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

        int NBR_DE_TOURS =10; //choisir le nombre de jours
        int tours_execut =0;
    for(int i=0;i<NBR_DE_TOURS;i++)
    {
        
        
        
        SDL_Event action_utilisateur;
        
        while (SDL_PollEvent(&action_utilisateur))
        {
            switch (action_utilisateur.type)
            {
                case SDL_QUIT:
                defaultSurface = SDL_LoadBMP("V.SDL/Assets/gameover.bmp");
                if (!defaultSurface) {
                    printf("Unable to load default gameover image! SDL_Error: %s\n", SDL_GetError());
                } else {
                    SDL_Texture* newTexture = SDL_CreateTextureFromSurface(renderer, defaultSurface);
                    if (!newTexture) {
                        printf("Unable to create texture from gameover image! SDL_Error: %s\n", SDL_GetError());
                    } else {
                        if (texture_background) {
                            SDL_DestroyTexture(texture_background); // Libérer l'ancienne texture
                        }
                        texture_background = newTexture; // Utiliser la nouvelle texture
                    }
                    SDL_FreeSurface(defaultSurface); // Libérer la surface
                }
                SDL_Delay(200); // Temps de pause avant de quitter
                program_launched = SDL_FALSE;
                break;

                case SDL_KEYDOWN:
                    if (action_utilisateur.key.keysym.sym == SDLK_ESCAPE)    // Quitter quand on appuie sur ECHAP
                    {
                            defaultSurface = SDL_LoadBMP("V.SDL/Assets/gameover.bmp");
                        if (!defaultSurface) {
                        printf("Unable to load default gameover image! SDL_Error: %s\n", SDL_GetError());
                        } else {
                        SDL_Texture* newTexture = SDL_CreateTextureFromSurface(renderer, defaultSurface);
                        if (!newTexture) {
                            printf("Unable to create texture from gameover image! SDL_Error: %s\n", SDL_GetError());
                        } else {
                            if (texture_background) {
                                
                            }
                            texture_background = newTexture; // Utiliser la nouvelle texture
                        }
                        SDL_FreeSurface(defaultSurface); // Libérer la surface
                        }   
                        SDL_Delay(100); // Temps de pause avant de quitter
                        program_launched = SDL_FALSE;
                        break;
                    }
                    else
                        continue;
            }
            
           
        }
        
        Display( i );

        
        mesInsectes = tourDeSimulation(mesInsectes, maRuche, jourNumero);
        if(mesInsectes  == NULL)
        {
        printf("Toute la colonie est morte\n");
        printf("_______________________________________________________________________________________________________\n");
        }
        SDL_Delay(10);
        
        change_de_saisons(cycleSaison(jourNumero),&texture_background);
        
    defaultSurface = SDL_LoadBMP("V.SDL/Assets/gameover.bmp"); // Remplacez par votre chemin d'accès
    if (!defaultSurface) {
        printf("Unable to load default gameover image! SDL_Error: %s\n", SDL_GetError());
        // Gérez l'erreur comme vous préférez ici (par exemple, quitter le programme)
    }
    
    mesInsectes = clear_list(mesInsectes);  
    print_list(mesInsectes);
    free(jourNumero);
    // 
    SDL_DestroyWindow(window);
    quit(window, renderer,font);
    return 0;
}