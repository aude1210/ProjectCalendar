#ifndef AGENDA
#define AGENDA

/*!
 * \file agenda.h
 * \brief Fichier gerant l'agenda de l'utilisateur
 */

using namespace std;


#include <vector>
#include "timing.h"
#include "programmation.h"
#include "evenement.h"
#include "tache.h"

using namespace TIME;


/*! \class AgendaException
   * \brief classe permettant de gérer les exceptions liées à l'agenda
   *
   *  La classe AgendaException est une classe qui renvoie une chaine de caractere
   *  pour informer l'utilisateur d'une éventuelle execption soulevée
   */

class AgendaException
{
    QString info; /*!< Message texte renvoyé en cas d'exception reliée à l'Agenda */

public:
   /*!
     *  \brief Constructeur
     *
     *  Constructeur de la classe AgendaException
     *
     *  \param s : le message d'erreur à afficher
     */
    AgendaException(const QString& s):info(s) {}

    /*!
        *  \brief getInfo
        *
        *  Accesseur en lecture sur le message d'erreur à renvoyer lorsqu'une exception survient.
        *
        */
    QString& getInfo() { return info; }
};


/*! \class Agenda
   * \brief classe representant un Agenda
   *
   *  La classe Agenda permet de gérer les differentes programmations de ses évenements (taches ou activités)
   *
   */
class Agenda {
private:
   vector<Programmation*> progs; /*!< Stocke les differentes programmations des evenements */

   /*!
       *  \brief addItem
       *
       *  Methode qui ajoute une programmation à la fin du vector des programmations
       *
       *  \param p : la programmation à ajouter
       */
   void addItem(Programmation* p);

   /*!
        *  \brief Constructeur
        *
        *  Destructeur de la classe Agenda
        */
   Agenda();

   /*!
        *  \brief Destructeur
        *
        *  Destructeur de la classe Agenda
        */
   ~Agenda();

   /*!
        *  \brief Constructeur de recopie
        *
        *  Ce constructeur de recopie n'est pas définie mais déclaré ici afin d'empecher la construction par recopie
        *  d'un objet Agenda (application du design pattern Singleton)
        */
   Agenda(const Agenda& a);

   /*!
        *  \brief Operateur d'affectation
        *
        *  Operateur d'affectation n'est pas définie mais déclaré ici afin d'empecher la dupplication
        *  d'un objet Agenda (application du design pattern Singleton)
        */
   Agenda& operator=(const Agenda& a);

   vector<Programmation*>::iterator trouverProgrammationIterator(Evenement* e);

   /*! \struct Handler
      * \brief classe permettant d'appliquer le design pattern Singleton
      *
      */
   struct Handler{
       Agenda* instance; /*!< Pointeur sur l'agenda */

       /*!
            *  \brief Constructeur du Handler
            *
            *  Initialise le pointeur sur agenda à zéro
            *
            */
       Handler():instance(0){}

       /*!
            *  \brief Destructeur du handler
            *
            *  Il est appelé à la fin du programme pour libérer l'instance d'Agenda
            *
            */
       ~Handler(){ if (instance) delete instance; }
   };
   static Handler handler;/*!< Attribut statique */

public:

   /*!
        *  \brief trouverProgrammation
        *
        *  Permet de rechercher si une programmation se trouve dans le tableau des programmations
        *  Retourne 0 si la programmation passée en argument n'est pas présente
        *
        *  \param e : Evenement dont la programmation est recherchée
        */
   Programmation* trouverProgrammation(Evenement* e) const;

   /*!
        *  \brief getInstance
        *
        *  Méthode statique permettant de générer un Agenda.
        *  Elle en génère un seulement si il n'en existe pas déja un
        * => Application du design pattern singleton
        *
        */
   static Agenda& getInstance();

   /*!
        *  \brief libererInstance()
        *
        *  Méthode statique permettant de libérer l'Agenda instancié
        * => Application du design pattern singleton
        *
        */
   static void libererInstance();

   /*!
        *  \brief ajouterProg
        *
        *  Permet d'ajouter une programmation dans le tableau des programmations
        *  Instancie la programmation et fait appel à la méthode addItem
        *
        *  \param e : Evenement dont la programmation souhaite être ajoutée
        *  \param d : Date à laquelle on veut ajouter la programmation dans l'agenda
        *  \param e : Horaire auquel on veut ajouter la programmation dans l'agenda
        */
   Programmation& ajouterProg(Evenement* e, const QDateTime &d, const Horaire& h);

   /*!
        *  \brief supprimerProg
        *
        *  Permet de supprimer une programmation du tableau des programmations
        *
        *  \param e : Evenement dont la programmation souhaite être supprimée
        */
   void supprimerProg(Evenement* e);

   /*!
        *  \brief afficherProg
        *
        *  Affiche l'ensemble des programmations de l'agenda
        *
        */

   /*! \class programmations_iterator
      * \brief Iterator sur les programmations de l'Agenda
      *
      */
   class programmations_iterator : public vector<Programmation*>::const_iterator{
   public:
       programmations_iterator():vector<Programmation*>::const_iterator(){}
       programmations_iterator(vector<Programmation*>::const_iterator it):vector<Programmation*>::const_iterator(it){}
   };

   /*!
        *  \brief begin_programmations()
        *
        *  Retourne un programmations_iterator sur la première programmation de l'Agenda
        *
        */
   programmations_iterator begin_programmations() const {return programmations_iterator(progs.begin());}

   /*!
        *  \brief end_programmations()
        *
        *  Retourne un programmations_iterator sur la dernière programmation de l'Agenda
        *
        */
   programmations_iterator end_programmations() const {return programmations_iterator(progs.end());}
};

#endif // AGENDA

