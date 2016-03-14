#ifndef FENETRESUPMODTACHE
#define FENETRESUPMODTACHE

/*!
 * \file fenetresupmodtache.h
 * \brief Fichier gerant la fenetre de suppression et de modification d'une tache
 */
#include<QtWidgets>
#include"mainwindow.h"


/*! \class FenetreSupModTache
   * \brief classe representant la fenetre de suppression et de modification d'une tache.
   *
   *  La classe gère l'ouverture d'une fenetre permettant la suppression et la modification d'une tache.
   *  Cette classe réutilise donc les méthodes de Projet.
   */

class FenetreSupModTache : public QMainWindow
{
    Q_OBJECT
public:
    FenetreSupModTache(QMainWindow *parent=0);

private slots:
    void modifier();/*!< Slot permettant d'enregistrer les modifications d'une tache*/
    void checkDate(const QDateTime &d);/*!< Slot permettant de vérifier la concordance des dates*/
    void supprimer();/*!< Slot permettant la suppression d'une tache en appelant une méthode de la classe Projet*/
    void load();/*!< Slot permettant de charger les informations sur une tache sélectionnée*/
    void loadTache();/*!< Slot permettant de charger les taches d'un projet sélectionné*/

private:
    QComboBox *idProjet; /*!< Liste déroulante permettant de choisir un projet dans lequel se situe une tache à supprimer ou modifier*/
    QComboBox *idTache; /*!< Liste déroulante permettant de choisir la tache à supprimer ou modifier*/
    QComboBox *supprimerPrecedence; /*!< Liste déroulante permettant de choisir une relation de précédence que l'on souhaite supprimer*/
    QComboBox *supprimerSousTache;/*!< Liste déroulante permettant de choisir une sous tache que l'on souhaite supprimer*/
    QLineEdit *titreTache;/*!< Zone de texte permettant de renseigner le titre de le titre*/

    QDateTimeEdit *dispoTache;/*!< Champs datetime permettant de renseigner la date et l'heure de disponibilité de la tache*/
    QDateTimeEdit *echeanceTache;/*!< Champs datetime permettant de renseigner la date et l'heure d'échéance de la tache*/

    QTimeEdit *dureeTache;/*!< Champs durée permettant de renseigner la durée de la tache*/

    QPushButton *supp;/*!< Bouton permettant de supprimer une tache*/
    QPushButton* ann; /*!< Bouton permettant d'annuler les modifications effectuées avant enregistrement*/
    QPushButton* mod;/*!< Bouton permettant d'enregistrer les modifications apportées à une tache*/

    QGroupBox *groupeTache;/*!< Groupe permettant d'afficher le layoutTache à l'intérieur*/

    QHBoxLayout *horizontal;/*!< layout permettant de rassembler les boutons sur un plan horizontal*/
    QFormLayout *layout21Form;/*!< layout permettant de rassembler les différentes zones d'édition sur un plan vertical*/
    QVBoxLayout* layoutTache;/*!< layout permettant de rassembler deux layout sur un plan vertical*/
    QHBoxLayout *layout;/*!< layout permettant d'afficher le groupeTache*/

    QWidget *fenetreSupModTache;/*!< Widget permettant de créer la fenetre*/
};


#endif // FENETRESUPMODTACHE

