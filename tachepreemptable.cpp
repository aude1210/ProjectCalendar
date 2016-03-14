#include "tachepreemptable.h"

void TachePreemptable::commencer()
{
    setDebut(QDateTime::currentDateTime());
    setFin(getDebut().addSecs(getDuree().getDureeEnMinutes()*60));
    setEnCours(true);
}

void TachePreemptable::interruption()
{
    if (getEnCours()==false)
    {
        //QMessageBox::warning(this,"error", "tache pas commencée");
        return;
    }
    setEnCours(false);

    int diff = getDebut().secsTo(QDateTime::currentDateTime());
    int y=getDuree().getDureeEnMinutes()*60 - diff;

    setReste(y*360);
}

void TachePreemptable::reprise()
{
    if (getEnCours()==true)
    {
        std::cout<<"Tache déja en cours";
        return;
    }
    setEnCours(true);
    setFin(QDateTime::currentDateTime().addSecs(getReste().getDureeEnMinutes()*60));
}

