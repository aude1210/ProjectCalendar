#include "fenetresupmodprogrammation.h"

class Activite; class Reunion; class Rdv;

FenetreSupModProg::FenetreSupModProg(QMainWindow *parent):QMainWindow(parent){
    Agenda& A = Agenda::getInstance();
    fenetreSupModProg = new QWidget;
    setWindowTitle("Supprimer ou modifier une programmation");

    idEvenement = new QComboBox;
    idEvenement->addItem("");
    listeTitresEvenements.push_back("");
    listeEvenements.push_back(0);
    listeDisposEvenements.push_back(QDateTime());
    listeEcheancesEvenements.push_back(QDateTime());
    listeProgsEvenements.push_back(QDateTime());
    for(Agenda::programmations_iterator it = A.begin_programmations() ; it != A.end_programmations() ; ++it){
        idEvenement->addItem((*it)->getEvenement()->getId());
        listeEvenements.push_back((*it)->getEvenement());
        listeTitresEvenements.push_back((*it)->getEvenement()->getTitre());
        listeDisposEvenements.push_back((*it)->getEvenement()->getDate());
        listeEcheancesEvenements.push_back((*it)->getEvenement()->getEcheance());
        QDate dateProg = (*it)->getDate().date();
        QTime heureProg = QTime((*it)->getHoraire().getHeure(), (*it)->getHoraire().getMinute());
        listeProgsEvenements.push_back(QDateTime(dateProg,heureProg));
    }
    titreEvenement = new QLineEdit;
    titreEvenement->setReadOnly(true);

    dispoEvenement = new QDateTimeEdit;
    dispoEvenement->setReadOnly(true);
    echeanceEvenement = new QDateTimeEdit;
    echeanceEvenement->setReadOnly(true);
    dateHeureProg = new QDateTimeEdit;

    modifierProg = new QPushButton("Modifier");
    supprimerProg = new QPushButton("Supprimer");
    reinitProg = new QPushButton("Réinitialiser");

    layoutForm = new QFormLayout;
    layoutForm->addRow("ID",idEvenement);
    layoutForm->addRow("Titre", titreEvenement);
    layoutForm->addRow("Disponibilité", dispoEvenement);
    layoutForm->addRow("Echeance", echeanceEvenement);
    layoutForm->addRow("Date et heure", dateHeureProg);

    layoutButtons = new QHBoxLayout;
    layoutButtons->addWidget(modifierProg);
    layoutButtons->addWidget(supprimerProg);
    layoutButtons->addWidget(reinitProg);

    Vlayout1 = new QVBoxLayout;
    Vlayout1->addLayout(layoutForm);
    Vlayout1->addLayout(layoutButtons);

    groupeSupModProg = new QGroupBox("Modifier ou supprimer la programmation d'événement du calendrier", this);
    groupeSupModProg->setLayout(Vlayout1);

    layout = new QVBoxLayout;
    layout->addWidget(groupeSupModProg);

    fenetreSupModProg->setLayout(layout);
    setCentralWidget(fenetreSupModProg);

    QObject::connect(idEvenement, SIGNAL(currentIndexChanged(int)), this, SLOT(updateInfosEvenement()));
    QObject::connect(reinitProg, SIGNAL(clicked()),this, SLOT(updateInfosEvenement()));
    QObject::connect(modifierProg, SIGNAL(clicked()), this, SLOT(modifierProgrammtion()));
    QObject::connect(supprimerProg, SIGNAL(clicked()), this, SLOT(supprimerProgrammation()));

}

void FenetreSupModProg::updateInfosEvenement(){
    int i = idEvenement->currentIndex();
    QString titre = listeTitresEvenements[i];
    titreEvenement->setText(titre);
    QDateTime dispo = listeDisposEvenements[i];
    dispoEvenement->setDateTime(dispo);
    QDateTime echeance = listeEcheancesEvenements[i];
    echeanceEvenement->setDateTime(echeance);
    QDateTime prog = listeProgsEvenements[i];
    dateHeureProg->setDateTime(prog);
}

void FenetreSupModProg::supprimerProgrammation(){
    int i = idEvenement->currentIndex();
    if(listeEvenements[i]){
        try{
            Evenement* e = listeEvenements[i];
            Agenda& A = Agenda::getInstance();
            A.supprimerProg(e);
        }
        catch(AgendaException& e){
            QMessageBox::warning(this, "Erreur",e.getInfo());
        }
    }
    this->close();
}

void FenetreSupModProg::modifierProgrammtion(){
    int i = idEvenement->currentIndex();
    if (dateHeureProg->dateTime() != listeProgsEvenements[i]){ //La date de programmation a pas été changée
        if (listeEvenements[i]){ //L'événement sélectionné existe bien
            try{
                Evenement* e = listeEvenements[i];
                Programmation* p = Agenda::getInstance().trouverProgrammation(e);
                QDateTime date = dateHeureProg->dateTime();
                Horaire horaire(dateHeureProg->time().hour(), dateHeureProg->time().minute());
                p->setDate(date);
                p->setHoraire(horaire);
            }
            catch(AgendaException& e){
                QMessageBox::warning(this, "Erreur",e.getInfo());
            }
        }
    }
    this->close();
}
