#include "qt.h"
#include <iostream>
#include "activite.h"
#include "activitemanager.h"
#include "agenda.h"
#include "evenement.h"
#include "programmation.h"
#include "projet.h"
#include "projetmanager.h"
#include "tache.h"
#include "tachecomposite.h"
#include "tacheunitaire.h"
#include "timing.h"
#include <vector>
#include <unistd.h>
#include "export.h"
#include"mainwindow.h"
#include "import.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow fenetre;
    fenetre.showMaximized();
    return app.exec();
}
