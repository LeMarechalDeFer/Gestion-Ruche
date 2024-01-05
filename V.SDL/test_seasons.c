#include <stdio.h>
#include <time.h>  // Pour time() et difftime()

void printSeasons(int seasonIndex) {
    char* seasons[] = {"Printemps", "Été", "Automne", "Hiver"};
    // Assurez-vous que l'index est toujours entre 0 et 3
    printf("%s\n", seasons[seasonIndex % 4]);
}

int main() {
    int currentSeason = 0;
    time_t start, end;
    printf("%s\n", "Hiver");
    // Enregistre le temps actuel
    time(&start);

    while(1) { // Boucle infinie pour répéter les saisons
        // Enregistre le nouveau temps actuel
        time(&end);

        // Vérifie si 3 secondes se sont écoulées
        if (difftime(end, start) >= 3) {
            printSeasons(currentSeason); // Appelle la fonction pour imprimer la saison actuelle
            currentSeason++;  // Passe à la saison suivante

            // Réinitialise le compteur de temps
            time(&start);
        }
    }

    return 0;
}
