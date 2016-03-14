#ifndef FENETRELOAD_H
#define FENETRELOAD_H

/*!
 * \file fenetreload.h
 * \brief Fichier de déclaration de la classe FenetreLoad
 */

#include "qt.h"
#include "mainwindow.h"

/*! \class FenetreLoad
   * \brief Fenetre permettant de charger un calendrier depuis un fichier
   *
   *  Classe dérivée de QFileDialog permettant de charger un calendrier depuis un fichier choisi
   *
   */

class FenetreLoad : public QFileDialog{
    Q_OBJECT
public:
    FenetreLoad(); /*< Constructeur : affiche une fentere de choix du fichier à charger puis importe le calendrier dans le ProjetManager avec la méthode load() de ProjetManager */
};

#endif // FENETRELOAD_H

