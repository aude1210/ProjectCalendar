#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    mainWindow = new QWidget;
    setWindowTitle("Project Calendar");

    //Chargement d'un fichier XML
    chargerFichier();

    //Cr�ation de 2 onglets

    barreOnglet= new QTabWidget;
    onglet1 = new QWidget;
    onglet2 = new QWidget;

    //Onglet numero 1
    Semaine = new VueSemaine(this);
    QVBoxLayout* layout1 = new QVBoxLayout;
    layout1->addWidget(Semaine);

    onglet1->setLayout(layout1);

    //Onglet numero 2

        //Projet

        label1 = new QLabel("Projet");
        nouveau = new QPushButton("Nouveau Projet");
        supmod=new QPushButton("Modifier ou supprimer Projet");

        layoutBoutonProjet = new QVBoxLayout;
        layoutBoutonProjet->addWidget(nouveau);
        layoutBoutonProjet->addWidget(supmod);


        groupeProjet = new QGroupBox("Projet", onglet2);
        groupeProjet->setLayout(layoutBoutonProjet);


        QObject::connect(nouveau, SIGNAL(clicked()), this, SLOT(ajouterProjet()));
        QObject::connect(supmod, SIGNAL(clicked()), this, SLOT(supmodProjet()));


        //Tache

        unitaire = new QPushButton("Unitaire");
        composite = new QPushButton("Composite");
        precedence = new QPushButton("Precedence");
        supmodtache =new QPushButton("Modifier ou supprimer une tache");


        layoutAjoutTache = new QHBoxLayout;
        layoutAjoutTache->addWidget(unitaire);
        layoutAjoutTache->addWidget(composite);
        layoutAjoutTache->addWidget(precedence);
        layoutTache = new QVBoxLayout;
        layoutTache->addLayout(layoutAjoutTache);
        layoutTache->addWidget(supmodtache);

        groupeTache = new QGroupBox("Tache", onglet2);
        groupeTache->setLayout(layoutTache);

        QObject::connect(unitaire, SIGNAL(clicked()), this, SLOT(ajouterTacheUnitaire()));
        QObject::connect(composite, SIGNAL(clicked()), this, SLOT(ajouterTacheComposite()));
        QObject::connect(precedence, SIGNAL(clicked()), this, SLOT(ajouterPrecedence()));
        QObject::connect(supmodtache, SIGNAL(clicked()), this, SLOT(supModTache()));


        //Activité


        nouvact= new QPushButton("Nouvelle activité");
        supmodact = new QPushButton("Modifier ou supprimer une activité"),

        layoutBoutonActivite = new QVBoxLayout;
        layoutBoutonActivite->addWidget(nouvact);
        layoutBoutonActivite->addWidget(supmodact);

        groupeActivite = new QGroupBox("Activite", this);
        groupeActivite->setLayout(layoutBoutonActivite);

        QObject::connect(nouvact,SIGNAL(clicked()), this, SLOT(nouvelleActivite()));
        QObject::connect(supmodact,SIGNAL(clicked()), this, SLOT(supModActivite()));

        // Ajouter au calendrier

        ajoutProgTache = new QPushButton("Tache");
        ajoutProgActivite= new QPushButton("Activite");
        supModProg = new QPushButton("Modifier ou supprimer une programmation");

        layoutAjoutProg  =new QHBoxLayout;
        layoutAjoutProg->addWidget(ajoutProgTache);
        layoutAjoutProg->addWidget(ajoutProgActivite);

        layoutProg = new QVBoxLayout;
        layoutProg->addLayout(layoutAjoutProg);
        layoutProg->addWidget(supModProg);

        groupeAjout = new QGroupBox("Programmer", onglet2);
        groupeAjout->setLayout(layoutProg);

        QObject::connect(ajoutProgTache, SIGNAL(clicked()), this, SLOT(ajoutTacheCalendrier()));
        QObject::connect(ajoutProgActivite, SIGNAL(clicked()), this, SLOT(ajoutActiviteCalendrier()));
        QObject::connect(supModProg,SIGNAL(clicked()), this, SLOT(supModProgrammation()));


        // Tree view

        tree =  new TreeView;

        refresh = new QPushButton("Refresh");
        refresh->setMaximumWidth(100);

        layoutTree = new QHBoxLayout;
        layoutTree->addWidget(tree);

        groupeTree = new QGroupBox("Tree-View", onglet2);
        groupeTree->setLayout(layoutTree);

        layoutDemiOnglet2 = new QVBoxLayout;
        layoutOnglet2 = new QHBoxLayout;
        layoutDemiOnglet2->addWidget(groupeProjet);
        layoutDemiOnglet2->addWidget(groupeTache);
        layoutDemiOnglet2->addWidget(groupeActivite);
        layoutDemiOnglet2->addWidget(groupeAjout);
        layoutOnglet2->addLayout(layoutDemiOnglet2);
        layoutOnglet2->addWidget(groupeTree);

        onglet2->setLayout(layoutOnglet2);



    //Cr�ation du bouton quitter

    quitter = new QPushButton("Quitter");
    quitter->setMaximumWidth(100);



        //Cr�ation d'un layout horizontal pour le bouton "quitter"
        layoutHorizontal2 = new QHBoxLayout;
        layoutHorizontal2->addWidget(quitter);
        layoutHorizontal2->addWidget(refresh);


        // Connection pour le bouton quitter
        QObject::connect(quitter, SIGNAL(clicked()), this, SLOT(close()));
        QObject::connect(refresh, SIGNAL(clicked()), this, SLOT(refreshViews()));


        //Attachement de ces onglets � la barre d'onglet

    barreOnglet->addTab(onglet1, "Calendrier");
    barreOnglet->addTab(onglet2, "Evenement");

    QObject::connect(barreOnglet, SIGNAL(currentChanged(int)), this, SLOT(refreshViews()));

    layout = new QVBoxLayout;
    layout->addWidget(barreOnglet);
    layout->addLayout(layoutHorizontal2);

    mainWindow->setLayout(layout);


    setCentralWidget(mainWindow);
}


void MainWindow::supmodProjet(){
    FenetreSupModProjet *p=new FenetreSupModProjet;
    p->show();
}

void MainWindow::ajouterProjet()
{
    FenetreProjet* p= new FenetreProjet;
    p->show();
}

void MainWindow::ajouterTacheUnitaire()
{
    FenetreUnitaire *t = new FenetreUnitaire;
    t->show();
}

void MainWindow::ajouterTacheComposite()
{
    FenetreComposite *t = new FenetreComposite;
    t->show();
}

void MainWindow::supModTache(){
    FenetreSupModTache *p=new FenetreSupModTache;
    p->show();
}



void MainWindow::nouvelleActivite()
{
    FenetreActivite *p=new FenetreActivite;
    p->show();
}

void MainWindow::supModActivite()
{
    FenetreSupModActivite *p=new FenetreSupModActivite;
    p->show();
}

void MainWindow::ajouterPrecedence(){
    FenetrePrecedence* pr = new FenetrePrecedence();
    pr->show();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton ret;
    ret = QMessageBox::warning(this, tr("Project Calendar"), tr("Voulez-vous sauvegarder votre calendrier ?"),
                QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    if (ret == QMessageBox::Save){
       new FenetreSave();
        event->accept();
    }
    else if (ret == QMessageBox::Cancel)
       event->ignore();
    else if (ret == QMessageBox::Discard)
       event->accept();
}

void MainWindow::chargerFichier(){
    QMessageBox::StandardButton ret;
    ret = QMessageBox::question(this, tr("Project Calendar"), tr("Voulez-vous charger un calendrier ?"),
                QMessageBox::Yes | QMessageBox::No);
    if (ret == QMessageBox::Yes){
       new FenetreLoad();
    }
}

void MainWindow::ajoutTacheCalendrier(){
    FenetreAjoutProgTache* f = new FenetreAjoutProgTache();
    f->show();
}

void MainWindow::ajoutActiviteCalendrier()
{
    FenetreAjoutProgActivite* f = new FenetreAjoutProgActivite();
    f->show();
}

void MainWindow::supModProgrammation(){
    FenetreSupModProg* f = new FenetreSupModProg();
    f->show();
}

void MainWindow::refreshViews(){
    int onglet = barreOnglet->currentIndex();
    switch(onglet){
    case 0: Semaine->updateVueSemaine(); break;
    case 1: tree->updateTreeView(); break;
    default:break;
    }
}

