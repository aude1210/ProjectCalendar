#include "fenetrecomposite.h"
#include "projetmanager.h"
#include<QDebug>

FenetreComposite::FenetreComposite(QMainWindow *parent) : QMainWindow(parent)
{
    tacheComposite = new QWidget;
    setWindowTitle("Ajouter une tache composite");

    titreComposite = new QLineEdit;
    titreComposite->setDisabled(true);
    dispoComposite = new QDateTimeEdit(QDateTime::currentDateTime());
    dispoComposite->setDisabled(true);
    echeanceComposite = new QDateTimeEdit(QDateTime::currentDateTime());
    echeanceComposite->setDisabled(true);
    idComposite = new QLineEdit;
    idComposite->setDisabled(true);
    idProjet = new QComboBox(this);
    idProjet->addItem("");
    dispoProjet= new QDateTimeEdit;
    echeanceProjet= new QDateTimeEdit;
    dispoProjet->setReadOnly(true);
    echeanceProjet->setReadOnly(true);
    ProjetManager& pm=ProjetManager::getInstance();
    for(ProjetManager::projets_iterator it = pm.begin_projets() ; it != pm.end_projets() ; ++it){
        idProjet->addItem((*it)->getId());
    }
    idSousCompo = new QComboBox;
    idSousCompo->addItem("");
    idSousCompo->setDisabled("true");
    enregistrerComposite = new QPushButton("Enregistrer");
    quitterComposite = new QPushButton("Quitter");

    layoutTitreProjetDispoEcheanceDuree = new QFormLayout;
    layoutTitreProjetDispoEcheanceDuree->addRow("Projet", idProjet);
    layoutTitreProjetDispoEcheanceDuree->addRow("Dispo projet", dispoProjet);
    layoutTitreProjetDispoEcheanceDuree->addRow("Echeance projet", echeanceProjet);
    layoutTitreProjetDispoEcheanceDuree->addRow("Composite : ", idSousCompo);
    layoutTitreProjetDispoEcheanceDuree->addRow("ID", idComposite);
    layoutTitreProjetDispoEcheanceDuree->addRow("Titre", titreComposite);
    layoutTitreProjetDispoEcheanceDuree->addRow("Dispo", dispoComposite);
    layoutTitreProjetDispoEcheanceDuree->addRow("Echeance", echeanceComposite);

    layoutEnregistrerQuitter  =new QHBoxLayout;
    layoutEnregistrerQuitter->addWidget(enregistrerComposite);
    layoutEnregistrerQuitter->addWidget(quitterComposite);

    layoutComposite = new QVBoxLayout;
    layoutComposite->addLayout(layoutTitreProjetDispoEcheanceDuree);
    layoutComposite->addLayout(layoutEnregistrerQuitter);

    groupeComposite = new QGroupBox("Ajouter une nouvelle tache composite", tacheComposite);
    groupeComposite->setLayout(layoutComposite);

    layout=new QVBoxLayout;
    layout->addWidget(groupeComposite);

    tacheComposite->setLayout(layout);

    setCentralWidget(tacheComposite);

    QObject::connect(idProjet, SIGNAL(currentIndexChanged(int)), this, SLOT(load()));
    QObject::connect(enregistrerComposite, SIGNAL(clicked()), this, SLOT(enregistrerTacheComposite()));
    QObject::connect(dispoComposite, SIGNAL(dateTimeChanged(const QDateTime)), this, SLOT(checkDate(const QDateTime&)));
    QObject::connect(echeanceComposite, SIGNAL(dateTimeChanged(const QDateTime&)), this, SLOT(checkDate(const QDateTime&)));
    QObject::connect(quitterComposite, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(idProjet, SIGNAL(currentIndexChanged(int)), this, SLOT(checkModifier()));
    QObject::connect(idComposite, SIGNAL(textChanged(QString)), this, SLOT(checkModifier()));
    QObject::connect(titreComposite, SIGNAL(textChanged(QString)), this, SLOT(checkModifier()));
    QObject::connect(echeanceComposite, SIGNAL(dateTimeChanged(QDateTime)), this, SLOT(checkModifier()));
    QObject::connect(dispoComposite, SIGNAL(dateTimeChanged(QDateTime)), this, SLOT(checkModifier()));
}


void FenetreComposite::checkModifier(){
    if(!idProjet->currentText().isEmpty() && !idComposite->text().isEmpty() && !titreComposite->text().isEmpty() && dispoComposite->dateTime().secsTo(echeanceComposite->dateTime())>0){
        enregistrerComposite->setEnabled(true);
    }
    else enregistrerComposite->setDisabled(true);
}


void FenetreComposite::enregistrerTacheComposite()
{
    ProjetManager& pm = ProjetManager::getInstance();
    if(!(pm.trouverProjet(idProjet->currentText())))
    {
        QMessageBox::warning(this, "erreur","sauvegarde impossible, projet inexistant");
        dispoComposite->setDateTime(QDateTime::currentDateTime());
        echeanceComposite->setDateTime(QDateTime::currentDateTime());
    }
    else if(pm.trouverProjet(idProjet->currentText())->trouverTache(idComposite->text()))
    {
        QMessageBox::warning(this, "erreur","sauvegarde impossible, tache deja existante");
        dispoComposite->setDateTime(QDateTime::currentDateTime());
        echeanceComposite->setDateTime(QDateTime::currentDateTime());
    }
    else if(pm.trouverProjet(idProjet->currentText())->getDispo()>dispoComposite->dateTime())
    {
        QMessageBox::warning(this, "erreur","sauvegarde impossible, date de dispo de la tache inferieure a la date de dispo du projet");
        dispoComposite->setDateTime(QDateTime::currentDateTime());
        echeanceComposite->setDateTime(QDateTime::currentDateTime());
    }
    else if(pm.trouverProjet(idProjet->currentText())->getEcheance()<echeanceComposite->dateTime())
    {
        QMessageBox::warning(this, "erreur","sauvegarde impossible, date d'echeance de la tache superieure a la date d'echeance du projet");
        dispoComposite->setDateTime(QDateTime::currentDateTime());
        echeanceComposite->setDateTime(QDateTime::currentDateTime());
    }
    else if(idSousCompo->currentText()!="")
    {
        if(pm.trouverProjet(idProjet->currentText())->getTache(idSousCompo->currentText()).getEcheance()<echeanceComposite->dateTime())
        {
            QMessageBox::warning(this, "erreur", "date echeance de la composite inferieure a l'echeance de la tache que vous ajoutez");
        }
        else if(pm.trouverProjet(idProjet->currentText())->getTache(idSousCompo->currentText()).getDate()>dispoComposite->dateTime())
        {
            QMessageBox::warning(this, "erreur", "date dispo de la composite superierue a la dispo que la date que vous ajoutez");
        }
        else {
        pm.trouverProjet(idProjet->currentText())->ajouterTacheComposite(idComposite->text(),titreComposite->text(),dispoComposite->dateTime(), echeanceComposite->dateTime());
        pm.trouverProjet(idProjet->currentText())->getTache(idSousCompo->currentText()).ajouterSousTache(pm.trouverProjet(idProjet->currentText())->trouverTache(idComposite->text()));
        QMessageBox::about(this, "ajout", "Tache composite dans composite ajoutée");
        this->close();
        }
    }
    else {
        pm.trouverProjet(idProjet->currentText())->ajouterTacheComposite(idComposite->text(),titreComposite->text(),dispoComposite->dateTime(), echeanceComposite->dateTime());
        QMessageBox::about(this, "ajout", "Tache composite ajoutée");
        this->close();
    }
}
void FenetreComposite::checkDate(const QDateTime& d)
{
    if(d==dispoComposite->dateTime() && echeanceComposite->dateTime()<dispoComposite->dateTime())
        echeanceComposite->setDateTime(dispoComposite->dateTime());
    else if (d==echeanceComposite->dateTime() && echeanceComposite->dateTime()<dispoComposite->dateTime())
            dispoComposite->setDateTime(echeanceComposite->dateTime());
}

void FenetreComposite::load()
{

    ProjetManager& pm= ProjetManager::getInstance();
    Projet* projet = pm.trouverProjet(idProjet->currentText());
    idComposite->clear();
    idSousCompo->clear();
    titreComposite->clear();
    echeanceComposite->setDateTime(QDateTime::currentDateTime());
    dispoComposite->setDateTime(QDateTime::currentDateTime());

    if(projet)
    {
        idSousCompo->setEnabled(true);
        titreComposite->setEnabled(true);
        echeanceComposite->setEnabled(true);
        dispoComposite->setEnabled(true);
        idComposite->setEnabled(true);
        idSousCompo->clear();
        idSousCompo->addItem("");
        dispoProjet->setDateTime(projet->getDispo());
        echeanceProjet->setDateTime(projet->getEcheance());
        for(Projet::taches_iterator it = projet->begin_taches() ; it != projet->end_taches() ; ++it){
            if(typeid(**it) == typeid(TacheComposite)){
                idSousCompo->addItem((*it)->getId());
            }
        }
    }else{
        dispoComposite->setDisabled(true);
        idComposite->setDisabled(true);
        idSousCompo->setDisabled(true);
        echeanceComposite->setDisabled(true);
        titreComposite->setDisabled(true);
    }
}
