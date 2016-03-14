#ifndef FENETRECOMPOSITE_H
#define FENETRECOMPOSITE_H
/*!
 * \file fenetrecomposite.h
 * \brief Fichier gerant la fenetre de création d'une tache composite
 */

#include<QtWidgets>

/*! \class FenetreComposite
   * \brief classe representant la fenetre de création des taches composites.
   *
   *  La classe gère l'ouverture d'une fenetre permettant la création de taches composites.
   *  Cette classe réutilise donc les méthodes de Projet.
   */

class FenetreComposite : public QMainWindow
{
    Q_OBJECT
public :
    FenetreComposite(QMainWindow *parent=0);

private slots:
    void enregistrerTacheComposite(); /*!< Slot permettant d'ajouter une tache composite en appelant une méthode de la classe Projet*/
    void checkDate(const QDateTime &d); /*!< Slot permettant de vérifier la concordance des dates*/
    void load();/*!< Slot permettant de charger les différentes taches composites d'un projet choisi*/
    void checkModifier();/*!< Slot permettant l'affichage du bouton enregistrerComposite qu'une fois tous les champs complétés*/

private:
    QWidget *tacheComposite; /*!< Widget permettant de créer la fenetre*/

    QComboBox* idProjet; /*!< Liste déroulante permettant de renseigner le projet dans lequel on veut ajouter la tache composite*/
    QComboBox* idSousCompo; /*!< Liste déroulante permettant de renseigner la tache composite dont on veut créer en tant que sous tache une tache composite(on peut ne sélectionner aucune tache si on souhaite créer la tache composite directement dans le projet)*/
    QLineEdit* idComposite;/*!< Zone de texte permettant de renseigner l'identifiant de la tache composite*/
    QLineEdit* titreComposite;  /*!< Zone de texte permettant de renseigner le titre de la tache composite*/

    QDateTimeEdit *dispoProjet;/*!< Champs datetime permettant de renseigner la date et l'heure de disponibilité du projet*/
    QDateTimeEdit *echeanceProjet;/*!< Champs datetime permettant de renseigner la date et l'heure d'échéance du projet*/
    QDateTimeEdit *dispoComposite;  /*!< Champs datetime permettant de renseigner la date et l'heure de disponibilité de la tache composite*/
    QDateTimeEdit *echeanceComposite;  /*!< Champs datetime permettant de renseigner la date et l'heure d'échéance de la tache composite*/

    QPushButton *enregistrerComposite;/*!< Bouton permettant d'ajouter une nouvelle tache composite*/
    QPushButton* quitterComposite; /*!< Bouton permettant de quitter la fenetre*/

    QGroupBox* groupeComposite;/*!< Groupe permettant d'afficher le layoutTitreProjetDispoEcheanceDuree à l'intérieur*/

    QFormLayout *layoutTitreProjetDispoEcheanceDuree; /*!< layout permettant de rassembler les différentes zones d'édition sur un plan vertical*/
    QHBoxLayout* layoutEnregistrerQuitter; /*!< layout permettant de rassembler les boutons sur un plan horizontal*/
    QVBoxLayout* layoutComposite; /*!< layout permettant de rassembler deux layout sur un plan vertical*/
    QVBoxLayout *layout;/*!< layout permettant d'affiche le groupeComposite*/
};


#endif // FENETRECOMPOSITE_H

