#ifndef FENETRESUPMODACTIVITE
#define FENETRESUPMODACTIVITE

/*!
 * \file fenetresupmodactivite.h
 * \brief Fichier gerant la fenetre de suppression et de modification d'une activité
 */
#include<QtWidgets>
#include"mainwindow.h"

/*! \class FenetreSupModActivite
   * \brief classe representant la fenetre de suppression et de modification d'une activité.
   *
   *  La classe gère l'ouverture d'une fenetre permettant la suppression et la modification d'une activite.
   *  Cette classe réutilise donc les méthodes de ActiviteManager.
   */

class FenetreSupModActivite : public QMainWindow
{
    Q_OBJECT
public:
    FenetreSupModActivite(QMainWindow *parent=0);

private slots:
    void modifier();/*!< Slot permettant d'enregistrer les modifications d'une activité*/
    void checkDate(const QDateTime &d);/*!< Slot permettant de vérifier la concordance des dates*/
    void supprimer();/*!< Slot permettant la suppression d'une activité en appelant une méthode de la classe ActiviteManager*/
    void load();/*!< Slot permettant de charger les informations sur une activité sélectionnée*/

private:
    QComboBox *idActivite;/*!< Liste déroulante permettant de choisir l'activite à supprimer ou modifier*/
    QLineEdit *titreActivite; /*!< Zone de texte permettant de renseigner le titre de l'activite*/


    QDateTimeEdit *dispoActivite;/*!< Champs datetime permettant de renseigner la date et l'heure de disponibilité de l'activite*/
    QDateTimeEdit *echeanceActivite;/*!< Champs datetime permettant de renseigner la date et l'heure d'échéance de l'activite*/

    QTimeEdit *dureeActivite;/*!< Champs durée permettant de renseigner la durée de l'activite*/
    QLineEdit *lieuActivite;/*!< Zone de texte permettant de renseigner le lieu de l'activite*/
    QLineEdit *personne;/*!< Zone de texte permettant de renseigner l'interlocuteur du rdv*/
    QLineEdit *ajoutParticipant;/*!< Zone de texte permettant d'ajouter un membre à une réunion*/
    QComboBox *supprimerParticipant;/*!< Liste déroulante permettant de choisir un membre d'une réunion à supprimer*/

    QPushButton *supp; /*!< Bouton permettant de supprimer une activite*/
    QPushButton* ann;  /*!< Bouton permettant d'annuler les modifications effectuées avant enregistrement*/
    QPushButton* mod;  /*!< Bouton permettant d'enregistrer les modifications apportées à une activité*/

    QGroupBox *groupeActivite; /*!< Groupe permettant d'afficher le layoutActivite à l'intérieur*/

    QHBoxLayout *horizontal; /*!< layout permettant de rassembler les boutons sur un plan horizontal*/
    QFormLayout *layout21Form;/*!< layout permettant de rassembler les différentes zones d'édition sur un plan vertical*/
    QVBoxLayout* layoutActivite;/*!< layout permettant de rassembler deux layout sur un plan vertical*/
    QHBoxLayout *layout;/*!< layout permettant d'afficher le groupeActivite*/

    QWidget *fenetreSupModActivite;/*!< Widget permettant de créer la fenetre*/
};


#endif // FENETRESUPMODACTIVITE

