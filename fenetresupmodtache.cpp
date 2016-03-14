#include "fenetresupmodtache.h"
#include "projetmanager.h"

FenetreSupModTache::FenetreSupModTache(QMainWindow *parent) : QMainWindow(parent)
{
    fenetreSupModTache = new QWidget;
    setWindowTitle("Supprimer ou modifier une tache");

    idProjet= new QComboBox(this);
    idProjet->addItem("");
    ProjetManager& pm=ProjetManager::getInstance();
    for(ProjetManager::projets_iterator it = pm.begin_projets() ; it != pm.end_projets() ; ++it){
        idProjet->addItem((*it)->getId());
    }

    idTache = new QComboBox(this);


    titreTache = new QLineEdit;
    titreTache->setDisabled(true);
    dispoTache = new QDateTimeEdit;
    dispoTache->setDisabled(true);
    echeanceTache = new QDateTimeEdit;
    echeanceTache->setDisabled(true);
    dureeTache = new QTimeEdit;
    dureeTache->setDisabled(true);
    supprimerPrecedence=new QComboBox;
    supprimerPrecedence->setDisabled(true);
    supprimerSousTache = new QComboBox;
    supprimerSousTache->setDisabled(true);
    mod = new QPushButton("Modifier");
    mod->setDisabled(true);
    ann = new QPushButton("Réinitialiser");
    ann->setDisabled(true);
    supp = new QPushButton("supprimer");
    supp->setDisabled(true);

    layout21Form = new QFormLayout;
    layout21Form->addRow("Projet",idProjet);
    layout21Form->addRow("Id", idTache);
    layout21Form->addRow("Titre", titreTache);
    layout21Form->addRow("Date de disponnibilite", dispoTache);
    layout21Form->addRow("Date d'echeance", echeanceTache);
    layout21Form->addRow("Duree", dureeTache);
    layout21Form->addRow("Supprimer une sous tache", supprimerSousTache);
    layout21Form->addRow("Supprimer une relation de précédence", supprimerPrecedence);

    horizontal=new QHBoxLayout;
    horizontal->addWidget(supp);
    horizontal->addWidget(mod);
    horizontal->addWidget(ann);

    layoutTache = new QVBoxLayout;
    layoutTache->addLayout(layout21Form);
    layoutTache->addLayout(horizontal);

    groupeTache = new QGroupBox("Supprimer ou modifier une tache", this);
    groupeTache->setLayout(layoutTache);

    layout = new QHBoxLayout;
    layout->addWidget(groupeTache);

    fenetreSupModTache->setLayout(layout);

    setCentralWidget(fenetreSupModTache);

    QObject::connect(idProjet, SIGNAL(currentIndexChanged(int)), this, SLOT(loadTache()));
    QObject::connect(idTache, SIGNAL(currentIndexChanged(int)), this, SLOT(load()));
    QObject::connect(mod, SIGNAL(clicked()), this, SLOT(modifier()));
    QObject::connect(mod, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(ann, SIGNAL(clicked()), this, SLOT(load()));
    QObject::connect(supp, SIGNAL(clicked()), this, SLOT(supprimer()));
    QObject::connect(supp, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(dispoTache, SIGNAL(dateTimeChanged(QDateTime)), this, SLOT(checkDate(const QDateTime&)));
    QObject::connect(echeanceTache, SIGNAL(dateTimeChanged(QDateTime)), this, SLOT(checkDate(const QDateTime&)));

}


void FenetreSupModTache::loadTache(){
        ProjetManager& pm=ProjetManager::getInstance();
        if(pm.trouverProjet(idProjet->currentText())){
            idTache->clear();
            idTache->addItem("");
            Projet* projet = pm.trouverProjet(idProjet->currentText());
            for(Projet::taches_iterator it = projet->begin_taches() ; it != projet->end_taches() ; ++it){
                idTache->addItem((*it)->getId());
            }
        }
}

void FenetreSupModTache::load(){
    ProjetManager& pm=ProjetManager::getInstance();
    Tache* tache = pm.trouverProjet(idProjet->currentText())->trouverTache(idTache->currentText());
    if(tache){
        supprimerSousTache->setDisabled(true);
        supprimerSousTache->clear();
        supprimerSousTache->addItem("");
        supprimerPrecedence->clear();
        supprimerPrecedence->addItem("");
        supprimerPrecedence->setEnabled(true);
        dureeTache->clear();
        mod->setEnabled(true);
        ann->setEnabled(true);
        supp->setEnabled(true);
        titreTache->setEnabled(true);
        dispoTache->setEnabled(true);
        echeanceTache->setEnabled(true);
        dureeTache->setDisabled(true);
        titreTache->setText(tache->getTitre());
        dispoTache->setDateTime(tache->getDate());
        echeanceTache->setDateTime(tache->getEcheance());
        for(precedences_iterator it = tache->begin_precedences() ; it != tache->end_precedences() ; ++it){
            supprimerPrecedence->addItem((*it)->getId());
        }
        if (typeid(*tache)==typeid(TacheUnitaire)){
            QTime time(tache->getDuree().getHeures(), tache->getDuree().getMinutes());
            dureeTache->setEnabled(true);
            dureeTache->setTime(time);
        }
        if (typeid(*tache)==typeid(TacheComposite)){
            supprimerSousTache->setEnabled(true);
            for(soustaches_iterator it = tache->begin_soustaches() ; it != tache->end_soustaches() ; ++it){
                supprimerSousTache->addItem((*it)->getId());
            }
        }
    }else{
            titreTache->clear();
            titreTache->setDisabled(true);
            dispoTache->clear();
            dispoTache->setDisabled(true);
            echeanceTache->clear();
            echeanceTache->setDisabled(true);
            dureeTache->clear();
            dureeTache->setDisabled(true);
            supprimerSousTache->setDisabled(true);
            supprimerSousTache->clear();
            supprimerPrecedence->setDisabled(true);
            supprimerPrecedence->clear();
        }
}

void FenetreSupModTache::modifier(){
    ProjetManager& pm= ProjetManager::getInstance();
    Duree du(dureeTache->time().hour(), dureeTache->time().minute());
    Tache* tache = pm.trouverProjet(idProjet->currentText())->trouverTache(idTache->currentText());
    tache->setTitre(titreTache->text());
    tache->setDateDisponibilite(dispoTache->dateTime());
    tache->setEcheance(echeanceTache->dateTime());
    tache->supprimerPrecedence(supprimerPrecedence->currentText());
    if (typeid(*tache)==typeid(TacheComposite)){
        tache->supprimerSousTache(supprimerSousTache->currentText());
        pm.trouverProjet(idProjet->currentText())->supprimerTache(supprimerSousTache->currentText());
    }
    if (typeid(*tache)==typeid(TacheUnitaire)){
        tache->setDuree(du);

    }

}

void FenetreSupModTache::checkDate(const QDateTime& d){
    if(d==dispoTache->dateTime() && echeanceTache->dateTime()<dispoTache->dateTime())
        echeanceTache->setDateTime(dispoTache->dateTime());
    if (d==echeanceTache->dateTime() && echeanceTache->dateTime()<dispoTache->dateTime())
        dispoTache->setDateTime(echeanceTache->dateTime());
}

void FenetreSupModTache::supprimer(){
    ProjetManager& pm= ProjetManager::getInstance();
    pm.trouverProjet(idProjet->currentText())->supprimerTache(idTache->currentText());
}


