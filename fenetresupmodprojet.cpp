#include "fenetresupmodprojet.h"
#include "projetmanager.h"

FenetreSupModProjet::FenetreSupModProjet(QMainWindow *parent) : QMainWindow(parent)
{
    fenetreSupModProjet = new QWidget;
    setWindowTitle("Supprimer ou modifier un projet");

    idProjet = new QComboBox(this);
    idProjet->addItem("");
    ProjetManager& pm=ProjetManager::getInstance();
    for(ProjetManager::projets_iterator it = pm.begin_projets() ; it != pm.end_projets() ; ++it){
        idProjet->addItem((*it)->getId());
    }

    titreProjet = new QLineEdit;
    titreProjet->setDisabled(true);
    descriptionProjet = new QTextEdit;
    descriptionProjet->setDisabled(true);
    dispoProjet = new QDateTimeEdit;
    dispoProjet->setDisabled(true);
    echeanceProjet = new QDateTimeEdit;
    echeanceProjet->setDisabled(true);
    mod = new QPushButton("Modifier");
    mod->setDisabled(true);
    ann = new QPushButton("Réinitialiser");
    ann->setDisabled(true);
    supp = new QPushButton("supprimer");
    supp->setDisabled(true);

    layout21Form = new QFormLayout;
    layout21Form->addRow("Id", idProjet);
    layout21Form->addRow("Titre", titreProjet);
    layout21Form->addRow("Descritpion", descriptionProjet);
    layout21Form->addRow("Date de disponnibilite", dispoProjet);
    layout21Form->addRow("Date d'echeance", echeanceProjet);

    horizontal=new QHBoxLayout;
    horizontal->addWidget(supp);
    horizontal->addWidget(mod);
    horizontal->addWidget(ann);

    layoutProjet = new QVBoxLayout;
    layoutProjet->addLayout(layout21Form);
    layoutProjet->addLayout(horizontal);

    QObject::connect(idProjet, SIGNAL(currentIndexChanged(int)), this, SLOT(load()));
    QObject::connect(mod, SIGNAL(clicked()), this, SLOT(modifier()));
    QObject::connect(mod, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(ann, SIGNAL(clicked()), this, SLOT(load()));
    QObject::connect(supp, SIGNAL(clicked()), this, SLOT(supprimer()));
    QObject::connect(supp, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(dispoProjet, SIGNAL(dateTimeChanged(QDateTime)), this, SLOT(checkDate(const QDateTime&)));
    QObject::connect(echeanceProjet, SIGNAL(dateTimeChanged(const QDateTime&)), this, SLOT(checkDate(const QDateTime&)));

    groupeProjet = new QGroupBox("Rentrer un nouveau projet dans la base de donnee", this);
    groupeProjet->setLayout(layoutProjet);

    layout = new QHBoxLayout;
    layout->addWidget(groupeProjet);

    fenetreSupModProjet->setLayout(layout);

    setCentralWidget(fenetreSupModProjet);
}

void FenetreSupModProjet::load(){    
    ProjetManager& pm= ProjetManager::getInstance();
    if(pm.trouverProjet(idProjet->currentText())){
        mod->setEnabled(true);
        ann->setEnabled(true);
        supp->setEnabled(true);
        titreProjet->setEnabled(true);
        descriptionProjet->setEnabled(true);
        dispoProjet->setEnabled(true);
        echeanceProjet->setEnabled(true);
        titreProjet->setText(pm.trouverProjet(idProjet->currentText())->getTitre());
        descriptionProjet->setText(pm.trouverProjet(idProjet->currentText())->getDesc());
        dispoProjet->setDateTime(pm.trouverProjet(idProjet->currentText())->getDispo());
        echeanceProjet->setDateTime(pm.trouverProjet(idProjet->currentText())->getEcheance());
    }else {
        titreProjet->clear();
        titreProjet->setDisabled(true);
        descriptionProjet->clear();
        descriptionProjet->setDisabled(true);
        dispoProjet->clear();
        dispoProjet->setDisabled(true);
        echeanceProjet->clear();
        echeanceProjet->setDisabled(true);
    }


}

void FenetreSupModProjet::modifier(){
    ProjetManager& pm= ProjetManager::getInstance();
    pm.trouverProjet(idProjet->currentText())->setTitre(titreProjet->text());
    pm.trouverProjet(idProjet->currentText())->setDesc(descriptionProjet->toPlainText());
    pm.trouverProjet(idProjet->currentText())->setDispo(dispoProjet->dateTime());
    pm.trouverProjet(idProjet->currentText())->setEcheance(echeanceProjet->dateTime());
}

void FenetreSupModProjet::checkDate(const QDateTime& d){
    if(d==dispoProjet->dateTime() && echeanceProjet->dateTime()<dispoProjet->dateTime())
        echeanceProjet->setDateTime(dispoProjet->dateTime());
    else if (d==echeanceProjet->dateTime() && echeanceProjet->dateTime()<dispoProjet->dateTime())
            dispoProjet->setDateTime(echeanceProjet->dateTime());
}

void FenetreSupModProjet::supprimer(){
    ProjetManager& pm= ProjetManager::getInstance();
    pm.supprimerProjet(idProjet->currentText());
}
