#include <string>
#include <iostream>
#include "evenement.h"



bool operator ==(const Evenement& e1, const Evenement& e2){
    return(e1.getDate()==e2.getDate() && e1.getEcheance()==e2.getEcheance() && e1.getId()==e2.getId() && e1.getTitre()==e2.getTitre());
}
