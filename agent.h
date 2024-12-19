#ifndef AGENT_H
#define AGENT_H
#include <gtk/gtk.h>

#include <stdio.h>

// Définition de la structure date
typedef struct {
    int jour;
    int mois;
    int annee;
} date;

// Définition de la structure agent
typedef struct {
    char cin[9];
    char nom[50];
    char prenom[50];
    char num_tel[15];
    char mail[100];
    int sexe;  // 0 pour homme, 1 pour femme
    date date_naissance;  // Structure de type date
    char statut[20];  // Champ statut ajouté
} agent;

typedef struct {
    int id;                      // Identifiant
    char nom[50];                // Nom
    char categorie[50];          // Catégorie
    char description[200];       // Description
    char telephone[15];          // Téléphone
    int jour;                    // Jour
    int mois;                    // Mois
    int annee;                   // Année;
} reserv;

// Fonction pour saisir un agent
void saisir_agent(agent *a, FILE *input_file);

// Fonction pour afficher un agent
void afficher_agent(const agent *a, FILE *output_file);

// Fonction pour ajouter un agent dans un fichier
int ajouter_agent(const char *filename, agent a);

// Fonction pour modifier un agent
int modifier_ou_ajouter_agent(const char *filename, agent agent_modifie) ;

// Fonction pour supprimer un agent
//int supprimer_agent(const char *filename, const char *cin);

// Fonction pour chercher les réservations par date
reserv chercher_reserv_par_date(const char *filename, int jour, int mois, int annee) ;

// Fonction pour vérifier si un CIN est valide
int est_un_cin_valide(const char *cin);

// Fonction pour vérifier si un numéro de téléphone est valide
int est_un_num_tel_valide(const char *num_tel);

// Fonction pour vérifier si un email est valide
int est_un_mail_valide(const char *mail);

// Fonction pour vérifier si une chaîne est une chaîne de lettres
int est_une_chaine_de_lettres(const char *str);

// Fonction pour vérifier si une chaîne est composée uniquement de chiffres
int est_une_chaine_de_chiffres(const char *str);

GtkListStore *creer_model_treeview() ;

void configurer_columns_treeview(GtkTreeView *treeview) ;
void afficher_agent_dans_treeview(agent a, GtkTreeView *treeview) ;
agent chercher_agent(const char *filename, const char *cin) ;

//void configurer_columns_treeview(GtkTreeView *treeview) ;

agent rechercher_agent(FILE *file, const char *cin) ;
int supprimer_agentt(const char *filename, const char *id);

#endif // AGENT_H

