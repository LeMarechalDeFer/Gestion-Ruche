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
                    printf("Type: Reine, Ponte Journaliere: %s\n",
                           listeInsectes->data.reine.ponteJournaliere ? "Oui" : "Non");
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
            break;
        case TYPE_OUVRIERE:
            nouvelInsecte->data.ouvriere.cohesion = COHESION_MAX; 
            nouvelInsecte->data.ouvriere.efficacite = EFFICACITE_MAX; 
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
        listeInsectes = GENERATION_push_front_list(listeInsectes, TYPE_OUVRIERE, NOURRICE, ADULTE, 13, SANTE_MAX, false); //teste santé
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

ListeInsectes attributionRoleOuvriere(ListeInsectes listeInsectes){
    if(listeInsectes->type == TYPE_OUVRIERE){
        if(listeInsectes->data.ouvriere.role == AUCUN && listeInsectes->age >= TEMPS_PUPAISON_OUVRIERE_J){
            listeInsectes->data.ouvriere.role = NETTOYEUSE;
        }
        if(listeInsectes->age >= AGE_NOURRICE_J){
            listeInsectes->data.ouvriere.role = NOURRICE;
        }
        if(listeInsectes->age >= AGE_MAGASINIERE_J){
            listeInsectes->data.ouvriere.role = MAGASINIERE;
        }
        if(listeInsectes->age >= AGE_CIRIERE_J){
            listeInsectes->data.ouvriere.role = CIRIERE;
        }
        if(listeInsectes->age >= AGE_VENTILEUSE_J){
            listeInsectes->data.ouvriere.role = VENTILEUSE;
        }
        if(listeInsectes->age >= AGE_GARDIENNE_J){
            listeInsectes->data.ouvriere.role = GARDIENNE;
        }
        if(listeInsectes->age >= AGE_BUTINEUSE_J){
            listeInsectes->data.ouvriere.role = BUTINEUSE;
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


bool cycledeMort(ListeInsectes insecte, Saisons Saison)
{

    if (insecte == NULL) {
        return false;
    }
    if ( insecte->sante == 0) {
        return true;
    }
        if (((Saison == PRINTEMPS || Saison == ETE)&&(insecte->type == TYPE_OUVRIERE && insecte->age >= DUREE_VIE_MAX_OUVRIERE_ETE_J))
        ||((Saison == HIVER || Saison == AUTOMNE) && (insecte->type == TYPE_OUVRIERE && insecte->age >= DUREE_VIE_MAX_OUVRIERE_HIVER_J))){
        return true;
    }

    if (insecte->type == TYPE_REINE && insecte->age >=DUREE_VIE_MAX_REINE_J) { //DUREE_VIE_MAX_REINE_J) {
        return true;
    }
    if (insecte->type == TYPE_FAUX_BOURDON && insecte->age >=DUREE_VIE_MAX_FAUX_BOURDON_J) { //DUREE_VIE_MAX_REINE_J) {
        return true;
    }
    // Ajoutez ici d'autres conditions pour d'autres types d'insectes

    return false;
}


// ListeInsectes cycledeMort(ListeInsectes insecteActuel, ListeInsectes listeInsectes)
// {
//     if (insecteActuel == NULL) {
//         return insecteActuel;
//     }
//     if (insecteActuel->sante == 0) {
//         printf("l'abeille ID: %d est morte de: santé\n ",insecteActuel->id);
//         listeInsectes = Kill_Abeille(listeInsectes, insecteActuel->id);
//         return insecteActuel;
//     }
//     if (insecteActuel->type == TYPE_OUVRIERE && insecteActuel->age >= DUREE_VIE_MAX_OUVRIERE_ETE_J) {
//         listeInsectes = Kill_Abeille(listeInsectes, insecteActuel->id);
//         printf("l'abeille ID: %d est morte de: vieillese\n",insecteActuel->id);
//         return insecteActuel;
//     }

//     if (insecteActuel->type == TYPE_REINE && insecteActuel->age >=DUREE_VIE_MAX_REINE_J) { //DUREE_VIE_MAX_REINE_J) {
//         listeInsectes = Kill_Abeille(listeInsectes, insecteActuel->id);
//         return insecteActuel;
//     }
//     if (insecteActuel->type == TYPE_FAUX_BOURDON && insecteActuel->age >=DUREE_VIE_MAX_FAUX_BOURDON_J) { //DUREE_VIE_MAX_REINE_J) {
//         listeInsectes = Kill_Abeille(listeInsectes, insecteActuel->id);
//         return insecteActuel;
//     }

//     return insecteActuel;
// }

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

ListeInsectes Kill_Abeille(ListeInsectes listeInsectes, unsigned int ID) {
    if (listeInsectes == NULL) {
        // Liste vide
        printf ("la liste est bien vide kill fonctionne ");
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

ListeInsectes cycledeFaim(ListeInsectes listeInsectes, RuchePtr ruche){
    
    if(ruche->reserveMiel > 0 && ruche->reserveEau > 0 && listeInsectes->type == TYPE_OUVRIERE && listeInsectes->cycleCroissanceAbeilles == ADULTE){
        listeInsectes->faim = false;
        ruche->reserveMiel -= CONSOMMATION_MIEL_J;
        ruche->reserveEau -= CONSOMMATION_EAU_J;
    }
    else if(ruche->reserveMiel > 0 && ruche->reserveEau > 0 && listeInsectes->type == TYPE_FAUX_BOURDON && listeInsectes->cycleCroissanceAbeilles == ADULTE){
        listeInsectes->faim = false;
        ruche->reserveMiel -= CONSOMMATION_MIEL_J;
        ruche->reserveEau -= CONSOMMATION_EAU_J;
    }
    else if(ruche->reserveGeleeRoyale > 0 && ruche->reserveEau > 0 && listeInsectes->type == TYPE_REINE && listeInsectes->cycleCroissanceAbeilles == ADULTE){
        listeInsectes->faim = false;
        ruche->reserveGeleeRoyale -= CONSOMMATION_GELEE_ROYALE_J;
        ruche->reserveEau -= CONSOMMATION_EAU_J;
        
    }  
    // else if(listeInsectes->cycleCroissanceAbeilles == LARVE || listeInsectes->cycleCroissanceAbeilles == PUPAISON || listeInsectes->cycleCroissanceAbeilles == OEUF){
    //     listeInsectes->faim = false;
    //     //printf("Nous verrons bien si les larves ont faim\n");
    // }
    
    else if(listeInsectes->type == TYPE_OURSE || listeInsectes->type == TYPE_GUEPE){
        //implementer nourriture ou non des ourse/guepe ? rand nourriture trouver => agressivité  => rand ruche trouvé => attaque ruche
    }
    /*  else if(ruche->reserveMiel > 0 && (listeInsectes->cycleCroissanceAbeilles == OEUF || listeInsectes->cycleCroissanceAbeilles == LARVE || listeInsectes->cycleCroissanceAbeilles == PUPAISON))
    {
        listeInsectes->faim = false;
        ruche->reserveMiel -= 1;
        ruche->reserveEau -= 1;
    }*/
    else if(listeInsectes->faim == true){
        listeInsectes->sante -= 25;
        //printf("L'abeille ID: %d n'a pas mangé\n",listeInsectes->id);

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


//fonction implémentée main non utilisée car efficatie/experience non implémentée
ListeInsectes competenceMaxAbeille(ListeInsectes listeInsectes){
    if(listeInsectes->type == TYPE_OUVRIERE || listeInsectes->type == TYPE_FAUX_BOURDON){
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
        printf("La ruche déborde de miel\n");
    }
    if(ruche->reserveEau > CAPACITE_MAX_EAU_ML){
        ruche->reserveEau = CAPACITE_MAX_EAU_ML;
        printf("La ruche déborde d'eau\n");
    }
    if(ruche->reservePollen > CAPACITE_MAX_POLLEN_G){
        ruche->reservePollen = CAPACITE_MAX_POLLEN_G;
        printf("La ruche déborde de pollen\n");
    }
    if(ruche->reserveGeleeRoyale > CAPACITE_MAX_GELEE_ROYALE_G){
        ruche->reserveGeleeRoyale = CAPACITE_MAX_GELEE_ROYALE_G;
        printf("La ruche déborde de gelee royale\n");
    }
    if(ruche->sante >= SANTE_RUCHE_MAX){
        printf("La ruche est en trop bonne santé\n");
        ruche->sante = SANTE_RUCHE_MAX ;
    }
    if(ruche->salete <= SALETE_MIN){
        printf("La ruche est trop propre\n");
        ruche->salete = SALETE_MIN;
    }
    return ruche;
}

RuchePtr evenementJouranilerRuche(RuchePtr ruche){
    ruche->salete += SALETE_JOURNALIERE_RUCHE;

    if (ruche->sante >= USURE_JOURNALIERE_RUCHE) {
        ruche->sante -= USURE_JOURNALIERE_RUCHE;
    } else {
        ruche->sante = SANTE_RUCHE_MIN;
    }
    
    return ruche;
}

ListeInsectes actionOuvriere(ListeInsectes listeInsectes, RuchePtr ruche){
    if(listeInsectes->type == TYPE_OUVRIERE){
        switch(listeInsectes->data.ouvriere.role){
            case NETTOYEUSE: //fontionnelle (teste unitaire effectué)
                if(ruche->salete >= SALETE_MIN){
                    ruche->salete -= SALETE_NETTOYAGE;
                    //printf("Nettoyeuse a fait son travail\n");
                }
                break;
            case NOURRICE:
                    Insecte *current = listeInsectes;
                    while (current != NULL ) 
                    {
                    if((current->cycleCroissanceAbeilles == LARVE || current->cycleCroissanceAbeilles == OEUF || current->cycleCroissanceAbeilles == PUPAISON) && current->faim == true)
                         if(ruche->reserveMiel > 0 && ruche->reserveEau > 0)
                         {
                             ruche->reserveMiel -= CONSOMMATION_MIEL_J;
                             ruche->reserveEau -= CONSOMMATION_EAU_J;
                             listeInsectes->faim = false;
                             //printf("Nourrice a nourrit la larve %d\n", current->id);
                         }
                         current = current->next;
                    }
                    while(current != NULL ) 
                    {
                    if((current->cycleCroissanceAbeilles == LARVE || current->cycleCroissanceAbeilles == OEUF || current->cycleCroissanceAbeilles == PUPAISON) && current->faim == true)
                         if(ruche->reserveMiel > 0 && ruche->reserveEau > 0)
                         {
                             ruche->reserveMiel -= CONSOMMATION_MIEL_J;
                             ruche->reserveEau -= CONSOMMATION_EAU_J;
                             current->faim = false;
                            //printf("Nourrice a nourrit la larve %d\n", current->id);
                         }
                         current = current->previous;
                    }
                    break;
            case MAGASINIERE: //fontionnelle (teste unitaire effectué)
                if(ruche->reservePollen > 0){
                    ruche->reservePollen -= TRANSFORMATION_POLLEN_UTILISE_J;
                    ruche->reserveMiel += TRANSFORMATION_POLLEN_EN_MIEL_J;
                    ruche->reserveGeleeRoyale += TRANSFORMATION_POLLEN_EN_GELEE_ROYAL_J;
                    //printf("Magasiniere a fait son travail\n");
                }
                else{
                    //printf("Pas assez de pollen pour notre Stakhanov en chef\n");
                }
                break;
            case CIRIERE: ///fontionnelle (teste unitaire effectué)
                if(ruche->sante <= SANTE_RUCHE_MAX){
                    ruche->sante += SANTE_RUCHE_REPARATION;
                    //printf("Ciriere a fait son travail\n");
                }
                else{
                    //printf("Ruche santé max : Ciriere profite de ses RTT\n");
                }
                break;

            case VENTILEUSE: //fontionnelle (teste unitaire effectué)
                if(ruche->temperature > TEMPERATURE_IDEAL){
                    ruche->temperature -= TEMPERATURE_VENTILATION ;
                    //printf("Ventileuse a fait son travail\n");
                }
                if(ruche->temperature < TEMPERATURE_IDEAL){
                    ruche->temperature += TEMPERATURE_VENTILATION ;
                    //printf("Ventileuse a fait son travail\n");
                }
                else{
                    //printf("Ruche temperature idéale : Ventilleuse profitede ses RTT\n");
                }
                break;
            case GARDIENNE:

                break;
            case BUTINEUSE: //fontionnelle (teste unitaire effectué)
                ruche->reservePollen += RECOLTE_POLLEN_J;
                ruche->reserveEau += RECOLTE_EAU_J;
                //printf("Butineuse a fait son travail\n");

                break;

            default:
                break;
        }
                
            
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
        if((saison == PRINTEMPS || saison == ETE)&& listeInsectes->data.reine.spermatheque > 0){  
            listeInsectes->data.reine.ponteJournaliere = true;
            listeInsectes->data.reine.spermatheque -= 1;
            printf("C'est la reine Reine et elle pond\n");
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

bool parcoursListeTrouverReine(ListeInsectes listeInsectes){
    ListeInsectes insecteActuel = listeInsectes;
    while(insecteActuel != NULL){
        if(insecteActuel->type == TYPE_REINE){
            if(insecteActuel->data.reine.spermatheque <20){
                insecteActuel->data.reine.spermatheque += 1;
                return true;
            } 
            else{
                return false;
            }
            
        }
        else{
            insecteActuel = insecteActuel->next;
        }
    }
    return false;
}



ListeInsectes actionFauxBourdon(ListeInsectes listeInsectes, Saisons saison){
    if(listeInsectes->type == TYPE_FAUX_BOURDON){
        if(saison == PRINTEMPS || saison == ETE){
            listeInsectes->data.FauxBourdon.enQueteReine = true;
            if(parcoursListeTrouverReine(listeInsectes) == true){
                printf("Faux Bourdon a trouvé la reine\n");                
            }
        }
        else{
            listeInsectes->data.FauxBourdon.enQueteReine = false;
        }
    }
    return listeInsectes;
}

bool conditionMortRuche(RuchePtr ruche, ListeInsectes listeInsectes){
    if(ruche->sante <= SANTE_MIN){
        printf("La ruche est morte d'usure\n");
        return true;
    }
    else if(ruche->salete >= SALETE_MAX){
        printf("La ruche est morte de saleté\n");
        return true;
    }
    else if (list_length(listeInsectes) == 0){
        printf("La ruche est morte\n");
        return true;
    }
    else if(ruche->temperature >= TEMPERATURE_MAX){
        printf("La ruche est morte de chaleur\n");
        return true;
    }
    else if(ruche->temperature <= TEMPERATURE_MIN){
        printf("La ruche est morte de froid\n");
        return true;
    }
    else{
        printf("La ruche est en vie\n");
        return false;
    }
}



ListeInsectes tourDeSimulation(ListeInsectes listeInsectes, RuchePtr ruche, unsigned int *jourNumero)
{
    if(is_empty_list(listeInsectes)){
        return new_list();
    }
    else{
        unsigned int nombreNaissance = 0;
        unsigned int nombreMort = 0;
        unsigned int tailleListe = list_length(listeInsectes);  

        Saisons saison = cycleSaison(jourNumero); 
        float temperatureJournee = generationJouraliereTemperature(saison);
        ruche->temperature = temperatureJournee;
        ruche = evenementJouranilerRuche(ruche);
        
        ListeInsectes insecteActuel = listeInsectes;
        
        bool reine_Va_Pondre = false;
        
        while(insecteActuel != NULL)
        {
            listeInsectes->faim = true;
            insecteActuel = cycleCroissance(insecteActuel); 
            insecteActuel = attributionRoleOuvriere(insecteActuel);
            insecteActuel = actionOuvriere(insecteActuel, ruche);
            insecteActuel = actionFauxBourdon(insecteActuel, saison);
            insecteActuel = cycledeFaim(insecteActuel, ruche);
            
            
            if (cycledeMort(insecteActuel, saison))
            {

                if ( insecteActuel->sante == SANTE_MIN) {
                    //printf("l'abeille ID: %d est morte de: santé\n ",insecteActuel->id);
                }
                if (insecteActuel->type == TYPE_OUVRIERE && insecteActuel->age >= DUREE_VIE_MAX_OUVRIERE_ETE_J) {
                    //printf("l'abeille ID: %d est morte de: vieillese\n",insecteActuel->id);
                }
                listeInsectes = Kill_Abeille(listeInsectes, insecteActuel->id);
            }


            //listeInsectes = cycledeMort(insecteActuel, listeInsectes); refactorisation non fonctionnelle
            reine_Va_Pondre = reineVaPondre(saison, insecteActuel);
            //insecteActuel = competenceMaxAbeille(insecteActuel); competence/xp non fonctionnelle
            
            insecteActuel = insecteActuel->next; 
        }

        unsigned int tailleListeAfter = list_length(listeInsectes); 
        nombreMort = nombreMortJ(tailleListe, tailleListeAfter);

        listeInsectes = actionReine(listeInsectes, reine_Va_Pondre);
        listeInsectes = nombreMaxAbeille(listeInsectes);           
        ruche = capaciteMaxRuche(ruche);                         

        nombreNaissance = nombreNaissanceJ(reine_Va_Pondre);
        
        affichageTour(listeInsectes, ruche, jourNumero, nombreNaissance, nombreMort, saison, temperatureJournee);

        return listeInsectes;
    }
            
}

unsigned int nombreMortJ(unsigned int tailleListe, unsigned int tailleListeAfter){
    unsigned int nombreMort = 0;
    nombreMort += (tailleListe - tailleListeAfter);
    return nombreMort;
}

unsigned int nombreNaissanceJ(bool reine_Va_Pondre){
    unsigned int nombreNaissance = 0;
    if(reine_Va_Pondre == true){
        nombreNaissance = PONTE_OUVRIERE_JOUR + PONTE_FAUX_BOURDON_JOUR;
    }
    return nombreNaissance;
}



void affichageTour(ListeInsectes listeInsectes, 
                    RuchePtr ruche, 
                    unsigned int *jourNumero, 
                    unsigned int nombreNaissance, 
                    unsigned int nombreMort, 
                    Saisons saison,
                    float temperatureJournee){

        printf("_______________________________________________________________________________________________________\n\n");
        print_list(listeInsectes);

        
        printf("Saison: %s\n", SaisonsStrings[saison]);
        printf("Taille de la liste: %u\n", list_length(listeInsectes));
        printf("Le nombre de naissances: %u\n", nombreNaissance);
        printf("Le nombre de morts: %u\n", nombreMort);
        printf("Nourriture ruche: Miel: %u, Eau: %u, Pollen: %u, Gelee Royale: %u\n", ruche->reserveMiel, ruche->reserveEau, ruche->reservePollen, ruche->reserveGeleeRoyale);
        printf("Statistiques ruche: Temperature: %f, Sante: %u / 500, Salete: %u / 1000\n", ruche->temperature, ruche->sante, ruche->salete);

        printf("_______________________________________________________________________________________________________\n");
}


//initialisation de la ruche
RuchePtr initialisationRuche()
{
    RuchePtr ruche = malloc(sizeof(Ruche));
    if(ruche == NULL){
        perror("Erreur allocation mémoire\n");
        exit(EXIT_FAILURE);
    }
    ruche->temperature = TEMPERATURE_IDEAL;
    ruche->sante = SANTE_RUCHE_MAX;
    ruche->salete = SALETE_MIN;
    ruche->reserveMiel = CAPACITE_INITIALE_MIEL_g;
    ruche->reserveEau = CAPACITE_INITIALE_EAU_ML;
    ruche->reservePollen = CAPACITE_INITIALE_POLLEN_G;
    ruche->reserveGeleeRoyale = CAPACITE_INITIALE_GELEE_ROYALE_G;
    ruche->nombreOuvrieres = 0;
    ruche->nombreFauxBourdon = 0;
    return ruche;
}


//testy comit