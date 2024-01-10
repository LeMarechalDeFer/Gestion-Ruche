#include "abeille.h"

int main()
{
    srand(time(NULL));
    unsigned int *jourNumero = malloc(sizeof(unsigned int));
    *jourNumero = 0;
    int i;


    RuchePtr maRuche = initialisationRuche();
    ListeInsectes mesInsectes = new_list();
    print_list(mesInsectes);

    mesInsectes = initialisationEssaim(mesInsectes, 1000);
    maRuche = initialisationRuche(maRuche);

    
    int NBR_DE_TOURS =45; //choisir le nombre de jours
    
    /* NB : Notons un soucis de conception au niveau de la complexité algorithmique dans la fonction actionOuvriere (lors de la distribution par les nourriciere au larve) ralentissant le programme 
    On aura s'il on avait voulu pu simplement nourrir automatiquement les larves sans passer par une autre abeille (nourriciere) mais cela aurait été moins réaliste
    */
    for(i=0; (i<NBR_DE_TOURS)&& (conditionMortRuche(maRuche, mesInsectes)==false); i++)
    {
        mesInsectes = tourDeSimulation(mesInsectes, maRuche, jourNumero);
        //delay(2);  
        if(mesInsectes  == NULL){
        printf("Toute la colonie est morte\n");
        printf("_______________________________________________________________________________________________________\n");
        break;
        }
    }
    

    //print_list(mesInsectes);
    mesInsectes = clear_list(mesInsectes);  
    print_list(mesInsectes);
    free(jourNumero);
    return 0;


    
}