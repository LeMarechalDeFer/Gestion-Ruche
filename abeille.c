#include "abeille.h"



const char* RoleOuvriereStrings[] = {
    "AUCUN", "NETTOYEUSE", "NOURRICE", "MAGASINIERE", "CIRIERE", "VENTILEUSE", "GARDIENNE", "BUTINEUSE"
};

const char *CycleCroissanceAbeillesStrings[] = {
    "OEUF", "LARVE", "PUPAISON", "ADULTE"
};

const char* SaisonsStrings[] = {
    "PRINTEMPS", "ETE", "AUTOMNE", "HIVER"
};

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
                case TYPE_OURSE:
                    printf("Type: Ourse\n");
                    break;
                case TYPE_GUEPE:
                    printf("Type: Guepe\n");
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
        case TYPE_OURSE:
            break;
        case TYPE_GUEPE:
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
        listeInsectes = GENERATION_push_front_list(listeInsectes, TYPE_OUVRIERE, NETTOYEUSE, ADULTE, 13, SANTE_MAX, false);
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





ListeInsectes clear_list(ListeInsectes listeInsectes){
    if(is_empty_list(listeInsectes)){
        return new_list() ;
    }
    else{
        while(listeInsectes != NULL){
            listeInsectes = Kill_Abeille( listeInsectes,  listeInsectes->id);
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



// On assume un depart au debut printemps pour un maximum de ponte et de reserve de nourriture
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
bool cycledeMort(ListeInsectes insecte)
{

    if (insecte == NULL) {
        return false;
    }

    if (insecte->type == TYPE_OUVRIERE && insecte->age >= DUREE_VIE_MAX_OUVRIERE_ETE_J) {
        return true;
    }
    
    if (insecte->type == TYPE_REINE && insecte->age >=30) { //DUREE_VIE_MAX_REINE_J) {
        return true;
    }
    // Ajoutez ici d'autres conditions pour d'autres types d'insectes

    return false;
}
/*
     if (listeActuelle->type == TYPE_OUVRIERE)
        {
            if(listeInsectes->age >= DUREE_VIE_MAX_OUVRIERE_ETE_J){
                listeInsectes = Kill_Abeille( listeInsectes,  listeActuelle->id);
            }
        }
        if (listeActuelle->type == TYPE_REINE)
        {
            if(listeInsectes->age >= 30){
                listeInsectes = Kill_Abeille( listeInsectes,  listeActuelle->id);
            }
        }

    if (listeInsectes == NULL) {
        // La liste est vide, rien à faire
        return listeInsectes;
    }
    if(listeInsectes->type == TYPE_REINE){
        if(listeInsectes->age >= DUREE_VIE_MAX_REINE_J){
            listeInsectes = Kill_Abeille( listeInsectes,  listeInsectes->id);
        }
    }
    if(listeInsectes->type == TYPE_OUVRIERE){
        if(listeInsectes->age >= DUREE_VIE_MAX_OUVRIERE_ETE_J )
        {
            listeInsectes = Kill_Abeille( listeInsectes,  listeInsectes->id);
        }
    }
    if(listeInsectes->type == TYPE_FAUX_BOURDON){
        if(listeInsectes->age >= DUREE_VIE_MAX_FAUX_BOURDON_J){
            listeInsectes = Kill_Abeille( listeInsectes,  listeInsectes->id);
        }
    }
    return listeInsectes;
}*/

ListeInsectes Kill_Abeille(ListeInsectes listeInsectes, unsigned int ID) {
    if (listeInsectes == NULL) {
        // Liste vide
        return NULL;
    }

    ListeInsectes current = listeInsectes;
    ListeInsectes previous = NULL;

    while (current != NULL && current->id != ID) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        // ID non trouvé
        return listeInsectes;
    }

    // Vérification pour s'assurer que l'élément n'a pas déjà été libéré
    if (current->next != NULL) {
        current->next->previous = previous;
    }
    if (previous != NULL) {
        previous->next = current->next;
    } else {
        // Si 'current' est le premier élément
        listeInsectes = current->next;
    }

    free(current);
    return listeInsectes;
}




// ListeInsectes Kill_Abeille(ListeInsectes listeInsectes, int ID){

//     while(listeInsectes->id != ID){
//         if(listeInsectes->next == NULL){
//             return listeInsectes;
//         }

//         listeInsectes = listeInsectes->next;
//     }   
// }

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


ListeInsectes actionOuvriere (ListeInsectes listeInsectes, RuchePtr ruche)
{ 
    switch(listeInsectes->data.ouvriere.role)
    {
            case AUCUN:
                break;
            case NETTOYEUSE:
                //nettoie la ruche et cadavre
                while (listeInsectes->data.ouvriere.efficacite > 0 )
                {
                    listeInsectes->data.ouvriere.efficacite-=1;
                    ruche->salete -= 1;
                }
                
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
    
    return listeInsectes;
}

ListeInsectes tourDeSimulation(ListeInsectes listeInsectes, RuchePtr ruche, unsigned int *jourNumero)
{
        //ListeInsectes prev = NULL;
    if(is_empty_list(listeInsectes)){
        return new_list();
    }
    else{
        Saisons saison = cycleSaison(jourNumero); 
        ruche->temperature = generationJouraliereTemperature(saison);
        ruche = evenementJouraniler(ruche);

        printf("_______________________________________________________________________________________________________\n\n");
        print_list(listeInsectes);
        printf("Jour numéro: %u\n", *jourNumero);
        printf("Saison: %s\n", SaisonsStrings[saison]);
        printf("Jour numéro: %u\n",*jourNumero);
        printf("Temperature: %f\n", ruche->temperature);
        printf("Taille de la liste: %u\n", list_length(listeInsectes));
        printf("Le nombre de naissances: %u\n", list_length(listeInsectes));// à ajuster
        printf("Le nombre de morts: %u\n", list_length(listeInsectes));// à ajuster
        printf("_______________________________________________________________________________________________________\n");

        
        ListeInsectes listeActuelle = listeInsectes;
        ListeInsectes next;
        while(listeActuelle  != NULL)
        {
        next = listeActuelle->next; // Sauvegarde du pointeur suivant avant de potentiellement supprimer 'listeActuelle'

        listeActuelle = cycleCroissance(listeActuelle);
        listeActuelle = cycledeFaim(listeActuelle, ruche);
        //insecteActuel = actionReine(listeInsectes, saison); 
            
        //     // insecteActuel= actionFauxBourdon(insecteActuel, saison);
        //     // insecteActuel = actionOuvriere(insecteActuel, ruche);
       
        /*if (listeActuelle->type == TYPE_OUVRIERE)
        {
            if(listeActuelle->age >= DUREE_VIE_MAX_OUVRIERE_ETE_J){
                listeInsectes = Kill_Abeille( listeInsectes,  listeActuelle->id);
            }
        }
        if (listeActuelle->type == TYPE_REINE)
        {
            if(listeActuelle->age >= 30){
                listeInsectes = Kill_Abeille( listeInsectes,  listeActuelle->id);
            }
        }*/
        if (cycledeMort(listeActuelle))
        {
            listeInsectes = Kill_Abeille(listeInsectes, listeActuelle->id);
        }

        //listeActuelle = cycledeMort(listeInsectes,listeActuelle, saison);


        listeActuelle = next; // Utiliser le pointeur sauvegardé
        
        }
        
        
        return listeInsectes;
    }
            
}

//initialisation de la ruche
RuchePtr initialisationRuche()
{
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


//testy comit




