#ifndef TREEVIEW
#define TREEVIEW

/*!
 * \file treeview.h
 * \brief Fichier gerant l'affichage du Tree View
 */

#include "qt.h"
#include "projetmanager.h"

/*! \class TreeView
   * \brief classe qui permet l'affichage du widget tree view avec les projets à jour
   *
   *  La classe TreeView permet d'avoir une vue d'enseble du projet
   *
   */

class TreeView : public QTreeWidget{
    Q_OBJECT
private:
    vector<QTreeWidgetItem*> items;/*!< vector contenant tous les item du tree view*/
    QTreeWidgetItem* projetToTreeView(Projet* projet);/*!< convertir un projet en un item ajoutable au tree view*/
    QTreeWidgetItem* tacheToTreeView(Tache* tache);/*!< convertir une tache en un item ajoutable au tree view*/
public:

    TreeView(QTreeWidget* parent = 0);
    ~TreeView();

public slots:
    void updateTreeView();/*!< Slot permettant la mise à jour du tree view apres l'ajout d'une tache/activité/projet dans le logiciel */
};

#endif // TREEVIEW

