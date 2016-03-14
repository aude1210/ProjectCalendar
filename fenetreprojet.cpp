#include "fenetreprojet.h"
#include "projetmanager.h"

FenetreProjet::FenetreProjet(QMainWindow *parent) : QMainWindow(parent)
{
    fenetreProjet = new QWidget;
    setWindowTitle("Ajouter un Projet");

    idProjet = new QLineEdit;
    titreProjet = new QLineEdit;
    descriptionProjet = new QTextEdit;
    dispoProjet = new QDateTimeEdit(QDateTime::currentDateTime());
    echeanceProjet = new QDateTimeEdit(QDateTime::currentDateTime());
    enregistrerProjet = new QPushButton("Enregister");
    enregistrerProjet->setDisabled(true);
    quitter= new QPushButton("quitter");

    layout21Form = new QFormLayout;
    layout21Form->addRow("Id", idProjet);
    layout21Form->addRow("Titre", titreProjet);
    layout21Form->addRow("Descritpion", descriptionProjet);
    layout21Form->addRow("Date de disponnibilite", dispoProjet);
    layout21Form->addRow("Date d'echeance", echeanceProjet);

    horizontal=new QHBoxLayout;
    horizontal->addWidget(enregistrerProjet);
    horizontal->addWidget(quitter);

    layoutNouveauProjet = new QVBoxLayout;
    layoutNouveauProjet->addLayout(layout21Form);
    layoutNouveauProjet->addLayout(horizontal);

    QObject::connect(enregistrerProjet, SIGNAL(clicked()), this, SLOT(saveProjet()));
    QObject::connect(quitter, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(dispoProjet, SIGNAL(dateTimeChanged(QDateTime)), this, SLOT(checkDate(const QDateTime&)));
    QObject::connect(echeanceProjet, SIGNAL(dateTimeChanged(QDateTime)), this, SLOT(checkDate(const QDateTime&)));
    QObject::connect(idProjet, SIGNAL(textChanged(QString)), this, SLOT(checkModifier()));
    QObject::connect(titreProjet, SIGNAL(textChanged(QString)), this, SLOT(checkModifier()));
    QObject::connect(descriptionProjet, SIGNAL(textChanged()), this, SLOT(checkModifier()));
    QObject::connect(echeanceProjet, SIGNAL(dateTimeChanged(QDateTime)), this, SLOT(checkModifier()));
    QObject::connect(dispoProjet, SIGNAL(dateTimeChanged(QDateTime)), this, SLOT(checkModifier()));

    groupeNouveauProjet = new QGroupBox("Rentrer un nouveau projet dans la base de donnee", this);
    groupeNouveauProjet->setLayout(layoutNouveauProjet);

    layout = new QHBoxLayout;
    layout->addWidget(groupeNouveauProjet);

    fenetreProjet->setLayout(layout);

    setCentralWidget(fenetreProjet);
}

void FenetreProjet::checkModifier(){
    if(!idProjet->text().isEmpty() && !titreProjet->text().isEmpty() && !descriptionProjet->toPlainText().isEmpty() && dispoProjet->dateTime().secsTo(echeanceProjet->dateTime())>0){
        enregistrerProjet->setEnabled(true);
    }
    else enregistrerProjet->setDisabled(true);
}


void FenetreProjet::saveProjet()
{
    ProjetManager& pm= ProjetManager::getInstance();
    if(pm.trouverProjet(idProjet->text()))
        QMessageBox::warning(this, "erreur","sauvegarde impossible, id deja utilise");
    else {
        pm.ajouterProjet(idProjet->text(), titreProjet->text(), descriptionProjet->toPlainText(), dispoProjet->dateTime(), echeanceProjet->dateTime());
        QMessageBox::about(this, "bravo", "projet ajouté");
        this->close();
    }
}



void FenetreProjet::checkDate(const QDateTime& d){
    if(d==dispoProjet->dateTime() && d<QDateTime::currentDateTime())
        dispoProjet->setDateTime(QDateTime::currentDateTime());
    if(d==dispoProjet->dateTime() && echeanceProjet->dateTime()<dispoProjet->dateTime())
        echeanceProjet->setDateTime(dispoProjet->dateTime());
    else if (d==echeanceProjet->dateTime() && echeanceProjet->dateTime()<dispoProjet->dateTime())
            dispoProjet->setDateTime(echeanceProjet->dateTime());
}
