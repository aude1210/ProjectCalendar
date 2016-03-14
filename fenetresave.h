#ifndef FENETRESAVE_H
#define FENETRESAVE_H

/*!
 * \file fenetresave.h
 * \brief Fichier de déclaration de la classe FenetreSave
 */

#include "qt.h"
#include "mainwindow.h"

/*! \class FenetreSave
   * \brief Fenetre permettant la sauvegarde du calendrier
   *
   *  Classe dérivée de QFileDialog permettant la sauvegarde du calendrier dans un fichier choisi
   *
   */

class FenetreSave : public QFileDialog{
    Q_OBJECT
public:
    FenetreSave(); /*< Constructeur : affiche une fentere de choix du fichier de sauvegarde puis exporte le calendrier dans ce fichier avec la méthode save() de ProjetManager */
};


#endif // FENETRESAVE_H

