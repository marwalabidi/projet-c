#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "agent.h"




void
on_button28_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{

    // Déclaration des widgets GTK
    GtkWidget *entry_cin, *entry_nom, *entry_prenom, *entry_num_tel, *entry_mail;
    GtkWidget *radio_femme, *radio_homme;
    GtkWidget *spin_jour, *spin_mois, *spin_annee;
    GtkWidget *label_status, *combo_statut;

    // Déclaration de la structure agent
    agent a;

    // Nom du fichier
    char filename[] = "agents.txt";

    // Récupération des widgets via lookup_widget
    entry_cin = lookup_widget(GTK_WIDGET(button), "entry26");
    entry_nom = lookup_widget(GTK_WIDGET(button), "entry27");
    entry_prenom = lookup_widget(GTK_WIDGET(button), "entry28");
    entry_num_tel = lookup_widget(GTK_WIDGET(button), "entry29");
    entry_mail = lookup_widget(GTK_WIDGET(button), "entry30");
    radio_femme = lookup_widget(GTK_WIDGET(button), "radiobutton6");
    radio_homme = lookup_widget(GTK_WIDGET(button), "radiobutton7");
    spin_jour = lookup_widget(GTK_WIDGET(button), "spinbutton9");
    spin_mois = lookup_widget(GTK_WIDGET(button), "spinbutton10");
    spin_annee = lookup_widget(GTK_WIDGET(button), "spinbutton11");
    label_status = lookup_widget(GTK_WIDGET(button), "label161");
    combo_statut = lookup_widget(GTK_WIDGET(button), "combo5");  // Récupérer le combobox

    // Récupération des textes entrés par l'utilisateur
    strcpy(a.cin, gtk_entry_get_text(GTK_ENTRY(entry_cin)));
    strcpy(a.nom, gtk_entry_get_text(GTK_ENTRY(entry_nom)));
    strcpy(a.prenom, gtk_entry_get_text(GTK_ENTRY(entry_prenom)));
    strcpy(a.num_tel, gtk_entry_get_text(GTK_ENTRY(entry_num_tel)));
    strcpy(a.mail, gtk_entry_get_text(GTK_ENTRY(entry_mail)));

    // Validation : Vérifiez si le champ CIN est vide
    if (strlen(a.cin) == 0) {
        gtk_label_set_text(GTK_LABEL(label_status), "Erreur : CIN vide !");
        return;
    }

    // Validation du CIN (doit contenir 8 chiffres)
    if (strlen(a.cin) != 8 || !est_une_chaine_de_chiffres(a.cin)) {
        gtk_label_set_text(GTK_LABEL(label_status), "Erreur : CIN invalide !");
        return;
    }

    // Récupération du sexe via les boutons radio (0 pour homme, 1 pour femme)
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_femme))) {
        a.sexe = 1;  // Femme
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_homme))) {
        a.sexe = 0;  // Homme
    } else {
        gtk_label_set_text(GTK_LABEL(label_status), "Erreur : Sexe non sélectionné !");
        return;
    }

    // Récupération de la date de naissance
    a.date_naissance.jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_jour));
    a.date_naissance.mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_mois));
    a.date_naissance.annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_annee));

    // Validation de l'email
    if (!est_un_mail_valide(a.mail)) {
        gtk_label_set_text(GTK_LABEL(label_status), "Erreur : Email invalide !");
        return;
    }

    // Récupération du statut sélectionné dans le ComboBox
    int active_index = gtk_combo_box_get_active(GTK_COMBO_BOX(combo_statut));
    if (active_index == 0) {
        strcpy(a.statut, "Actif");
    } else if (active_index == 1) {
        strcpy(a.statut, "Inactif");
    } else {
        gtk_label_set_text(GTK_LABEL(label_status), "Erreur : Statut non sélectionné !");
        return;
    }

    // Écriture dans le fichier texte
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        gtk_label_set_text(GTK_LABEL(label_status), "Erreur : Impossible d'ouvrir le fichier.");
        return;
    }

    // Écriture des données dans le fichier avec le sexe et la date sous forme d'entiers
    fprintf(file, "%s;%s;%s;%s;%s;%d;%02d/%02d/%d;%s\n",
            a.cin, a.nom, a.prenom, a.num_tel, a.mail, a.sexe, 
            a.date_naissance.jour, a.date_naissance.mois, a.date_naissance.annee, a.statut);

    fclose(file);

    // Message de succès
    gtk_label_set_text(GTK_LABEL(label_status), "Agent ajouté avec succès !");

    // Réinitialiser les champs
    gtk_entry_set_text(GTK_ENTRY(entry_cin), "");
    gtk_entry_set_text(GTK_ENTRY(entry_nom), "");
    gtk_entry_set_text(GTK_ENTRY(entry_prenom), "");
    gtk_entry_set_text(GTK_ENTRY(entry_num_tel), "");
    gtk_entry_set_text(GTK_ENTRY(entry_mail), "");
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_femme), FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_homme), FALSE);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_jour), 1);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_mois), 1);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_annee), 2000);
}

void on_button312_clicked(GtkButton *button, gpointer user_data) {
    // Récupération des widgets
    GtkWidget *entry_cin = lookup_widget(GTK_WIDGET(button), "entry252");
    GtkWidget *entry_nom = lookup_widget(GTK_WIDGET(button), "entry262");
    GtkWidget *entry_prenom = lookup_widget(GTK_WIDGET(button), "entry272");
    GtkWidget *entry_num_tel = lookup_widget(GTK_WIDGET(button), "entry282");
    GtkWidget *entry_mail = lookup_widget(GTK_WIDGET(button), "entry292");

    GtkWidget *radio_homme = lookup_widget(GTK_WIDGET(button), "radiobutton82");
    GtkWidget *radio_femme = lookup_widget(GTK_WIDGET(button), "radiobutton83");
    GtkWidget *entry_jour = lookup_widget(GTK_WIDGET(button), "spinbutton102");
    GtkWidget *entry_mois = lookup_widget(GTK_WIDGET(button), "spinbutton112");
    GtkWidget *entry_annee = lookup_widget(GTK_WIDGET(button), "spinbutton122");
    GtkWidget *combobox_statut = lookup_widget(GTK_WIDGET(button), "combo42");

    GtkWidget *label_status = lookup_widget(GTK_WIDGET(button), "label1023");

    // Vérification des widgets essentiels
    if (!entry_cin || !label_status) {
        g_print("Erreur : Widgets non trouvés.\n");
        return;
    }

    // Vérification du CIN
    const char *cin_text = gtk_entry_get_text(GTK_ENTRY(entry_cin));
    if (!cin_text || strlen(cin_text) != 8) {
        gtk_label_set_text(GTK_LABEL(label_status), "Erreur : Veuillez entrer un CIN valide (8 caractères).");
        return;
    }

    // Recherche de l'agent
    agent ag = chercher_agent("agents.txt", cin_text);
    if (ag.cin == -1) {
        gtk_label_set_text(GTK_LABEL(label_status), "Erreur : Agent introuvable.");
        return;
    }

    // Remplissage des champs
    gtk_entry_set_text(GTK_ENTRY(entry_nom), ag.nom);
    gtk_entry_set_text(GTK_ENTRY(entry_prenom), ag.prenom);
    gtk_entry_set_text(GTK_ENTRY(entry_num_tel), ag.num_tel);
    gtk_entry_set_text(GTK_ENTRY(entry_mail), ag.mail);

    // Mise à jour du combo box pour le statut
    if (combobox_statut && GTK_IS_COMBO_BOX(combobox_statut)) {
        GtkTreeModel *model = gtk_combo_box_get_model(GTK_COMBO_BOX(combobox_statut));
        GtkTreeIter iter;
        gboolean valid = gtk_tree_model_get_iter_first(model, &iter);
        gboolean statut_found = FALSE ;
        while (valid) {
            gchar *statut_text = NULL;
            gtk_tree_model_get(model, &iter, 0, &statut_text, -1);
            g_strstrip(statut_text);
            g_strstrip(ag.statut);
            g_print("Comparaison : '%s' avec '%s'\n", statut_text,ag.statut);

            if (statut_text && strcmp(statut_text, ag.statut) == 0) {
                gtk_combo_box_set_active_iter(GTK_COMBO_BOX(combobox_statut), &iter);
                g_free(statut_text);
                break;
            }
            g_free(statut_text);
            valid = gtk_tree_model_iter_next(model, &iter);
        }
    }

    // Mise à jour des boutons radio pour le sexe
    if (radio_homme && radio_femme) {
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_homme), ag.sexe == 0);
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_femme), ag.sexe == 1);
    }

    // Mise à jour des spin buttons pour la date de naissance
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(entry_jour), ag.date_naissance.jour);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(entry_mois), ag.date_naissance.mois);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(entry_annee), ag.date_naissance.annee);

    // Mise à jour du label de statut
    gtk_label_set_text(GTK_LABEL(label_status), "Agent trouvé .");
 }
void on_button322edit_clicked(GtkButton *button, gpointer user_data) {
    
  // Récupération des widgets via lookup_widget
    GtkWidget *entry_cin = lookup_widget(GTK_WIDGET(button), "entry252");
    GtkWidget *entry_nom = lookup_widget(GTK_WIDGET(button), "entry262");
    GtkWidget *entry_prenom = lookup_widget(GTK_WIDGET(button), "entry272");
    GtkWidget *spin_jour = lookup_widget(GTK_WIDGET(button), "spinbutton102");
    GtkWidget *spin_mois = lookup_widget(GTK_WIDGET(button), "spinbutton112");
    GtkWidget *spin_annee = lookup_widget(GTK_WIDGET(button), "spinbutton122");
    GtkWidget *combobox_statut = lookup_widget(GTK_WIDGET(button), "combo42");
    GtkWidget *radio_homme = lookup_widget(GTK_WIDGET(button), "radiobutton82");
    GtkWidget *radio_femme = lookup_widget(GTK_WIDGET(button), "radiobutton83");
    GtkWidget *entry_num_tel = lookup_widget(GTK_WIDGET(button), "entry282");
    GtkWidget *entry_mail = lookup_widget(GTK_WIDGET(button), "entry292");
    GtkWidget *label_status = lookup_widget(GTK_WIDGET(button), "label1023");

    // Récupération des valeurs des champs
    const char *cin_text = gtk_entry_get_text(GTK_ENTRY(entry_cin));
    const char *nom_text = gtk_entry_get_text(GTK_ENTRY(entry_nom));
    const char *prenom_text = gtk_entry_get_text(GTK_ENTRY(entry_prenom));
    const char *num_tel_text = gtk_entry_get_text(GTK_ENTRY(entry_num_tel));
    const char *mail_text = gtk_entry_get_text(GTK_ENTRY(entry_mail));

    const char *statut_text = gtk_combo_box_get_active_text(GTK_COMBO_BOX(combobox_statut));
    if (!statut_text) {
        gtk_label_set_text(GTK_LABEL(label_status), "Erreur : Aucun statut sélectionné.");
        return;
    }

    int jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_jour));
    int mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_mois));
    int annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_annee));

    // Vérification des boutons radio pour le sexe
    int sexe = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_homme)) ? 0 : 1;

    // Création de l'agent 
agent agent_modifie; 
// Assurez-vous que strncpy gère correctement la taille et la terminaison nulle
 strncpy(agent_modifie.cin, cin_text, sizeof(agent_modifie.cin) - 1); 
agent_modifie.cin[sizeof(agent_modifie.cin) - 1] = '\0';
 strncpy(agent_modifie.nom, nom_text, sizeof(agent_modifie.nom) - 1);
 agent_modifie.nom[sizeof(agent_modifie.nom) - 1] = '\0'; 
strncpy(agent_modifie.prenom, prenom_text, sizeof(agent_modifie.prenom) - 1);
 agent_modifie.prenom[sizeof(agent_modifie.prenom) - 1] = '\0';
 strncpy(agent_modifie.num_tel, num_tel_text, sizeof(agent_modifie.num_tel) - 1);
 agent_modifie.num_tel[sizeof(agent_modifie.num_tel) - 1] = '\0'; 
strncpy(agent_modifie.mail, mail_text, sizeof(agent_modifie.mail) - 1); 
agent_modifie.mail[sizeof(agent_modifie.mail) - 1] = '\0'; 
agent_modifie.sexe = sexe;
 agent_modifie.date_naissance.jour = jour; 
agent_modifie.date_naissance.mois = mois; 
agent_modifie.date_naissance.annee = annee;
 strncpy(agent_modifie.statut, statut_text, sizeof(agent_modifie.statut) - 1); 
agent_modifie.statut[sizeof(agent_modifie.statut) - 1] = '\0'; 
// Appel de la fonction pour modifier ou ajouter l'agent if (modifier_ou_ajouter_agent("agents.txt", agent_modifie)) { gtk_label_set_text(GTK_LABEL(label_status), "Agent modifié ou ajouté avec succès."); } else { gtk_label_set_text(GTK_LABEL(label_status), "Erreur lors de la modification ou de l'ajout de l'agent."); } 
    
// Appel de la fonction pour modifier ou ajouter l'agent
    if (modifier_ou_ajouter_agent("agents.txt", agent_modifie)) {
        gtk_label_set_text(GTK_LABEL(label_status), "Agent modifié ou ajouté avec succès.");
    } else {
        gtk_label_set_text(GTK_LABEL(label_status), "Erreur lors de la modification ou de l'ajout de l'agent.");
    }
}



void
on_button315_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{

  GtkWidget *entry_cin = lookup_widget(GTK_WIDGET(button), "entry303");
 
    GtkWidget *label_status = lookup_widget(GTK_WIDGET(button), "label1025");

    // Vérification des widgets essentiels
    if (!entry_cin || !label_status) {
        g_print("Erreur : Widgets non trouvés.\n");
        return;
    }

    // Vérification du CIN
    const char *cin_text = gtk_entry_get_text(GTK_ENTRY(entry_cin));
    if (!cin_text || strlen(cin_text) != 8) {
        gtk_label_set_text(GTK_LABEL(label_status), "Erreur : Veuillez entrer un CIN valide (8 caractères).");
        return;
    }

    // Recherche de l'agent
    agent ag = chercher_agent("agents.txt", cin_text);
    if (ag.cin == -1) {
        gtk_label_set_text(GTK_LABEL(label_status), "Erreur : Agent introuvable.");
        return;
    }

    // Remplissage des champs
   

    // Mise à jour du label de statut
    gtk_label_set_text(GTK_LABEL(label_status), "Agent trouvé .");
}


void on_button314_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *entry_id, *label_status, *treeview9;
    const char *id_text;
    agent agent_trouve;
    const char *filename = "agents.txt";

    // Récupération des widgets
    entry_id = lookup_widget(GTK_WIDGET(button), "entry303");
    label_status = lookup_widget(GTK_WIDGET(button), "label1025");
    treeview9 = lookup_widget(GTK_WIDGET(button), "treeview3");

    // Vérification des widgets
    if (!entry_id || !label_status || !treeview9) {
        g_print("Erreur : Widgets non trouvés.\n");
        return;
    }

    // Configuration des colonnes si nécessaire
    GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeview9));
    if (!model) {
        GtkListStore *store = creer_model_treeview();
        gtk_tree_view_set_model(GTK_TREE_VIEW(treeview9), GTK_TREE_MODEL(store));
        configurer_columns_treeview(GTK_TREE_VIEW(treeview9));  // Configure les colonnes
        g_object_unref(store);  // Libère la référence locale
    }

    // Récupération de l'ID
    id_text = gtk_entry_get_text(GTK_ENTRY(entry_id));

    // Réinitialisation du TreeView
    GtkListStore *store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(treeview9)));
    gtk_list_store_clear(store);

    gboolean found = FALSE;

    // Recherche par CIN dans le fichier
    FILE *file = fopen(filename, "r");
    if (file != NULL) {
        agent_trouve = rechercher_agent(file, id_text);
        fclose(file);
    }

    // Si un agent a été trouvé, l'afficher dans le TreeView
    if (agent_trouve.cin[0] != '\0') {
        afficher_agent_dans_treeview(agent_trouve, GTK_TREE_VIEW(treeview9));
        found = TRUE;
    }

    // Affichage du message de statut
    if (found) {
        gtk_label_set_text(GTK_LABEL(label_status), "agent trouvé et affiché.");
    } else {
        gtk_label_set_text(GTK_LABEL(label_status), "Aucun agenttrouvé.");
    }
}



void on_button313_clicked(GtkButton *button, gpointer user_data) {
    // Récupération de l'ID dans l'Entry (entry19)
    GtkWidget *entry = lookup_widget(GTK_WIDGET(button), "entry303");
    const char *id = gtk_entry_get_text(GTK_ENTRY(entry));

    // Vérifier que l'ID n'est pas vide
    if (strlen(id) == 0) {
        GtkWidget *label_status = lookup_widget(GTK_WIDGET(button), "label1025");
        gtk_label_set_text(GTK_LABEL(label_status), "Erreur : ID non fourni.");
        return;
    }

    // Supprimer lagent du fichier
    if (supprimer_agentt("agents.txt", id)) {
        // Afficher un message de confirmation
        GtkWidget *label_status = lookup_widget(GTK_WIDGET(button), "label1025");
        gtk_label_set_text(GTK_LABEL(label_status), "agent supprimé avec succès.");
    } else {
        // Afficher un message d'erreur
        GtkWidget *label_status = lookup_widget(GTK_WIDGET(button), "label1025");
        gtk_label_set_text(GTK_LABEL(label_status), "Erreur : agent non trouvé.");
    }
}




// Fonction pour configurer les colonnes du TreeView si elles n'existent pas encore
void setup_treeview(GtkTreeView *treeview) {
    GtkCellRenderer *renderer;

    // Colonne Nom
    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_insert_column_with_attributes(treeview, -1, "Nom", renderer, "text", 0, NULL);

    // Colonne Description
    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_insert_column_with_attributes(treeview, -1, "Description", renderer, "text", 1, NULL);

    // Colonne ID
    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_insert_column_with_attributes(treeview, -1, "ID", renderer, "text", 2, NULL);

    // Colonne Date
    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_insert_column_with_attributes(treeview, -1, "Date", renderer, "text", 3, NULL);
}

// Bouton 317 : Recherche et affiche *une seule réservation* pour une date donnée
void on_button317_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *entry_date = lookup_widget(GTK_WIDGET(button), "entry304");
    GtkWidget *treeview = lookup_widget(GTK_WIDGET(button), "treeview2");
    GtkWidget *label_status = lookup_widget(GTK_WIDGET(button), "label1033");

    if (!entry_date || !label_status || !treeview) {
        g_print("Erreur : Widgets non trouvés.\n");
        return;
    }

    const char *date_text = gtk_entry_get_text(GTK_ENTRY(entry_date));
    if (!date_text || strlen(date_text) == 0) {
        gtk_label_set_text(GTK_LABEL(label_status), "Erreur : Veuillez entrer une date.");
        return;
    }

    int jour, mois, annee;
    if (sscanf(date_text, "%d/%d/%d", &jour, &mois, &annee) != 3 || jour <= 0 || mois <= 0 || annee <= 0) {
        gtk_label_set_text(GTK_LABEL(label_status), "Erreur : Format de date invalide.");
        return;
    }

    reserv res = chercher_reserv_par_date("reservation.txt", jour, mois, annee);

    GtkListStore *store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(treeview)));
    if (!store) {
        store = gtk_list_store_new(4, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT, G_TYPE_STRING);
        gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));
        setup_treeview(GTK_TREE_VIEW(treeview));
    }
    gtk_list_store_clear(store); // Nettoyer les anciennes données

    if (res.jour != -1) {
        GtkTreeIter iter;
        gtk_list_store_append(store, &iter);
        char date[20];
        snprintf(date, sizeof(date), "%02d/%02d/%d", res.jour, res.mois, res.annee);

        gtk_list_store_set(store, &iter,
                           0, res.nom,
                           1, res.description,
                           2, res.id,
                           3, date,
                           -1);
        gtk_label_set_text(GTK_LABEL(label_status), "Réservation trouvée.");
    } else {
        gtk_label_set_text(GTK_LABEL(label_status), "Aucune réservation trouvée pour cette date.");
    }
}

// Bouton 316 : Recherche et affiche *toutes les réservations* pour une date donnée
void on_button316_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *entry_date = lookup_widget(GTK_WIDGET(button), "entry304");
    GtkWidget *treeview = lookup_widget(GTK_WIDGET(button), "treeview2");
    GtkWidget *label_status = lookup_widget(GTK_WIDGET(button), "label1033");

    if (!entry_date || !label_status || !treeview) {
        g_print("Erreur : Widgets non trouvés.\n");
        return;
    }

    const char *date_text = gtk_entry_get_text(GTK_ENTRY(entry_date));
    if (!date_text || strlen(date_text) == 0) {
        gtk_label_set_text(GTK_LABEL(label_status), "Erreur : Veuillez entrer une date.");
        return;
    }

    int jour, mois, annee;
    if (sscanf(date_text, "%d/%d/%d", &jour, &mois, &annee) != 3 || jour <= 0 || mois <= 0 || annee <= 0) {
        gtk_label_set_text(GTK_LABEL(label_status), "Erreur : Format de date invalide.");
        return;
    }

    // Lire toutes les réservations correspondant à la date donnée
    FILE *file = fopen("reservation.txt", "r");
    if (!file) {
        gtk_label_set_text(GTK_LABEL(label_status), "Erreur : Impossible d'ouvrir le fichier.");
        return;
    }

    GtkListStore *store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(treeview)));
    if (!store) {
        store = gtk_list_store_new(4, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT, G_TYPE_STRING);
        gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));
        setup_treeview(GTK_TREE_VIEW(treeview));
    }
    gtk_list_store_clear(store); // Nettoyer les anciennes données

    char line[512];
    gboolean found = FALSE;
    while (fgets(line, sizeof(line), file)) {
        reserv temp;
        if (sscanf(line, "%d|%49[^|]|%49[^|]|%199[^|]|%14[^|]|%d|%d|%d",
                   &temp.id, temp.nom, temp.categorie, temp.description,
                   temp.telephone, &temp.jour, &temp.mois, &temp.annee) == 8) {
            if (temp.jour == jour && temp.mois == mois && temp.annee == annee) {
                GtkTreeIter iter;
                gtk_list_store_append(store, &iter);
                char date[20];
                snprintf(date, sizeof(date), "%02d/%02d/%d", temp.jour, temp.mois, temp.annee);

                gtk_list_store_set(store, &iter,
                                   0, temp.nom,
                                   1, temp.description,
                                   2, temp.id,
                                   3, date,
                                   -1);
                found = TRUE;
            }
        }
    }
    fclose(file);

    if (found) {
        gtk_label_set_text(GTK_LABEL(label_status), "Réservations affichées avec succès.");
    } else {
        gtk_label_set_text(GTK_LABEL(label_status), "Aucune réservation trouvée pour cette date.");
    }
}
