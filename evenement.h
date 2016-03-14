#ifndef EVENEMENT
#define EVENEMENT

/*!
 * \file evenement.h
 * \brief Fichier gerant les evenements divers presents dans l'agenda
 */

#include "timing.h"
#include "qt.h"

using namespace std;
using namespace TIME;

class Tache;

/*! \class precedences_iterator
   * \brief Iterator sur les taches precedentes d'une Tache
   *
   */
class precedences_iterator : public vector<Tache*>::const_iterator{
public:
    precedences_iterator():vector<Tache*>::const_iterator(){}
    precedences_iterator(vector<Tache*>::const_iterator it):vector<Tache*>::const_iterator(it){}
};

/*! \class Evenement
   * \brief classe representant les evenements.
   *
   *  La classe gere la creation d'evenements diverses et que l'on pourrait avoir a l'interieur de notre agenda.
   *  Cela pourrait etre un rendez vous ou autre mais ne peut pas être une tache.
   */

class Evenement {
private:
    QString id;/*!< Identifiant de l'evenement*/
    QString titre;/*!< Titre de l'evenement*/
    QDateTime dispo;/*!< Date de disponibilite de l'evenement*/
    QDateTime echeance;/*!< Date d'echeance de l'evenement*/
    bool estProg;/*!< Booleen permettant de savoir si un evenement est programmé*/
public: 
    /*!
         *  \brief Constructeur
         *
         *  Constructeur de la classe Evenement
         *
         *  \param ident : Identifiant de l'evenement
         *  \param t : Titre de l'evenement
         *  \param d : Date de disponibilite de l'evenement
         *  \param ech : Date d'echeance de l'evenement
         *  \param b : Etat de programmation de l'evenement
         */
    Evenement(const QString& ident, const QString& t, const QDateTime& d,const QDateTime& ech, bool b=false):id(ident),titre(t),dispo(d),echeance(ech), estProg(b){std::cout<<"\ncreation d'un evenement";}

    /*!
         *  \brief getId
         *
         *  Accesseur en lecture de l'identifiant de l'evenement
         */
    QString getId() const{return id;}

    /*!
         *  \brief getStauts
         *
         *  Accesseur en lecture de l'etat de l'evenement : programmé ou non
         */
    bool getStatus()const {return estProg;}

    /*!
         *  \brief getTitre
         *
         *  Accesseur en lecture du titre de l'evenement
         */
    QString getTitre() const{return titre;}

    /*!
         *  \brief getDate
         *
         *  Accesseur en lecture de la date de disponibilite de l'evenement
         */
    QDateTime getDate() const{return dispo;}

    /*!
         *  \brief getEcheance
         *
         *  Accesseur en lecture de la date d'écheance de l'evenement
         */
    QDateTime getEcheance() const{return echeance;}

    /*!
         *  \brief getDuree
         *
         *  Méthode virtuelle pure. Permet d'accéder à la durée d'une classe fille en passant par un pointeur d'Evenement
         */
    virtual const Duree getDuree() const = 0;

    /*!
         *  \brief setTitre
         *
         *  Accesseur en écriture du titre de l'evenement
         *
         *  \param t : nom du titre avec lequel on veut initialiser le titre de l'evenement
         */
    void setTitre(const QString& t) {titre = t;}

    /*!
         *  \brief setDateDisponibilite
         *
         *  Accesseur en écriture de la date de disponibilite de l'evenement
         *
         *  \param d : date avec laquelle on veut initialiser la date de disponibilite de l'evenement
         */
    void setDateDisponibilite(const QDateTime& d) {dispo = d;}

    /*!
         *  \brief setEcheance
         *
         *  Accesseur en écriture de la date d'écheance de l'evenement
         *
         *  \param ech : date avec laquelle on veut initialiser la date d'echeance de l'evenement
         */
    void setEcheance(const QDateTime& ech) {echeance = ech;}

    /*!
         *  \brief setEffectue
         *
         *  Accesseur en écriture du status de l'evenement (programme ou non)
         *
         *  \param effect : valeur avec laquelle on veut changer le status de l'evenement (vrai ou faux)
         */
     void setEstProg(bool effect){estProg=effect;}

    /*!
         *  \brief Destructeur
         *
         *  Destructeur de la classe Evenement
         */
     virtual ~Evenement() {}

    /*!
         *  \brief operator<
         *
         *  Surcharge de l'operateur < pour comparer deux evenements entre eux : savoir lequel est antérieur à l'autre
         *
         *  \param e : Evenement avec lequel on souhaite comparer notre objet
         */
    bool operator<(const Evenement& e)const
    {
        return dispo<e.dispo && echeance<e.echeance;
    }

    /*!
         *  \brief begin_precedences()
         *
         *  Méthode virtuelle pure créant une interface pour accéder à begin_precedences() dans la classe fille Tache
         *
         */
    virtual precedences_iterator begin_precedences() const = 0;

    /*!
         *  \brief end_precedences()
         *
         *  Méthode virtuelle pure créant une interface pour accéder à end_precedences() dans la classe fille Tache
         *
         */
    virtual precedences_iterator end_precedences() const = 0;

    virtual bool withPrecedence() const = 0;

};


/*!
     *  \brief operator==
     *
     *  Surcharge de l'opérator == pour permettre de comparer deux evenements entre eux
     *
     *  \param e1 : Premier evenement que l'on souhaite comparer
     *  \param e2 : Second evenement que l'on compare avec le premier
     *
     */
bool operator ==(const Evenement& e1, const Evenement& e2);


#endif // EVENEMENT

