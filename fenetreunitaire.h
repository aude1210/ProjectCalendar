#ifndef FENETREUNITAIRE
#define FENETREUNITAIRE

/*!
 * \file fenetreunitaire.h
 * \brief Fichier gerant la fenetre de création d'une tache unitaire
 */
#include "qt.h"
#include"mainwindow.h"

/*! \class FenetreUnitaire
   * \brief classe representant la fenetre de création des taches unitaires.
   *
   *  La classe gère l'ouverture d'une fenetre permettant la création de taches unitaires.
   *  Cette classe réutilise donc les méthodes de Projet.
   */
class FenetreUnitaire : public QMainWindow
{
    Q_OBJECT
public :
    FenetreUnitaire(QMainWindow* parent=0);

private slots:
    void enregistrerTacheUnitaire();/*!< Slot permettant d'ajouter une tache unitaire en appelant une méthode de la classe Projet*/
    void checkDate(const QDateTime &d);/*!< Slot permettant de vérifier la concordance des dates*/
    void load();/*!< Slot permettant de charger les différentes taches unitaires d'un projet choisi*/
    void checkModifier();/*!< Slot permettant l'affichage du bouton enregistrerUnitaire qu'une fois tous les champs complétés*/

private:
    QWidget *fenetreUnitaire; /*!< Widget permettant de créer la fenetre*/

    QLineEdit* idUnitaire;/*!< Zone de texte permettant de renseigner l'identifiant de la tache unitaire*/
    QLineEdit* titreUnitaire; /*!< Zone de texte permettant de renseigner le titre de la tache unitaire*/
    QComboBox* idProjet;/*!< Liste déroulante permettant de renseigner le projet dans lequel on veut ajouter la tache unitaire*/
    QComboBox* idComposite; /*!< Liste déroulante permettant de renseigner la tache composite dont on veut créer en tant que sous tache une tache unitaire(on peut ne sélectionner aucune tache si on souhaite créer la tache unitaire directement dans le projet)*/

    QDateTimeEdit *dispoProjet;/*!< Champs datetime permettant de renseigner la date et l'heure de disponibilité du projet*/
    QDateTimeEdit *echeanceProjet;/*!< Champs datetime permettant de renseigner la date et l'heure d'échéance du projet*/
    QDateTimeEdit *dispoUnitaire;/*!< Champs datetime permettant de renseigner la date et l'heure de disponibilité de la tache unitaire*/
    QDateTimeEdit *echeanceUnitaire; /*!< Champs datetime permettant de renseigner la date et l'heure d'échéance de la tache unitaire*/
    QTimeEdit* dureeUnitaire;/*!< Champs durée permettant de renseigner la durée de la tache unitaire*/
    QCheckBox* preemptive;/*!< Case à cocher permettant de renseigner si la tache unitaire est préemptive*/

    QPushButton *enregistrerUnitaire;/*!< Bouton permettant d'ajouter une nouvelle tache unitaire*/
    QPushButton* quitterUnitaire;/*!< Bouton permettant de quitter la fenetre*/

    QGroupBox* groupeUnitaire;/*!< Groupe permettant d'afficher le layoutUnitaire à l'intérieur*/

    QFormLayout *layoutTitreProjetDispoEcheanceDuree;/*!< layout permettant de rassembler les différentes zones d'édition sur un plan vertical*/
    QHBoxLayout* layoutEnregistrerQuitter;/*!< layout permettant de rassembler les boutons sur un plan horizontal*/
    QVBoxLayout* layoutUnitaire; /*!< layout permettant de rassembler deux layout sur un plan vertical*/
    QVBoxLayout *layout; /*!< layout permettant d'affiche le groupeUnitaire*/

};


#endif // FENETREUNITAIRE

