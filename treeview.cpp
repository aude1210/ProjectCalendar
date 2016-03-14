#include "treeview.h"

TreeView::TreeView(QTreeWidget *parent):QTreeWidget(parent){
    updateTreeView();
}

void TreeView::updateTreeView(){
    this->clear();
    ProjetManager& pm = ProjetManager::getInstance();
    for(ProjetManager::projets_iterator it1 = pm.begin_projets() ; it1 != pm.end_projets() ; ++it1)
    {
        this->addTopLevelItem(projetToTreeView((*it1)));
    }
}

QTreeWidgetItem* TreeView::projetToTreeView(Projet* projet){
    QTreeWidgetItem* item = new QTreeWidgetItem;
    item->setText(0, projet->getTitre());
    item->setTextColor(0, Qt::blue);
    for(Projet::taches_iterator it = projet->begin_taches() ; it != projet->end_taches() ; ++it)
    {
        if(!(*it)->getInTree()){
            item->addChild(tacheToTreeView((*it)));
        }
    }
    items.push_back(item);
    return item;
}

QTreeWidgetItem* TreeView::tacheToTreeView(Tache* tache){
    QTreeWidgetItem* item = new QTreeWidgetItem;
    item->setText(0, tache->getTitre());
    if(tache->getStatus()) item->setTextColor(0,Qt::green);
    else item->setTextColor(0,Qt::red);

    if (typeid(*tache) == typeid(TacheComposite)){
        for(soustaches_iterator it = tache->begin_soustaches() ; it != tache->end_soustaches() ; ++it){
            item->addChild(tacheToTreeView((*it)));
            (*it)->setInTree(true);
        }
    }
    items.push_back(item);
    return item;
}

TreeView::~TreeView(){
    items.clear();
}
