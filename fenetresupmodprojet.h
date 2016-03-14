#ifndef FENETRESUPPRIMERPROJET
#define FENETRESUPPRIMERPROJET

/*!
 * \file fenetresupmodprojet.h
 * \brief Fichier gerant la fenetre de suppression et de modification d'un projet
 */

#include<QtWidgets>
#include"mainwindow.h"
/*! \class FenetreSupModProjet
   * \brief classe representant la fenetre de suppression et de modification d'un projet.
   *
   *  La classe gère l'ouverture d'une fenetre permettant la suppression et la modification d'un projet.
   *  Cette classe réutilise donc les méthodes de ProjetManager.
   */

class FenetreSupModProjet : public QMainWindow
{
    Q_OBJECT
public:
    FenetreSupModProjet(QMainWindow *parent=0);

private slots:
    void modifier();/*!< Slot permettant d'enregistrer les modifications d'un projet*/
    void checkDate(const QDateTime &d);/*!< Slot permettant de vérifier la concordance des dates*/
    void supprimer();/*!< Slot permettant la suppression d'un projet en appelant une méthode de la classe ProjetManager*/
    void load();/*!< Slot permettant de charger les informations sur un projet sélectionné*/

private:
    QComboBox *idProjet;/*!< Liste déroulante permettant de choisir le projet à supprimer ou modifier*/
    QLineEdit *titreProjet; /*!< Zone de texte permettant de renseigner le titre du projet*/

    QTextEdit* descriptionProjet; /*!< Zone de texte permettant de renseigner la description du projet*/

    QDateTimeEdit *dispoProjet;/*!< Champs datetime permettant de renseigner la date et l'heure de disponibilité du projet*/
    QDateTimeEdit *echeanceProjet;/*!< Champs datetime permettant de renseigner la date et l'heure d'échéance du projet*/

    QPushButton *supp; /*!< Bouton permettant de supprimer un projet*/
    QPushButton* ann;/*!< Bouton permettant d'annuler les modifications effectuées avant enregistrement*/
    QPushButton* mod; /*!< Bouton permettant d'enregistrer les modifications apportées à un projet*/

    QGroupBox* groupeProjet; /*!< Groupe permettant d'afficher le layoutProjet à l'intérieur*/

    QHBoxLayout*horizontal;/*!< layout permettant de rassembler les boutons sur un plan horizontal*/
    QFormLayout *layout21Form;/*!< layout permettant de rassembler les différentes zones d'édition sur un plan vertical*/
    QVBoxLayout* layoutProjet;/*!< layout permettant de rassembler deux layout sur un plan vertical*/
    QHBoxLayout* layout;/*!< layout permettant d'afficher le groupeProjet*/

    QWidget *fenetreSupModProjet;/*!< Widget permettant de créer la fenetre*/
};

#endif // FENETRESUPPRIMERPROJET

