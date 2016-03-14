#include "fenetreunitaire.h"
#include"projetmanager.h"
#include<QDebug>

FenetreUnitaire::FenetreUnitaire(QMainWindow* parent) : QMainWindow(parent)
{
    fenetreUnitaire = new QWidget;
    setWindowTitle("Ajouter une tache unitaire");

    idProjet = new QComboBox;
    idProjet->addItem("");
    ProjetManager& pm=ProjetManager::getInstance();
    for(ProjetManager::projets_iterator it = pm.begin_projets() ; it != pm.end_projets() ; ++it){
        idProjet->addItem((*it)->getId());
    }
    dispoProjet= new QDateTimeEdit;
    echeanceProjet = new QDateTimeEdit;
    dispoProjet->setReadOnly(true);
    echeanceProjet->setReadOnly(true);
    idComposite = new QComboBox;
    idComposite->addItem("");
    idComposite->setDisabled(true);
    idUnitaire = new QLineEdit;
    idUnitaire->setDisabled(true);
    titreUnitaire = new QLineEdit;
    titreUnitaire->setDisabled(true);
    dispoUnitaire = new QDateTimeEdit(QDateTime::currentDateTime());
    dispoUnitaire->setDisabled(true);
    echeanceUnitaire = new QDateTimeEdit(QDateTime::currentDateTime());
    echeanceUnitaire->setDisabled(true);
    dureeUnitaire = new QTimeEdit;
    dureeUnitaire->setDisabled(true);
    preemptive = new QCheckBox;
    preemptive->setDisabled(true);
    enregistrerUnitaire = new QPushButton("Enregistrer");
    enregistrerUnitaire->setDisabled(true);
    quitterUnitaire = new QPushButton("Quitter");


    layoutTitreProjetDispoEcheanceDuree = new QFormLayout;
    layoutTitreProjetDispoEcheanceDuree->addRow("Projet", idProjet);
    layoutTitreProjetDispoEcheanceDuree->addRow("Dispo projet", dispoProjet);
    layoutTitreProjetDispoEcheanceDuree->addRow("Echeance projet", echeanceProjet);
    layoutTitreProjetDispoEcheanceDuree->addRow("Composite : ", idComposite);
    layoutTitreProjetDispoEcheanceDuree->addRow("ID", idUnitaire);
    layoutTitreProjetDispoEcheanceDuree->addRow("preemptive", preemptive);
    layoutTitreProjetDispoEcheanceDuree->addRow("Titre", titreUnitaire);
    layoutTitreProjetDispoEcheanceDuree->addRow("Dispo", dispoUnitaire);
    layoutTitreProjetDispoEcheanceDuree->addRow("Echeance", echeanceUnitaire);
    layoutTitreProjetDispoEcheanceDuree->addRow("Duree", dureeUnitaire);

    layoutEnregistrerQuitter  =new QHBoxLayout;
    layoutEnregistrerQuitter->addWidget(enregistrerUnitaire);
    layoutEnregistrerQuitter->addWidget(quitterUnitaire);

    layoutUnitaire = new QVBoxLayout;
    layoutUnitaire->addLayout(layoutTitreProjetDispoEcheanceDuree);
    layoutUnitaire->addLayout(layoutEnregistrerQuitter);

    groupeUnitaire = new QGroupBox("Ajouter une nouvelle tache unitaire",fenetreUnitaire);
    groupeUnitaire->setLayout(layoutUnitaire);

    layout=new QVBoxLayout;
    layout->addWidget(groupeUnitaire);

    fenetreUnitaire->setLayout(layout);

    setCentralWidget(fenetreUnitaire);

    QObject::connect(idProjet, SIGNAL(currentIndexChanged(int)), this, SLOT(load()));
    QObject::connect(enregistrerUnitaire, SIGNAL(clicked()), this, SLOT(enregistrerTacheUnitaire()));
    QObject::connect(dispoUnitaire, SIGNAL(dateTimeChanged(const QDateTime)), this, SLOT(checkDate(const QDateTime)));
    QObject::connect(echeanceUnitaire, SIGNAL(dateTimeChanged(const QDateTime)), this, SLOT(checkDate(const QDateTime)));
    QObject::connect(quitterUnitaire, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(idUnitaire, SIGNAL(textChanged(QString)), this, SLOT(checkModifier()));
    QObject::connect(titreUnitaire, SIGNAL(textChanged(QString)), this, SLOT(checkModifier()));
    QObject::connect(dureeUnitaire, SIGNAL(timeChanged(QTime)), this, SLOT(checkModifier()));
    QObject::connect(dispoUnitaire, SIGNAL(dateTimeChanged(QDateTime)), this, SLOT(checkModifier()));
    QObject::connect(echeanceUnitaire, SIGNAL(dateTimeChanged(QDateTime)), this, SLOT(checkModifier()));
}

void FenetreUnitaire::checkModifier(){
    if(!idProjet->currentText().isEmpty() && !idUnitaire->text().isEmpty() && !titreUnitaire->text().isEmpty() && dureeUnitaire->time()>QTime(0,0) && dispoUnitaire->dateTime().secsTo(echeanceUnitaire->dateTime())>QTime(0,0,0).secsTo(dureeUnitaire->time())){
        if (!preemptive->isChecked() && dureeUnitaire->time()>QTime(12,00))
            enregistrerUnitaire->setDisabled(true);
        else enregistrerUnitaire->setEnabled(true);
    }
    else enregistrerUnitaire->setDisabled(true);
}


void FenetreUnitaire::enregistrerTacheUnitaire()
{
    Duree du(dureeUnitaire->time().hour(), dureeUnitaire->time().minute());
    ProjetManager& pm = ProjetManager::getInstance();
    Projet* projet = pm.trouverProjet(idProjet->currentText());
    if(projet->trouverTache(idUnitaire->text()))
    {
        QMessageBox::warning(this, "erreur","sauvegarde impossible, tache deja existante");
        dispoUnitaire->setDateTime(QDateTime::currentDateTime());
        echeanceUnitaire->setDateTime(QDateTime::currentDateTime());
    }
    else if(projet->getEcheance()<echeanceUnitaire->dateTime())
    {
        QMessageBox::warning(this, "erreur","sauvegarde impossible, date d'échéance de la tache postérieure à la date d'échéance du projet");
        echeanceUnitaire->setDateTime(QDateTime::currentDateTime());
    }
    else if(projet->getDispo()>dispoUnitaire->dateTime())
    {
        QMessageBox::warning(this, "erreur","sauvegarde impossible, date de dispo de la tache antérieure a la date de dispo du projet");
        dispoUnitaire->setDateTime(QDateTime::currentDateTime());
    }
    else if(preemptive->isChecked())
    {
        if(idComposite->currentText()!="")
        {
            if(projet->getTache(idComposite->currentText()).getEcheance()<echeanceUnitaire->dateTime())
            {
                QMessageBox::warning(this, "erreur", "date echeance de la composite inferieure a l'echeance de la tache que vous ajoutez");
            }
            else if(projet->getTache(idComposite->currentText()).getDate()>dispoUnitaire->dateTime())
            {
                QMessageBox::warning(this, "erreur", "date dispo de la composite superieure a la dispo que la date que vous ajoutez");
            }
            else {
                projet->ajouterTacheUnitaire(idUnitaire->text(),titreUnitaire->text(),dispoUnitaire->dateTime(), echeanceUnitaire->dateTime(), du);
                projet->getTache(idComposite->currentText()).ajouterSousTache(projet->trouverTache(idUnitaire->text()));
                QMessageBox::about(this, "ajout", "Tache preemptive dans composite ajoutée");
                this->close();
            }
        }else{
            pm.trouverProjet(idProjet->currentText())->ajouterTachePreemptable(idUnitaire->text(),titreUnitaire->text(),dispoUnitaire->dateTime(), echeanceUnitaire->dateTime(), du);
            QMessageBox::about(this, "ajout", "Tache préemptive ajoutée");
            this->close();
        }
    }else{
        if(idComposite->currentText()!="")
        {
            projet->ajouterTacheUnitaire(idUnitaire->text(),titreUnitaire->text(),dispoUnitaire->dateTime(), echeanceUnitaire->dateTime(), du);
            projet->getTache(idComposite->currentText()).ajouterSousTache(projet->trouverTache(idUnitaire->text()));
            QMessageBox::about(this, "ajout", "Tache unitaire dans composite ajoutée");
            this->close();
        }
        else
        {
            projet->ajouterTacheUnitaire(idUnitaire->text(),titreUnitaire->text(),dispoUnitaire->dateTime(), echeanceUnitaire->dateTime(), du);
            QMessageBox::about(this, "ajout", "Tache unitaire ajoutée");
            this->close();
       }
    }
}

void FenetreUnitaire::checkDate(const QDateTime& d)
{
    if(d==dispoUnitaire->dateTime() && d<QDateTime::currentDateTime())
        dispoUnitaire->setDateTime(QDateTime::currentDateTime());
    if(d==dispoUnitaire->dateTime() && echeanceUnitaire->dateTime()<dispoUnitaire->dateTime())
        echeanceUnitaire->setDateTime(dispoUnitaire->dateTime());
    else if (d==echeanceUnitaire->dateTime() && echeanceUnitaire->dateTime()<dispoUnitaire->dateTime())
            dispoUnitaire->setDateTime(echeanceUnitaire->dateTime());
}

void FenetreUnitaire::load()
{

    ProjetManager& pm= ProjetManager::getInstance();
    Projet* projet = pm.trouverProjet(idProjet->currentText());
    dureeUnitaire->clear();
    preemptive->setChecked(false);
    idComposite->clear();
    idUnitaire->clear();
    titreUnitaire->clear();
    echeanceUnitaire->setDateTime(QDateTime::currentDateTime());
    dispoUnitaire->setDateTime(QDateTime::currentDateTime());

    if(projet)
    {
        preemptive->setEnabled(true);
        idUnitaire->setEnabled(true);
        dispoUnitaire->setEnabled(true);
        echeanceUnitaire->setEnabled(true);
        titreUnitaire->setEnabled(true);
        dureeUnitaire->setEnabled(true);
        idComposite->setEnabled(true);
        idComposite->clear();
        idComposite->addItem("");
        dispoProjet->setDateTime(projet->getDispo());
        echeanceProjet->setDateTime(projet->getEcheance());
        for(Projet::taches_iterator it = projet->begin_taches() ; it != projet->end_taches() ; ++it){
            if(typeid(**it) == typeid(TacheComposite)){
                idComposite->addItem((*it)->getId());
            }
        }
    }else{
        dureeUnitaire->setDisabled(true);
        dispoUnitaire->setDisabled(true);
        idComposite->setDisabled(true);
        idUnitaire->setDisabled(true);
        echeanceUnitaire->setDisabled(true);
        titreUnitaire->setDisabled(true);
        preemptive->setDisabled(true);
    }
}
