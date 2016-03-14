#include "projetmanager.h"
#include "activitemanager.h"
#include "agenda.h"
#include "import.h"

void ImportXML::load(const QString& f){
    //qDebug()<<"debut load\n";
    //this->~TacheManager();
    //file=f;
    ProjetManager& PM = ProjetManager::getInstance();
    Agenda& A = Agenda::getInstance();
    QFile fin(f);
    // If we can't open it, let's show an error message.
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw AgendaException("Erreur ouverture fichier tâches");
    }
    // QXmlStreamReader takes any QIODevice.
    QXmlStreamReader xml(&fin);
    //qDebug()<<"debut fichier\n";
    // We'll parse the XML until we reach end of it.
    while(!xml.atEnd() && !xml.hasError()) {
        // Read next element.
        QXmlStreamReader::TokenType token = xml.readNext();
        // If token is just StartDocument, we'll go to next.
        if(token == QXmlStreamReader::StartDocument) continue;
        // If token is StartElement, we'll see if we can read it.
        if(token == QXmlStreamReader::StartElement) {
            // If it's named projectcalendar, we'll go to the next.
            if(xml.name() == "projectcalendar") continue;
            // If it's named projets, we dig into to find all the projects.
            if(xml.name() == "projets") {
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "projets")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                        if(xml.name() == "projet"){
                            //qDebug()<<"new projet\n";
                            QString id_projet;
                            QString titre_projet;
                            QString description_projet;
                            QDateTime disponibilite_projet;
                            QDateTime echeance_projet;

                            xml.readNext();
                            //We're going to loop over the things because the order might change.
                            //We'll continue the loop until we hit an EndElement named projet.
                            while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "projet")) {
                                if(xml.tokenType() == QXmlStreamReader::StartElement) {
                                    // We've found identificteur.
                                    if(xml.name() == "identificateur") {
                                        xml.readNext(); id_projet=xml.text().toString();
                                        //qDebug()<<"titre_projet="<<titre_projet<<"\n";
                                    }

                                    // We've found titre.
                                    if(xml.name() == "titre") {
                                        xml.readNext(); titre_projet=xml.text().toString();
                                        //qDebug()<<"titre_projet="<<titre_projet<<"\n";
                                    }
                                    // We've found description.
                                    if(xml.name() == "description") {
                                        xml.readNext(); description_projet=xml.text().toString();
                                        //qDebug()<<"description_projet="<<description_projet<<"\n";
                                    }
                                    // We've found disponibilite
                                    if(xml.name() == "disponibilite_projet") {
                                        xml.readNext();
                                        disponibilite_projet=QDateTime::fromString(xml.text().toString(),Qt::ISODate);
                                        //qDebug()<<"disp_projet="<<disponibilite_projet.toString()<<"\n";
                                    }
                                    // We've found echeance
                                    if(xml.name() == "echeance") {
                                        xml.readNext();
                                        echeance_projet=QDateTime::fromString(xml.text().toString(),Qt::ISODate);
                                        //qDebug()<<"echeanc_projete="<<echeance_projet.toString()<<"\n";
                                    }
                                    // We've found taches, we dig into to find all the taches
                                    if(xml.name() == "taches"){
                                        Projet* projet = PM.ajouterProjet(id_projet, titre_projet,description_projet,disponibilite_projet,echeance_projet);
                                        // We loop on all the taches of the <taches> element
                                        while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "taches")){
                                            if(xml.tokenType() == QXmlStreamReader::StartElement) {
                                                if(xml.name() == "tache"){
                                                    //! il faudra prendre en compte si la tache est programmée ou non
                                                    QString id_tache;
                                                    QString titre_tache;
                                                    QDateTime disponibilite_tache;
                                                    QDateTime echeance_tache;
                                                    Duree duree_tache;
                                                    bool preemptive;
                                                    bool composite;
                                                    bool unitaire;
                                                    bool programmed = false;
                                                    QDateTime date_prog;
                                                    Horaire heure_prog(1,1);

                                                    QXmlStreamAttributes attributes = xml.attributes();
                                                    if(attributes.hasAttribute("preemptive")) {
                                                        QString val =attributes.value("preemptive").toString();
                                                        preemptive=(val == "true" ? true : false);
                                                    }
                                                    if(attributes.hasAttribute("composite")) {
                                                        QString val =attributes.value("composite").toString();
                                                        composite=(val == "true" ? true : false);
                                                    }
                                                    if(attributes.hasAttribute("unitaire")) {
                                                        QString val =attributes.value("unitaire").toString();
                                                        unitaire=(val == "true" ? true : false);
                                                    }
                                                    xml.readNext();
                                                    // We loop on all the elements of the <tache> element
                                                    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "tache")){
                                                        if(xml.tokenType() == QXmlStreamReader::StartElement) {
                                                            // We've found identificteur.
                                                            if(xml.name() == "identificateur") {
                                                                xml.readNext(); id_tache=xml.text().toString();
                                                                //qDebug()<<"id="<<id_tache<<"\n";
                                                            }

                                                            // We've found titre.
                                                            if(xml.name() == "titre") {
                                                                xml.readNext(); titre_tache=xml.text().toString();
                                                                //qDebug()<<"titre="<<titre_tache<<"\n";
                                                            }
                                                            // We've found disponibilite
                                                            if(xml.name() == "disponibilite") {
                                                                xml.readNext();
                                                                disponibilite_tache=QDateTime::fromString(xml.text().toString(),Qt::ISODate);
                                                                //qDebug()<<"disp="<<disponibilite_tache.toString(Qt::ISODate)<<"\n";
                                                            }
                                                            // We've found echeance
                                                            if(xml.name() == "echeance") {
                                                                xml.readNext();
                                                                echeance_tache=QDateTime::fromString(xml.text().toString(),Qt::ISODate);
                                                                //qDebug()<<"echeance="<<echeance_tache.toString(Qt::ISODate)<<"\n";
                                                            }
                                                            // We've found duree
                                                            if(xml.name() == "duree") {
                                                                xml.readNext();
                                                                duree_tache=xml.text().toString().toInt();
                                                                //qDebug()<<"duree="<<duree_tache.getDureeEnMinutes()<<"\n";
                                                            }
                                                            // We've found programmation
                                                            if(xml.name() == "programmation") {
                                                                xml.readNext();
                                                                programmed = true;
                                                                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "programmation")){
                                                                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                                                                        if(xml.name() == "date"){
                                                                            xml.readNext();
                                                                            date_prog = QDateTime::fromString(xml.text().toString(), Qt::ISODate);
                                                                        }
                                                                        if(xml.name() == "heure"){
                                                                            xml.readNext();
                                                                            heure_prog.setFromString(xml.text().toString());
                                                                        }
                                                                    }
                                                                    xml.readNext();
                                                                }//Fin while programmation
                                                            }//Fin if programmation
                                                        }
                                                        xml.readNext();
                                                    } // Fin while tache
                                                    if (composite){
                                                        //qDebug()<<id_tache<<" "<<titre_tache<<"\n";
                                                        projet->ajouterTacheComposite(id_tache,titre_tache,disponibilite_tache,echeance_tache);
                                                    }
                                                    if (preemptive){
                                                        //qDebug()<<"load tache preemptable : "<<qPrintable(id_tache)<<" "<<qPrintable(titre_tache)<<std::endl;
                                                        projet->ajouterTachePreemptable(id_tache,titre_tache,disponibilite_tache,echeance_tache,duree_tache);
                                                    }
                                                    if (unitaire){
                                                        //qDebug()<<"load tache unitaire : "<<qPrintable(id_tache)<<" "<<qPrintable(titre_tache)<<std::endl;
                                                        projet->ajouterTacheUnitaire(id_tache,titre_tache,disponibilite_tache,echeance_tache,duree_tache);
                                                    }
                                                    if (programmed){
                                                        A.ajouterProg(projet->trouverTache(id_tache), date_prog, heure_prog);
                                                    }
                                                } // Fin if tache
                                            }
                                            xml.readNext();
                                        } // Fin while taches
                                    } // Fin if taches
                                }
                                xml.readNext();
                            } // Fin while projet
                        } // Fin if projet
                    }
                    xml.readNext();
                } // Fin while projets
            } // Fin if projets

            if(xml.name() == "precedences") {
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "precedences")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                        if(xml.name() == "precedence") {
                            QString id_projet;
                            QString id_tache;
                            QXmlStreamAttributes attributes = xml.attributes();
                            if(attributes.hasAttribute("id_projet")) {
                                id_projet =attributes.value("id_projet").toString();
                            }
                            if(attributes.hasAttribute("id_tache")) {
                                id_tache =attributes.value("id_tache").toString();
                            }
                            Tache* tache = PM.trouverProjet(id_projet)->trouverTache(id_tache);
                            xml.readNext();
                            while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "precedence")) {
                                if(xml.tokenType() == QXmlStreamReader::StartElement) {
                                    if (xml.name() == "id_precedence"){
                                        xml.readNext();
                                        Tache* preced = PM.trouverProjet(id_projet)->trouverTache(xml.text().toString());
                                        tache->addPrecedence(preced);
                                    } // Fin if id_precedence
                                }
                                xml.readNext();
                            } //Fin while precedence
                        }// Fin if precedence
                    }
                    xml.readNext();
                } // Fin while precedences
            } // Fin if precedences
            if(xml.name() == "composites"){
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "composites")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                        if(xml.name() == "composite") {
                            QString id_projet;
                            QString id_tache;
                            QXmlStreamAttributes attributes = xml.attributes();
                            if(attributes.hasAttribute("id_projet")) {
                                id_projet =attributes.value("id_projet").toString();
                            }
                            if(attributes.hasAttribute("id_tache")) {
                                id_tache =attributes.value("id_tache").toString();
                            }
                            Tache* tache = PM.trouverProjet(id_projet)->trouverTache(id_tache);
                            xml.readNext();
                            while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "composite")) {
                                if(xml.tokenType() == QXmlStreamReader::StartElement) {
                                    if (xml.name() == "id_composant"){
                                        xml.readNext();
                                        Tache* composant = PM.trouverProjet(id_projet)->trouverTache(xml.text().toString());
                                        tache->ajouterSousTache(composant);
                                    } // Fin if precedence
                                }
                                xml.readNext();
                            } //Fin while composite
                        }// Fin if composite
                    }
                    xml.readNext();
                } // Fin while composites
            } // Fin if composites
            if(xml.name() == "activites"){
                ActiviteManager& AM = ActiviteManager::getInstance();
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "activites")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                        if(xml.name() == "activite") {
                            QString id_activite, titre_activite, lieu_activite, interlocuteur_activite;
                            QDateTime dispo_activite, echeance_activite, date_prog;
                            Duree duree_activite;
                            bool reunion, rdv, programmed = false;
                            vector<QString> participants_activite;
                            Horaire heure_prog(1,1);

                            //Lecture des attributs
                            QXmlStreamAttributes attributes = xml.attributes();
                            if(attributes.hasAttribute("reunion")) {
                                QString val =attributes.value("reunion").toString();
                                reunion=(val == "true" ? true : false);
                            }
                            if(attributes.hasAttribute("rdv")) {
                                QString val =attributes.value("rdv").toString();
                                rdv=(val == "true" ? true : false);
                            }

                            xml.readNext();
                            while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "activite")){
                                if(xml.tokenType() == QXmlStreamReader::StartElement) {
                                    if(xml.name() == "identificateur") {
                                        xml.readNext(); id_activite=xml.text().toString();
                                        //qDebug()<<"id="<<id_tache<<"\n";
                                    }

                                    // We've found titre.
                                    if(xml.name() == "titre") {
                                        xml.readNext(); titre_activite=xml.text().toString();
                                        //qDebug()<<"titre="<<titre_tache<<"\n";
                                    }
                                    // We've found disponibilite
                                    if(xml.name() == "disponibilite") {
                                        xml.readNext();
                                        dispo_activite =QDateTime::fromString(xml.text().toString(),Qt::ISODate);
                                        //qDebug()<<"disp="<<disponibilite_tache.toString(Qt::ISODate)<<"\n";
                                    }
                                    // We've found echeance
                                    if(xml.name() == "echeance") {
                                        xml.readNext();
                                        echeance_activite=QDateTime::fromString(xml.text().toString(),Qt::ISODate);
                                        //qDebug()<<"echeance="<<echeance_tache.toString(Qt::ISODate)<<"\n";
                                    }
                                    // We've found duree
                                    if(xml.name() == "duree") {
                                        xml.readNext();
                                        duree_activite=xml.text().toString().toInt();
                                        //qDebug()<<"duree="<<duree_tache.getDureeEnMinutes()<<"\n";
                                    }
                                    // We've found lieu
                                    if(xml.name() == "lieu") {
                                        xml.readNext();
                                        lieu_activite=xml.text().toString();
                                        //qDebug()<<"duree="<<duree_tache.getDureeEnMinutes()<<"\n";
                                    }
                                    //WE've found participants
                                    if(xml.name() == "participants") {
                                        xml.readNext();
                                        QString participant;
                                        while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "participants")){
                                            if(xml.tokenType() == QXmlStreamReader::StartElement) {
                                                if(xml.name() == "participant") {
                                                    xml.readNext();
                                                    participant=xml.text().toString();
                                                    participants_activite.push_back(participant);
                                                }
                                            }
                                            xml.readNext();
                                        }//Fin while participants
                                    }//Fin if participants
                                    //We've found interlocuteur
                                    if(xml.name() == "interlocuteur") {
                                        xml.readNext();
                                        interlocuteur_activite=xml.text().toString();
                                    }
                                    // We've found programmation
                                    if(xml.name() == "programmation") {
                                        xml.readNext();
                                        programmed = true;
                                        while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "programmation")){
                                            if(xml.tokenType() == QXmlStreamReader::StartElement) {
                                                if(xml.name() == "date"){
                                                    xml.readNext();
                                                    date_prog = QDateTime::fromString(xml.text().toString(), Qt::ISODate);
                                                }
                                                if(xml.name() == "heure"){
                                                    xml.readNext();
                                                    heure_prog.setFromString(xml.text().toString());
                                                }
                                            }
                                            xml.readNext();
                                        }//Fin while programmation
                                        xml.readNext();
                                    }//Fin if programmation

                                }//Fin if activite
                                xml.readNext();
                            }//Fin while activite
                            if(reunion){
                                Reunion* reu = AM.ajouterReunion(id_activite,titre_activite,dispo_activite,echeance_activite,duree_activite,lieu_activite);
                                for(vector<QString>::iterator it = participants_activite.begin() ; it != participants_activite.end() ; ++it)
                                    reu->ajouterParticipant(*it);
                            }
                            else if (rdv){
                                AM.ajouterRdv(id_activite,titre_activite,dispo_activite,echeance_activite,duree_activite,interlocuteur_activite, lieu_activite);
                            }
                            else{
                                AM.ajouterActivite(id_activite,titre_activite,dispo_activite,echeance_activite,duree_activite,lieu_activite);
                            }
                            if(programmed){
                                A.ajouterProg(AM.trouverActivite(id_activite), date_prog, heure_prog);
                            }

                        }//Fin if activite
                    }
                    xml.readNext();
                }//Fin while activites
            }//Fin if activites
        }
    } // Fin lecture document
    // Error handling.
    //qDebug()<<"fin load\n";
    if(xml.hasError()) {
        throw AgendaException("Erreur lecteur fichier taches, parser xml");
    }
    // Removes any device() or data from the reader * and resets its internal state to the initial state.
    xml.clear();
}
