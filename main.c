#include "abeille.h"

int main()
{
    srand(time(NULL));
    unsigned int *jourNumero = malloc(sizeof(unsigned int));
    *jourNumero = 0;


    RuchePtr maRuche = initialisationRuche();
    ListeInsectes mesInsectes = new_list();
    print_list(mesInsectes);

    mesInsectes = initialisationEssaim(mesInsectes, 1000);
    maRuche = initialisationRuche(maRuche);

    
    int NBR_DE_TOURS =5; //choisir le nombre de jours
    for(int i=0;i<NBR_DE_TOURS;i++){
        mesInsectes = tourDeSimulation(mesInsectes, maRuche, jourNumero);
        if(mesInsectes  == NULL)
        {
        printf("Toute la colonie est morte\n");
        printf("_______________________________________________________________________________________________________\n");
        break;
        }
        
    }
    print_list(mesInsectes);
    mesInsectes = clear_list(mesInsectes);  
    print_list(mesInsectes);
    free(jourNumero);
    return 0;


    
}