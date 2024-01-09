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

#define SANTE_MAX 100 
#define SANTE_MIN 0
#define COHESION_MAX 100
#define COHESION_MIN 0

#define EFFICACITE_MAX 100
#define EFFICACITE_MIN 0
#define EFFICACITER_PAR_DEFAUT 50


#define CAPACITE_MAX_POLLEN_G 500 
#define CAPACITE_MAX_MIEL_g 1000 
#define CAPACITE_MAX_GELEE_ROYALE_G 100 
#define CAPACITE_MAX_EAU_ML 250 

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
    bool emmet_feromones; 
     
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


bool cycledeMort(ListeInsectes insecte);

ListeInsectes actionReine(ListeInsectes listeInsectes, bool reine_Va_Pondre);

ListeInsectes cycledeFaim(ListeInsectes listeInsectes, RuchePtr ruche);



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