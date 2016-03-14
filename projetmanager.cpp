#include"projetmanager.h"

ProjetManager::Handler ProjetManager::handler=ProjetManager::Handler();
ProjetManager::ProjetManager(): projets(0){}
ProjetManager::~ProjetManager(){} //à faire avec file

ProjetManager& ProjetManager::getInstance(){
    if (handler.instance==0) handler.instance=new ProjetManager;
    return *(handler.instance);
}

void ProjetManager::libererInstance(){
    if (handler.instance!=0) delete handler.instance;
    handler.instance=0;
}

Projet* ProjetManager::trouverProjet(const QString &id) const
{
    for(std::size_t i=0;i<projets.size();++i) {
        if (id==projets[i]->getId()) return projets[i];
    }
    return 0;
}


Projet* ProjetManager::ajouterProjet(const QString& id, const QString &ti, const QString &desc, const QDateTime &d, const QDateTime &ech)
{
    Projet* newP = new Projet(id, ti, desc, d, ech);
    projets.push_back(newP);
    return newP;
}

void ProjetManager::supprimerProjet(const QString& id)
{
    for(std::size_t i=0; i< projets.size(); ++i)
    {
        if(projets[i]->getId()==id){
            projets.erase(projets.begin()+i);
            return;
        }
    }
}
