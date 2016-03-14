#include "tachecomposite.h"


Tache* TacheComposite::trouverTache(const QString& id)const{
    for(std::size_t i=0;i<soustaches.size();++i) {
        if (id==soustaches[i]->getId()) return soustaches[i];
    }
    return 0;
}


void TacheComposite::supprimerSousTache(const QString& ident){
    for(std::size_t i=0;i<soustaches.size();++i) {
        if (ident==soustaches[i]->getId())
        {
            soustaches.erase(soustaches.begin()+i);
            return;
        }
    }
}

void TacheComposite::commencer()
{
    setDebut(QDateTime::currentDateTime());
}

