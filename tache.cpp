#include "tache.h"



void Tache::addItem(Tache *t)
{
    for(std::size_t i=0; i<tachesPrecedentes.size(); i++)
    {
        if(t->getId()==tachesPrecedentes[i]->getId())
        {
            std::cout<<"tache deja présente dans la contrainte de precedence";
            return;
        }
    }
    if((this->getEcheance())<(t->getDate()))
    {
        std::cout<<"Tache précédente finie avant que notre tache commence";
        return;
    }
    tachesPrecedentes.push_back(t);
}

