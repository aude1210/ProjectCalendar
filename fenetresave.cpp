#include "fenetresave.h"

FenetreSave::FenetreSave(){
    QString filename = getSaveFileName(this, tr("Save project"), "..", tr("XML Files (*.xml)"));
    if(filename != ""){
        ProjetManager::getInstance().save(new ExportXML, filename);
    }
}
