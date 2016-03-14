#ifndef ACTIVITEMANAGER_H
#define ACTIVITEMANAGER_H

#include "qt.h"
#include "activite.h"

/*! \class ActiviteManagerException
   * \brief classe permettant de gérer les exceptions liées au activiteManager
   *
   *  La classe ActiviteManagerException est une classe qui renvoie une chaine de caractere
   *  pour informer l'utilisateur d'une éventuelle execption soulevée
   */
class ActiviteManagerException
{
    QString info; /*!< Message texte renvoyé en cas d'exception reliée au activiteManager */

public:
    /*!
      *  \brief Constructeur
      *
      *  Constructeur de la classe ActiviteManagerException
      *
      *  \param s : le message d'erreur à afficher
      */
    ActiviteManagerException(const QString& s):info(s) {}

    /*!
        *  \brief getInfo
        *
        *  Accesseur en lecture sur le message d'erreur à renvoyer lorsqu'une exception survient.
        *
        */
    QString& getInfo() { return info; }
};

/*! \class ActiviteManager
   * \brief classe representant un ActiviteManager
   *
   *  La classe ActivteManager permet de gérer des Activites
   *  Seul le ActiviteManager a la possibilite de créer des Activites
   *
   */
class ActiviteManager {
private:
    vector<Activite*> activites; /*!< Tableau de pointeur sur l'ensemble des activites que le ActiviteManager gère */

    /*!
         *  \brief Constructeur
         *
         *  Constructeur privé de la classe ActiviteManager
         *
         *
         */
    ActiviteManager();

    /*!
         *  \brief Destructeur
         *
         *  Destructeur privé de la classe ActiviteManager
         *
         *
         */
    ~ActiviteManager();

    /*!
         *  \brief Constructeur de recopie
         *
         *  Ce constructeur de recopie n'est pas défini mais déclaré ici afin d'empecher la construction par recopie
         *  d'un objet ActiviteManager (application du design pattern Singleton)
         */
    ActiviteManager(const ActiviteManager& am);

    /*!
         *  \brief Operateur d'affectation
         *
         *  Operateur d'affectation n'est pas définie mais déclaré ici afin d'empecher la duplication
         *  d'un objet ActiviteManager (application du design pattern Singleton)
         */
    ActiviteManager& operator=(const ActiviteManager& am);

    /*! \struct Handler
       * \brief classe permettant d'appliquer le design pattern Singleton
       *
       */
    struct Handler{
        ActiviteManager* instance; /*!< Pointeur sur le ActiviteManager */

        /*!
             *  \brief Constructeur du Handler
             *
             *  Initialise le pointeur sur ActiviteManager à zéro
             *
             */
        Handler():instance(0){}

        /*!
             *  \brief Destructeur du handler
             *
             *  Il est appelé à la fin du programme pour libérer l'instance de ActiviteManager
             *
             */
        ~Handler(){ if (instance) delete instance; }
    };
    static Handler handler; /*!< Attribut statique */

public:
    /*!
         *  \brief getInstance
         *
         *  Méthode statique permettant de générer un ActiviteManager.
         *  Elle en génère un seulement si il n'en existe pas déja un
         * => Application du design pattern singleton
         *
         */
    static ActiviteManager& getInstance();

    /*!
         *  \brief libererInstance()
         *
         *  Méthode statique permettant de libérer le ActiviteManager instancié
         * => Application du design pattern singleton
         *
         */
    static void libererInstance();

    /*!
         *  \brief ajouterActivite
         *
         *  Permet d'ajouter une activité dans le tableau des Activites du ActiviteManager
         *
         * \param ident : identifiant de l'activite
         * \param t : titre de l'activite
         * \param d : date de disponibilite de l'activite
         * \param ech : date d'écheance de l'activite
         * \param du : durée de l'activite
         * \param li : Lieu de l'activite
         * \param b : Etat de programmation de l'evenement
         */
    Activite* ajouterActivite(const QString& ident, const QString& t, const QDateTime &d, const QDateTime ech, const Duree& du, const QString& li, bool b=false);

    /*!
         *  \brief ajouterReunion
         *
         *  Permet d'ajouter une réunion dans le tableau des Activites du ActiviteManager
         *
         *  \param ident : Identifiant de l'activite
         *  \param t : Titre de l'activite
         *  \param d : Date de disponibilite de l'activite
         *  \param ech : Date d'echeance de l'activite
         *  \param du : Duree de l'activite
         *  \param li : Lieu de l'activite
         *  \param b : Etat de programmation de l'evenement
         */
    Reunion* ajouterReunion(const QString& ident, const QString& t, const QDateTime &d, const QDateTime &ech, const Duree& du, const QString& li, bool b=false);

    /*!
         *  \brief ajouterRdv
         *
         *  Permet d'ajouter un rendez-vous dans le tableau des Activites du ActiviteManager
         *
         *  \param ident : Identifiant de l'activite
         *  \param t : Titre de l'activite
         *  \param d : Date de disponibilite de l'activite
         *  \param ech : Date d'echeance de l'activite
         *  \param du : Duree de l'activite
         *  \param pers : interlocuteur du rendez-vous
         *  \param li : Lieu de l'activite
         *  \param b : Etat de programmation de l'evenement
         */
    Rdv* ajouterRdv(const QString& ident, const QString& t, const QDateTime &d, const QDateTime &ech, const Duree& du, const QString& pers, const QString& li, bool b=false);

    /*!
         *  \brief supprimerActivite
         *
         *  Permet de supprimer une activité du tableau des activités
         *
         *  \param id : identifiant de l'activité qu'on souhaite être supprimé
         */
    void supprimerActivite(const QString& id);

    /*!
         *  \brief trouverActivite
         *
         *  Permet de rechercher si une activité se trouve dans le tableau des activités
         *  Retourne 0 si l'activité passée en argument n'est pas présente
         *
         *  \param id : identifiant de l'activité recherchée
         */
    Activite* trouverActivite(const QString &id) const;

    /*! \class activites_iterator
       * \brief Iterator sur les activites de ActiviteManager
       *
       */
    class activites_iterator : public vector<Activite*>::const_iterator{
    public:
        activites_iterator():vector<Activite*>::const_iterator(){}
        activites_iterator(vector<Activite*>::const_iterator it):vector<Activite*>::const_iterator(it){}
    };

    /*!
         *  \brief begin_activites
         *
         *  Retourne un activites_iterator sur la première activité de ActiviteManager
         *
         */
    activites_iterator begin_activites() const {return activites_iterator(activites.begin());}

    /*!
         *  \brief end_activites
         *
         *  Retourne un activites_iterator sur la dernière activité de ActiviteManager
         *
         */
    activites_iterator end_activites() const {return activites_iterator(activites.end());}

};

#endif // ACTIVITEMANAGER_H

