#include "abeille.c"

int main()
{
    srand(time(NULL));
    unsigned int *jourNumero = malloc(sizeof(unsigned int));
    *jourNumero = 0;

    RuchePtr maRuche = initialisationRuche();
    ListeInsectes mesInsectes = new_list();
    print_list(mesInsectes);

    mesInsectes = initialisationEssaim(mesInsectes, 30);
    maRuche = initialisationRuche(maRuche);

    print_list(mesInsectes);
    printf("Taille de la liste: %u\n", list_length(mesInsectes));
    mesInsectes = tourDeSimulation(mesInsectes, maRuche, jourNumero);
    print_list(mesInsectes);
    mesInsectes = clear_list(mesInsectes);  
    
    free(jourNumero);
    return 0;

    
}