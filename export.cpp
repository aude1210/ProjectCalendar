#include "projetmanager.h"
#include "agenda.h"
#include "activitemanager.h"
#include "export.h"
#include <typeinfo>

void ExportXML::save(const QString& f){
    //file=f;
    ProjetManager& PM = ProjetManager::getInstance();
    Agenda& A = Agenda::getInstance();
    QFile newfile(f);
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
        throw AgendaException(QString("erreur sauvegarde tâches : ouverture fichier xml"));
    QXmlStreamWriter stream(&newfile);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("projectcalendar");
    //Liste des projets dans la balise <projets>
    stream.writeStartElement("projets");
    for(ProjetManager::projets_iterator it1 = PM.begin_projets() ; it1 != PM.end_projets() ; ++it1){
        //chaque projet est dans une balise <projet>
        stream.writeStartElement("projet");
        stream.writeTextElement("identificateur",(*it1)->getId());
        stream.writeTextElement("titre",(*it1)->getTitre());
        stream.writeTextElement("description",(*it1)->getDesc());
        stream.writeTextElement("disponibilite",(*it1)->getDispo().toString(Qt::ISODate));
        stream.writeTextElement("echeance",(*it1)->getEcheance().toString(Qt::ISODate));
        //Liste des taches du projet et de leurs programmations dans une balise <taches>
        stream.writeStartElement("taches");
        for(Projet::taches_iterator it2 = (*it1)->begin_taches() ; it2 != (*it1)->end_taches() ; ++it2){
            //Chaque tache dans une balise <tache>
            stream.writeStartElement("tache");
            //Met l'attribut preemptive à true si tache préemptable, false sinon
            if (typeid(**it2) == typeid(TachePreemptable))
                stream.writeAttribute("preemptive", "true");
            else
                stream.writeAttribute("preemptive", "false");
            //Met l'attribut composite à true si tache composite, false sinon
            if (typeid(**it2) == typeid(TacheComposite))
                stream.writeAttribute("composite", "true");
            else
                stream.writeAttribute("composite", "false");
            //Met l'attribut unitaire à true si tache unitaire, false sinon
            if (typeid(**it2) == typeid(TacheUnitaire))
                stream.writeAttribute("unitaire", "true");
            else
                stream.writeAttribute("unitaire", "false");

            stream.writeTextElement("identificateur",(*it2)->getId());
            stream.writeTextElement("titre",(*it2)->getTitre());
            stream.writeTextElement("disponibilite",(*it2)->getDate().toString(Qt::ISODate));
            stream.writeTextElement("echeance",(*it2)->getEcheance().toString(Qt::ISODate));
            //Durée uniquement si tache unitaire
            if ((typeid(**it2) ==  typeid(TacheUnitaire)) || (typeid(**it2) == typeid(TachePreemptable))){
                QString str;
                str.setNum((*it2)->getDuree().getDureeEnMinutes());
                stream.writeTextElement("duree",str);
            }

            //Programmation si la tâche est programmée
            if ((*it2)->getStatus()){ // La Tache est programmée nous écrivons ici sa programmation
                Programmation* prog = A.trouverProgrammation(*it2);
                if (prog){
                    stream.writeStartElement("programmation");
                    stream.writeTextElement("date",prog->getDate().toString(Qt::ISODate));
                    stream.writeTextElement("heure", prog->getHoraire().toString());
                    stream.writeEndElement(); // Fin <programmation>
                }
            }

            stream.writeEndElement();// Fin <tache>
        }
        stream.writeEndElement(); // Fin <taches>
        stream.writeEndElement(); // Fin <projet>
    }
    stream.writeEndElement(); // Fin <projets>

    //Liste des précédences de Taches dans la balise <precedences>
    stream.writeStartElement("precedences");
    for(ProjetManager::projets_iterator it1 = PM.begin_projets() ; it1 != PM.end_projets() ; ++it1){ //Itération sur les projets
        for(Projet::taches_iterator it2 = (*it1)->begin_taches() ; it2 != (*it1)->end_taches() ; ++it2){ //Itération sur les taches du projet
            if ((*it2)->withPrecedence()){ //La tache a des contraintes de precedence
                stream.writeStartElement("precedence");
                stream.writeAttribute("id_projet", (*it1)->getId());
                stream.writeAttribute("id_tache", (*it2)->getId());
                for(precedences_iterator it3 = (*it2)->begin_precedences() ; it3 != (*it2)->end_precedences() ; ++it3) //Pour chaque tache, itération sur les taches précédentes
                    stream.writeTextElement("id_precedence", (*it3)->getId());
                stream.writeEndElement(); // Fin <precedence>
            }
        }
    }
    stream.writeEndElement(); // Fin <precedences>

    //Liste des composants pour les taches compositees
    stream.writeStartElement("composites");
    for(ProjetManager::projets_iterator it1 = PM.begin_projets() ; it1 != PM.end_projets() ; ++it1){ //Itération sur les projets
        for(Projet::taches_iterator it2 = (*it1)->begin_taches() ; it2 != (*it1)->end_taches() ; ++it2){ //Itération sur les taches du projet
            if (typeid(**it2) == typeid(TacheComposite)){
                soustaches_iterator it3 = (*it2)->begin_soustaches();
                if (it3 != (*it2)->end_soustaches()) { //on teste si la tache a des taches composants
                    stream.writeStartElement("composite");
                    stream.writeAttribute("id_projet", (*it1)->getId());
                    stream.writeAttribute("id_tache", (*it2)->getId());
                    for(it3 = (*it2)->begin_soustaches() ; it3 != (*it2)->end_soustaches() ; ++it3) //Pour chaque tache, itération sur les sous taches
                        stream.writeTextElement("id_composant", (*it3)->getId());
                    stream.writeEndElement(); // Fin <composite>
                }
            }
        }
    }
    stream.writeEndElement(); // Fin <composites>

    //Liste des activités et de leurs programmations
    stream.writeStartElement("activites");
    ActiviteManager& AM = ActiviteManager::getInstance();
    for(ActiviteManager::activites_iterator it1 = AM.begin_activites() ; it1 != AM.end_activites() ; ++it1){
        stream.writeStartElement("activite");
        //Met l'attribut reunion à true si c'est une reunion, false sinon
        if (typeid(**it1) == typeid(Reunion))
            stream.writeAttribute("reunion", "true");
        else
            stream.writeAttribute("reunion", "false");
        //Met l'attribut rdv à true si c'est un rdv, false sinon
        if (typeid(**it1) == typeid(Rdv))
            stream.writeAttribute("rdv", "true");
        else
            stream.writeAttribute("rdv", "false");
        stream.writeTextElement("identificateur",(*it1)->getId());
        stream.writeTextElement("titre",(*it1)->getTitre());
        stream.writeTextElement("disponibilite",(*it1)->getDate().toString(Qt::ISODate));
        stream.writeTextElement("echeance",(*it1)->getEcheance().toString(Qt::ISODate));
        QString str;
        str.setNum((*it1)->getDuree().getDureeEnMinutes());
        stream.writeTextElement("duree",str);
        stream.writeTextElement("lieu",(*it1)->getLieu());
        if (typeid(**it1) == typeid(Reunion)){ // C'est un réunion, on ajoute la liste des participants
            stream.writeStartElement("participants");
            //for(int i = 0 ; i < (*it1)->getNbParticipants() ; i++){
            for(participants_iterator it2 = (*it1)->begin_participants() ; it2 != (*it1)->end_participants() ; ++it2){
                stream.writeTextElement("participant",*it2);
            }
            stream.writeEndElement();// Fin <participants
        }
        if (typeid(**it1) == typeid(Rdv)){ //C'est un rdv, on ajoute l'interlocuteur du rdv
            stream.writeTextElement("interlocuteur", (*it1)->getInterlocuteur());
        }
        //Programmation si l'activité est programmée
        if ((*it1)->getStatus()){ // L'a Tache 'activité est programmée nous écrivons ici sa programmation
            Programmation* prog = A.trouverProgrammation(*it1);
            if (prog){
                stream.writeStartElement("programmation");
                stream.writeTextElement("date",prog->getDate().toString(Qt::ISODate));
                stream.writeTextElement("heure", prog->getHoraire().toString());
                stream.writeEndElement(); // Fin <programmation>
            }
        }
        stream.writeEndElement(); // Fin <activite>
    }
    stream.writeEndElement(); // Fin <activites>
    stream.writeEndElement(); // Fin <projectcalendar>
    stream.writeEndDocument();
    newfile.close();
}

