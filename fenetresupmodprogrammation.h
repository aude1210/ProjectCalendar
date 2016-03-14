#ifndef FENETRESUPMODPROGRAMMATION
#define FENETRESUPMODPROGRAMMATION

/*!
 * \file fenetresupmodprogrammation.h
 * \brief Fichier gerant la fenetre de suppression et de modification d'une programmation
 */
#include "qt.h"
#include "agenda.h"
/*! \class FenetreSupModProg
   * \brief classe representant la fenetre de suppression et de modification d'une programmation.
   *
   *  La classe gère l'ouverture d'une fenetre permettant la suppression et la modification d'une programmation.
   *  Cette classe réutilise donc les méthodes de Agenda.
   */

class FenetreSupModProg : public QMainWindow{
    Q_OBJECT
public:
    FenetreSupModProg(QMainWindow* parent = 0);
private:
    QWidget *fenetreSupModProg; /*!< Widget permettant de créer la fenetre*/
    QGroupBox* groupeSupModProg; /*!< Groupe permettant d'afficher le Vlayout1 à l'intérieur*/

    QComboBox* idEvenement;/*!< Liste déroulante permettant de choisir la programmation de l'évènement à supprimer ou modifier*/
    QLineEdit* titreEvenement;/*!< Zone de texte permettant de renseigner le titre de l'évènement programmé*/

    QDateTimeEdit* dispoEvenement;/*!< Champs datetime permettant de renseigner la date et l'heure de disponibilité de l'évènement programmé*/
    QDateTimeEdit* echeanceEvenement;/*!< Champs datetime permettant de renseigner la date et l'heure d'échéance de l'évènement programmé*/
    QDateTimeEdit* dateHeureProg;/*!< Champs datetime permettant de renseigner la date et l'heure de programmation de l'évènement programmé*/

    QPushButton *modifierProg; /*!< Bouton permettant d'enregistrer les modifications apportées à la programmation d'un évènement*/
    QPushButton* supprimerProg; /*!< Bouton permettant de supprimer la programmation d'un évènement*/
    QPushButton* reinitProg;/*!< Bouton permettant d'annuler les modifications effectuées avant enregistrement*/

    QFormLayout* layoutForm; /*!< layout permettant de rassembler les différentes zones d'édition sur un plan vertical*/
    QHBoxLayout* layoutButtons; /*!< layout permettant de rassembler les boutons sur un plan horizontal*/
    QVBoxLayout* layout;/*!< layout permettant d'afficher le groupeSupModProg*/
    QVBoxLayout* Vlayout1; /*!< layout permettant de rassembler deux layout sur un plan vertical*/

    vector<QString> listeTitresEvenements;
    vector<Evenement*> listeEvenements;
    vector<QDateTime> listeDisposEvenements;
    vector<QDateTime> listeEcheancesEvenements;
    vector<QDateTime> listeProgsEvenements;

private slots:
    void updateInfosEvenement();/*!< Slot permettant de charger les informations sur une programmation sélectionnée*/
    void supprimerProgrammation();/*!< Slot permettant la suppression d'une programmation en appelant une méthode de la classe Agenda*/
    void modifierProgrammtion(); /*!< Slot permettant d'enregistrer les modifications d'une programmation*/
};

#endif // FENETRESUPMODPROGRAMMATION

