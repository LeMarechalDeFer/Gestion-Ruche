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

typedef enum Saisons {
    PRINTEMPS,
    ETE,
    AUTOMNE,
    HIVER
} Saisons;


typedef struct Ruche {
    float temperature;
    float humidite;
    float salete;

    unsigned int sante;

    unsigned int reserveMiel;
    unsigned int reserveEau;
    unsigned int reservePollen;
    unsigned int reserveGeleeRoyale;

    unsigned int nombreOuvrieres;
    unsigned int nombreFauxBourdon;
    unsigned int jourNumero;
    Saisons saison;
    
} Ruche;

typedef	enum cycleCroissance{
    OEUF,
    LARVE,
    PUPAISON,
    ADULTE
} cycleCroissance ;
typedef enum RoleOuvriere {
    OEUF,
    LARVE,
    PUPAISON,
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

typedef enum Pheromones {
    INCITATRICE,
    MODIFICATRICE
} Pheromones;


typedef enum TypeInsecte{
    TYPE_REINE,
    TYPE_OUVRIERE,
    TYPE_FAUX_BOURDON,
    TYPE_OURSE,
    TYPE_GUEPE
} TypeInsecte;

typedef struct Reine {
    bool ponteJournaliere;  
    bool emmet_feromones; 
} Reine;

typedef struct Ouvriere{
    unsigned int cohesion;
    unsigned int efficacite; 
    unsigned int experience; 
    RoleOuvriere role;
} Ouvriere;

typedef struct FauxBourdon {
    bool feromones;
    bool enQueteReine;
} FauxBourdon;

typedef struct Insecte {
    unsigned int id;
    unsigned int sante; 
    unsigned int age; 
    bool faim;
    TypeInsecte type; 
    union {
        Reine reine;
        Ouvriere ouvriere;
        FauxBourdon FauxBourdon;
    } data;
    struct Insecte *next;
    struct Insecte *previous;
} Insecte, *ListeInsectes;





ListeInsectes new_list(void){
    return NULL;
}

bool is_empty_list(ListeInsectes listeInsectes){
    if(listeInsectes == NULL){
        return(true);
    }
    else{
        return(false);
    }
}

int list_length(ListeInsectes listeInsectes){
    int length = 0;

    if(!is_empty_list(listeInsectes)){
        while(listeInsectes != NULL){
            length += 1;
            listeInsectes = listeInsectes->next ;
        }
    }
    return length ;
}

void print_list(ListeInsectes listeInsectes){  
    if(is_empty_list(listeInsectes)){
        printf("La liste est vide\n");
    }
    else{
        while(listeInsectes != NULL){
            printf("ID: %u, Age: %u, Sante: %u, Faim: %s, ", 
                    listeInsectes->id,
                    listeInsectes->age, 
                    listeInsectes->sante, 
                    listeInsectes->faim ? "Oui" : "Non");
            switch(listeInsectes->type) {
                case TYPE_REINE:
                    printf("Type: Reine, Ponte Journaliere: %s, Emet Feromones: %s\n",
                           listeInsectes->data.reine.ponteJournaliere ? "Oui" : "Non",
                           listeInsectes->data.reine.emmet_feromones ? "Oui" : "Non");
                    break;
                case TYPE_OUVRIERE:
                    printf("Type: Ouvriere, Cohésion: %u, Efficacite: %u, Experience: %u, Role: %s\n",
                            listeInsectes->data.ouvriere.cohesion,
                            listeInsectes->data.ouvriere.efficacite,
                            listeInsectes->data.ouvriere.experience,
                            RoleOuvriereStrings[listeInsectes->data.ouvriere.role]);
                    break;
                case TYPE_FAUX_BOURDON:
                    printf("Type: Faux Bourdon, Féromones: %s, En quete de Reine: %s\n",
                            listeInsectes->data.FauxBourdon.feromones ? "Oui" : "Non",
                            listeInsectes->data.FauxBourdon.enQueteReine ? "Oui" : "Non");
                    break;
            }
            listeInsectes = listeInsectes->next ; 
        }
        printf("\n");
    }
}


ListeInsectes GENERATION_push_front_list(ListeInsectes listeInsectes, 
                                        TypeInsecte type, 
                                        RoleOuvriere role,
                                        unsigned int age, 
                                        unsigned int sante, 
                                        bool faim){
    ListeInsectes nouvelInsecte = malloc(sizeof(Insecte));
    if(nouvelInsecte == NULL){
        perror("Erreur allocation mémoire\n");
        exit(EXIT_FAILURE);
    }
    nouvelInsecte->id = rand() % ID_MAX; 
    nouvelInsecte->age = age;
    nouvelInsecte->sante = sante;
    nouvelInsecte->faim = faim;
    nouvelInsecte->type = type;

    switch(type){
        case TYPE_REINE:
            nouvelInsecte->data.reine.ponteJournaliere = true; 
            nouvelInsecte->data.reine.emmet_feromones = true; 
            break;
        case TYPE_OUVRIERE:
            nouvelInsecte->data.ouvriere.cohesion = COHESION_MAX; 
            nouvelInsecte->data.ouvriere.efficacite = EFFICACITER_PAR_DEFAUT; 
            nouvelInsecte->data.ouvriere.experience = 0; 
            nouvelInsecte->data.ouvriere.role = role;
            break;
        case TYPE_FAUX_BOURDON:
            nouvelInsecte->data.FauxBourdon.feromones = true; 
            nouvelInsecte->data.FauxBourdon.enQueteReine = false; 
            break;
        
    }

    // Gestion de la liste chaînée
    nouvelInsecte->next = listeInsectes;
    if(listeInsectes != NULL){
        listeInsectes->previous = nouvelInsecte;
    }
    nouvelInsecte->previous = NULL;

    return nouvelInsecte; // Retourner la nouvelle tête de la liste
}


/*
LARVE 20%, NETTOYEUSE 5%, NOURRICE 15, MAGASINIERE 10%, CIRIERE 10%, VENTILEUSE 5%, GARDIENNE 2%, BUTINEUSE 33%
*/

ListeInsectes initialisationEssaim(ListeInsectes listeInsectes, unsigned int nbOuvrieres) {
    unsigned int i;
    unsigned int nbLarves = (nbOuvrieres * 20) / 100; // 20%
    unsigned int nbNettoyeuses = (nbOuvrieres * 5) / 100; // 5%
    unsigned int nbNourrices = (nbOuvrieres * 15) / 100; // 15%
    unsigned int nbMagasinieres = (nbOuvrieres * 10) / 100; // 10%
    unsigned int nbCirieres = (nbOuvrieres * 10) / 100; // 10%
    unsigned int nbVentileuses = (nbOuvrieres * 5) / 100; // 5%
    unsigned int nbGardiennes = (nbOuvrieres * 2) / 100; // 2%
    unsigned int nbButineuses = (nbOuvrieres * 33) / 100; // 33%
    unsigned int nbFauxBourdon = (nbOuvrieres * 5) / 100;

    listeInsectes = GENERATION_push_front_list(listeInsectes, TYPE_REINE, 0, 0, SANTE_MAX, false);
    
    for(i = 0; i < nbLarves; i++) {
        listeInsectes = GENERATION_push_front_list(listeInsectes, TYPE_OUVRIERE, LARVE, 0, SANTE_MAX, false);
    }
    for(i = 0; i < nbNettoyeuses; i++) {
        listeInsectes = GENERATION_push_front_list(listeInsectes, TYPE_OUVRIERE, NETTOYEUSE, 0, SANTE_MAX, false);
    }
    for(i = 0; i < nbNourrices; i++) {
        listeInsectes = GENERATION_push_front_list(listeInsectes, TYPE_OUVRIERE, NOURRICE, 0, SANTE_MAX, false);
    }
    for(i = 0; i < nbMagasinieres; i++) {
        listeInsectes = GENERATION_push_front_list(listeInsectes, TYPE_OUVRIERE, MAGASINIERE, 0, SANTE_MAX, false);
    }
    for(i = 0; i < nbCirieres; i++) {
        listeInsectes = GENERATION_push_front_list(listeInsectes, TYPE_OUVRIERE, CIRIERE, 0, SANTE_MAX, false);
    }
    for(i = 0; i < nbVentileuses; i++) {
        listeInsectes = GENERATION_push_front_list(listeInsectes, TYPE_OUVRIERE, VENTILEUSE, 0, SANTE_MAX, false);
    }
    for(i = 0; i < nbGardiennes; i++) {
        listeInsectes = GENERATION_push_front_list(listeInsectes, TYPE_OUVRIERE, GARDIENNE, 0, SANTE_MAX, false);
    }
    for(i = 0; i < nbButineuses; i++) {
        listeInsectes = GENERATION_push_front_list(listeInsectes, TYPE_OUVRIERE, BUTINEUSE, 0, SANTE_MAX, false);
    }

    for(i=0; i< nbFauxBourdon; i++ ){
        listeInsectes = GENERATION_push_front_list(listeInsectes, TYPE_FAUX_BOURDON, 0, 0, SANTE_MAX, false);
    }

    return listeInsectes;
}



ListeInsectes pop_front_list(ListeInsectes listeInsectes){
    ListeInsectes nouvelleTete = malloc(sizeof(Ouvriere));
    if(nouvelleTete == NULL){
        perror("Erreur allocation mémoire\n");
        exit(EXIT_FAILURE);
    }

    if(is_empty_list(listeInsectes)){
        return new_list();
    }

    nouvelleTete = listeInsectes->next ; 
    free(listeInsectes);
    listeInsectes = NULL;
    if(!is_empty_list(nouvelleTete)){
        nouvelleTete->previous = NULL;
    }
    return nouvelleTete ;


}

ListeInsectes clear_list(ListeInsectes listeInsectes){
    if(is_empty_list(listeInsectes)){
        return new_list() ;
    }
    else{
        while(listeInsectes != NULL){
            listeInsectes = pop_front_list(listeInsectes);
        }
        return listeInsectes;
    }
}

// ON PROGRESS !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


/*
- Cycle de vie : naissance croissance mort 
- Cycle des saisons : Printemps Ete Automne Hiver
- Activité journaliere de reine: 
    - ponte larves
    - auto-gestion/intelligence collective de la colonie 
- Activité journaliere des ouvrieres avec ces sous categories
- Activité journaliere faux bourdons
- SDL
- Ruche
- Meteo
- Prédateurs/ Nuisibles
- Maladies 
*/



ListeInsectes cycleCroissance(ListeInsectes listeInsectes){
    if(listeInsectes->type == TYPE_OUVRIERE){
        if(listeInsectes->age >= TEMPS_OEUF_OUVRIERE_J){
            listeInsectes->data.ouvriere.role = LARVE;
        }
        if(listeInsectes->age >= TEMPS_LARVE_OUVRIERE_J){
            listeInsectes->data.ouvriere.role = PUPAISON;
        }
        if(listeInsectes->age >= TEMPS_PUPAISON_OUVRIERE_J){
            listeInsectes->data.ouvriere.role = NETTOYEUSE;
        }
    }
    if(listeInsectes->type == TYPE_FAUX_BOURDON){
        if(listeInsectes->age >= TEMPS_OEUF_FAUX_BOURDON_J){
            listeInsectes.
        } 
        if
    }

    return listeInsectes
}

ListeInsectes cyclePondaisonReine(ListeInsectes listeInsectes, Saisons saison){
    if(is_empty_list(listeInsectes)){
        return new_list();
    }
    else{
        while(listeInsectes != NULL){
            if(listeInsectes->type == TYPE_REINE){
                if(saison == PRINTEMPS || saison == ETE){
                    listeInsectes->data.reine.ponteJournaliere = true;
                }
                // if(listeInsectes->data.reine.emmet_feromones){
                //     //emission de feromones
                // }
            }
            listeInsectes = listeInsectes->next ;
        }
        return listeInsectes;
    }
}

// On assume un depart au debut printemps pour un maximum de ponte et de reserver de nourriture
Saisons cycleSaison(unsigned int jourNumero){
    jourNumero += 1;
    if(jourNumero >= 1 && jourNumero <= 90){
        return PRINTEMPS;
    }
    else if(jourNumero >= 91 && jourNumero <= 180){
        return ETE;
    }
    else if(jourNumero >= 181 && jourNumero <= 270){
        return AUTOMNE;
    }
    else if(jourNumero >= 271 && jourNumero <= 365){
        return HIVER;
    }
    else{
        return PRINTEMPS;
    }
}


// Pas de test effectuer 
ListeInsectes cycledeMort(ListeInsectes listeInsectes, Saisons saisons){
    if(is_empty_list(listeInsectes)){
        return new_list();
    }
    else{
        while(listeInsectes != NULL){
            // if(listeInsectes->faim==true){
            //     listeInsectes->sante -= 25; //sachant 100 pts de vie, donner une valeur arbitraire pour determiner le nombre de jour de famine acceptable/ capacité abeille ? 
            // }
            if(listeInsectes->type == TYPE_REINE){
                if(listeInsectes->age >= DUREE_VIE_MAX_REINE_J){
                    listeInsectes = pop_front_list(listeInsectes);
                }
            }
            if(listeInsectes->type == TYPE_OUVRIERE){
                if((listeInsectes->age >= DUREE_VIE_MAX_OUVRIERE_ETE_J && (saisons == ETE || saisons == PRINTEMPS)) 
                    || listeInsectes->age >= DUREE_VIE_MAX_OUVRIERE_HIVER_J && (saisons == HIVER || saisons == AUTOMNE)){
                    listeInsectes = pop_front_list(listeInsectes);
                }
            }
            if(listeInsectes->type == TYPE_FAUX_BOURDON){
                if(listeInsectes->age >= DUREE_VIE_MAX_FAUX_BOURDON_J){
                    listeInsectes = pop_front_list(listeInsectes);
                }
            }
            listeInsectes = listeInsectes->next ;
        }
        return listeInsectes;
    }
}

// A TESTER !!!!!!!!!!!!!!!!!!!!!!!! et a finir
ListeInsectes cycledeFaim(ListeInsectes listeInsectes, Ruche ruche){
    if(is_empty_list(listeInsectes)){
        return new_list();
    }
    else{
        while(listeInsectes != NULL){
            if(ruche.reserveMiel >= 0 && ruche.reserveEau >= 0 && listeInsectes->type == TYPE_OUVRIERE){
                listeInsectes->faim = false;
                ruche.reserveMiel -= 1;
                ruche.reserveEau -= 1;
            }
            else if(ruche.reserveMiel >= 0 && ruche.reserveEau >= 0 && listeInsectes->type == TYPE_FAUX_BOURDON){
                listeInsectes->faim = false;
                ruche.reserveMiel -= 1;
                ruche.reserveEau -= 1;
            }
            else if(ruche.reserveGeleeRoyale >= 0 && ruche.reserveGeleeRoyale >= 0 && listeInsectes->type == TYPE_REINE){
                listeInsectes->faim = false;
                ruche.reserveGeleeRoyale -= 1;
                ruche.reserveEau -= 1;
            }  
            else if(listeInsectes->type == TYPE_OURSE || listeInsectes->type == TYPE_GUEPE){
                //implementer nourriture ou non des ourse/guepe ? rand nourriture trouver => agressivité  => rand ruche trouvé => attaque ruche
            }
            else{
                listeInsectes->faim = true;
                listeInsectes->sante -= 25;

            }
            listeInsectes = listeInsectes->next ;
        }
        return listeInsectes;
    }
}


ListeInsectes tourDeSimulation(ListeInsectes listeInsectes, Saisons saison, Ruche ruche){
    if(is_empty_list(listeInsectes)){
        return new_list();
    }
    else{
        while(listeInsectes != NULL){
            if(listeInsectes->type == TYPE_REINE){
                if(saison == PRINTEMPS || saison == ETE){
                    listeInsectes->data.reine.ponteJournaliere = true;    
                    GENERATION_push_front_list(listeInsectes, TYPE_OUVRIERE, OEUF, 0, SANTE_MAX, false);

                }
                listeInsectes->age += 1;
                
                // if(listeInsectes->data.reine.emmet_feromones){
                //     //emission de feromones
                // }
            }
            if(listeInsectes->type == TYPE_OUVRIERE){
                switch(listeInsectes->data.ouvriere.role){
                    case LARVE:
                        //tavail nettoyeuse
                        break;
                    case NETTOYEUSE:
                        //tavail nourrice
                        break;
                    case NOURRICE:
                        //tavail magasiniere
                        break;
                    case MAGASINIERE:
                        //tavail cireuse
                        break;
                    case CIRIERE:
                        //tavail ventileuse
                        break;
                    case VENTILEUSE:
                        //tavail gardienne
                        break;
                    case GARDIENNE:
                        //tavail butineuse
                        break;
                    case BUTINEUSE:
                        //tavail butineuse
                        break;
                }
            }
            if(listeInsectes->type == TYPE_FAUX_BOURDON){
                // if(listeInsectes->data.FauxBourdon.feromones){
                //     //emission de feromones
                // }
                if(listeInsectes->data.FauxBourdon.enQueteReine){
                    //en quete de reine
                }
            }
            listeInsectes = listeInsectes->next ;
            
       
        }
        return listeInsectes;
    }
}



int main(){
    srand(time(NULL));
    ListeInsectes maRuche = new_list();
    
    print_list(maRuche);
    maRuche = initialisationEssaim(maRuche, 100);
    print_list(maRuche);
    printf("Taille de la liste: %d\n", list_length(maRuche));
    
    maRuche = clear_list(maRuche);
    print_list(maRuche);

    
}

