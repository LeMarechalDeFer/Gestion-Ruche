#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


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

typedef struct Ruche {
    Reine* reine; 
    Ouvriere* ouvrieres; 
    FauxBourdon* faux_bourdons;
    unsigned int nbOuvrieres; 
    unsigned int nbFauxBourdons; 
    // CelluleCouvain* cellulesCouvain;
    // CelluleStockage* cellulesStockage; 
    // BesoinsRuche besoins; 
    // EntreeRuche entree;
    // SystemeVentilation ventilation; 
    // ZoneRepos repos; 
    // Statistiques stats;

} Ruche;

typedef enum Pheromones {
    INCITATRICE,
    MODIFICATRICE
} Pheromones;


typedef struct Reine {
    unsigned int age; 
    unsigned int ponteJournaliere; 
    unsigned int sante; 
    unsigned int cohesion;
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
    unsigned int cohesion;
    bool touche_par_feromones;
    bool faim;
    unsigned int efficacite; 
    unsigned int experience; 
    RoleOuvriere role;
} Ouvriere ;


typedef struct FauxBourdon {
    unsigned int age;
    unsigned int sante;
    unsigned int cohesion;
    bool feromones;
    bool faim;
    bool enQueteReine;
} FauxBourdon;



void mettreAJourRole(Ouvriere* ouvriere, enum RoleOuvriere roleOuvriere) {
    if (ouvriere->age >= 1 && ouvriere->age <= 3) {
        ouvriere->role = roleOuvriere->NETTOYEUSE;
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



void initialisationRuche(Ruche* ruche, unsigned int nbOuvrieres, unsigned int nbFauxBourdons){
    int i ;
    ruche->reine = malloc(sizeof(Reine));
    if(ruche->reine == NULL){
        perror("Erreur allocation mémoire reine");
        exit(EXIT_FAILURE);
    }

    ruche->ouvrieres = malloc(sizeof(Ouvriere) * nbOuvrieres);
    if(ruche->ouvrieres == NULL){
        perror("Erreur allocation mémoire ouvrières");
        exit(EXIT_FAILURE);
    }
    ruche->faux_bourdons = malloc(sizeof(FauxBourdon) * nbFauxBourdons);
    if(ruche->faux_bourdons == NULL){
        perror("Erreur allocation mémoire faux bourdons");
        exit(EXIT_FAILURE);
    }
    
    ruche->nbOuvrieres = nbOuvrieres;
    ruche->nbFauxBourdons = nbFauxBourdons;

    for(i=0; i<nbOuvrieres; i++){
        Ouvriere* nouvelleOuvriere = malloc(sizeof(Ouvriere));
        if(nouvelleOuvriere == NULL){
            perror("Erreur allocation mémoire nouvelle ouvrière");
            exit(EXIT_FAILURE);
        }
        //initialisation des attributs ouvrieres
        nouvelleOuvriere->age = 13;
        nouvelleOuvriere->sante = SANTE_MAX;
        nouvelleOuvriere->cohesion = COHESION_MAX;
        nouvelleOuvriere->touche_par_feromones = true;
        nouvelleOuvriere->faim = false;
        nouvelleOuvriere->efficacite = EFFICACITER_PAR_DEFAUT;
        nouvelleOuvriere->experience = 0;
        nouvelleOuvriere->role = NULL;

        
    }
    for(i=0; i<nbFauxBourdons; i++){
        FauxBourdon* nouveauFauxBourdon = malloc(sizeof(FauxBourdon));
        if(nouveauFauxBourdon == NULL){
            perror("Erreur allocation mémoire nouveau faux bourdon");
            exit(EXIT_FAILURE);
        }
        //initialisation des attributs faux bourdons
    }
}


void fonctionnement_Ruche(Ruche* ruche, unsigned int nbOuvrieres, unsigned int nbFauxBourdons)
{
    
}


void effectuerTache(Ouvriere* ouvriere) {
    switch (ouvriere->role) {
        case NETTOYEUSE:
            // Code pour le nettoyage de la ruche
            // Par exemple, nettoyer les cellules, éjecter les déchets, etc.
            break;
        case NOURRICE:
            // Code pour nourrir les larves
            // Par exemple, préparer la gelée royale, nourrir la reine, etc.
            break;
        case MAGASINIERE:
            // Code pour gérer le stockage du pollen et du miel
            break;
        case CIRIERE:
            // Code pour la construction et la réparation de la ruche
            break;
        case VENTILEUSE:
            // Code pour la ventilation de la ruche
            break;
        case GARDIENNE:
            // Code pour la défense de la ruche
            break;
        case BUTINEUSE:
            // Code pour la collecte de nectar et de pollen
            break;
        default:
            // Comportement par défaut si nécessaire
            break;
    }
}

void miseAJourSanteEfficacite(Ouvriere* ouvriere) {
    // Ajoutez ici la logique pour ajuster santé et efficacité

    
}

//Relatif à la simulation de la ruche

void gererStockNourriture(Ruche* ruche) {
    // Logique pour gérer le stock de miel et de pollen
    // Peut-être influencé par les conditions environnementales et la santé de la ruche
}

void simulerEnvironnement(Ruche* ruche) {
    // Mise à jour des conditions environnementales
    // Peut influencer la disponibilité des ressources, la santé des abeilles, etc.
}

void gererEvenements(Ruche* ruche) 
{
    // Logique pour gérer des événements comme des attaques de prédateurs, des maladies, etc.
    // Ajuster le niveau de menace et prendre des mesures en conséquence
}

void evaluerSanteAbeilles(Ruche* ruche)
{
    // Évaluer la santé globale des abeilles
    // Prendre des mesures pour traiter les maladies ou améliorer les conditions
}



void simulationJour(Ruche* ruche) {
    for (int i = 0; i < NOMBRE_MAX_OUVRIERES; i++) 
    {
        Ouvriere* ouvriere = &(ruche->ouvrieres[i]);
        ouvriere->age++;
        miseAJourSanteEfficacite(&(ruche->ouvrieres[i]));
        mettreAJourRole(ouvriere);
        effectuerTache(ouvriere);
    }
    gererStockNourriture(ruche);
    simulerEnvironnement(ruche);
    gererEvenements(ruche);

}
void Mise_a_jour_journee(Ruche* ruche) // un jour est passé on mets tout à jour !
{
    //age +1J pour ouvieres
    //age +1J pour reine
    //age +1J pour fakebourdon
    Ruche* Ouvriere_modif_age =malloc(sizeof(*Ouvriere_modif_age));
    Ouvriere_modif_age= Ruche->Ouvriere;

    
    Ruche * Ouvriere_modif_age =malloc(sizeof(*Ouvriere_modif_age));
    Ruche* Q =malloc(sizeof(*Q));
   // Q = ruche->first; // changer pour du hachage 
   
    if (slist== NULL || Ouvriere_modif_age==NULL || Q==NULL)
    {
        printf("[fatal error]");
         exit(-1);
    }
   

    nouvellecarte_Index->next=NULL;
    for(int i=0;i<nbOuvrieres-1;i++)
    {
        Ouvriere->age+1;
        //besoin en eau/ nouriture  
        Q =Q->next;
    }
    nouvellecarte_Index->next = Q->next;
    Q->next = nouvellecarte_Index;
   
    slist->NombreCarte++;
    printf("la carte index a été créer\n");

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
