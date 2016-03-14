#include "fenetreactivite.h"
#include "activitemanager.h"

FenetreActivite::FenetreActivite(QMainWindow *parent) : QMainWindow(parent)
{
    fenetreActivite = new QWidget;
    setWindowTitle("Ajouter une activité");


    idActivite = new QLineEdit;
    reunion = new QCheckBox;
    rdv = new QCheckBox;
    titreActivite = new QLineEdit;
    dispoActivite = new QDateTimeEdit(QDateTime::currentDateTime());
    echeanceActivite = new QDateTimeEdit(QDateTime::currentDateTime());
    dureeActivite = new QTimeEdit;
    lieuActivite= new QLineEdit;
    personne = new QLineEdit;
    personne->setDisabled(true);
    enregistrerActivite = new QPushButton("Enregister");
    enregistrerActivite->setDisabled(true);
    quitter = new QPushButton("quitter");


    layout21Form = new QFormLayout;
    layout21Form->addRow("Id", idActivite);
    layout21Form->addRow("Réunion", reunion);
    layout21Form->addRow("Rendez-vous", rdv);
    layout21Form->addRow("Titre", titreActivite);
    layout21Form->addRow("Date de disponnibilite", dispoActivite);
    layout21Form->addRow("Date d'echeance", echeanceActivite);
    layout21Form->addRow("Durée", dureeActivite);
    layout21Form->addRow("Lieu", lieuActivite);
    layout21Form->addRow("Interlocuteur", personne);

    horizontal=new QHBoxLayout;
    horizontal->addWidget(enregistrerActivite);
    horizontal->addWidget(quitter);

    layoutNouvelleActivite = new QVBoxLayout;
    layoutNouvelleActivite->addLayout(layout21Form);
    layoutNouvelleActivite->addLayout(horizontal);

    QObject::connect(enregistrerActivite, SIGNAL(clicked()), this, SLOT(saveActivite()));
    QObject::connect(quitter, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(dispoActivite, SIGNAL(dateTimeChanged(QDateTime)), this, SLOT(checkDate(const QDateTime&)));
    QObject::connect(echeanceActivite, SIGNAL(dateTimeChanged(QDateTime)), this, SLOT(checkDate(const QDateTime&)));
    QObject::connect(reunion, SIGNAL(stateChanged(int)), this, SLOT(checkType()));
    QObject::connect(rdv, SIGNAL(stateChanged(int)), this, SLOT(checkType()));
    QObject::connect(idActivite, SIGNAL(textChanged(QString)), this, SLOT(checkModifier()));
    QObject::connect(titreActivite, SIGNAL(textChanged(QString)), this, SLOT(checkModifier()));
    QObject::connect(dureeActivite, SIGNAL(dateTimeChanged(QDateTime)), this, SLOT(checkModifier()));
    QObject::connect(lieuActivite, SIGNAL(textChanged(QString)), this, SLOT(checkModifier()));
    QObject::connect(personne, SIGNAL(textChanged(QString)), this, SLOT(checkModifier()));
    QObject::connect(rdv, SIGNAL(stateChanged(int)), this, SLOT(checkModifier()));
    QObject::connect(dispoActivite, SIGNAL(dateTimeChanged(QDateTime)), this, SLOT(checkModifier()));
    QObject::connect(echeanceActivite, SIGNAL(dateTimeChanged(QDateTime)), this, SLOT(checkModifier()));


    groupeNouvelleActivite = new QGroupBox("Rentrez une nouvelle activité dans la base de donnée");
    groupeNouvelleActivite->setLayout(layoutNouvelleActivite);

    layout = new QHBoxLayout;
    layout->addWidget(groupeNouvelleActivite);

    fenetreActivite->setLayout(layout);

    setCentralWidget(fenetreActivite);
}


void FenetreActivite::saveActivite()
{
    ActiviteManager& am= ActiviteManager::getInstance();
    Duree du(dureeActivite->time().hour(), dureeActivite->time().minute());
    if(am.trouverActivite(idActivite->text()))
        QMessageBox::warning(this, "erreur","sauvegarde impossible, id deja utilise");
    else if(reunion->isChecked()){
        am.ajouterReunion(idActivite->text(), titreActivite->text(), dispoActivite->dateTime(), echeanceActivite->dateTime(), du, lieuActivite->text());
        this->close();
    }else if (rdv->isChecked()){
        am.ajouterRdv(idActivite->text(), titreActivite->text(), dispoActivite->dateTime(), echeanceActivite->dateTime(), du, personne->text(), lieuActivite->text());
        this->close();
    }else{
        am.ajouterActivite(idActivite->text(), titreActivite->text(), dispoActivite->dateTime(), echeanceActivite->dateTime(), du, lieuActivite->text());
        this->close();
    }
}

void FenetreActivite::checkModifier(){
    if(!idActivite->text().isEmpty() && !titreActivite->text().isEmpty() && !lieuActivite->text().isEmpty() && dureeActivite->time()>QTime(0,0) && dispoActivite->dateTime().secsTo(echeanceActivite->dateTime())>QTime(0,0,0).secsTo(dureeActivite->time())){
        if(rdv->isChecked() && personne->text().isEmpty())
            enregistrerActivite->setDisabled(true);
        else enregistrerActivite->setEnabled(true);
    }
    else enregistrerActivite->setDisabled(true);
}


void FenetreActivite::checkDate(const QDateTime& d){
    if(d==dispoActivite->dateTime() && d<QDateTime::currentDateTime())
        dispoActivite->setDateTime(QDateTime::currentDateTime());
    if(d==dispoActivite->dateTime() && echeanceActivite->dateTime()<dispoActivite->dateTime())
        echeanceActivite->setDateTime(dispoActivite->dateTime());
    else if (d==echeanceActivite->dateTime() && echeanceActivite->dateTime()<dispoActivite->dateTime())
            dispoActivite->setDateTime(echeanceActivite->dateTime());
}

void FenetreActivite::checkType(){
    if(reunion->isChecked()){
        personne->setEnabled(false);
        rdv->setDisabled(true);
    }else rdv->setEnabled(true);
    if (rdv->isChecked()) {
        reunion->setDisabled(true);
        personne->setEnabled(true);
    }else reunion->setEnabled(true);
    if (!rdv->isChecked() && !reunion->isChecked()){
        personne->clear();
        personne->setDisabled(true);
    }
}
