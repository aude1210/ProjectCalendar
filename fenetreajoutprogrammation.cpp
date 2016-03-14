#include "fenetreajoutprogrammation.h"

FenetreAjoutProgTache::FenetreAjoutProgTache(QMainWindow *parent):QMainWindow(parent){
    fenetreAjoutProgTache = new QWidget;
    setWindowTitle("Programmer une tache");

    idProjet = new QComboBox;
    ProjetManager& pm = ProjetManager::getInstance();
    idProjet->addItem("");
    for(ProjetManager::projets_iterator it = pm.begin_projets() ; it != pm.end_projets() ; ++it){
        idProjet->addItem((*it)->getId());
    }

    idTache = new QComboBox;
    idTache->setDisabled(true);
    titreTache = new QLineEdit;
    titreTache->setReadOnly(true);
    dispoTache = new QDateTimeEdit;
    dispoTache->setReadOnly(true);
    echeanceTache = new QDateTimeEdit;
    echeanceTache->setReadOnly(true);
    dateHeureTache = new QDateTimeEdit(QDateTime::currentDateTime());
    enregistrerProgTache = new QPushButton("Enregistrer");
    quitterProgTache = new QPushButton("Quitter");

    layoutChoixProjetTache = new QFormLayout;
    layoutChoixProjetTache->addRow("Projet", idProjet);
    layoutChoixProjetTache->addRow("ID", idTache);
    layoutChoixProjetTache->addRow("Titre", titreTache);
    layoutChoixProjetTache->addRow("Disponibilité", dispoTache);
    layoutChoixProjetTache->addRow("Échéance",echeanceTache);
    layoutChoixProjetTache->addRow("Date et Heure", dateHeureTache);

    layoutEnregistrerQuitter  =new QHBoxLayout;
    layoutEnregistrerQuitter->addWidget(enregistrerProgTache);
    layoutEnregistrerQuitter->addWidget(quitterProgTache);

    Vlayout = new QVBoxLayout;
    Vlayout->addLayout(layoutChoixProjetTache);
    Vlayout->addLayout(layoutEnregistrerQuitter);

    groupeNouvelleProgTache = new QGroupBox("Rentrez une programmation");
    groupeNouvelleProgTache->setLayout(Vlayout);

    layout= new QHBoxLayout;
    layout->addWidget(groupeNouvelleProgTache);

    fenetreAjoutProgTache->setLayout(layout);
    setCentralWidget(fenetreAjoutProgTache);

    QObject::connect(quitterProgTache, SIGNAL(clicked()),this, SLOT(close()));
    QObject::connect(idProjet, SIGNAL(currentTextChanged(QString)),this, SLOT(updateIdTache(QString)));
    QObject::connect(idTache, SIGNAL(currentTextChanged(QString)), this, SLOT(updateInfosTache(QString)));
    QObject::connect(enregistrerProgTache, SIGNAL(clicked()), this, SLOT(saveProg()));
}

void FenetreAjoutProgTache::updateIdTache(QString s){
    idTache->setDisabled(false);
    idTache->clear();
    ProjetManager& pm = ProjetManager::getInstance();
    Projet* projet = pm.trouverProjet(s);
    if(projet){
        for(Projet::taches_iterator it = projet->begin_taches() ; it != projet->end_taches() ; ++it){
            if(!(*it)->getStatus()){
                idTache->addItem((*it)->getId());
            }
        }
    }
}

void FenetreAjoutProgTache::updateInfosTache(QString s){
    QString id_projet = idProjet->currentText();
    if(s!=""){
        Tache* tache = ProjetManager::getInstance().trouverProjet(id_projet)->trouverTache(s);
        titreTache->setText(tache->getTitre());
        dispoTache->setDateTime(tache->getDate());
        echeanceTache->setDateTime(tache->getEcheance());
    }
}

void FenetreAjoutProgTache::saveProg(){
    QDateTime dateHeure = dateHeureTache->dateTime();
    ProjetManager& pm = ProjetManager::getInstance();
    Projet* projet = pm.trouverProjet(idProjet->currentText());

    if(idProjet->currentText().isEmpty()){
        QMessageBox::warning(this, "Erreur","Rentrer un projet");
    }
    else if(idTache->currentText().isEmpty()){
        QMessageBox::warning(this, "Erreur","Rentrer une tache");
    }
    else if (dateHeure < projet->getDispo() || dateHeure > projet->getEcheance()){
        QMessageBox::warning(this, "Erreur","Date incompatible avec les dates du projet");
        dateHeureTache->setDateTime(QDateTime::currentDateTime());
    }
    else {
        Evenement* e = projet->trouverTache(idTache->currentText());
        Horaire horaire(dateHeure.time().hour(), dateHeure.time().minute());
        try{
        Agenda::getInstance().ajouterProg(e,dateHeure, horaire);
        this->close();
        }
        catch(AgendaException& e){
            QMessageBox::warning(this, "Erreur",e.getInfo());
        }
    }
}

FenetreAjoutProgActivite::FenetreAjoutProgActivite(QMainWindow *parent):QMainWindow(parent){

    fenetreAjoutProgActivite = new QWidget;
    setWindowTitle("Programmer une activité");

    ActiviteManager& AM = ActiviteManager::getInstance();
    idActivite = new QComboBox;
    idActivite->addItem("");
    for(ActiviteManager::activites_iterator it = AM.begin_activites() ; it != AM.end_activites() ; ++it){
        if(!(*it)->getStatus()){
            idActivite->addItem((*it)->getId());
        }
    }

    titreActivite = new QLineEdit;
    titreActivite->setReadOnly(true);

    dispoActivite = new QDateTimeEdit;
    dispoActivite->setReadOnly(true);
    echeanceActivite = new QDateTimeEdit;
    echeanceActivite->setReadOnly(true);
    dateHeureActivite = new QDateTimeEdit(QDateTime::currentDateTime());
    enregistrerProgActivite = new QPushButton("Enregistrer");
    quitterProgActivite = new QPushButton("Quitter");

    layoutChoixActivite = new QFormLayout;
    layoutChoixActivite->addRow("ID", idActivite);
    layoutChoixActivite->addRow("Titre", titreActivite);
    layoutChoixActivite->addRow("Disponibilité", dispoActivite);
    layoutChoixActivite->addRow("Échéance", echeanceActivite);
    layoutChoixActivite->addRow("Date & Heure", dateHeureActivite);

    layoutEnregistrerQuitter  =new QHBoxLayout;
    layoutEnregistrerQuitter->addWidget(enregistrerProgActivite);
    layoutEnregistrerQuitter->addWidget(quitterProgActivite);

    Vlayout = new QVBoxLayout;
    Vlayout->addLayout(layoutChoixActivite);
    Vlayout->addLayout(layoutEnregistrerQuitter);

    fenetreAjoutProgActivite->setLayout(Vlayout);
    setCentralWidget(fenetreAjoutProgActivite);

    QObject::connect(quitterProgActivite, SIGNAL(clicked()),this, SLOT(close()));
    QObject::connect(idActivite, SIGNAL(currentTextChanged(QString)), this, SLOT(updateInfosActivite(QString)));
    QObject::connect(enregistrerProgActivite, SIGNAL(clicked()), this, SLOT(saveActivite()));
}

void FenetreAjoutProgActivite::updateInfosActivite(QString s){
    Activite* activite = ActiviteManager::getInstance().trouverActivite(s);

    if (activite){
        titreActivite->setText(activite->getTitre());
        dispoActivite->setDateTime(activite->getDate());
        echeanceActivite->setDateTime(activite->getEcheance());
    }
}

void FenetreAjoutProgActivite::saveActivite(){
    QDateTime dateHeure = dateHeureActivite->dateTime();
    ActiviteManager& AM = ActiviteManager::getInstance();
    if(idActivite->currentText().isEmpty()){
        QMessageBox::warning(this, "Erreur","Rentrer une activité");
    }
    else{
        Evenement* e = AM.trouverActivite(idActivite->currentText());
        Horaire horaire(dateHeure.time().hour(), dateHeure.time().minute());
        try{
        Agenda::getInstance().ajouterProg(e,dateHeure, horaire);
        this->close();
        }
        catch(AgendaException& e){
            QMessageBox::warning(this, "Erreur",e.getInfo());
        }
    }
}
