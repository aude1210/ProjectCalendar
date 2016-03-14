#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/*!
 * \file mainwindow.h
 * \brief Fichier gerant la fenetre principale de l'interface
 */
#include "timing.h"
#include "fenetreprojet.h"
#include "fenetresupmodprojet.h"
#include <iostream>
#include "activite.h"
#include "agenda.h"
#include "evenement.h"
#include "programmation.h"
#include "projet.h"
#include "projetmanager.h"
#include "tache.h"
#include "fenetrecomposite.h"
#include "fenetreunitaire.h"
#include <vector>
#include <unistd.h>
#include "export.h"
#include "fenetresupmodactivite.h"
#include "fenetresave.h"
#include "fenetreload.h"
#include "fenetreprecedence.h"
#include "fenetreactivite.h"
#include "vuesemaine.h"
#include "fenetresupmodtache.h"
#include "fenetreajoutprogrammation.h"
#include "qt.h"
#include "fenetresupmodprogrammation.h"
#include "treeview.h"
/*! \class MainWindow
   * \brief classe representant la fenetre principale de l'interface.
   *  La classe gère l'ouverture de la fenetre principale de l'interface
   */
class MainWindow: public QMainWindow
{

    Q_OBJECT

public :
    MainWindow(QWidget *parent=0);
    //Méthode permettant de redéfinir l'action effectuée en sortie de l'application (ici demander si sauvegarde ou non)
    void closeEvent(QCloseEvent *event);

public slots:
    void supmodProjet();/*!< Slot permettant d'ouvrir la fenetre de suppression et modification de projet*/
    void ajouterProjet();/*!< Slot permettant d'ouvrir la fenetre de création de projet*/
    void ajouterTacheUnitaire();/*!< Slot permettant d'ouvrir la fenetre de création d'une tache unitaire*/
    void ajouterTacheComposite();/*!< Slot permettant d'ouvrir la fenetre de création d'une tache composite*/
    void supModTache();/*!< Slot permettant d'ouvrir la fenetre de suppression et de modification de tache*/
    void nouvelleActivite();/*!< Slot permettant d'ouvrir la fenetre de création d'activite*/
    void supModActivite();/*!< Slot permettant d'ouvrir la fenetre de suppression et de modification d'activité*/
    void ajoutTacheCalendrier();/*!< Slot permettant d'ouvrir la fenetre de programmation d'une tache*/
    void ajoutActiviteCalendrier();/*!< Slot permettant d'ouvrir la fenetre de programmation d'une activite*/
    void ajouterPrecedence();/*!< Slot permettant d'ouvrir la fenetre de création de relation de précédence*/
    void supModProgrammation();/*!< Slot permettant d'ouvrir la fenetre de suppression et de modification de programmation*/
    void refreshViews();/*!< Slot permettant d'actualiser le treeview et le calendrier*/

protected:
    void chargerFichier(); /*!< Fonction permettant de charger un calendrier*/
    QTreeWidgetItem* tacheToTreeView(Tache* tache);
    QTreeWidgetItem* projetToTreeView(Projet* projet);


    QList<QTreeWidgetItem*>  treeProjets;
    QList<QTreeWidgetItem*> tachei;

    QWidget *mainWindow; /*!< Widget permettant de créer la fenetre*/
    QTabWidget *barreOnglet; /*!< Widget permettant de créer une barre d'onglet*/
    QWidget *onglet1;/*!< Widget permettant de créer un onglet*/
    QWidget *onglet2;/*!< Widget permettant de créer un onglet*/
    QWidget *onglet3;/*!< Widget permettant de créer un onglet*/

    VueSemaine* Semaine; /*!< Permet de créer le calendrier en vue par semaine*/

    //onglet 2

    QLabel* label1;
    QLabel* label2;
    QLabel* label3;
    QLabel* label4;

    QPushButton* nouveau;/*!< Bouton permettant de créer un nouveau projet*/
    QPushButton* supmod;/*!< Bouton permettant de modifier ou supprimer un projet*/
    QPushButton* unitaire;/*!< Bouton permettant de créer une nouvelle tache unitaire*/
    QPushButton* precedence;/*!< Bouton permettant de créer une nouvelle relation de précédence*/
    QPushButton* composite;/*!< Bouton permettant de créer une nouvelle tache composite*/
    QPushButton *supmodtache;/*!< Bouton permettant de modifer ou supprimer une tache*/
    QPushButton* ajoutProgActivite;/*!< Bouton permettant de programmer une activité*/
    QPushButton* refresh;/*!< Bouton permettant d'actualiser le treeview et le calendrier*/
    QPushButton *ajoutProgTache;/*!< Bouton permettant de programmer une tache*/
    QPushButton* supModProg;/*!< Bouton permettant de modifier ou de supprimer une programmation*/
    QPushButton* nouvact;/*!< Bouton permettant de créer une nouvelle activité*/
    QPushButton* supmodact;/*!< Bouton permettant de modifier ou supprimer une activité*/
    QPushButton* quitter; /*!< Bouton permettant de quitter*/

    TreeView* tree;

    QGroupBox* groupeProjet;
    QGroupBox* groupeTache;
    QGroupBox* groupeAjout;
    QGroupBox* groupeTree;
    QGroupBox* groupeActivite;


    QVBoxLayout* layoutBoutonProjet;

    QHBoxLayout* layoutAjoutTache;
    QVBoxLayout* layoutTache;

    QHBoxLayout* layoutAjoutProg;
    QVBoxLayout* layoutProg;

    QHBoxLayout* layoutTree;

    QVBoxLayout* layoutDemiOnglet2;
    QHBoxLayout* layoutOnglet2;


    QVBoxLayout * layoutBoutonActivite;


    QHBoxLayout *layoutHorizontal2;
    QVBoxLayout* layout;


};

#endif // MAINWINDOW_H

