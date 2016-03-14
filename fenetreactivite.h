#ifndef FENETREACTIVITE
#define FENETREACTIVITE

/*!
 * \file fenetreactivite.h
 * \brief Fichier gerant la fenetre de création d'une activité
 */

#include <QMainWindow>
#include <QtWidgets>

/*! \class FenetreActivite
   * \brief classe representant la fenetre de création des Activite.
   *
   *  La classe gère l'ouverture d'une fenetre permettant la création d'Activite.
   *  Cette classe réutilise donc les méthodes de ActiviteManager.
   */

class FenetreActivite : public QMainWindow
{
    Q_OBJECT
public:
    FenetreActivite(QMainWindow *parent=0);

private slots:
    void saveActivite(); /*!< Slot permettant d'ajouter une activité en appelant une méthode de la classe ActiviteManager*/
    void checkDate(const QDateTime &d);/*!< Slot permettant de vérifier la concordance des dates*/
    void checkType();/*!< Slot permettant de gérer l'apparition de certains champs en fonction du choix du type d'activité*/
    void checkModifier();/*!< Slot permettant l'affichage du bouton enregistrerActivite qu'une fois tous les champs complétés*/

private:
    QLineEdit *idActivite; /*!< Zone de texte permettant de renseigner l'identifiant de l'activite*/
    QCheckBox *reunion;/*!< Case à cocher permettant de renseigner si l'activite est une réunion*/
    QCheckBox *rdv;/*!< Case à cocher permettant de renseigner si l'activite est un rdv*/
    QLineEdit *titreActivite;/*!< Zone de texte permettant de renseigner le titre de l'activite*/
    QDateTimeEdit *dispoActivite; /*!< Champs datetime permettant de renseigner la date et l'heure de disponibilité de l'activite*/
    QDateTimeEdit *echeanceActivite; /*!< Champs datetime permettant de renseigner la date et l'heure d'échéance de l'activite*/
    QTimeEdit *dureeActivite; /*!< Champs durée permettant de renseigner la durée de l'activite*/
    QLineEdit *lieuActivite;/*!< Zone de texte permettant de renseigner le lieu de l'activite*/
    QLineEdit *personne;/*!< Zone de texte permettant de renseigner l'interlocuteur du rdv*/

    QPushButton *enregistrerActivite; /*!< Bouton permettant d'ajouter une nouvelle activite*/
    QPushButton* quitter; /*!< Bouton permettant de quitter la fenetre*/

    QGroupBox* groupeNouvelleActivite; /*!< Groupe permettant d'afficher le layoutNouvelleActivite à l'intérieur*/
    QHBoxLayout *horizontal; /*!< layout permettant de rassembler les boutons sur un plan horizontal*/
    QFormLayout *layout21Form; /*!< layout permettant de rassembler les différentes zones d'édition sur un plan vertical*/
    QVBoxLayout* layoutNouvelleActivite; /*!< layout permettant de rassembler deux layout sur un plan vertical*/
    QHBoxLayout* layout; /*!< layout permettant d'affiche le groupeNouvelleActivite*/

    QWidget *fenetreActivite; /*!< Widget permettant de créer la fenetre*/
};

#endif // FENETREACTIVITE

