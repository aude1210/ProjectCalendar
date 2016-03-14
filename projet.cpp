#include "projet.h"

Tache* Projet::trouverTache(const QString& id)const{
    for(std::size_t i=0;i<taches.size();++i) {
        if (id==taches[i]->getId()) return taches[i];
    }
    return 0;
}



TacheUnitaire& Projet::ajouterTacheUnitaire(const QString& id, const QString& t, const QDateTime &dispo, const QDateTime &deadline, const Duree &dur, bool b){
    if (trouverTache(id)) throw ProjetException("erreur, tache deja existante dans le projet");
    TacheUnitaire* newt=new TacheUnitaire(id,t,dispo,deadline, dur, b);
    addItem(newt);
    return *newt;
}

TachePreemptable& Projet::ajouterTachePreemptable(const QString& id, const QString& t, const QDateTime& dispo, const QDateTime& deadline, const Duree& dur, bool b){
    if (trouverTache(id)) throw ProjetException("erreur, tache deja existante dans le projet");
    TachePreemptable* newt=new TachePreemptable(id,t,dispo,deadline, dur, b);
    addItem(newt);
    return *newt;
}


TacheComposite& Projet::ajouterTacheComposite(const QString& id, const QString& t, const QDateTime &dispo, const QDateTime &deadline, bool b){
    if (trouverTache(id)) throw ProjetException("erreur, tache deja existante dans le projet");
    TacheComposite* newt=new TacheComposite(id,t,dispo,deadline, b);
    addItem(newt);
    return *newt;
}

void Projet::supprimerTache(const QString& ident){
    for(std::size_t i=0;i<taches.size();++i) {
        if (ident==taches[i]->getId())
        {
            if (taches[i]->getStatus()){
                throw ProjetException("erreur, supprimer d'abord la programmation de cette tache");
            }
            taches.erase(taches.begin()+i);
            return;
        }
    }
}

Tache& Projet::getTache(const QString& id){
    Tache* t=trouverTache(id);
    return *t;
}

void Projet::addItem(Tache* t){
    taches.push_back(t);
}

const Tache& Projet::getTache(const QString& id)const{
    return const_cast<Projet*>(this)->getTache(id);
}


std::ostream& operator<<(std::ostream& f, const Projet& p){
    f<<p.getId().toStdString()<<"\n";
    f<<p.getTitre().toStdString()<<"\n";
    f<<p.getDesc().toStdString()<<"\n";
    f<<qPrintable(p.getDispo().toString(Qt::ISODate))<<"\n";
    f<<qPrintable(p.getEcheance().toString(Qt::ISODate))<<"\n";
    f<<"\n";
    return f;
}



