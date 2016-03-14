#ifndef VUESEMAINE
#define VUESEMAINE

/*!
 * \file vuesemaine.h
 * \brief Fichier de déclaration des widgets ChoixSemaine et VueSemaine, permettant la vue 7 jours
 */

#include "qt.h"
#include "agenda.h"

/*! \class ChoixSemaine
   * \brief Widget permettant le choix de la semaine à afficher
   *
   *  Classe dérivée de QDateEdit permettant de naviguer de semaine en semaine dans le calendrier
   *
   */

class ChoixSemaine : public QDateEdit{
    Q_OBJECT
public slots:
    void semaineSuivante(); /*!< Slot actualisant la valeur du widget à la semaine suivante */
    void semainePrecedente();/*!< Slot actualisant la valeur du widget à la semaine précédente */
public:
    ChoixSemaine(const QDate& date, QDateEdit* parent=0) : QDateEdit(date,parent){}
};

/*! \class VueSemaine
   * \brief Affiche les programmation des événements sous forme de vue 7 jours
   *
   *  Widget affichant les programmations dans un tableau représentant les jours d'une semaine. On peut naviguer de semaine en semaine ou choisir une date à visualiser directement.
   *
   */

class VueSemaine : public QWidget{

    Q_OBJECT

private:
    QStringList ListeJours; /*!< Liste contenant l'ensemble des jours de la semaine sélectionnée sous la forme "jour JJ/MM" pour affichage des titres de colonnes */
    QStringList ListeHeures; /*!< Liste contenant l'ensemble des heures d'une journée sous la forme "HHhMM" pour affichage des titres de lignes */
    QTableView* vueSemaine; /*!< Widget QTableView qui représente la vue d'une semaine */
    ChoixSemaine* choixSemaine; /*< Permet de choisir la semaine à afficher */
    QStandardItemModel* model; /*< Modèle de vueSemaine. Permet de définir les headers de lignes et de colonnes */
    QHBoxLayout *Hlayout1; /*< Layout rassemblant les boutons semaineSuivante et semainePrecedente et le widget de choix de semaine */
    QVBoxLayout* Vlayout; /*< Layout vertical rassemblant Hlayout1 et la vue semaine */
    QPushButton *semaineSuivante, *semainePrecedente; /*< Boutons permettant de passer à la semaine précédente et suivante */

public:
    VueSemaine(QWidget* parent=0);
    /*!
         *  \brief getJours
         *
         *  Retourne le numero du jour j (qui représente Lundi, Mardi,...) de la même semaine que la date passée en argument.
         *  ex : getJours(14/06/2015, 3)
         *      14/06/2015 est un dimanche. L'appel va retourner le numéro du jour 3 (=Mercredi) de la même semaine que 14/06/2015.
         *      Cela retourne donc 10.
         *
         *  \param date : date de référence pour le calcul
         *  \param j : entier représentant le jour dont on veut le numéro (1=Lundi, 2=Mardi,...)
         */
    int getJours(QDate& date, int j){return date.addDays(-date.dayOfWeek()+j).day();}

    /*!
         *  \brief getMois
         *
         *  Retourne le numero de mois du jour j (qui représente Lundi, Mardi,...) de la même semaine que la date passée en argument.
         *  ex : getMois(30/06/2015, 3)
         *      30/06/2015 est un mardi. L'appel va retourner le numéro de mois du jour 3 (=Mercredi) de la même semaine que 30/06/2015. Le mercredi de cette semaine est le 01/07/2015.
         *      Cela retourne donc 7.
         *
         *  \param date : date de référence pour le calcul
         *  \param j : entier représentant le jour dont on veut le numéro de mois (1=Lundi, 2=Mardi,...)
         */
    int getMois(QDate& date, int j){return date.addDays(-date.dayOfWeek()+j).month();}

public slots:
    void updateVueSemaine(); /*< Slot qui met à jour la vue semaine en fonction de la semaine séléctionnée */

};

#endif // WEEKVIEW

