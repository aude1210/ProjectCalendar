#ifndef ACTIVITE
#define ACTIVITE

/*!
 * \file activite.h
 * \brief Fichier gerant les activités diverses presents dans l'agenda
 */

using namespace std;
#include "qt.h"
#include "timing.h"
#include "evenement.h"
#include <vector>
#include <sstream>
#include <iostream>
#include <typeinfo>

/*! \class participants_iterator
   * \brief Iterator sur les participants d'une Réunion
   *
   */
class participants_iterator : public vector<QString>::const_iterator{
public:
    participants_iterator():vector<QString>::const_iterator(){}
    participants_iterator(vector<QString>::const_iterator it):vector<QString>::const_iterator(it){}
};

/*! \class Activite
   * \brief classe representant une Activite traditionnelle
   *
   *  La classe Activite est un evenement ayant une duree
   *  specifiee ainsi qu'un lieu.
   */

class Activite : public Evenement {
protected:
    Duree duree;/*!< Duree de l'evenement*/
    QString lieu;/*!< Lieu de l'evenement*/
    /*!
         *  \brief Constructeur
         *
         *  Constructeur privé de la classe Activite
         *  Permet d'éviter l'instanciation d'objet Activite
         *
         *  \param ident : Identifiant de l'activite
         *  \param t : Titre de l'activite
         *  \param d : Date de disponibilite de l'activite
         *  \param ech : Date d'echeance de l'activite
         *  \param du : Duree de l'activite
         *  \param li : Lieu de l'activite
         *  \param b : Etat de programmation de l'evenement
         */
    Activite(const QString& ident, const QString& t, const QDateTime& d,const QDateTime& ech,const Duree& du,const QString& li,bool b=false): Evenement(ident,t,d,ech,b), duree(du),lieu(li){}
    /*!
         *  \brief Destructeur
         *
         *  Destructeur privé de la classe Activite
         */
    ~Activite() {}
    /*!
         *  \brief Constructeur de recopie
         *
         *  Constructeur de recopie privé de la classe Activite
         */
    Activite (const Activite&);
    /*!
         *  \brief opérateur d'affectation
         *
         *  Opérateur d'affectation privé de la classe Activite
         */
    Activite& operator=(const Activite&);
    friend class ActiviteManager; /*!< Classe ActiviteManager amie de Activite : seul ActiviteManager pourra instancier des Activite*/
public:

    /*!
         *  \brief getDuree
         *
         *  Accesseur en lecture de la duree de l'activite
         */

    const Duree getDuree()const{return duree;}

    /*!
         *  \brief getLieu
         *
         *  Accesseur en lecture du lieu de l'activite
         */
    const QString& getLieu()const{return lieu;}

    /*!
         *  \brief setLieu
         *
         *  Accesseur en écriture du lieu de l'activite
         *
         *  \param newLieu : nom du lieu avec lequel on veut initialiser le lieu de l'activité
         */
    void setLieu(QString newLieu) { lieu = newLieu; }

    /*!
         *  \brief setDuree
         *
         *  Accesseur en écriture de la duree de l'activite
         *
         *  \param newDuree : la duree avec lequelle on veut initialiser la duree de l'activité
         */
    void setDuree(Duree newDuree) { duree = newDuree; }


    /*!
         *  \brief getInterlocuteur
         *
         *  Accesseur en lecture sur l'interlocuteur
         */

    virtual const QString getInterlocuteur() const { return 0; }

    /*!
         *  \brief setInterlocuteur
         *
         *  Accesseur en écriture sur l'interlocuteur
         *
         * \param interl : initialise notre interlocuteur avec ce nom
         */
    virtual void setInterlocuteur(const QString& ) {}

    /*!
         *  \brief ajouterParticipant
         *
         *  Permet d'ajouter un participant à la réunion
         *
         *  \param parti : nom du participant que l'on veut rajouter à la réunion
         */

    virtual void ajouterParticipant(const QString &){}

    /*!
         *  \brief supprimmerParticipant
         *
         *  Permet de supprimer un participant de la réunion
         *
         *  \param parti : nom du participant que l'on veut supprimer de la réunion
         */
    virtual void supprimerParticipant(const QString & ){}

    /*!
         *  \brief begin_participant
         *
         *  Méthode virtuelle créant une interface pour accéder à begin_participant dans la classe fille Réunion
         *  Retourne un participants_iterator vide
         *
         */
    virtual participants_iterator begin_participants() const {return participants_iterator();}

    /*!
         *  \brief end_participant
         *
         * Méthode virtuelle créant une interface pour accéder à end_participant dans la classe fille Réunion
         * Retourne un participants_iterator vide.
         *
         */
    virtual participants_iterator end_participants() const {return participants_iterator();}

    /*!
         *  \brief begin_precedences
         *
         *  Une activité n'a pas de précédence donc retourne un precedences_iterator vide
         *
         */
    precedences_iterator begin_precedences() const {return precedences_iterator();}

    /*!
         *  \brief end_precedences
         *
         *  Une activité n'a pas de précédence donc retourne un precedences_iterator vide
         *
         */
    precedences_iterator end_precedences() const {return precedences_iterator();}

    bool withPrecedence() const { return false;}

};


/*! \class Reunion
   * \brief classe representant une Activite spéciale : une Reunion
   *
   *  La classe Reunion est une activite ayant une liste de participants spécifiée.
   */

class Reunion : public Activite {
private:
    vector<QString> participants;/*!< Liste des participants à la reunion*/
    /*!
         *  \brief Constructeur
         *
         *  Constructeur privé de la classe Reunion
         *  Permet d'éviter l'instanciation d'objet Reunion
         *
         *  \param ident : Identifiant de l'activite
         *  \param t : Titre de l'activite
         *  \param d : Date de disponibilite de l'activite
         *  \param ech : Date d'echeance de l'activite
         *  \param du : Duree de l'activite
         *  \param li : Lieu de l'activite
         *  \param b : Etat de programmation de l'evenement
         */
    Reunion(const QString& ident, const QString& t, const QDateTime& d,const QDateTime& ech,const Duree& du,const QString& li,bool b=false):Activite(ident,t,d,ech,du,li,b){}

    /*!
         *  \brief Destructeur
         *
         *  Destructeur privé de la classe Reunion
         */
     ~Reunion() {}
    /*!
         *  \brief Constructeur de recopie
         *
         *  Constructeur de recopie privé de la classe Reunion
         */
    Reunion (const Reunion&);
    /*!
         *  \brief Opérateur d'affectation
         *
         *  Opérateur d'affectation privé de la classe Reunion
         */
    Reunion& operator=(const Reunion&);
    friend class ActiviteManager; /*!< Classe ActiviteManager amie de Reunion : seul ActiviteManager pourra instancier des Reunion*/
public:

    /*!
         *  \brief ajouterParticipant
         *
         *  Permet d'ajouter un participant à la réunion
         *
         *  \param parti : nom du participant que l'on veut rajouter à la réunion
         */
    void ajouterParticipant(const QString & parti);

    /*!
         *  \brief supprimmerParticipant
         *
         *  Permet de supprimer un participant de la réunion
         *
         *  \param parti : nom du participant que l'on veut supprimer de la réunion
         */
    void supprimerParticipant(const QString & parti);

    /*!
         *  \brief begin_participants
         *
         *  Retourne un participants_iterator sur le premier participant
         *
         */
    participants_iterator begin_participants() const {return participants_iterator(participants.begin());}

    /*!
         *  \brief end_participants
         *
         *  Retourne un participants_iterator sur le dernier participant
         *
         */
    participants_iterator end_participants() const {return participants_iterator(participants.end());}
};


/*! \class Rdv
   * \brief classe representant une Activite spéciale : une Rdv
   *
   *  La classe Reunion est une activite ayant un interlocuteur spécifiée.
   */

class Rdv : public Activite{
private:
    QString personne;/*!< représente l'interlocuteur du rendez vous */
    /*!
         *  \brief Constructeur
         *
         *  Constructeur privé de la classe Rdv
         *  Permet d'éviter l'instanciation d'objet Rdv
         *
         *  \param ident : Identifiant de l'activite
         *  \param t : Titre de l'activite
         *  \param d : Date de disponibilite de l'activite
         *  \param ech : Date d'echeance de l'activite
         *  \param du : Duree de l'activite
         *  \param li : Lieu de l'activite
         *  \param pers : interlocuteur du rendez-vous
         *  \param b : Etat de programmation de l'evenement
         */
    Rdv(const QString& ident, const QString& t, const QDateTime& d,const QDateTime& ech,const Duree& du, const QString& pers, const QString& li,bool b=false):Activite(ident,t,d,ech,du,li,b),personne(pers){}
    /*!
         *  \brief Destructeur
         *
         *  Destructeur privé de la classe Rendez vous
         */
     ~Rdv() {}
    /*!
         *  \brief Constructeur de recopie
         *
         *  Constructeur de recopie privé de la classe Rendez vous
         */
    Rdv (const Rdv&);
    /*!
         *  \brief Opérateur d'affectation
         *
         *  Opérateur d'affectation privé de la classe Rendez vous
         */
    Rdv& operator=(const Rdv&);
    friend class ActiviteManager; /*!< Classe ActiviteManager amie de Rdv : seul ActiviteManager pourra instancier des Rdv*/

public: 
    /*!
         *  \brief getInterlocuteur
         *
         *  Accesseur en lecture sur l'interlocuteur
         */

    const QString getInterlocuteur() const { return personne; }

    /*!
         *  \brief setInterlocuteur
         *
         *  Accesseur en écriture sur l'interlocuteur
         *
         * \param interl : initialise notre interlocuteur avec ce nom
         */
    void setInterlocuteur(const QString& interl) { personne = interl; }

};

#endif // ACTIVITE

