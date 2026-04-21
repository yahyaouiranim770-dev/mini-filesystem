#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure de fichier
typedef struct Fichier {
    char nom[100];
    char contenu[1000];
} Fichier;

// Structure de dossier
typedef struct Dossier {
    char nom[100];
    struct Dossier* sous_dossiers;
    struct Fichier* fichiers;
    int nb_sous_dossiers;
    int nb_fichiers;
} Dossier;

Dossier* creer_dossier(char* nom) {
    Dossier* nouveau_dossier = (Dossier*)malloc(sizeof(Dossier));
    strcpy(nouveau_dossier->nom, nom);
    nouveau_dossier->sous_dossiers = NULL;
    nouveau_dossier->fichiers = NULL;
    nouveau_dossier->nb_sous_dossiers = 0;
    nouveau_dossier->nb_fichiers = 0;
    return nouveau_dossier;
}

void ajouter_dossier(Dossier* dossier, Dossier* dossier_a_ajouter) {
    dossier->nb_sous_dossiers++;
    dossier->sous_dossiers = (Dossier*)realloc(dossier->sous_dossiers, dossier->nb_sous_dossiers * sizeof(Dossier));
    dossier->sous_dossiers[dossier->nb_sous_dossiers - 1] = *dossier_a_ajouter;
}

Fichier* creer_fichier(char* nom) {
    Fichier* nouveau_fichier = (Fichier*)malloc(sizeof(Fichier));
    strcpy(nouveau_fichier->nom, nom);
    strcpy(nouveau_fichier->contenu, "");
    return nouveau_fichier;
}

void ecrire_fichier(Fichier* fichier, char* contenu) {
    strncpy(fichier->contenu, contenu, 999);
    fichier->contenu[999] = '\0'; // Assurer la terminaison de la chaîne
}

char* lire_fichier(Fichier* fichier) {
    return fichier->contenu;
}

void supprimer_fichier(Dossier* dossier, char* nom_fichier) {
    for (int i = 0; i < dossier->nb_fichiers; i++) {
        if (strcmp(dossier->fichiers[i].nom, nom_fichier) == 0) {
            for (int j = i; j < dossier->nb_fichiers - 1; j++) {
                dossier->fichiers[j] = dossier->fichiers[j + 1];
            }
            dossier->nb_fichiers--;
            dossier->fichiers = (Fichier*)realloc(dossier->fichiers, dossier->nb_fichiers * sizeof(Fichier));
            return;
        }
    }
}

void afficher_contenu(Dossier* dossier) {
    printf("Contenu du dossier %s:\n", dossier->nom);
    for (int i = 0; i < dossier->nb_fichiers; i++) {
        printf("Fichier: %s, Contenu: %s\n", dossier->fichiers[i].nom, dossier->fichiers[i].contenu);
    }
}

void aller_a(Dossier* dossier) {
    printf("Vous êtes dans le dossier: %s\n", dossier->nom);
}

void afficher_arbo(Dossier* dossier, int niveau) {
    for (int i = 0; i < niveau; i++) {
        printf("  ");
    }
    printf("Dossier: %s\n", dossier->nom);
    for (int i = 0; i < dossier->nb_sous_dossiers; i++) {
        afficher_arbo(&dossier->sous_dossiers[i], niveau + 1);
    }
}

int taille_totale(Dossier* dossier) {
    int taille = 0;
    for (int i = 0; i < dossier->nb_fichiers; i++) {
        taille += strlen(dossier->fichiers[i].contenu);
    }
    for (int i = 0; i < dossier->nb_sous_dossiers; i++) {
        taille += taille_totale(&dossier->sous_dossiers[i]);
    }
    return taille;
}

