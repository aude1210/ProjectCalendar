#ifndef TACHEPREEMPTABLE
#define TACHEPREEMPTABLE

/*!
 * \file tachepreemptable.h
 * \brief Fichier gerant les taches préemptables d'un projet
 */

#include "timing.h"
#include "tacheunitaire.h"



/*! \class TachePreemptable
   * \brief classe representant une tache qui peut être arrétée et reprise
   *
   *  La classe TachePreemptable spécialise la classe TacheUnitaire
   *
   */
class TachePreemptable : public TacheUnitaire {
private:
    bool enCours; /*!< Booleen permettant de savoir si une tache est en cours d'éxécution ou non */
    Duree reste; /*!< Duree d'éxécution qu'il reste de la tache préemptable */

    /*!
         *  \brief TachePreemptable
         *
         *  Constructeur de la classe TachePreemptable
         *
         * \param ident : identifiant de la tache preemptable
         * \param t : titre de la tache preemptable
         * \param d : date de disponibilite de la tache preemptable
         * \param ech : date d'écheance de la tache preemptable
         * \param du : duree d'execution qu'il reste de la tache préemptable
         *
         */
    TachePreemptable(const QString& ident, const QString& t, const QDateTime& d,const QDateTime& ech,const Duree& du, bool b=false):TacheUnitaire(ident,t,d,ech, du,b), enCours(false), reste(getDuree()){std::cout<<" qui est preemptable\n";}
    ~TachePreemptable(){};
    TachePreemptable(const TachePreemptable&);
    TachePreemptable& operator=(const TachePreemptable&);
    friend class Projet;
public:

    /*!
        *  \brief commencer
        *
        *  Methode pour "commencer" une tache
        *  Initialise le début et la fin de la tache
        *  Mentionne que la tache est désormais en cours (appel de setEnCours)
        *
        */
    void commencer();

    /*!
        *  \brief getEnCours
        *
        *  Accesseur en lecture sur l'état de la tache preemptable : en cours ou non
        *
        */
    bool getEnCours() const {return enCours;}

    /*!
        *  \brief setEnCours
        *
        *  Accesseur en ecriture sur l'état de la tache preemptable : change l'état : en cours ou non
        *
        */
    void setEnCours(bool b){enCours=b;}

    /*!
        *  \brief getReste
        *
        *  Accesseur en lecture sur la durée restante de la tache preemptable
        *
        */
    Duree getReste() const {return reste;}

    /*!
        *  \brief setReste
        *
        *  Accesseur en écriture sur la durée restante de la tache preemptable
        *
        */
    void setReste(int r){reste=r;}

    /*!
        *  \brief setReste
        *
        *  ...
        *
        */

    void interruption();

    /*!
        *  \brief reprise
        *
        *  Permet de reprendre une tache préemptable interrompue
        *
        */
    void reprise();
};

/*!
     *  \brief operator<<
     *
     *  Surcharge de l'opérator << pour permettre d'afficher les caractéristiques d'une tache préemptable sur le flux de sortie.
     *
     *  \param fout : Flux sur lequel on écrit
     *  \param t : Tache préemtable que l'on souhaite afficher
     *
     */
QTextStream& operator<<(QTextStream& fout, const TachePreemptable& t);

#endif // TACHEPREEMPTABLE

