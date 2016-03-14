#ifndef PROJETMANAGER
#define PROJETMANAGER

/*!
 * \file projetmanager.h
 * \brief Fichier permettant l'instanciation de projets et leur gestion
 */
#include "qt.h"
#include "projet.h"
#include "export.h"
#include "import.h"

/*! \class ProjetManagerException
   * \brief classe permettant de gérer les exceptions liées au projetManager
   *
   *  La classe ProjetManagerException est une classe qui renvoie une chaine de caractere
   *  pour informer l'utilisateur d'une éventuelle execption soulevée
   */
class ProjetManagerException
{
    QString info; /*!< Message texte renvoyé en cas d'exception reliée au projetManager */

public:
    /*!
      *  \brief Constructeur
      *
      *  Constructeur de la classe ProjetManagerException
      *
      *  \param s : le message d'erreur à afficher
      */
    ProjetManagerException(const QString& s):info(s) {}

    /*!
        *  \brief getInfo
        *
        *  Accesseur en lecture sur le message d'erreur à renvoyer lorsqu'une exception survient.
        *
        */
    QString& getInfo() { return info; }
};

/*! \class ProjetManager
   * \brief classe representant un ProjetManager
   *
   *  La classe ProjetManager permet de gérer des projets
   *  Seul le ProjetManager a la possibilite de créer des projets
   *
   */
class ProjetManager {
private:
    vector<Projet*> projets; /*!< Tableau de pointeur sur l'ensemble des projets que le ProjetManager gère */

    /*!
         *  \brief Constructeur
         *
         *  Constructeur privé de la classe ProjetManager
         *
         *
         */
    ProjetManager();

    /*!
         *  \brief Destructeur
         *
         *  Destructeur privé de la classe ProjetManager
         *
         *
         */
    ~ProjetManager();

    /*!
         *  \brief Constructeur de recopie
         *
         *  Ce constructeur de recopie n'est pas définie mais déclaré ici afin d'empecher la construction par recopie
         *  d'un objet ProjetManager (application du design pattern Singleton)
         */
    ProjetManager(const ProjetManager& pm);

    /*!
         *  \brief Operateur d'affectation
         *
         *  Operateur d'affectation n'est pas définie mais déclaré ici afin d'empecher la dupplication
         *  d'un objet ProjetManager (application du design pattern Singleton)
         */
    ProjetManager& operator=(const ProjetManager& pm);

    /*! \struct Handler
       * \brief classe permettant d'appliquer le design pattern Singleton
       *
       */
    struct Handler{
        ProjetManager* instance; /*!< Pointeur sur le projetManager */

        /*!
             *  \brief Constructeur du Handler
             *
             *  Initialise le pointeur sur projetManager à zéro
             *
             */
        Handler():instance(0){}

        /*!
             *  \brief Destructeur du handler
             *
             *  Il est appelé à la fin du programme pour libérer l'instance de projetManager
             *
             */
        ~Handler(){ if (instance) delete instance; }
    };
    static Handler handler; /*!< Attribut statique */

public:
    /*!
         *  \brief getInstance
         *
         *  Méthode statique permettant de générer un ProjetManager.
         *  Elle en génère un seulement si il n'en existe pas déja un
         * => Application du design pattern singleton
         *
         */
    static ProjetManager& getInstance();

    /*!
         *  \brief libererInstance()
         *
         *  Méthode statique permettant de libérer le ProjetManager instancié
         * => Application du design pattern singleton
         *
         */
    static void libererInstance();

    /*!
         *  \brief ajouterProjet
         *
         *  Permet d'ajouter un projet dans le tableau des projets du ProjetManager
         *
         * \param id : identifiant du projet
         * \param ti : titre du projet
         * \param desc : description du projet
         * \param d : date de disponibilite du projet
         * \param ech : date d'écheance du projet
         */
    Projet* ajouterProjet(const QString& id, const QString& ti, const QString& desc, const QDateTime& d,const QDateTime& ech);

    /*!
         *  \brief supprimerProjet
         *
         *  Permet de supprimer un projet du tableau des projets
         *
         *  \param id : identifiant du projet qui souhaite être supprimé
         */
    void supprimerProjet(const QString& id);

    /*!
         *  \brief trouverProjet
         *
         *  Permet de rechercher si un projet se trouve dans le tableau des projets
         *  Retourne 0 si le projet passée en argument n'est pas présent
         *
         *  \param id : identifiant du projet qui souhaite être recherché
         */
    Projet* trouverProjet(const QString &id) const;


    /*!
         *  \brief save
         *
         *  Methode permettant de sauvegarder l'ensemble des projets selon une méthode spécifiée par le paramètre strategy. (Design pattern strategy)
         *
         * \param strategy : le type de ce paramètre permet de spécifier la méthode de sauvegarde
         * \param f : emplacement de sauvegarde
         */
    void save(ExportStrategy *strategy ,const QString& f){strategy->save(f);}

    void load(ImportStrategy* strategy, const QString& f){strategy->load(f);}

    /*! \class projets_iterator
       * \brief Iterator sur les projetsdu ProjetManager
       *
       */
    class projets_iterator : public vector<Projet*>::const_iterator{
    public:
        projets_iterator():vector<Projet*>::const_iterator(){}
        projets_iterator(typename vector<Projet*>::const_iterator it):vector<Projet*>::const_iterator(it){}
    };

    /*!
         *  \brief begin_projets()
         *
         *  Retourne un projets_iterator sur le premier projet du ProjetManager
         *
         */
    projets_iterator begin_projets() const {return projets_iterator(projets.begin());}

    /*!
         *  \brief end_projets()
         *
         *  Retourne un projets_iterator sur le dernier projet du ProjetManager
         *
         */
    projets_iterator end_projets() const {return projets_iterator(projets.end());}
};

#endif // PROJETMANAGER

