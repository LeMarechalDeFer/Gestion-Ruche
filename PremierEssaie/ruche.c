#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define TABLE_HACHAGE_TAILLE 1000

#define NOMBRE_ABEILLES_MAX 60000
#define PONTE_MAX_JOUR 3000


#define TEMPS_INCUBATION_REINE_J 3
#define TEMPS_LARVE_REINE_J 6
#define TEMPS_PUPAISON_REINE_J 7
//sort de sa cellule à 16 jours
#define DUREE_VIE_MAX_REINE_J 1460

#define TEMPS_OEUF_OUVRIERE_J 3
#define TEMPS_LARVE_OUVRIERE_J 6
#define TEMPS_PUPAISON_OUVRIERE_J 12
//sort de sa cellule à 21 jours
#define DUREE_VIE_MAX_OUVRIERE_ETE_J 45
#define DUREE_VIE_MAX_OUVRIERE_HIVER_J 140

#define DUREE_VIE_MAX_FAUX_BOURDON_J 60
#define TEMPS_OEUF_FAUX_BOURDON_J 3
#define TEMPS_LARVE_FAUX_BOURDON_J 6
#define TEMPS_PUPAISON_FAUX_BOURDON_J 12

#define SANTE_MAX 100
#define SANTE_MIN 0


typedef enum Pheromones {
    INCITATRICE,
    MODIFICATRICE
} Pheromones;


typedef struct Reine {
    unsigned int age; 
    unsigned int ponteJournaliere; 
    unsigned int sante; 
    unsigned int cohésion;
    bool emet_feromones;
    bool faim;
} Reine;



typedef enum RoleOuvriere {
    NETTOYEUSE,
    NOURRICE,
    MAGASINIERE,
    CIRIERE,
    VENTILEUSE,
    GARDIENNE,
    BUTINEUSE
} RoleOuvriere;

typedef struct Ouvriere {
    unsigned int age; 
    unsigned int sante; 
    unsigned int cohésion;
    bool touche_par_feromones;
    bool faim;
    unsigned int efficacite; 
    unsigned int experience; 
    RoleOuvriere role;
} Ouvriere ;


typedef struct FauxBourdon {
    unsigned int age;
    unsigned int sante;
    unsigned int cohésion;
    bool feromones;
    bool faim;
    bool enQueteReine;
} FauxBourdon;


typedef struct Noeud {
    void* donnee; 
    struct Noeud *suivant;
    struct Noeud *precedent;
} Noeud;

typedef struct EntreeTableHachage {
    int cle;   
    Noeud* noeud;
} EntreeTableHachage;

EntreeTableHachage tableHachage[TABLE_HACHAGE_TAILLE]; 

void mettreAJourRole(Ouvriere* ouvriere) {
    if (ouvriere->age >= 1 && ouvriere->age <= 3) {
        ouvriere->role = NETTOYEUSE;
    } else if (ouvriere->age <= 9) {
        ouvriere->role = NOURRICE;
    } else if (ouvriere->age <= 12) {
        ouvriere->role = MAGASINIERE;
    } else if (ouvriere->age <= 18) {
        ouvriere->role = CIRIERE;
    } else if (ouvriere->age <= 21) {
        ouvriere->role = VENTILEUSE;
    } else if (ouvriere->age <= 25) {
        ouvriere->role = GARDIENNE;
    } else {
        ouvriere->role = BUTINEUSE;
    }
}


void ajouterEnTete(Noeud** tete, void* donnee) {
    Noeud* nouveauNoeud = (Noeud*)malloc(sizeof(Noeud));
    nouveauNoeud->donnee = donnee;
    nouveauNoeud->suivant = (*tete);
    nouveauNoeud->precedent = NULL;

    if ((*tete) != NULL) {
        (*tete)->precedent = nouveauNoeud;
    }

    *tete = nouveauNoeud;
}

void supprimerNoeud(Noeud** tete, Noeud* aSupprimer) {
    if (*tete == NULL || aSupprimer == NULL) return;

    if (*tete == aSupprimer) {
        *tete = aSupprimer->suivant;
    }

    if (aSupprimer->suivant != NULL) {
        aSupprimer->suivant->precedent = aSupprimer->precedent;
    }

    if (aSupprimer->precedent != NULL) {
        aSupprimer->precedent->suivant = aSupprimer->suivant;
    }

    free(aSupprimer);  
}

int fonctionHachage(int cle) {
    return cle % TABLE_HACHAGE_TAILLE;
}

void insererTableHachage(EntreeTableHachage* table, int cle, void* donnee) {
    int index = fonctionHachage(cle);
    ajouterEnTete(&(table[index].noeud), donnee);  
    table[index].cle = cle;  
}

Noeud* rechercherTableHachage(EntreeTableHachage* table, int cle) {
    int index = fonctionHachage(cle);
    Noeud* courant = table[index].noeud;
    while (courant != NULL) {
        
        // Ajouter des conditions de correspondance de clé ou de donnée ici si nécessaire
        if (table[index].cle == cle) {
            return courant;
        }

        courant = courant->suivant;
    }
    return NULL; 
}

int main(int argc, char **argv) {
    // Exemple d'initialisation des abeilles
    Reine* reine = malloc(sizeof(Reine));
    Ouvriere* ouvriere1 = malloc(sizeof(Ouvriere));
    FauxBourdon* fauxBourdon1 = malloc(sizeof(FauxBourdon));
    
    // Initialiser les attributs si nécessaire...
    reine->age = 0;  // et ainsi de suite pour les autres attributs

    // Insérer dans la table de hachage et la liste liée
    insererTableHachage(tableHachage, 1, reine);
    insererTableHachage(tableHachage, 2, ouvriere1);
    insererTableHachage(tableHachage, 3, fauxBourdon1);

    // Exemple de mise à jour de rôle
    ouvriere1->age = 5;  // Simuler un âge pour la mise à jour de rôle
    mettreAJourRole(ouvriere1);  // Mettre à jour le rôle de l'ouvrière

    // Supposons que vous voulez rechercher et supprimer un noeud spécifique
    Noeud* noeudTrouve = rechercherTableHachage(tableHachage, 2); // Recherche par clé, exemple avec clé = 2
    if (noeudTrouve != NULL) {
        supprimerNoeud(&(tableHachage[fonctionHachage(2)].noeud), noeudTrouve); // Supprime du noeud spécifique
    }

    // Nettoyage et fin du programme
    free(reine);       // Libérer la mémoire allouée pour la reine
    free(ouvriere1);   // Libérer la mémoire allouée pour l'ouvrière
    free(fauxBourdon1); // Libérer la mémoire pour le faux bourdon

    return 0;
}
