#include "tacheunitaire.h"


void TacheUnitaire::commencer()
{
    setDebut(QDateTime::currentDateTime());
    setFin(getDebut().addSecs(getDuree().getDureeEnMinutes()*60));
}
