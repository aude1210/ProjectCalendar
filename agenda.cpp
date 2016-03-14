#include "agenda.h"

Agenda::Handler Agenda::handler=Agenda::Handler();
Agenda::Agenda(): progs(0){}
Agenda::~Agenda(){} //à faire avec file

Agenda& Agenda::getInstance(){
    if (handler.instance==0) handler.instance=new Agenda;
    return *(handler.instance);
}

void Agenda::libererInstance(){
    if (handler.instance!=0) delete handler.instance;
    handler.instance=0;
}

Programmation& Agenda::ajouterProg(Evenement* e, const QDateTime& d, const Horaire& h){
    if (trouverProgrammation(e)) throw AgendaException("erreur, tache deja existante dans le projet");
    if (e->getDate()<d && d<e->getEcheance()){
        if(e->getStatus()==false){
            //on vérifie qu'une tache precédente n'est pas programmée avant la tache qu'on programme
            if (e->withPrecedence()){ //Si l'événement a des precedences
                for(precedences_iterator it = e->begin_precedences() ; it != e->end_precedences() ; ++it){
                    if((*it)->getStatus()){//Si la précédence est programmée
                        //On vérifie la cohérence des dates
                        Programmation* prog = trouverProgrammation(*it);
                        if(prog->getDate() > d)
                            throw AgendaException("Impossible de programmer une tache avant de ses tâches précédentes");
                        else if (prog->getDate() == d && h < prog->getHoraire())
                            throw AgendaException("Impossible de programmer une tache avant de ses tâches précédentes");
                    }
                }
            }
            //L'événement n'est pas encore programmé et la date choisie est cohérente avec ses taches précédentes.
            //On peut créer la programmation
            Programmation* newt=new Programmation(d,h,e);
            e->setEstProg(true);
            addItem(newt);
            return *newt;
        }else throw AgendaException("l'evenement est déjà programmé");
    }else throw AgendaException("erreur les dates ne concordent pas");
};

Programmation* Agenda::trouverProgrammation(Evenement* e) const{
    for(std::size_t i=0;i<progs.size();++i)
        if (e==progs[i]->getEvenement()) return progs[i];
    return 0;
}

vector<Programmation*>::iterator Agenda::trouverProgrammationIterator(Evenement* e){
    for(vector<Programmation*>::iterator it = progs.begin() ; it != progs.end() ; ++it)
        if (e==(*it)->getEvenement()) return it;
    return progs.end();
}

void Agenda::addItem(Programmation* p){
            progs.push_back(p);
        }



void Agenda::supprimerProg(Evenement* e)
{
    vector<Programmation*>::iterator it = trouverProgrammationIterator(e);
    if(it != progs.end()) {
        progs.erase(it);
        e->setEstProg(false);
        return;
    }
    throw AgendaException("Prog inexistante");

}
