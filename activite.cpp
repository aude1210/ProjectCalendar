

#include "activite.h"

void Reunion::ajouterParticipant(const QString & parti){
    participants.push_back(parti);
}

void Reunion::supprimerParticipant(const QString & parti){
    for(std::size_t i=0;i<participants.size();++i){
        if(participants[i] == parti){
            participants.erase(participants.begin()+i);
            return;
        }
    }
}
