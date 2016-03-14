#ifndef FENETREPROJET_H
#define FENETREPROJET_H
/*!
 * \file fenetreprojet.h
 * \brief Fichier gerant la fenetre de création de projets
 */

#include<QtWidgets>
#include"mainwindow.h"
#include "projetmanager.h"


/*! \class FenetreProjet
   * \brief classe representant la fenetre de création de projets.
   *
   *  La classe gère l'ouverture d'une fenetre permettant la création de projets.
   *  Cette classe réutilise donc les méthodes de ProjetManager.
   */
class FenetreProjet : public QMainWindow
{
    Q_OBJECT

public:
    FenetreProjet(QMainWindow *parent=0);

private slots:
    void saveProjet();/*!< Slot permettant d'ajouter un projet en appelant une méthode de la classe ProjetManager*/
    void checkDate(const QDateTime &d); /*!< Slot permettant de vérifier la concordance des dates*/
    void checkModifier();/*!< Slot permettant l'affichage du bouton enregistrerProjet qu'une fois tous les champs complétés*/

private:
    QLineEdit *idProjet;/*!< Zone de texte permettant de renseigner l'identifiant du projet*/
    QLineEdit *titreProjet;/*!< Zone de texte permettant de renseigner le titre du projet*/

    QTextEdit* descriptionProjet;/*!< Zone de texte permettant de renseigner la description du projet*/

    QDateTimeEdit *dispoProjet;/*!< Champs datetime permettant de renseigner la date et l'heure de disponibilité du projet*/
    QDateTimeEdit *echeanceProjet;/*!< Champs datetime permettant de renseigner la date et l'heure d'échéance du projet*/

    QPushButton *enregistrerProjet;/*!< Bouton permettant d'ajouter un nouveau projet*/
    QPushButton* quitter;/*!< Bouton permettant de quitter la fenetre*/

    QGroupBox* groupeNouveauProjet; /*!< Groupe permettant d'afficher le layoutNouveauProjet à l'intérieur*/

    QHBoxLayout*horizontal; /*!< layout permettant de rassembler les boutons sur un plan horizontal*/
    QFormLayout *layout21Form;/*!< layout permettant de rassembler les différentes zones d'édition sur un plan vertical*/
    QVBoxLayout* layoutNouveauProjet;/*!< layout permettant de rassembler deux layout sur un plan vertical*/
    QHBoxLayout* layout;/*!< layout permettant d'affiche le groupeNouveauProjet*/

    QWidget *fenetreProjet;/*!< Widget permettant de créer la fenetre*/
};

#endif // FENETREPROJET_H

