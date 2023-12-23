#ifndef __RUCHE__H__
#define __RUCHE__H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Constantes pour la cellule de couvain
#define CAPACITE_MAX_OEUFS_CELLULE 10 // Capacité maximale d'œufs par cellule de couvain
#define CAPACITE_MAX_LARVES_CELLULE 10
#define CAPACITE_MAX_NYMPHES_CELLULE 10

// Constantes pour la cellule de stockage
#define CAPACITE_MAX_POLLEN_CELLULE 500 // En grammes
#define CAPACITE_MAX_MIEL_CELLULE 1000 // En grammes
#define CAPACITE_MAX_GELEE_ROYALE_CELLULE 100 // En grammes
#define CAPACITE_MAX_EAU_CELLULE 250 // En millilitres

// Constantes pour les besoins de la ruche
#define HUMIDITE_IDEAL 80 // Pourcentage d'humidité idéale
#define TEMPERATURE_IDEAL 35 // Température idéale en degrés Celsius


typedef struct Ruche {
    Reine* reine; // Pointeur vers la reine
    Ouvriere* ouvrieres; // Pointer vers un tableau ou une liste chaînée
    FauxBourdon* faux_bourdons; // Pointer vers un tableau ou une liste chaînée
    CelluleCouvain* cellulesCouvain; // Ajout de la structure des cellules de couvain
    CelluleStockage* cellulesStockage; // Ajout de la structure des cellules de stockage
    BesoinsRuche besoins; // Besoins en humidité et température
    EntreeRuche entree; // Nombre d'abeilles entrant et sortant
    SystemeVentilation ventilation; // Nombre d'abeilles ventilant la ruche
    ZoneRepos repos; // Nombre d'abeilles pouvant se reposer
    Statistiques stats; // Statistiques sur la ruche

} Ruche;

typedef struct CelluleCouvain {
    int oeufs; // Nombre d'œufs
    int larves; // Nombre de larves
    int nymphes; // Nombre de nymphes
    int nombreOeufsTotal; // Nombre total d'œufs pondus

} CelluleCouvain;

typedef struct CelluleStockage {
    int capaciteNourritureTotal; // Capacité de stockage de la ruche
    int capacitePollen; // Capacité de stockage du pollen
    int capaciteMiel; // Capacité de stockage du miel
    int capaciteGeléeRoyale; // Capacité de stockage de la gelée royale
    int capaciteEau; // Capacité de stockage de l'eau
    int pollenActuel; // Quantité de pollen stockée
    int mielActuel; // Quantité de miel stockée
    int geléeRoyaleActuelle; // Quantité de gelée royale stockée
    int eauActuel; // Quantité d'eau stockée

} CelluleStockage;

typedef struct BesoinsRuche {
    float humidite; // Pourcentage d'humidité
    float temperature; // Température en degrés Celsius
    float tauxRenouvellementAir; // Taux de renouvellement de l'air
    float humiditeSeuil; // Seuil d'humidité à ne pas dépasser
    float temperatureSeuil; // Seuil de température à ne pas dépasser

} BesoinsRuche;

typedef struct EntreeRuche {
    int garde; // Nombre d'abeilles gardiennes
    float fluxAbeilles; // Taux de sortie et d'entrée des abeilles
    int nombreAbeillesSorties; // Statistiques sur les sorties des butineuses
} EntreeRuche;

typedef struct SystemeVentilation {
    int ventilateurs; // Nombre d'abeilles ventilatrices
    float efficaciteVentilation; // Efficacité de la ventilation (influence l'humidité et la température)
} SystemeVentilation;

typedef struct ZoneRepos {
    int capaciteRepos; // Nombre d'abeilles pouvant se reposer en même temps
    int abeillesRepos; // Nombre d'abeilles se reposant actuellement
} ZoneRepos;

typedef struct Statistiques {
    int nombreOeufsPondus; // Nombre total d'œufs pondus
    int nombreAbeillesSorties; // Nombre total d'abeilles sorties
    int nombreAbeillesMortes; // Nombre total d'abeilles mortes
    int nombreAbeillesNees; // Nombre total d'abeilles nées
    int nombreAbeillesButineuses; // Nombre total d'abeilles butineuses
    int nombreAbeillesGardiennes; // Nombre total d'abeilles gardiennes
    int nombreAbeillesVentilatrices; // Nombre total d'abeilles ventilatrices
    int nombreAbeillesCirieres; // Nombre total d'abeilles cirieres
    int nombreAbeillesNourrices; // Nombre total d'abeilles nourrices
    int nombreAbeillesNettoyeuses; // Nombre total d'abeilles nettoyeuses
    int nombreAbeillesMagasiniere; // Nombre total d'abeilles magasiniere
    int nombreAbeillesFauxBourdons; // Nombre total de faux bourdons

    int niveauMenace; // Indicateur de menaces potentielles (prédateurs, maladies)
    int niveauSanteGlobale; // Santé globale de la ruche
    
} Statistiques;


#endif