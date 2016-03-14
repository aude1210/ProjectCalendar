#ifndef TACHEUNITAIRE
#define TACHEUNITAIRE


/*!
 * \file tacheunitaire.h
 * \brief Fichier gerant les taches unitaire d'un projet
 */

#include "timing.h"
#include "tache.h"
#include "qt.h"

/*! \class TacheUnitaire
   * \brief classe representant une tache qui ne contient pas de sous taches
   *
   *  La classe TacheUnitaire spécialise la classe Tache
   *
   */
class TacheUnitaire : public Tache {
private:
    static const int DUREE_MAX = 12; /*!< Variable statique pour implémentée la contrainte de durée maximum d'une tacheu- unitaire : 12h */
    Duree duree; /*!< Duree de la tache Unitaire */

    /*!
         *  \brief TacheUnitaire
         *
         *  Constructeur de la classe TacheUnitaire
         *
         * \param ident : identifiant de la tache unitaire
         * \param t : titre de la tache unitaire
         * \param d : date de disponibilite de la tache unitaire
         * \param ech : date d'écheance de la tache unitaire
         * \param du : duree d'execution de la tache unitaire
         *
         */
    TacheUnitaire(const QString& ident, const QString& t, const QDateTime& d,const QDateTime& ech,const Duree& du,bool b=false):Tache(ident,t,d,ech,b),duree(du){std::cout<<"\ncreation d'une tache unitaire\n";}
    TacheUnitaire(const TacheUnitaire&);
    TacheUnitaire& operator=(const TacheUnitaire&);
    ~TacheUnitaire(){};
    friend class Projet;
    friend class TachePreemptable;
public:

    /*!
         *  \brief getDuree
         *
         *  Accesseur en lecture de la duree de la tache unitaire
         */
    const Duree getDuree() const{return duree;}

    /*!
        *  \brief commencer
        *
        *  Methode pour "commencer" une tache
        *  Initialise le début et la fin de la tache
        *
        */
    void commencer();

    /*!
        *  \brief setDuree
        *
        *  Accesseur en écriture qui initialise la durée de la tache unitaire en question
        *
        */
    void setDuree(Duree d){duree=d;}


};

#endif // TACHEUNITAIRE

