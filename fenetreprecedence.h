#ifndef FENETREPRECEDENCE_H
#define FENETREPRECEDENCE_H

/*!
 * \file fenetreprecedence.h
 * \brief Fichier gerant la fenetre de création de précédence entre deux taches
 */

#include<QtWidgets>
#include"projetmanager.h"

/*! \class FenetrePrecedence
   * \brief classe representant la fenetre de création de précédence entre deux taches.
   *
   *  La classe gère l'ouverture d'une fenetre permettant la création de précédences entre deux taches.
   *  Cette classe réutilise donc les méthodes de Tache.
   */

class FenetrePrecedence : public QMainWindow
{
    Q_OBJECT

public:
    FenetrePrecedence(QMainWindow* parent=0);

private slots :
    void ajouterPrecedence();/*!< Slot permettant d'ajouter une précédence ente deux taches en appelant une méthode de la classe Tache*/
    void load();/*!< Slot permettant de charger les différentes taches d'un projet choisi*/
    void checkModifier(); /*!< Slot permettant l'affichage du bouton ajouter qu'une fois tous les champs complétés et cohérents*/

private:
    QWidget *fenetrePrecedence;/*!< Widget permettant de créer la fenetre*/

    QComboBox* projets; /*!< Liste déroulante permettant de choisir le projet dans lequel on veut créer des relations de précédence*/
    QComboBox* taches; /*!< Liste déroulante permettant de choisir la tache sur laquelle on veut créer une relation de précédence*/
    QComboBox* precedente; /*!< Liste déroulante permettant de choisir la tache que l'on souhaite comme étant la tache précédente de la tache précédemment sélectionnée*/

    QPushButton* ajouter;/*!< Bouton permettant d'ajouter une relation de précédence*/
    QPushButton* quitter; /*!< Bouton permettant de quitter la fenetre*/

    QHBoxLayout* layoutHorizontal;/*!< layout permettant de rassembler les boutons sur un plan horizontal*/
    QFormLayout* layoutFormulaire;/*!< layout permettant de rassembler les différentes zones d'édition sur un plan vertical*/
    QVBoxLayout* layout; /*!< layout permettant de rassembler deux layout sur un plan vertical*/
};

#endif // FENETREPRECEDENCE_H

