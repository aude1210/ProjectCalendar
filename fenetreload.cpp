#include "fenetreload.h"

FenetreLoad::FenetreLoad(){
    QString filename = getOpenFileName(this, tr("Load project"), "..", tr("XML Files (*.xml)"));
    if (filename != ""){
        ProjetManager::getInstance().load(new ImportXML, filename);
    }
}
