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

int list_length_type(ListeInsectes listeInsectes, TypeInsecte type){
    int length = 0;

    if(!is_empty_list(listeInsectes)){
        while(listeInsectes != NULL){
            if(listeInsectes->type == type){
                length += 1;
            }
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

    //srand(time(NULL));
    
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

    if (listeInsectes == NULL) {
        // La liste est vide, rien à faire
        return listeInsectes;
    }
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


// ListeInsectes Kill_Abeille(ListeInsectes listeInsectes, int ID){
//     ListeInsectes Indice = malloc(sizeof(Ouvriere));
//     ListeInsectes Recherche_Indice = malloc(sizeof(Ouvriere));
//     int ID_Recherche = -1;

//     if(Indice == NULL){
//         perror("Erreur allocation mémoire\n");
//         exit(EXIT_FAILURE);
//     }

//     ID_Recherche = Recherche_Indice->id;

//     while (ID!=ID_Recherche){
//         Indice->next;
//         Recherche_Indice->next;
//         ID_Recherche = Recherche_Indice->id;
//     }
//     Indice->previous;
//     Indice->next =Recherche_Indice->next;
//     free(Recherche_Indice);

//     return Indice ;
// }


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

ListeInsectes pop_specific_type(ListeInsectes liste, TypeInsecte type){
    ListeInsectes insecteActuel = liste;
    ListeInsectes prev = NULL;
    while(insecteActuel != NULL){
        if(insecteActuel->type == type){
            if(prev == NULL){
                liste->data.ouvriere.cohesion = 0; //Si le nombre d'abeille est trop grand, on supprime les abeilles en trop en mettant la cohesion a 0 
                liste = pop_front_list(liste);
                insecteActuel = liste;
                break;
            }
            else{
                prev->next = insecteActuel->next;
                free(insecteActuel);
                insecteActuel = prev->next;
                break;
            }
        }
        else{
            prev = insecteActuel;
            insecteActuel = insecteActuel->next;
        }
    }
    return liste;
}

ListeInsectes nombreMaxAbeille(ListeInsectes listeInsectes) {
    while(list_length_type(listeInsectes, TYPE_OUVRIERE) > NOMBRE_MAX_OUVRIERES) {
        //printf("Nombre d'ouvrieres trop grand\n");
        listeInsectes = pop_specific_type(listeInsectes, TYPE_OUVRIERE);
    }
    while(list_length_type(listeInsectes, TYPE_FAUX_BOURDON) > NOMBRE_MAX_FAUX_BOURDONS) {
        listeInsectes = pop_specific_type(listeInsectes, TYPE_FAUX_BOURDON);
    }
    return listeInsectes;
}



ListeInsectes competenceMaxAbeille(ListeInsectes listeInsectes){
    if(listeInsectes->type == TYPE_OUVRIERE || listeInsectes->type == TYPE_FAUX_BOURDON){
        if(listeInsectes->data.ouvriere.cohesion > COHESION_MAX){
            listeInsectes->data.ouvriere.cohesion = COHESION_MAX;
        }
        if(listeInsectes->data.ouvriere.efficacite > EFFICACITE_MAX){
            listeInsectes->data.ouvriere.efficacite = EFFICACITE_MAX;
        }
        // if(listeInsectes->data.ouvriere.experience > EXPERIENCE_MAX){
        //     listeInsectes->data.ouvriere.experience = EXPERIENCE_MAX;
        // }
    }
    return listeInsectes;
}

RuchePtr capaciteMaxRuche(RuchePtr ruche){
    if(ruche->reserveMiel > CAPACITE_MAX_MIEL_g){
        ruche->reserveMiel = CAPACITE_MAX_MIEL_g;
    }
    if(ruche->reserveEau > CAPACITE_MAX_EAU_ML){
        ruche->reserveEau = CAPACITE_MAX_EAU_ML;
    }
    if(ruche->reservePollen > CAPACITE_MAX_POLLEN_G){
        ruche->reservePollen = CAPACITE_MAX_POLLEN_G;
    }
    if(ruche->reserveGeleeRoyale > CAPACITE_MAX_GELEE_ROYALE_G){
        ruche->reserveGeleeRoyale = CAPACITE_MAX_GELEE_ROYALE_G;
    }
    return ruche;
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



ListeInsectes actionReine(ListeInsectes listeInsectes, bool reine_Va_Pondre){
    if(reine_Va_Pondre == true){
        //printf("Reine\n");
        int i;
        for(i=0; i<PONTE_OUVRIERE_JOUR; i++){
            listeInsectes = GENERATION_push_front_list(listeInsectes, TYPE_OUVRIERE, AUCUN, OEUF, 0, SANTE_MAX, false);
        }
        for(i=0; i<PONTE_FAUX_BOURDON_JOUR; i++){
            listeInsectes = GENERATION_push_front_list(listeInsectes, TYPE_FAUX_BOURDON, AUCUN, OEUF, 0, SANTE_MAX, false);
        }
    }
    return listeInsectes;
}

bool reineVaPondre(Saisons saison, ListeInsectes listeInsectes){
    if(listeInsectes->type == TYPE_REINE){
        //printf("C'est la reine Reine \n");
        if(saison == PRINTEMPS || saison == ETE){  
            listeInsectes->data.reine.ponteJournaliere = true;
            return true;
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }

}
ListeInsectes tourDeSimulation(ListeInsectes listeInsectes, RuchePtr ruche, unsigned int *jourNumero)
{
    if(is_empty_list(listeInsectes)){
        return new_list();
    }
    else{
        Saisons saison = cycleSaison(jourNumero); 
        ruche->temperature = generationJouraliereTemperature(saison);
        ruche = evenementJouranilerRuche(ruche);

        printf("_______________________________________________________________________________________________________\n\n");
        //print_list(listeInsectes);
        printf("Jour numéro: %u\n", *jourNumero);
        printf("Saison: %s\n", SaisonsStrings[saison]);
        printf("Jour numéro: %u\n",*jourNumero);
        printf("Temperature: %f\n", ruche->temperature);
        printf("Taille de la liste: %u\n", list_length(listeInsectes));
        // printf("Le nombre de naissances: %u\n", list_length(listeInsectes));// à ajuster
        // printf("Le nombre de morts: %u\n", list_length(listeInsectes));// à ajuster
        printf("_______________________________________________________________________________________________________\n");
        
        ListeInsectes insecteActuel = listeInsectes;
        ListeInsectes prev = NULL;
        bool reine_Va_Pondre = false;
        
        while(insecteActuel != NULL)
        {
            
            insecteActuel = cycleCroissance(insecteActuel);
            insecteActuel = cycledeFaim(insecteActuel, ruche);
            
            
            reine_Va_Pondre = reineVaPondre(saison, insecteActuel);
            //printf("reine_Va_Pondre: %s\n", reine_Va_Pondre ? "Oui" : "Non");
            insecteActuel = insecteActuel->next;
        }
        listeInsectes = nombreMaxAbeille(listeInsectes);
        listeInsectes = actionReine(listeInsectes, reine_Va_Pondre);
        
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


//testy comit




