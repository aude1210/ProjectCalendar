#ifndef TACHECOMPOSITE
#define TACHECOMPOSITE

/*!
 * \file tachecomposite.h
 * \brief Fichier gerant les taches composites d'un projet et leurs exceptions
 */

#include "timing.h"
#include "tache.h"
#include <vector>


/*! \class CompositeException
   * \brief classe permettant de gérer les exceptions liées aux taches composites
   *
   *  La classe CompositeException est une classe qui renvoie une chaine de caractere
   *  pour informer l'utilisateur d'une éventuelle execption soulevée
   */
class CompositeException
{
    QString info; /*!< Message texte renvoyé en cas d'exception reliée à une tache composite */

public:

    /*!
      *  \brief Constructeur
      *
      *  Constructeur de la classe CompositeException
      *
      *  \param s : le message d'erreur à afficher
      */
    CompositeException(const QString& s):info(s) {}

    /*!
        *  \brief getInfo
        *
        *  Accesseur en lecture sur le message d'erreur à renvoyer lorsqu'une exception survient.
        *
        */
    QString& getInfo() { return info; }

};

/*! \class TacheComposite
   * \brief classe representant une tache composées d'autres taches
   *
   *  La classe TacheComposite spécialise la classe Tache
   *
   */
class TacheComposite : public Tache {
private:
    vector<Tache*> soustaches; /*!< Tableau de taches représentant les sous taches d'une tache composite */
    /*!
         *  \brief Constructeur
         *
         *  Constructeur de la classe TacheComposite
         *
         * \param ident : identifiant de la tache composite
         * \param t : titre de la tache composite
         * \param d : date de disponibilite de la tache composite
         * \param ech : date d'écheance de la tache composite
         *
         */
    TacheComposite(const QString& ident, const QString& t, const QDateTime& d,const QDateTime& ech, bool b=false):Tache(ident,t,d,ech,b), soustaches(0){std::cout<<"\ncreation d'une tache composite\n";}
    ~TacheComposite(){};
    TacheComposite(const TacheComposite&);
    TacheComposite& operator=(const TacheComposite&);
    friend class Projet;
public:


    /*!
         *  \brief ajouterSousTache
         *
         *  Permet d'ajouter une sous tache au tableau des sous taches d'une tache composite
         *
         * \param t : pointeur sur la tache à ajouter
         *
         */
    void ajouterSousTache(Tache * t){soustaches.push_back(t);}

    /*!
         *  \brief supprimerSousTache
         *
         *  Supprime une sous tache du tableau des sous taches d'une tache composite
         *
         * \param ident : identifiant de la tache à supprimer
         *
         */
    void supprimerSousTache(const QString& ident);


    /*!
         *  \brief getDuree
         *
         *  Methode qui ne fait rien mais qui permet de rendre la classe tachecomposite concrète
         *
         *
         */
    const Duree getDuree() const{return Duree(0,0);}

    /*!
         *  \brief setDuree
         *
         *  Définition de la méthode virtuelle pure de la classe Tache, pour pouvoir instancier TacheCompos
         *
         *  \param d : la duree avec laquelle on veut initialiser la duree de l'activité
         */
    virtual void setDuree(Duree d) {d.getHeures();}

    /*!
         *  \brief trouverTache
         *
         *  Methode qui permet de trouver une tache parmis les sous taches de la tache en question à partir de son identifiant
         *
         * \param id : identifiant de la tache que l'on souhaite trouver dans le tableau des sous taches
         */
    Tache* trouverTache(const QString& id)const;

    /*!
        *  \brief commencer
        *
        *  Methode pour "commencer" une tache
        *  Appel de la méthode setDebut(d)
        *
        */
    void commencer();

    /*!
         *  \brief begin_soustaches
         *
         *  Retourne un soustaches_iterator sur la première sous tache
         *
         */
    soustaches_iterator begin_soustaches() const{return soustaches_iterator(soustaches.begin());}

    /*!
         *  \brief begin_soustaches
         *
         *  Retourne un soustaches_iterator sur la première sous tache
         *
         */
    soustaches_iterator end_soustaches() const {return soustaches_iterator(soustaches.end());}
};

#endif // TACHECOMPOSITE



