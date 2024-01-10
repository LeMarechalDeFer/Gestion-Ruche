#ifndef __RUCHE_H__
#define __RUCHE_H__

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

#define AGE_NETTOYEUSE_J 15
#define AGE_NOURRICE_J 18
#define AGE_MAGASINIERE_J 23
#define AGE_CIRIERE_J 25
#define AGE_VENTILEUSE_J 28
#define AGE_GARDIENNE_J 33
#define AGE_BUTINEUSE_J 38


#define SANTE_MAX 100 
#define SANTE_MIN 0
#define COHESION_MAX 100
#define COHESION_MIN 0

//non implémenté
#define EFFICACITE_MAX 100
#define EFFICACITE_MIN 0
#define EFFICACITER_PAR_DEFAUT 50

// Les capacités sont arbitraires et peuvent être modifiées à votre gise !!! Des valeurs plus réalistes sont les bienvenues
// Des valeurs plus faible peuvent être mise pour des tests de mort de la ruche

#define CAPACITE_MAX_POLLEN_G 5000 
#define CAPACITE_MAX_MIEL_g 10000000 
#define CAPACITE_MAX_GELEE_ROYALE_G 1000 
#define CAPACITE_MAX_EAU_ML 100000000 

#define CAPACITE_INITIALE_POLLEN_G 1000
#define CAPACITE_INITIALE_MIEL_g 10000000
#define CAPACITE_INITIALE_GELEE_ROYALE_G 100
#define CAPACITE_INITIALE_EAU_ML 10000000


#define RECOLTE_POLLEN_J 100
#define RECOLTE_EAU_J 100

#define TRANSFORMATION_POLLEN_UTILISE_J 100
#define TRANSFORMATION_POLLEN_EN_MIEL_J 100
#define TRANSFORMATION_POLLEN_EN_GELEE_ROYAL_J 100

#define CONSOMMATION_EAU_J 1
#define CONSOMMATION_MIEL_J 1
#define CONSOMMATION_GELEE_ROYALE_J 1

#define NOMBRE_MAX_OUVRIERES 60000 
#define NOMBRE_MAX_FAUX_BOURDONS 2000 

#define TEMPERATURE_IDEAL 35 
#define TEMPERATURE_MIN -30
#define TEMPERATURE_MAX 37
#define TEMPERATURE_VENTILATION 0.5

#define USURE_JOURNALIERE_RUCHE 1
#define SANTE_RUCHE_MAX 500
#define SANTE_RUCHE_MIN 0 
#define SANTE_RUCHE_REPARATION 1000

#define SALETE_JOURNALIERE_RUCHE 1
#define SALETE_MAX 1000
#define SALETE_MIN 0
#define SALETE_NETTOYAGE 1000

typedef enum Saisons {
    PRINTEMPS,
    ETE,
    AUTOMNE,
    HIVER
} Saisons;


typedef struct Ruche {
    float temperature;
    int salete;
    unsigned int sante;

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
    int spermatheque;
     
} Reine;

typedef struct Ouvriere{
    bool cohesion;
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


ListeInsectes clear_list(ListeInsectes listeInsectes);


ListeInsectes cycleCroissance(ListeInsectes listeInsectes);
Saisons cycleSaison(unsigned int *jourNumero);

ListeInsectes actionOuvriere (ListeInsectes listeInsectes, RuchePtr ruche);


//ListeInsectes cycledeMort(ListeInsectes insecteActuel, ListeInsectes listeInsectes);
bool cycledeMort(ListeInsectes insecte, Saisons Saison);

ListeInsectes actionReine(ListeInsectes listeInsectes, bool reine_Va_Pondre);

ListeInsectes cycledeFaim(ListeInsectes listeInsectes, RuchePtr ruche);

void delay(int secondes) ;

RuchePtr initialisationRuche();

ListeInsectes tourDeSimulation(ListeInsectes listeInsectes, 
                                RuchePtr ruche,
                                unsigned int *jourNumero
                                );
ListeInsectes Kill_Abeille(ListeInsectes listeInsectes, unsigned int ID);

int list_length_type(ListeInsectes listeInsectes, TypeInsecte type);
RuchePtr capaciteMaxRuche(RuchePtr ruche);                              
ListeInsectes competenceMaxAbeille(ListeInsectes listeInsectes);
ListeInsectes pop_specific_type(ListeInsectes liste, TypeInsecte type) ;
ListeInsectes nombreMaxAbeille(ListeInsectes listeInsectes) ;
RuchePtr evenementJouranilerRuche(RuchePtr ruche);
ListeInsectes pop_front_list(ListeInsectes listeInsectes);

bool reineVaPondre(Saisons saison, ListeInsectes listeInsectes);
bool parcoursListeTrouverReine(ListeInsectes listeInsectes);
ListeInsectes actionFauxBourdon(ListeInsectes listeInsectes, Saisons saison);
void affichageTour(ListeInsectes listeInsectes, 
                    RuchePtr ruche, 
                    unsigned int *jourNumero, 
                    unsigned int nombreNaissance, 
                    unsigned int nombreMort, 
                    Saisons saison,
                    float temperatureJournee);
unsigned int nombreMortJ(unsigned int tailleListe, unsigned int tailleListeAfter);
unsigned int nombreNaissanceJ(bool reine_Va_Pondre);
bool conditionMortRuche(RuchePtr ruche, ListeInsectes listeInsectes);
ListeInsectes attributionRoleOuvriere(ListeInsectes listeInsectes);
/*
- Cycle de vie : naissance croissance mort 
- Cycle des saisons : Printemps Ete Automne Hiver
- Activité journaliere de reine: 
    - ponte larves
    - auto-gestion/intelligence collective de la colonie 
- Activité journaliere des ouvrieres avec ces sous categoriccccces 
- Activité journaliere faux bourdons (hiver expulse, ete en quete de reine)
- Ruche
- Temperature   
- Prédateurs/ Nuisibles
*/

#endif