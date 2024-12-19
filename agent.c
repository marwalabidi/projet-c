#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "agent.h"
#include <gtk/gtk.h>


// Fonction pour vérifier si une chaîne est composée uniquement de chiffres
int est_une_chaine_de_chiffres(const char *str) {
    while (*str) {
        if (!isdigit(*str)) {
            return 0; // Invalide
        }
        str++;
    }
    return 1; // Valide
}

// Fonction pour vérifier si une chaîne est composée uniquement de lettres
int est_une_chaine_de_lettres(const char *str) {
    while (*str) {
        if (!isalpha(*str)) {
            return 0; // Invalide
        }
        str++;
    }
    return 1; // Valide
}

// Fonction pour vérifier si un email est valide (simple vérification de format)
int est_un_mail_valide(const char *mail) {
    const char *at = strchr(mail, '@');
    return at && strchr(at, '.'); // Vérifie la présence de '@' et '.'
}

// Fonction pour saisir un agent
void saisir_agent(agent *a, FILE *input_file) {
    do {
        fprintf(input_file, "Entrez le CIN (8 chiffres) : ");
        fscanf(input_file, "%s", a->cin);
    } while (strlen(a->cin) != 8 || !est_une_chaine_de_chiffres(a->cin));

    do {
        fprintf(input_file, "Entrez le nom (lettres uniquement) : ");
        fscanf(input_file, "%s", a->nom);
    } while (!est_une_chaine_de_lettres(a->nom));

    do {
        fprintf(input_file, "Entrez le prénom (lettres uniquement) : ");
        fscanf(input_file, "%s", a->prenom);
    } while (!est_une_chaine_de_lettres(a->prenom));

    do {
        fprintf(input_file, "Entrez le numéro de téléphone (8 chiffres) : ");
        fscanf(input_file, "%s", a->num_tel);
    } while (strlen(a->num_tel) != 8 || !est_une_chaine_de_chiffres(a->num_tel));

    do {
        fprintf(input_file, "Entrez l'email (format valide) : ");
        fscanf(input_file, "%s", a->mail);
    } while (!est_un_mail_valide(a->mail));

    do {
        fprintf(input_file, "Entrez le sexe (0 pour M, 1 pour F) : ");
        fscanf(input_file, "%d", &a->sexe);
    } while (a->sexe != 0 && a->sexe != 1);


}

// Fonction pour afficher un agent
void afficher_agent(const agent *a, FILE *output_file) {
    fprintf(output_file, "CIN: %s\n", a->cin);
    fprintf(output_file, "Nom: %s\n", a->nom);
    fprintf(output_file, "Prenom: %s\n", a->prenom);
    fprintf(output_file, "Numero de telephone: %s\n", a->num_tel);
    fprintf(output_file, "Email: %s\n", a->mail);
    fprintf(output_file, "Sexe: %s\n", (a->sexe == 0) ? "M" : "F");
    fprintf(output_file, "Date de naissance: %02d/%02d/%04d\n", a->date_naissance.jour, a->date_naissance.mois, a->date_naissance.annee);
    fprintf(output_file, "Statut: %s\n", a->statut);
}

// Fonction pour ajouter un agent dans un fichier
int ajouter_agent(const char *filename, agent a) {
    FILE *f = fopen(filename, "a");
    if (!f) {
        perror("Erreur d'ouverture du fichier");
        return 0; // Échec
    }

    fprintf(f, "%s %s %s %s %s %d %d %d %d %d %s\n",
            a.cin, a.nom, a.prenom, a.num_tel, a.mail, a.sexe,
            a.date_naissance.jour, a.date_naissance.mois, a.date_naissance.annee, a.statut);
    fclose(f);
    return 1; // Succès
}

// Fonction pour modifier un agent


// Fonction pour modifier un agent dans le fichier
int modifier_ou_ajouter_agent(const char *filename, agent agent_modifie) { 
FILE *file = fopen(filename, "r");
 if (!file) { printf("Erreur : Impossible d'ouvrir le fichier %s.\n", filename); 
return 0; 
// Échec
 } FILE *temp = fopen("temp.txt", "w"); if (!temp) { fclose(file); printf("Erreur : Impossible de créer le fichier temporaire.\n"); return 0; 
// Échec 
} agent a_temp; int trouve = 0; char line[512]; 
// Lire le fichier ligne par ligne 
while (fgets(line, sizeof(line), file) != NULL) { line[strcspn(line, "\n")] = 0; 
// Supprimer le saut de ligne 
// Extraire les informations de l'agent actuel
 if (sscanf(line, "%49[^;];%49[^;];%49[^;];%49[^;];%49[^;];%d;%d/%d/%d;%49[^;]", a_temp.cin, a_temp.nom, a_temp.prenom, a_temp.num_tel, a_temp.mail, &a_temp.sexe, &a_temp.date_naissance.jour, &a_temp.date_naissance.mois, &a_temp.date_naissance.annee, a_temp.statut) == 10) { 
// Comparer les CIN pour trouver l'agent à modifier
 if (strcmp(a_temp.cin, agent_modifie.cin) == 0) { trouve = 1; 
// Agent trouvé, on le modifie
 a_temp = agent_modifie; 
// Mettre à jour les données 
} 
// Réécrire dans le fichier temporaire 
fprintf(temp, "%s;%s;%s;%s;%s;%d;%02d/%02d/%04d;%s\n", a_temp.cin, a_temp.nom, a_temp.prenom, a_temp.num_tel, a_temp.mail, a_temp.sexe, a_temp.date_naissance.jour, a_temp.date_naissance.mois, a_temp.date_naissance.annee, a_temp.statut); } } 
// Si l'agent n'a pas été trouvé, on l'ajoute à la fin 
if (!trouve) { fprintf(temp, "%s;%s;%s;%s;%s;%d;%02d/%02d/%04d;%s\n", agent_modifie.cin, agent_modifie.nom, agent_modifie.prenom, agent_modifie.num_tel, agent_modifie.mail, agent_modifie.sexe, agent_modifie.date_naissance.jour, agent_modifie.date_naissance.mois, agent_modifie.date_naissance.annee, agent_modifie.statut); }
 // Fermeture des fichiers 
fclose(file); fclose(temp); 
// Remplacer l'ancien fichier par le fichier temporaire 
remove(filename); 
rename("temp.txt", filename); 
return 1; 
// Succès } 


// Fonction pour supprimer un agent
int supprimer_agent(const char *filename, const char *cin) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        perror("Erreur d'ouverture du fichier");
        return 0; // Échec
    }

    FILE *temp = fopen("temp.txt", "w");
    if (!temp) {
        perror("Erreur d'ouverture du fichier temporaire");
        fclose(f);
        return 0; // Échec
    }

    agent a_temp;
    int trouve = 0;
    while (fscanf(f, "%s %s %s %s %s %d %d %d %d %d %s",
                  a_temp.cin, a_temp.nom, a_temp.prenom, a_temp.num_tel,
                  a_temp.mail, &a_temp.sexe, &a_temp.date_naissance.jour,
                  &a_temp.date_naissance.mois, &a_temp.date_naissance.annee, a_temp.statut) != EOF) {
        if (strcmp(a_temp.cin, cin) != 0) {
            fprintf(temp, "%s %s %s %s %s %d %d %d %d %d %s\n",
                    a_temp.cin, a_temp.nom, a_temp.prenom, a_temp.num_tel,
                    a_temp.mail, a_temp.sexe, a_temp.date_naissance.jour,
                    a_temp.date_naissance.mois, a_temp.date_naissance.annee, a_temp.statut);
        } else {
            trouve = 1; // Agent trouvé et supprimé
        }
    }

    fclose(f);
    fclose(temp);
    remove(filename);
    rename("temp.txt", filename);
}
    return trouve;
}

agent chercher_agent(const char *filename, const char *cin) {
    
    
    agent ag = {-1, "", "", "", "", 0, {0, 0, 0}, ""};
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        g_print("Erreur : Impossible d'ouvrir le fichier %s\n", filename);
        return ag;
    }
    char line[256]; 
// Pour stocker une ligne complète 
while (fgets(line, sizeof(line), file)) { 
// Variables temporaires pour la lecture 
char temp_cin[9], temp_nom[50], temp_prenom[50], temp_num_tel[15], temp_mail[100]; int temp_sexe, temp_jour, temp_mois, temp_annee; char temp_statut[20]; 

// Lire les données en utilisant ';' comme délimiteur
 if (sscanf(line, "%8[^;];%49[^;];%49[^;];%14[^;];%99[^;];%d;%d/%d/%d;%19s", temp_cin, temp_nom, temp_prenom, temp_num_tel, temp_mail, &temp_sexe, &temp_jour, &temp_mois, &temp_annee, temp_statut) == 10) { 
// Comparer le CIN avec celui recherché 
if (strcmp(temp_cin, cin) == 0) { 
// Copier les données dans la structure agent
 strcpy(ag.cin, temp_cin); strcpy(ag.nom, temp_nom); strcpy(ag.prenom, temp_prenom); strcpy(ag.num_tel, temp_num_tel); strcpy(ag.mail, temp_mail); ag.sexe = temp_sexe; ag.date_naissance.jour = temp_jour; ag.date_naissance.mois = temp_mois; ag.date_naissance.annee = temp_annee; strcpy(ag.statut, temp_statut); 
fclose(file); 
return ag; } 
}
} 
fclose(file); 
// Aucun agent trouvé, retourner un agent vide 
memset(&ag, 0, sizeof(agent));
 return ag; } 

GtkListStore *creer_model_treeview() {
    // Création d'un GtkListStore avec 8 colonnes
    GtkListStore *store = gtk_list_store_new(8, 
                                             G_TYPE_STRING,  // CIN
                                             G_TYPE_STRING,  // Nom
                                             G_TYPE_STRING,  // Prénom
                                             G_TYPE_STRING,  // Numéro de téléphone
                                             G_TYPE_STRING,  // Email
                                             G_TYPE_STRING,  // Sexe
                                             G_TYPE_STRING,  // Jour de naissance
                                             G_TYPE_STRING,  // Mois de naissance
                                             G_TYPE_STRING); // Année de naissance
    return store;
}

void configurer_columns_treeview(GtkTreeView *treeview) {
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;

    // Colonne 1 : CIN
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("CIN", renderer, "text", 0, NULL);
    gtk_tree_view_append_column(treeview, column);

    // Colonne 2 : Nom
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Nom", renderer, "text", 1, NULL);
    gtk_tree_view_append_column(treeview, column);

    // Colonne 3 : Prénom
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Prénom", renderer, "text", 2, NULL);
    gtk_tree_view_append_column(treeview, column);

    // Colonne 4 : Numéro de téléphone
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Numéro de téléphone", renderer, "text", 3, NULL);
    gtk_tree_view_append_column(treeview, column);

    // Colonne 5 : Email
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Email", renderer, "text", 4, NULL);
    gtk_tree_view_append_column(treeview, column);

    // Colonne 6 : Sexe
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Sexe", renderer, "text", 5, NULL);
    gtk_tree_view_append_column(treeview, column);

    // Colonne 7 : Jour de naissance
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Jour de naissance", renderer, "text", 6, NULL);
    gtk_tree_view_append_column(treeview, column);

    // Colonne 8 : Mois de naissance
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Mois de naissance", renderer, "text", 7, NULL);
    gtk_tree_view_append_column(treeview, column);

    // Colonne 9 : Année de naissance
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Année de naissance", renderer, "text", 8, NULL);
    gtk_tree_view_append_column(treeview, column);
}

void afficher_agent_dans_treeview(agent a, GtkTreeView *treeview) {
    GtkListStore *store = GTK_LIST_STORE(gtk_tree_view_get_model(treeview));
    GtkTreeIter iter;

    // Convertir le sexe en chaîne de caractères
    const char *sexe = (a.sexe == 0) ? "Homme" : "Femme";

    // Ajouter une nouvelle ligne dans le modèle
    gtk_list_store_append(store, &iter);

    // Ajouter les données de l'agent dans cette ligne
    gtk_list_store_set(store, &iter,
                       0, a.cin,                          // CIN
                       1, a.nom,                          // Nom
                       2, a.prenom,                       // Prénom
                       3, a.num_tel,                      // Numéro de téléphone
                       4, a.mail,                         // Email
                       5, sexe,                           // Sexe
                       6, g_strdup_printf("%d", a.date_naissance.jour),  // Jour de naissance
                       7, g_strdup_printf("%d", a.date_naissance.mois), // Mois de naissance
                   8, g_strdup_printf("%d", a.date_naissance.annee), // Année de naissance
                       -1);  // Fin de la liste des colonnes
}
agent rechercher_agent(FILE *file, const char *cin) {
    agent ag = {"", "", "", "", "", 0, {0, 0, 0}, ""};
    char line[256];

    while (fgets(line, sizeof(line), file)) {
        // Supprimer le caractère de fin de ligne
        line[strcspn(line, "\n")] = 0; // Remplace le '\n' par '\0'

        char temp_cin[9], temp_nom[50], temp_prenom[50], temp_num_tel[15], temp_mail[100];
        int temp_sexe, temp_jour, temp_mois, temp_annee;
        char temp_statut[20];

        // Affiche la ligne lue
        printf("Ligne lue: %s\n", line);

        if (sscanf(line, "%8[^;];%49[^;];%49[^;];%14[^;];%99[^;];%d;%d/%d/%d;%19s",
                    temp_cin, temp_nom, temp_prenom, temp_num_tel, temp_mail,
                    &temp_sexe, &temp_jour, &temp_mois, &temp_annee, temp_statut) == 10) {

            // Affiche les valeurs extraites de la ligne
            printf("Données extraites - CIN: %s, Nom: %s, Prénom: %s, Sexe: %d, Date de naissance: %d/%d/%d\n",
                   temp_cin, temp_nom, temp_prenom, temp_sexe, temp_jour, temp_mois, temp_annee);

            // Compare le CIN extrait avec celui recherché
            if (strcmp(temp_cin, cin) == 0) {
                // Si trouvé, affiche les détails de l'agent
                printf("Agent trouvé : %s %s %s\n", temp_nom, temp_prenom, temp_cin);
                strcpy(ag.cin, temp_cin);
                strcpy(ag.nom, temp_nom);
                strcpy(ag.prenom, temp_prenom);
                strcpy(ag.num_tel, temp_num_tel);
                strcpy(ag.mail, temp_mail);
                ag.sexe = temp_sexe;
                ag.date_naissance.jour = temp_jour;
                ag.date_naissance.mois = temp_mois;
                ag.date_naissance.annee = temp_annee;
                strcpy(ag.statut, temp_statut);
                return ag;
            }
        }
    }
    return ag; // Retourne un agent vide si non trouvé
}
int supprimer_agentt(const char *filename, const char *id) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier %s.\n", filename);
        return 0;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        fclose(f);
        printf("Erreur : Impossible de créer le fichier temporaire.\n");
        return 0;
    }

    agent comp;
    char line[1024];
    int found = 0;

    // Lire le fichier ligne par ligne
    while (fgets(line, sizeof(line), f)) {
        // Utilisation de sscanf pour lire la ligne et remplir la structure 'agent'
        if (sscanf(line, "%8[^;];%49[^;];%49[^;];%14[^;];%99[^;];%d;%d/%d/%d;%19s",
                   comp.cin, comp.nom, comp.prenom,
                   comp.num_tel, comp.mail, &comp.sexe, 
                   &comp.date_naissance.jour, &comp.date_naissance.mois, &comp.date_naissance.annee, comp.statut) == 10) {

            // Vérifier si l'ID (CIN) correspond
            if (strcmp(comp.cin, id) == 0) {
                found = 1; // Marquer comme trouvé
                continue; // Ne pas écrire cette ligne dans le fichier temporaire
            }
        }

        // Écrire les lignes non supprimées dans le fichier temporaire
        fprintf(temp, "%s", line);
    }

    fclose(f);
    fclose(temp);

    if (found) {
        remove(filename);  // Supprimer l'ancien fichier
        rename("temp.txt", filename);  // Renommer le fichier temporaire
        return 1;
    } else {
        remove("temp.txt");
        printf("Erreur : agent avec l'ID %s introuvable.\n", id);
        return 0;
    }
}

reserv chercher_reserv_par_date(const char *filename, int jour, int mois, int annee) {
    reserv r;
    r.jour = -1;  // Valeur par défaut si la réservation n'est pas trouvée

    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Erreur : Impossible d'ouvrir le fichier");
        return r; // Retourner l'objet avec la valeur par défaut
    }

    char line[512];
    while (fgets(line, sizeof(line), file)) {
        reserv temp;  // Utilisation cohérente de la même structure
        if (sscanf(line, "%d|%49[^|]|%49[^|]|%199[^|]|%14[^|]|%d|%d|%d", 
                   &temp.id, temp.nom, temp.categorie, temp.description, 
                   temp.telephone, &temp.jour, &temp.mois, &temp.annee) == 8) { 
            // Vérifier si la date correspond à celle recherchée
            if (temp.jour == jour && temp.mois == mois && temp.annee == annee) {
                r = temp;
                break;
            }
        }
    }

    fclose(file);
    return r; // Retourner l'objet trouvé ou par défaut
}

