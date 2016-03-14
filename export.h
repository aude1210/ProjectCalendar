#ifndef EXPORT_H
#define EXPORT_H

/*!
 * \file export.h
 * \brief Fichier définissant les classes ExportStrategy et ExportXML permettant l'export du calendrier
 */

#include "qt.h"

/*! \class ExportStrategy
   * \brief Classe définissant l'interface d'export du calendrier
   *
   *  Classe abstraite.
   *  Implémente le design pattern Strategy
   */
class ExportStrategy {
public:

    /*!
         *  \brief save
         *
         *  Methode virtuelle pure mise en place pour l'application du design pattern strategy
         *
         *  \param f : nom du fichier de destination
         */
    virtual void save(const QString& f) = 0;
};

/*! \class ExportXML
   * \brief classe permettant l'export des evenements programmés dans un fichier XML
   *
   * Implémentation de l'interface d'export ExportStrategy pour l'export vers un fichier XML
   *
   */
class ExportXML : public ExportStrategy {
public:
    /*!
         *  \brief save
         *
         *  Redéfinition de la méthode save pour l'export vers fichier XML
         *
         *  \param f : nom du fichier de destination
         */
    void save(const QString& f);
};

#endif // EXPORT_H
