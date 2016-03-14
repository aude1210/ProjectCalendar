#include "fenetresupmodactivite.h"
#include "activitemanager.h"

FenetreSupModActivite::FenetreSupModActivite(QMainWindow *parent) : QMainWindow(parent)
{
    fenetreSupModActivite = new QWidget;
    setWindowTitle("Supprimer ou modifier une activite");

    idActivite = new QComboBox(this);
    idActivite->addItem("");
    ActiviteManager& am=ActiviteManager::getInstance();
    for(ActiviteManager::activites_iterator it = am.begin_activites() ; it != am.end_activites() ; ++it){
        idActivite->addItem((*it)->getId());
    }

    titreActivite = new QLineEdit;
    titreActivite->setDisabled(true);
    dispoActivite = new QDateTimeEdit;
    dispoActivite->setDisabled(true);
    echeanceActivite = new QDateTimeEdit;
    echeanceActivite->setDisabled(true);
    dureeActivite = new QTimeEdit;
    dureeActivite->setDisabled(true);
    lieuActivite = new QLineEdit;
    lieuActivite->setDisabled(true);
    personne = new QLineEdit;
    personne->setDisabled(true);
    supprimerParticipant = new QComboBox;
    supprimerParticipant->setDisabled(true);
    ajoutParticipant = new QLineEdit;
    ajoutParticipant->setDisabled(true);
    mod = new QPushButton("Modifier");
    mod->setDisabled(true);
    ann = new QPushButton("Réinitialiser");
    ann->setDisabled(true);
    supp = new QPushButton("supprimer");
    supp->setDisabled(true);

    layout21Form = new QFormLayout;
    layout21Form->addRow("Id", idActivite);
    layout21Form->addRow("Titre", titreActivite);
    layout21Form->addRow("Date de disponnibilite", dispoActivite);
    layout21Form->addRow("Date d'echeance", echeanceActivite);
    layout21Form->addRow("Duree", dureeActivite);
    layout21Form->addRow("Lieu", lieuActivite);
    layout21Form->addRow("Interlocuteur", personne);
    layout21Form->addRow("Ajouter un participant", ajoutParticipant);
    layout21Form->addRow("Supprimer un participant", supprimerParticipant);

    horizontal=new QHBoxLayout;
    horizontal->addWidget(supp);
    horizontal->addWidget(mod);
    horizontal->addWidget(ann);

    layoutActivite = new QVBoxLayout;
    layoutActivite->addLayout(layout21Form);
    layoutActivite->addLayout(horizontal);

    groupeActivite = new QGroupBox("Supprimer ou modifier une activité", this);
    groupeActivite->setLayout(layoutActivite);

    layout = new QHBoxLayout;
    layout->addWidget(groupeActivite);

    fenetreSupModActivite->setLayout(layout);

    setCentralWidget(fenetreSupModActivite);

    QObject::connect(idActivite, SIGNAL(currentIndexChanged(int)), this, SLOT(load()));
    QObject::connect(mod, SIGNAL(clicked()), this, SLOT(modifier()));
    QObject::connect(mod, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(ann, SIGNAL(clicked()), this, SLOT(load()));
    QObject::connect(supp, SIGNAL(clicked()), this, SLOT(supprimer()));
    QObject::connect(supp, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(dispoActivite, SIGNAL(dateTimeChanged(QDateTime)), this, SLOT(checkDate(const QDateTime&)));
    QObject::connect(echeanceActivite, SIGNAL(dateTimeChanged(QDateTime)), this, SLOT(checkDate(const QDateTime&)));

}

void FenetreSupModActivite::load(){
        ActiviteManager& am= ActiviteManager::getInstance();
        Activite* activite = am.trouverActivite(idActivite->currentText());
        if(activite){
            QTime time(activite->getDuree().getDureeEnHeures(), activite->getDuree().getDureeEnMinutes());
            ajoutParticipant->setDisabled(true);
            ajoutParticipant->clear();
            supprimerParticipant->setDisabled(true);
            supprimerParticipant->clear();
            personne->setDisabled(true);
            personne->clear();
            mod->setEnabled(true);
            ann->setEnabled(true);
            supp->setEnabled(true);
            titreActivite->setEnabled(true);
            dispoActivite->setEnabled(true);
            echeanceActivite->setEnabled(true);
            dureeActivite->setEnabled(true);
            lieuActivite->setEnabled(true);
            titreActivite->setText(activite->getTitre());
            dispoActivite->setDateTime(activite->getDate());
            echeanceActivite->setDateTime(activite->getEcheance());
            dureeActivite->setTime(time);
            lieuActivite->setText(activite->getLieu());
            if (typeid(*activite)==typeid(Reunion)){
                ajoutParticipant->setEnabled(true);
                supprimerParticipant->addItem("");
                supprimerParticipant->setEnabled(true);
                for(participants_iterator it = activite->begin_participants() ; it != activite->end_participants() ; ++it){
                    supprimerParticipant->addItem(*it);
                }
            }
            if (typeid(*activite)==typeid(Rdv)){
                personne->setEnabled(true);
                personne->setText(activite->getInterlocuteur());
            }
        }else{
            titreActivite->clear();
            titreActivite->setDisabled(true);
            dispoActivite->clear();
            dispoActivite->setDisabled(true);
            echeanceActivite->clear();
            echeanceActivite->setDisabled(true);
            dureeActivite->clear();
            dureeActivite->setDisabled(true);
            lieuActivite->clear();
            lieuActivite->setDisabled(true);
            ajoutParticipant->clear();
            ajoutParticipant->setDisabled(true);
            supprimerParticipant->clear();
            supprimerParticipant->setDisabled(true);
            personne->clear();
            personne->setDisabled(true);
        }
}

    void FenetreSupModActivite::modifier(){
        ActiviteManager& am= ActiviteManager::getInstance();
        Activite* activite = am.trouverActivite(idActivite->currentText());
        Duree du(dureeActivite->time().hour(), dureeActivite->time().minute());
        activite->setTitre(titreActivite->text());
        activite->setDateDisponibilite(dispoActivite->dateTime());
        activite->setEcheance(echeanceActivite->dateTime());
        activite->setDuree(du);
        if (typeid(*activite)==typeid(Reunion)){
            activite->ajouterParticipant(ajoutParticipant->text());
            activite->supprimerParticipant(supprimerParticipant->currentText());
        }
        if (typeid(*activite)==typeid(Rdv)){
            activite->setInterlocuteur(personne->text());
        }

    }

    void FenetreSupModActivite::checkDate(const QDateTime& d){
        if(d==dispoActivite->dateTime() && echeanceActivite->dateTime()<dispoActivite->dateTime())
            echeanceActivite->setDateTime(dispoActivite->dateTime());
        if (d==echeanceActivite->dateTime() && echeanceActivite->dateTime()<dispoActivite->dateTime())
            dispoActivite->setDateTime(echeanceActivite->dateTime());
    }

    void FenetreSupModActivite::supprimer(){
        ActiviteManager& am= ActiviteManager::getInstance();
        am.supprimerActivite(idActivite->currentText());
    }

