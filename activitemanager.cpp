#include "activitemanager.h"

ActiviteManager::Handler ActiviteManager::handler=ActiviteManager::Handler();
ActiviteManager::ActiviteManager(): activites(0){}
ActiviteManager::~ActiviteManager(){}

ActiviteManager& ActiviteManager::getInstance(){
    if (handler.instance==0) handler.instance=new ActiviteManager;
    return *(handler.instance);
}

void ActiviteManager::libererInstance(){
    if (handler.instance!=0) delete handler.instance;
    handler.instance=0;
}

Activite* ActiviteManager::trouverActivite(const QString &id) const
{
    for(std::size_t i=0;i<activites.size();++i) {
        if (id==activites[i]->getId()) return activites[i];
    }
    return 0;
}

Activite* ActiviteManager::ajouterActivite(const QString& ident, const QString& t, const QDateTime& d,const QDateTime ech,const Duree& du,const QString& li,bool b)
{
    Activite* newActiv = new Activite(ident,t,d,ech,du,li,b);
    activites.push_back(newActiv);
    return newActiv;
}

Reunion* ActiviteManager::ajouterReunion(const QString& ident, const QString& t, const QDateTime& d,const QDateTime& ech,const Duree& du,const QString& li,bool b)
{
    Reunion* newReu = new Reunion(ident,t,d,ech,du,li,b);
    activites.push_back(newReu);
    return newReu;
}

Rdv* ActiviteManager::ajouterRdv(const QString& ident, const QString& t, const QDateTime& d,const QDateTime& ech,const Duree& du, const QString& pers, const QString& li,bool b)
{
    Rdv* newRdv = new Rdv(ident,t,d,ech,du,pers,li,b);
    activites.push_back(newRdv);
    return newRdv;
}

void ActiviteManager::supprimerActivite(const QString& id)
{
    for(std::size_t i=0; i< activites.size(); ++i)
    {
        if(activites[i]->getId()==id)
        {
            activites.erase(activites.begin()+i);
            return;
        }
    }
}


