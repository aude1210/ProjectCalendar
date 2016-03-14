#ifndef PROGRAMMATION
#define PROGRAMMATION

/*!
 * \file programmation.h
 * \brief Fichier gerant l'ensemble des programmations des évenements
 */

#include "timing.h"
#include "evenement.h"

using namespace TIME;

/*! \class Programmation
   * \brief classe gérant la programmation des évenements
   *
   *  Les évenements sont soit des taches soit des activités
   */
class Programmation {
private:
    QDateTime date;/*!< Date de la programmation*/
    Horaire heure;/*!< Horaire de la programmation */
    Evenement* event;/*!< Pointeur constant sur l'évenement à programmer */

    /*!
         *  \brief Constructeur
         *
         *  Constructeur privé de la classe Programmation
         *
         *  \param d : Date de la programmation
         *  \param h : Horaire de la programmation
         *  \param e : Evenement à programmer
         */
    Programmation(const QDateTime& d, const Horaire& h, Evenement* e):date(d),heure(h),event(e){}

    /*!
         *  \brief Destructeur
         *
         *  Destructeur de la classe Programmation
         */
    ~Programmation();
    Programmation(const Programmation&);
    Programmation& operator=(const Programmation&);
    friend class Agenda; /*!< Classe Agenda amie de Programmation : seul Agenda pourra construire des programmations*/
public:
    /*!
         *  \brief getDate
         *
         *  Accesseur en lecture sur la date de la programmation
         */
    QDateTime getDate() const {return date;}

    QDate getDate2() const {return date.date();}

    /*!
         *  \brief getHoraire
         *
         *  Accesseur en lecture sur l'horaire de la programmation
         */
    Horaire getHoraire() const {return heure;}

    /*!
         *  \brief getEvenement
         *
         *  Accesseur en lecture sur l'évenement à programmer
         */
     Evenement* getEvenement() const {return event;}


     /*!
          *  \brief afficher
          *
          *  Permet d'afficher une programmation avec tous ces parametres
          *
          *  \param f : Flux sur lequel on écrit
          */

     void setDate(QDateTime& d){date = d;}

     void setHoraire(Horaire& h){heure = h;}
};

#endif // PROGRAMMATION

