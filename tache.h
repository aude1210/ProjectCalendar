#ifndef TACHE
#define TACHE

/*!
 * \file taches.h
 * \brief Fichier gerant les taches d'un projets
 */

#include "timing.h"
#include "evenement.h"
#include <vector>
#include "qt.h"
#include <typeinfo>

class Projet;/*!< Déclaration au préalable de la classe Projet pour pouvoir l'utiliser dans la classe Tache*/

/*! \class soustaches_iterator
   * \brief Iterator sur les sous taches d'une TacheComposite
   *
   */
class soustaches_iterator : public vector<Tache*>::const_iterator{
public:
    soustaches_iterator():vector<Tache*>::const_iterator(){}
    soustaches_iterator(vector<Tache*>::const_iterator it):vector<Tache*>::const_iterator(it){}
};

/*! \class Tache
   * \brief classe abstraite representant une tache de manière générale
   *
   *  La classe Tache permet de représenter des caractéristiques communes à des taches qui vont spécialiser celle-ci
   *
   */
class Tache : public Evenement {
friend class Projet; /*!< Projet est ami de la classe Tache */
private:
    vector<Tache*> tachesPrecedentes; /*!< Tableau de pointeurs de taches représentant les taches précédentes */
    QDateTime debut; /*!< Date avec horaire représentant le début d'une tache */
    QDateTime fin; /*!< Date avec horaire représentant la fin d'une tache  */
    bool inTree;
public:

    bool getInTree(){return inTree;}

    void setInTree(bool b){inTree=b;}

    /*!
         *  \brief Constructeur
         *
         *  Constructeur privé de la classe Tache
         *
         * \param ident : identifiant de la tache
         * \param t : titre de la tache
         * \param d : date de disponibilite de la tache
         * \param ech : date d'écheance de la tache
         * \param b: Booleen représentant l'état de la tache à ajouter (par défaut non programmée)
         *
         */
    Tache(const QString& ident, const QString& t, const QDateTime& d,const QDateTime& ech, bool b=false): Evenement(ident,t,d,ech,b), tachesPrecedentes(0), debut(QDateTime::currentDateTime()), fin(QDateTime::currentDateTime()), inTree(false){}
    ~Tache(){};
    virtual void supprimerSousTache(const QString& ){}

    /*!
        *  \brief addItem
        *
        *  Methode qui ajoute un contrainte de précédence à une tache
        *
        *  \param t : la tache représentant la précédence à ajouter
        */
    void addItem(Tache* t);

    /*!
        *  \brief commencer
        *
        *  Methode virtuelle pure qui sera implémentée dans les sous classes pour "commencer" une tache
        *
        */
    virtual void commencer()=0;

    /*!
        *  \brief setDebut
        *
        *  Accesseur en écriture qui initialise la date de début (format date+horaire) d'une tache passée en paramètre
        *
        *  \param d : la date de début avec laquelle on veut initialiser la tache en question
        */
    void setDebut(QDateTime d){debut=d;}

    /*!
        *  \brief getDebut
        *
        *  Accesseur en lecture sur la date de début (format date+horaire) d'une tache
        */
    QDateTime getDebut() const {return debut;}

    /*!
        *  \brief setFin
        *
        *  Accesseur en écriture qui initialise la date de fin (format date+horaire) d'une tache passée en paramètre
        *
        *  \param f : la date de fin avec laquelle on veut initialiser la tache en question
        */
    void setFin(QDateTime f){fin=f;}

    /*!
        *  \brief getFin
        *
        *  Accesseur en lecture sur la date de fin (format date+horaire) d'une tache
        */
    QDateTime getFin() const{return fin;}

    /*!
        *  \brief getDuree
        *
        *  Méthode virtuelle pure pour permettre l'appel de getDuree() sur un pointeur de Tache
        *
        */
    const Duree getDuree() const = 0;

    /*!
        *  \brief withPrecedence
        *
        *  Retourne true si la tache a des precedences, false sinon.
        *
        */
    bool withPrecedence() const { return !tachesPrecedentes.empty();}

    /*!
         *  \brief setDuree
         *
         *  Méthode virtuelle pure définissant l'interface pour la modification de la durée d'une TacheUnitaire
         *
         *  \param d : la duree avec laquelle on veut initialiser la duree de l'activité
         */
    virtual void setDuree(Duree d) = 0;

    /*!
        *  \brief ajouterSousTache()
        *
        *  Méthode virtuelle pour permettre l'appel de ajouterSousTache() sur une Tache
        *
        */
    virtual void ajouterSousTache(Tache*){}

    /*!
         *  \brief begin_soustaches
         *
         *  Méthode virtuelle créant une interface pour accéder à begin_soustaches dans la classe fille TacheUnitaire
         *  Retourne un soustaches_iterator vide
         *
         */
    virtual soustaches_iterator begin_soustaches() const{return soustaches_iterator();}

    /*!
         *  \brief end_soustaches
         *
         *  Méthode virtuelle créant une interface pour accéder à end_soustaches dans la classe fille TacheUnitaire
         *  Retourne un soustaches_iterator vide
         *
         */
    virtual soustaches_iterator end_soustaches() const {return soustaches_iterator();}

    /*!
         *  \brief begin_precedences
         *
         *  Retourne un precedences_iterator sur la première tache précédente
         *
         */
    precedences_iterator begin_precedences() const {return precedences_iterator(tachesPrecedentes.begin());}

    /*!
         *  \brief end_precedences
         *
         *  Retourne un precedences_iterator sur la dernière tache précédente
         *
         */
    precedences_iterator end_precedences() const {return precedences_iterator(tachesPrecedentes.end());}

    /*!
        *  \brief addPrecedence
        *
        *  Méthode permettant d'ajouter une précédence à la tache
        *
        *  \param t : pointeur sur la tache à ajouter en précédence
        */
    void addPrecedence(Tache* t){addItem(t);}

    /*!
        *  \brief supprimerPrecedence
        *
        *  Méthode permettant de supprimer une précédence de la tache
        *
        *  \param id : id de la tache à supprimer
        */
    void supprimerPrecedence(const QString& id){
        for (size_t i=0;i<tachesPrecedentes.size();++i)
            if(tachesPrecedentes[i]->getId()==id)
                tachesPrecedentes.erase(tachesPrecedentes.begin()+i);
    }
};

/*!
     *  \brief operator<<
     *
     *  Surcharge de l'opérator << pour permettre d'afficher les caractéristiques d'une tache sur le flux de sortie.
     *
     *  \param f : Flux sur lequel on écrit
     *  \param t : Tache que l'on souhaite afficher
     *
     */
std::ostream& operator<<(std::ostream& f, const Tache& t);


#endif // TACHE

