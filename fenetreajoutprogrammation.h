#ifndef FENETREAJOUTPROGRAMMATION
#define FENETREAJOUTPROGRAMMATION
/*!
 * \file fenetreajoutprogrammtion.h
 * \brief Fichier gerant la fenetre de création de programmation
 */
#include "qt.h"
#include "agenda.h"
#include "projetmanager.h"
#include "projet.h"
#include"activitemanager.h"
#include "activite.h"


/*! \class FenetreAjoutProgTache
   * \brief classe representant la fenetre de création de la programmation d'une tache.
   *
   *  La classe gère l'ouverture d'une fenetre permettant la création de la programmtion d'une tache.
   *  Cette classe réutilise donc les méthodes de Agenda.
   */
class FenetreAjoutProgTache : public QMainWindow{
    Q_OBJECT
public:
    FenetreAjoutProgTache(QMainWindow* parent=0);
private:
    QWidget *fenetreAjoutProgTache; /*!< Widget permettant de créer la fenetre*/

    QComboBox* idProjet; /*!< Liste déroulante permettant de choisir le projet de la tache à programmer*/
    QComboBox* idTache;/*!< Liste déroulante permettant de choisir la tache à programmer*/
    QLineEdit* titreTache;/*!< Zone de texte permettant de renseigner le titre de la tache*/

    QDateTimeEdit *dateHeureTache; /*!< Champs datetime permettant de renseigner la date et l'heure de la programmtion de la tache*/
    QDateTimeEdit* dispoTache; /*!< Champs datetime readonly permettant d'afficher la date de disponibilite de la tache sélectionnée*/
    QDateTimeEdit* echeanceTache; /*!< Champs datetime readonly permettant d'afficher la date d'échéance de la tache sélectionnée*/

    QPushButton *enregistrerProgTache; /*!< Boutton permettant d'ajouter une nouvelle programmation*/
    QPushButton* quitterProgTache;/*!< Boutton permettant de quitter la fenetre en cours*/

    QGroupBox *groupeNouvelleProgTache;
    QFormLayout *layoutChoixProjetTache; /*!< layout permettant de rassembler les différentes zones d'édition sur un plan vertical*/
    QHBoxLayout* layoutEnregistrerQuitter; /*!< layout permettant de rassembler les différentes bouttons sur un plan horizontal*/
    QVBoxLayout* Vlayout; /*!< layout permettant de rassembler les deux précédents layout sur un plan vertical*/
    QHBoxLayout *layout;


private slots:
    void updateIdTache(QString s); /*!< Slot permettant de charger les taches présentes dans le projet sélectionné*/
    void updateInfosTache(QString s);/*!< Slot permettant de charger le titre de la tache sélectionnée*/
    void saveProg(); /*!< Slot permettant de sauvegarder la programmation*/
};


/*! \class FenetreAjoutProgActivite
   * \brief classe representant la fenetre de création de la programmation d'une activite.
   *
   *  La classe gère l'ouverture d'une fenetre permettant la création de la programmtion d'une activite.
   *  Cette classe réutilise donc les méthodes de Agenda.
   */
class FenetreAjoutProgActivite : public QMainWindow{
    Q_OBJECT
public:
    FenetreAjoutProgActivite(QMainWindow* parent=0);
private:
    QWidget *fenetreAjoutProgActivite; /*!< Widget permettant de créer la fenetre*/

    QComboBox* idActivite; /*!< Liste déroulante permettant de choisir l'activité à programmer*/
    QLineEdit* titreActivite;/*!< Zone de texte permettant de renseigner le titre de l'activite*/

    QDateTimeEdit* dispoActivite; /*!< Champs datetime readonly permettant d'afficher la date de disponibilite de l'activité sélectionnée*/
    QDateTimeEdit* echeanceActivite; /*!< Champs datetime readonly permettant d'afficher la date d'échéance de l'activité sélectionnée*/
    QDateTimeEdit *dateHeureActivite;/*!< Champs datetime permettant de renseigner la date et l'heure de la programmtion de l'activité*/

    QPushButton *enregistrerProgActivite; /*!< Bouton permettant d'ajouter une nouvelle programmation*/
    QPushButton* quitterProgActivite;/*!< Bouton permettant de quitter la fenetre en cours*/


    QFormLayout *layoutChoixActivite;/*!< layout permettant de rassembler les différentes zones d'édition sur un plan vertical*/
    QHBoxLayout* layoutEnregistrerQuitter;/*!< layout permettant de rassembler les différentes boutons sur un plan horizontal*/
    QVBoxLayout* Vlayout;/*!< layout permettant de rassembler les deux précédents layout sur un plan vertical*/

private slots:
    void updateInfosActivite(QString s);/*!< Slot permettant de charger le titre de l'activité sélectionnée*/
    void saveActivite();/*!< Slot permettant de sauvegarder la programmation*/
};

#endif // FENETREAJOUTPROGRAMMATION

