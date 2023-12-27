// #include "abeille.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define ID_MAX 10000

#define NOMBRE_ABEILLES_MAX 60000
#define PONTE_MAX_JOUR 2000

#define TEMPS_INCUBATION_REINE_J 3
#define TEMPS_LARVE_REINE_J 6
#define TEMPS_PUPAISON_REINE_J 7
//sort de sa cellule à 16 jours
#define DUREE_VIE_MAX_REINE_J 1460 // =~ 4 ans

#define TEMPS_OEUF_OUVRIERE_J 3
#define TEMPS_LARVE_OUVRIERE_J 6
#define TEMPS_PUPAISON_OUVRIERE_J 12
//sort de sa cellule à 21 jours
#define DUREE_VIE_MAX_OUVRIERE_ETE_J 45
#define DUREE_VIE_MAX_OUVRIERE_HIVER_J 140

#define TEMPS_OEUF_FAUX_BOURDON_J 3
#define TEMPS_LARVE_FAUX_BOURDON_J 6
#define TEMPS_PUPAISON_FAUX_BOURDON_J 12
#define DUREE_VIE_MAX_FAUX_BOURDON_J 60

#define SANTE_MAX 100 
#define SANTE_MIN 0
#define COHESION_MAX 100
#define COHESION_MIN 0

#define EFFICACITE_MAX 100
#define EFFICACITE_MIN 0
#define EFFICACITER_PAR_DEFAUT 50


#define CAPACITE_MAX_POLLEN_CELLULE_G 500 
#define CAPACITE_MAX_MIEL_CELLULE_g 1000 
#define CAPACITE_MAX_GELEE_ROYALE_CELLULE_G 100 
#define CAPACITE_MAX_EAU_CELLULE_ML 250 

#define NOMBRE_MAX_OUVRIERES 60000 
#define NOMBRE_MAX_FAUX_BOURDONS 2000 

#define HUMIDITE_IDEAL 80 
#define TEMPERATURE_IDEAL 35 

#define SANTE_RUCHE_MAX 500
#define SANTE_RUCHE_MIN 0 


typedef enum RoleOuvriere {
    LARVE,
    NETTOYEUSE,
    NOURRICE,
    MAGASINIERE,
    CIRIERE,            
    VENTILEUSE,
    GARDIENNE,
    BUTINEUSE
} RoleOuvriere;

const char* RoleOuvriereStrings[] = {
    "LARVE", "NETTOYEUSE", "NOURRICE", "MAGASINIERE", "CIRIERE", "VENTILEUSE", "GARDIENNE", "BUTINEUSE"
};


typedef struct Ouvriere{
    unsigned int id;
    unsigned int age; 
    unsigned int sante; 
    unsigned int cohesion;
    bool faim;
    unsigned int efficacite; 
    unsigned int experience; 
    RoleOuvriere role;

    struct Ouvriere *next ;
    struct Ouvriere *previous ;
}Ouvriere, *ListOuvrieres ;


ListOuvrieres new_list(void){
    return NULL;
}

bool is_empty_list(ListOuvrieres listeOuvrieres){
    if(listeOuvrieres == NULL){
        return(true);
    }
    else{
        return(false);
    }
}

int list_length(ListOuvrieres listeOuvrieres){
    int length = 0;

    if(!is_empty_list(listeOuvrieres)){
        while(listeOuvrieres != NULL){
            length += 1;
            listeOuvrieres = listeOuvrieres->next ;
        }
    }
    return length ;
}

void print_list(ListOuvrieres listeOuvrieres){
    if(is_empty_list(listeOuvrieres)){
        printf("La liste est vide\n");
    }
    else{
        while(listeOuvrieres != NULL){
            printf("Id: %1d : age(en J): %u : sante: %u : cohesion: %u : faim: %s : efficacite: %u : experience: %u : role: %s\n", 
                    listeOuvrieres->id, 
                    listeOuvrieres->age, 
                    listeOuvrieres->sante, 
                    listeOuvrieres->cohesion, 
                    listeOuvrieres->faim ? "Vrai" : "Faux", 
                    listeOuvrieres->efficacite, 
                    listeOuvrieres->experience, 
                    RoleOuvriereStrings[listeOuvrieres->role]);
            listeOuvrieres = listeOuvrieres->next ; 
        }
        printf("\n");
    }
} 



ListOuvrieres NAISSANCE_push_front_list(ListOuvrieres listeOuvrieres){
    ListOuvrieres nouvelleOuvriere = malloc(sizeof(Ouvriere));
    if(nouvelleOuvriere == NULL){
        perror("Erreur aloocation mémoire\n");
        exit(EXIT_FAILURE);
    }
    nouvelleOuvriere->id = rand() % ID_MAX;
    nouvelleOuvriere->age = 0 ;
    nouvelleOuvriere->cohesion = COHESION_MAX ;
    nouvelleOuvriere->efficacite = EFFICACITER_PAR_DEFAUT ;
    nouvelleOuvriere->experience = 0 ;
    nouvelleOuvriere->faim = false ;
    nouvelleOuvriere->role = LARVE ;
    nouvelleOuvriere->sante = SANTE_MAX ;

    nouvelleOuvriere->next = listeOuvrieres; 
    nouvelleOuvriere->previous = NULL; 

    if(!is_empty_list(listeOuvrieres)){
        listeOuvrieres->previous = nouvelleOuvriere; 
    }

    return nouvelleOuvriere ;
}


ListOuvrieres GENERATION_push_front_list(ListOuvrieres listeOuvrieres, unsigned int age, unsigned int sante, unsigned int cohesion, bool faim, unsigned int efficacite, unsigned int experience, RoleOuvriere role ){
    ListOuvrieres nouvelleOuvriere = malloc(sizeof(Ouvriere));
    if(nouvelleOuvriere == NULL){
        perror("Erreur aloocation mémoire\n");
        exit(EXIT_FAILURE);
    }
    nouvelleOuvriere->id = rand() % ID_MAX;
    nouvelleOuvriere->age = age ;
    nouvelleOuvriere->cohesion = cohesion ;
    nouvelleOuvriere->efficacite = efficacite ;
    nouvelleOuvriere->experience = experience;
    nouvelleOuvriere->faim = faim ;
    nouvelleOuvriere->role = role ;
    nouvelleOuvriere->sante = sante ;

    nouvelleOuvriere->next = listeOuvrieres; 
    nouvelleOuvriere->previous = NULL; 

    if(!is_empty_list(listeOuvrieres)){
        listeOuvrieres->previous = nouvelleOuvriere; 
    }

    return nouvelleOuvriere ;
}

/*
LARVE 20%, NETTOYEUSE 5%, NOURRICE 15, MAGASINIERE 10%, CIRIERE 10%, VENTILEUSE 5%, GARDIENNE 2%, BUTINEUSE 33%
*/


ListOuvrieres initialisationEssaim(ListOuvrieres listeOuvrieres, unsigned int nbOuvrieres){
    unsigned int i ;
    unsigned int nbLarves = (nbOuvrieres * 20) / 100; // 20%
    unsigned int nbNettoyeuses = (nbOuvrieres * 5) / 100; // 5%
    unsigned int nbNourrices = (nbOuvrieres * 15) / 100; // 15%
    unsigned int nbMagasinieres = (nbOuvrieres * 10) / 100; // 10%
    unsigned int nbCirieres = (nbOuvrieres * 10) / 100; // 10%
    unsigned int nbVentileuses = (nbOuvrieres * 5) / 100; // 5%
    unsigned int nbGardiennes = (nbOuvrieres * 2) / 100; // 2%
    unsigned int nbButineuses = (nbOuvrieres * 33) / 100; // 33%

    for( i = 0; i < nbLarves; i++){
        listeOuvrieres = GENERATION_push_front_list(listeOuvrieres, 0, SANTE_MAX, COHESION_MAX, false, EFFICACITER_PAR_DEFAUT, 0, LARVE);
    }
    for( i = 0; i < nbNettoyeuses; i++){
        listeOuvrieres = GENERATION_push_front_list(listeOuvrieres, 0, SANTE_MAX, COHESION_MAX, false, EFFICACITER_PAR_DEFAUT, 0, NETTOYEUSE);
    }
    for( i = 0; i < nbNourrices; i++){
        listeOuvrieres = GENERATION_push_front_list(listeOuvrieres, 0, SANTE_MAX, COHESION_MAX, false, EFFICACITER_PAR_DEFAUT, 0, NOURRICE);
    }
    for( i = 0; i < nbMagasinieres; i++){
        listeOuvrieres = GENERATION_push_front_list(listeOuvrieres, 0, SANTE_MAX, COHESION_MAX, false, EFFICACITER_PAR_DEFAUT, 0, MAGASINIERE);
    }
    for( i = 0; i < nbCirieres; i++){
        listeOuvrieres = GENERATION_push_front_list(listeOuvrieres, 0, SANTE_MAX, COHESION_MAX, false, EFFICACITER_PAR_DEFAUT, 0, CIRIERE);
    }
    for( i = 0; i < nbVentileuses; i++){
        listeOuvrieres = GENERATION_push_front_list(listeOuvrieres, 0, SANTE_MAX, COHESION_MAX, false, EFFICACITER_PAR_DEFAUT, 0, VENTILEUSE);
    }
    for( i = 0; i < nbGardiennes; i++){
        listeOuvrieres = GENERATION_push_front_list(listeOuvrieres, 0, SANTE_MAX, COHESION_MAX, false, EFFICACITER_PAR_DEFAUT, 0, GARDIENNE);
    }
    for( i = 0; i < nbButineuses; i++){
        listeOuvrieres = GENERATION_push_front_list(listeOuvrieres, 0, SANTE_MAX, COHESION_MAX, false, EFFICACITER_PAR_DEFAUT, 0, BUTINEUSE);
    }
    return listeOuvrieres ;

}



ListOuvrieres pop_front_list(ListOuvrieres listeOuvrieres){
    ListOuvrieres nouvelleTete = malloc(sizeof(Ouvriere));
    if(nouvelleTete == NULL){
        perror("Erreur allocation mémoire\n");
        exit(EXIT_FAILURE);
    }

    if(is_empty_list(listeOuvrieres)){
        return new_list();
    }

    nouvelleTete = listeOuvrieres->next ; 
    free(listeOuvrieres);
    listeOuvrieres = NULL;
    if(!is_empty_list(nouvelleTete)){
        nouvelleTete->previous = NULL;
    }
    return nouvelleTete ;


}

ListOuvrieres clear_list(ListOuvrieres listeOuvrieres){
    if(is_empty_list(listeOuvrieres)){
        return new_list() ;
    }
    else{
        while(listeOuvrieres != NULL){
            listeOuvrieres = pop_front_list(listeOuvrieres);
        }
        return listeOuvrieres;
    }
}



int main(){
    srand(time(NULL));
    ListOuvrieres maRuche = new_list();
    
    print_list(maRuche);
    maRuche = initialisationEssaim(maRuche, 100);
    print_list(maRuche);
    printf("Taille de la liste: %d\n", list_length(maRuche));
    
    maRuche = clear_list(maRuche);
    print_list(maRuche);

    
}

