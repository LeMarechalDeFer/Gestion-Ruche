// #ifndef __ABEILLE__H__
// #define __ABEILLE__H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


// Constantes pour la reine
#define DUREE_VIE_MAX_REINE 1825 // 5 ans en jours
#define PONTE_MAX_JOUR 2000 // Nombre maximal d'œufs pondus par jour par la reine

// Constantes pour les ouvrières et faux bourdons
#define DUREE_VIE_MAX_OUVRIERE_ETE 45 // Durée de vie maximale en été en jours
#define DUREE_VIE_MAX_OUVRIERE_HIVER 140 // Durée de vie maximale en hiver en jours
#define DUREE_VIE_MAX_FAUX_BOURDON 90 // Durée de vie maximale en jours



// Constantes pour les statistiques de la ruche
#define NOMBRE_MAX_SORTIES_JOUR 10000 // Nombre maximal de sorties d'abeilles par jour

// Autres constantes utiles
#define NOMBRE_MAX_OUVRIERES 60000 // Nombre maximal d'ouvrières dans la ruche
#define NOMBRE_MAX_FAUX_BOURDONS 2000 // Nombre maximal de faux bourdons

typedef struct Reine {
    int age; // Age en jours
    int dureeVieMax; // Durée de vie maximale en jours
    int ponte; // Nombre d'oeufs pondus depuis la naissance
    int ponteMax; // Nombre d'oeufs pondus par jour
    int sante; //  Champ pour la santé
    int pheromones; // Niveau de phéromones, affecte le comportement des ouvrières
} Reine;


typedef struct Ouvriere {
    int age; // Age en jours
    int dureeVieMax; // Durée de vie maximale en jours
    int sante; // Champ pour la santé
    int efficacite; // Peut-être influencée par l'expérience
    int experience; // Champ pour l'expérience acquise
    RoleOuvriere role;
} Ouvriere;


typedef struct FauxBourdon {
    int age; // Age en jours
    int dureeVieMax; // Durée de vie maximale en jours
    int enQueteReine; // Indique s'il est en quête de reproduction
} FauxBourdon;

typedef enum RoleOuvriere {
    NETTOYEUSE,
    NOURRICE,
    MAGASINIERE,
    CIRIERE,
    VENTILEUSE,
    GARDIENNE,
    BUTINEUSE
} RoleOuvriere;


// #endif