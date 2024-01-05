// #include "abeille.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define ID_MAX 10000

#define NOMBRE_ABEILLES_MAX 60000
#define PONTE_OUVRIERE_JOUR 2000
#define PONTE_FAUX_BOURDON_JOUR 50

#define TEMPS_OEUF_REINE_J 3
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

const char* SaisonsStrings[] = {
    "PRINTEMPS", "ETE", "AUTOMNE", "HIVER"
};
typedef struct Ruche {
    float temperature;
    float salete;
    float sante;

    unsigned int reserveMiel;
    unsigned int reserveEau;
    unsigned int reservePollen;
    unsigned int reserveGeleeRoyale;

    unsigned int nombreOuvrieres;
    unsigned int nombreFauxBourdon;
    
} Ruche, *RuchePtr;


//on utilisera CycleCroissanceAbeilles ADULTE pour les predateurs/nuisibles à leur génération
typedef	enum CycleCroissanceAbeilles{
    OEUF,
    LARVE,
    PUPAISON,
    ADULTE
} CycleCroissanceAbeilles ;

const char *CycleCroissanceAbeillesStrings[] = {
    "OEUF", "LARVE", "PUPAISON", "ADULTE"
};
typedef enum RoleOuvriere {
    AUCUN,
    NETTOYEUSE,
    NOURRICE,
    MAGASINIERE,
    CIRIERE,            
    VENTILEUSE,
    GARDIENNE,
    BUTINEUSE
} RoleOuvriere;

const char* RoleOuvriereStrings[] = {
    "AUCUN", "NETTOYEUSE", "NOURRICE", "MAGASINIERE", "CIRIERE", "VENTILEUSE", "GARDIENNE", "BUTINEUSE"
};

// typedef enum Pheromones {
//     INCITATRICE,
//     MODIFICATRICE
// } Pheromones;


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
    CycleCroissanceAbeilles cycleCroissanceAbeilles;
    TypeInsecte type; 
    union {
        Reine reine;
        Ouvriere ouvriere;
        FauxBourdon FauxBourdon;
    } data;
    struct Insecte *next;
    struct Insecte *previous;
} Insecte, *ListeInsectes;

ListeInsectes new_list(void);
bool is_empty_list(ListeInsectes listeInsectes);
int list_length(ListeInsectes listeInsectes);
void print_list(ListeInsectes listeInsectes);
ListeInsectes GENERATION_push_front_list(ListeInsectes listeInsectes, 
                                        TypeInsecte type, 
                                        RoleOuvriere role,
                                        CycleCroissanceAbeilles cycleCroissance,
                                        unsigned int age, 
                                        unsigned int sante, 
                                        bool faim);
ListeInsectes initialisationEssaim(ListeInsectes listeInsectes, unsigned int nbOuvrieres) ;
ListeInsectes pop_front_list(ListeInsectes listeInsectes);

ListeInsectes clear_list(ListeInsectes listeInsectes);


ListeInsectes cycleCroissance(ListeInsectes listeInsectes);
Saisons cycleSaison(unsigned int *jourNumero);

ListeInsectes actionOuvriere (ListeInsectes listeInsectes, RuchePtr ruche);
ListeInsectes actionReine(ListeInsectes listeInsectes, Saisons saison);
ListeInsectes cycledeMort(ListeInsectes listeInsectes, Saisons saisons);
ListeInsectes cycledeFaim(ListeInsectes listeInsectes, RuchePtr ruche);



ListeInsectes tourDeSimulation(ListeInsectes listeInsectes, 
                                RuchePtr ruche,
                                unsigned int *jourNumero
                                );

/*
- Cycle de vie : naissance croissance mort 
- Cycle des saisons : Printemps Ete Automne Hiver
- Activité journaliere de reine: 
    - ponte larves
    - auto-gestion/intelligence collective de la colonie 
- Activité journaliere des ouvrieres avec ces sous categories 
- Activité journaliere faux bourdons (hiver expulse, ete en quete de reine)
- Ruche
- Temperature
- Prédateurs/ Nuisibles
*/



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
            printf("ID: %u, Age: %u, Croissance : %s ,Sante: %u, Faim: %s, ", 
                    listeInsectes->id,
                    listeInsectes->age, 
                    CycleCroissanceAbeillesStrings[listeInsectes->cycleCroissanceAbeilles],
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
    printf("\n\n");
}


ListeInsectes GENERATION_push_front_list(ListeInsectes listeInsectes, 
                                        TypeInsecte type, 
                                        RoleOuvriere role,
                                        CycleCroissanceAbeilles cycleCroissance,
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
    nouvelInsecte->cycleCroissanceAbeilles = cycleCroissance;
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



// Valeur d'initialisation realiste d'une ruche pour n individus (+1 pour la reine) 
ListeInsectes initialisationEssaim(ListeInsectes listeInsectes, unsigned int nbAbeilles) {
    unsigned int i;
    unsigned int nbLarves = (nbAbeilles * 20) / 100; // 20%
    unsigned int nbNettoyeuses = (nbAbeilles * 5) / 100; // 5%
    unsigned int nbNourrices = (nbAbeilles * 15) / 100; // 15%
    unsigned int nbMagasinieres = (nbAbeilles * 10) / 100; // 10%
    unsigned int nbCirieres = (nbAbeilles * 7) / 100; // 7%
    unsigned int nbVentileuses = (nbAbeilles * 5) / 100; // 5%
    unsigned int nbGardiennes = (nbAbeilles * 5) / 100; // 5%
    unsigned int nbButineuses = (nbAbeilles * 30) / 100; // 30%
    unsigned int nbFauxBourdon = (nbAbeilles * 3) / 100; // 3%

    listeInsectes = GENERATION_push_front_list(listeInsectes, TYPE_REINE, AUCUN, ADULTE, 8, SANTE_MAX, false);
    
    for(i = 0; i < nbLarves; i++) {
        listeInsectes = GENERATION_push_front_list(listeInsectes, TYPE_OUVRIERE, AUCUN, LARVE, 0, SANTE_MAX, false);
    }
    for(i = 0; i < nbNettoyeuses; i++) {
        listeInsectes = GENERATION_push_front_list(listeInsectes, TYPE_OUVRIERE, NETTOYEUSE, ADULTE, 100, SANTE_MAX, false);
    }
    for(i = 0; i < nbNourrices; i++) {
        listeInsectes = GENERATION_push_front_list(listeInsectes, TYPE_OUVRIERE, NOURRICE, ADULTE, 13, SANTE_MAX, false);
    }
    for(i = 0; i < nbMagasinieres; i++) {
        listeInsectes = GENERATION_push_front_list(listeInsectes, TYPE_OUVRIERE, MAGASINIERE, ADULTE, 13, SANTE_MAX, false);
    }
    for(i = 0; i < nbCirieres; i++) {
        listeInsectes = GENERATION_push_front_list(listeInsectes, TYPE_OUVRIERE, CIRIERE, ADULTE, 13, SANTE_MAX, false);
    }
    for(i = 0; i < nbVentileuses; i++) {
        listeInsectes = GENERATION_push_front_list(listeInsectes, TYPE_OUVRIERE, VENTILEUSE, ADULTE, 13, SANTE_MAX, false);
    }
    for(i = 0; i < nbGardiennes; i++) {
        listeInsectes = GENERATION_push_front_list(listeInsectes, TYPE_OUVRIERE, GARDIENNE, ADULTE, 13, SANTE_MAX, false);
    }
    for(i = 0; i < nbButineuses; i++) {
        listeInsectes = GENERATION_push_front_list(listeInsectes, TYPE_OUVRIERE, BUTINEUSE, ADULTE, 13, SANTE_MAX, false);
    }

    for(i=0; i< nbFauxBourdon; i++ ){
        listeInsectes = GENERATION_push_front_list(listeInsectes, TYPE_FAUX_BOURDON, AUCUN, ADULTE, 13, SANTE_MAX, false);
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


ListeInsectes cycleCroissance(ListeInsectes listeInsectes){
    listeInsectes->age += 1;
    if(listeInsectes->type == TYPE_OUVRIERE){
        if(listeInsectes->age >= TEMPS_OEUF_OUVRIERE_J){
            listeInsectes->cycleCroissanceAbeilles = LARVE;
        }
        if(listeInsectes->age >= TEMPS_LARVE_OUVRIERE_J){
            listeInsectes->cycleCroissanceAbeilles = PUPAISON;
        }
        if(listeInsectes->age >= TEMPS_PUPAISON_OUVRIERE_J){
            listeInsectes->cycleCroissanceAbeilles = ADULTE;
        }
    }
    if(listeInsectes->type == TYPE_FAUX_BOURDON){
        if(listeInsectes->age >= TEMPS_OEUF_FAUX_BOURDON_J){
            listeInsectes->cycleCroissanceAbeilles = LARVE;
        } 
        if(listeInsectes->age >= TEMPS_LARVE_FAUX_BOURDON_J){
            listeInsectes->cycleCroissanceAbeilles = PUPAISON;
        }
        if(listeInsectes->age >= TEMPS_PUPAISON_FAUX_BOURDON_J){
            listeInsectes->cycleCroissanceAbeilles = ADULTE;
        }
    }
    if(listeInsectes->type == TYPE_REINE){
        if(listeInsectes->age >= TEMPS_OEUF_REINE_J){
            listeInsectes->cycleCroissanceAbeilles = LARVE;
        } 
        if(listeInsectes->age >= TEMPS_LARVE_REINE_J){
            listeInsectes->cycleCroissanceAbeilles = PUPAISON;
        }
        if(listeInsectes->age >= TEMPS_PUPAISON_REINE_J){
            listeInsectes->cycleCroissanceAbeilles = ADULTE;
        }
    }
    return listeInsectes;
}



// On assume un depart au debut printemps pour un maximum de ponte et de reserver de nourriture
Saisons cycleSaison(unsigned int *jourNumero){
    *jourNumero += 1;
    if(*jourNumero >= 1 && *jourNumero <= 90){
        return PRINTEMPS;
    }
    else if(*jourNumero >= 91 && *jourNumero <= 180){
        return ETE;
    }
    else if(*jourNumero >= 181 && *jourNumero <= 270){
        return AUTOMNE;
    }
    else if(*jourNumero >= 271 && *jourNumero <= 365){
        return HIVER;
    }
    else{
        return PRINTEMPS;
    }
}

float generationJouraliereTemperature(Saisons SaisonActuelle) {

    srand(time(NULL));
    
    float temperature;
    
    switch(SaisonActuelle) {
        case PRINTEMPS:
            temperature = (rand() % 15) + 10; // 10-25 degrees Celsius
            break;
        case ETE:
            temperature = (rand() % 15) + 25; // 25-40 degrees Celsius
            break;
        case AUTOMNE:
            temperature = (rand() % 15) + 10; // 10-25 degrees Celsius
            break;
        case HIVER:
            temperature = (rand() % 20) - 5;  // -5-15 degrees Celsius
            break;
        default:
            temperature = 20; 
    }
    
    return temperature;
}


// A TESTER !!
ListeInsectes cycledeMort(ListeInsectes listeInsectes, Saisons saisons){

    if(listeInsectes->type == TYPE_REINE){
        if(listeInsectes->age >= DUREE_VIE_MAX_REINE_J){
            listeInsectes = pop_front_list(listeInsectes);
        }
    }
    if(listeInsectes->type == TYPE_OUVRIERE){
        if((listeInsectes->age >= DUREE_VIE_MAX_OUVRIERE_ETE_J && (saisons == ETE || saisons == PRINTEMPS)) 
            || (listeInsectes->age >= DUREE_VIE_MAX_OUVRIERE_HIVER_J && (saisons == HIVER || saisons == AUTOMNE))){
            listeInsectes = pop_front_list(listeInsectes);
        }
    }
    if(listeInsectes->type == TYPE_FAUX_BOURDON){
        if(listeInsectes->age >= DUREE_VIE_MAX_FAUX_BOURDON_J){
            listeInsectes = pop_front_list(listeInsectes);
        }
    }
    return listeInsectes;
}


ListeInsectes cycledeFaim(ListeInsectes listeInsectes, RuchePtr ruche){
    if(ruche->reserveMiel > 0 && ruche->reserveEau > 0 && listeInsectes->type == TYPE_OUVRIERE){
        listeInsectes->faim = false;
        ruche->reserveMiel -= 1;
        ruche->reserveEau -= 1;
    }
    else if(ruche->reserveMiel > 0 && ruche->reserveEau > 0 && listeInsectes->type == TYPE_FAUX_BOURDON){
        listeInsectes->faim = false;
        ruche->reserveMiel -= 1;
        ruche->reserveEau -= 1;
    }
    else if(ruche->reserveGeleeRoyale > 0 && ruche->reserveGeleeRoyale > 0 && listeInsectes->type == TYPE_REINE){
        listeInsectes->faim = false;
        ruche->reserveGeleeRoyale -= 1;
        ruche->reserveEau -= 1;
    }  
    else if(listeInsectes->type == TYPE_OURSE || listeInsectes->type == TYPE_GUEPE){
        //implementer nourriture ou non des ourse/guepe ? rand nourriture trouver => agressivité  => rand ruche trouvé => attaque ruche
    }
    else{
        listeInsectes->faim = true;
        listeInsectes->sante -= 25;

    }
    return listeInsectes;
}

ListeInsectes actionReine(ListeInsectes listeInsectes, Saisons saison){
    
    if(listeInsectes->type == TYPE_REINE){
        printf("Reine\n");
        if(saison == PRINTEMPS || saison == ETE){
            
            int i;
            listeInsectes->data.reine.ponteJournaliere = true;
            for(i=0; i<PONTE_OUVRIERE_JOUR; i++){
                
                listeInsectes = GENERATION_push_front_list(listeInsectes, TYPE_OUVRIERE, AUCUN, OEUF, 0, SANTE_MAX, false);
            }
            for(i=0; i<PONTE_FAUX_BOURDON_JOUR; i++){
                listeInsectes = GENERATION_push_front_list(listeInsectes, TYPE_FAUX_BOURDON, AUCUN, OEUF, 0, SANTE_MAX, false);
            }
        }
        else{
            listeInsectes->data.reine.ponteJournaliere = false;
        } 
    }

    return listeInsectes;
}

RuchePtr evenementJouraniler(RuchePtr ruche){
    ruche->salete += 1;
    ruche->sante -= 1;

    return ruche;
}


ListeInsectes actionOuvriere (ListeInsectes listeInsectes, RuchePtr ruche){

    if(listeInsectes->type == TYPE_OUVRIERE){
        switch(listeInsectes->data.ouvriere.role){
            case AUCUN:
                break;
            case NETTOYEUSE:
                
                break;
            case NOURRICE:
                
                break;
            case MAGASINIERE:
                
                break;
            case CIRIERE:
                
                break;
            case VENTILEUSE:
               
                break;
            case GARDIENNE:
                
                break;
            case BUTINEUSE:
                
                break;
        }
    }
    return listeInsectes;
}

ListeInsectes tourDeSimulation(ListeInsectes listeInsectes, 
                                RuchePtr ruche,
                                unsigned int *jourNumero
                                ){
    if(is_empty_list(listeInsectes)){
        return new_list();
    }
    else{
        printf("Jour numéro: %u\n", *jourNumero);
        Saisons saison = cycleSaison(jourNumero); 
        printf("Saison: %s\n", SaisonsStrings[saison]);
        printf("Jour numéro: %u\n", *jourNumero);
        
        ruche->temperature = generationJouraliereTemperature(saison);
        printf("Temperature: %f\n", ruche->temperature);

        ruche = evenementJouraniler(ruche);
        
        ListeInsectes insecteActuel = listeInsectes;
        ListeInsectes prev = NULL;
        while(insecteActuel != NULL){

            insecteActuel = cycleCroissance(insecteActuel);
            insecteActuel = cycledeFaim(insecteActuel, ruche);
                
            //insecteActuel = actionReine(listeInsectes, saison); 
            
            // //insecteActuel= actionFauxBourdon(insecteActuel, saison);
            // insecteActuel = actionOuvriere(insecteActuel, ruche);

            //insecteActuel = cycledeMort(insecteActuel, saison);

            insecteActuel = insecteActuel->next;
        
        }
        return listeInsectes;
    }
            
}

//initialisation de la ruche
RuchePtr initialisationRuche(){
    RuchePtr ruche = malloc(sizeof(Ruche));
    if(ruche == NULL){
        perror("Erreur allocation mémoire\n");
        exit(EXIT_FAILURE);
    }
    ruche->temperature = 20;
    ruche->sante = SANTE_RUCHE_MAX;
    ruche->salete = 0;
    ruche->reserveMiel = 0;
    ruche->reserveEau = 0;
    ruche->reservePollen = 0;
    ruche->reserveGeleeRoyale = 0;
    ruche->nombreOuvrieres = 0;
    ruche->nombreFauxBourdon = 0;
    return ruche;
}



int main(){
    srand(time(NULL));
    unsigned int *jourNumero = malloc(sizeof(unsigned int));
    *jourNumero = 0;

    RuchePtr maRuche = initialisationRuche();
    ListeInsectes mesInsectes = new_list();
    print_list(mesInsectes);

    mesInsectes = initialisationEssaim(mesInsectes, 50);
    maRuche = initialisationRuche(maRuche);
    print_list(mesInsectes);
    printf("Taille de la liste: %u\n", list_length(mesInsectes));

    mesInsectes = tourDeSimulation(mesInsectes, maRuche, jourNumero);
    
    print_list(mesInsectes);

    mesInsectes = clear_list(mesInsectes);  
    print_list(mesInsectes);

    free(jourNumero);

    
}

