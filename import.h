#ifndef IMPORT_H
#define IMPORT_H


/*!
 * \file import.h
 * \brief Fichier définissant les classes ImportStrategy et ImportXML permettant l'import d'un calendrier
 */

#include "qt.h"

/*! \class ImportStrategy
   * \brief Classe définissant l'interface d'import du calendrier
   *
   *  Classe abstraite.
   *  Implémente le design pattern Strategy
   */
class ImportStrategy {
public: 
    /*!
         *  \brief load
         *
         *  Methode virtuelle pure mise en place pour l'application du design pattern strategy
         *
         *  \param f : nom du fichier de destination
         */
    virtual void load (const QString& f) = 0;
};

/*! \class ImportXML
   * \brief classe permettant l'import d'un calendrier depuis un fichier XML
   *
   * Implémentation de l'interface d'import ImportStrategy pour l'import depuis un fichier XML
   *
   */
class ImportXML : public ImportStrategy{
public: 
    /*!
         *  \brief load
         *
         *  Redéfinition de la méthode load pour l'import depuis un fichier XML
         *
         *  \param f : nom du fichier de destination
         */
    void load(const QString &f);
};

#endif // IMPORT_H

