#if !defined(CTIME)
#define CTIME

#include<iostream>
#include<iomanip>
#include <sstream>
#include "qt.h"

namespace TIME {
	/*! \class TimeException
			\brief Classe permettant de g�rer les exceptions des classes du namespace TIME 		
	*/
	class TimeException{
	public:
		//! Constructeur � partir d'une string
		TimeException(const std::string& m):info(m){}
		const std::string& GetInfo() const { return info; } //<! Retourne l'information stock�e dans la classe
	private:
		std::string info;
	};

	/*! \class Duree
			\brief Classe permettant de manipuler des durees	
			L'utilisation de cette classe n�cessite des dates valides au sens commun du terme. 
			D�clenchement d'exception dans le cas contraire
	*/	
	class Duree{
	public:
		//! Constructeur � partir de heure et minute
		/*! \param h heure avec h>=0
			\param m minute avec 0<=m<=59
			*/
		Duree(unsigned int h, unsigned int m):nb_minutes(h*60+m) {if (m>59) throw TimeException("erreur: initialisation duree invalide");}
		//! Constructeur � partir de minute
		/*! \param m minute avec m>=0
			*/
		Duree(unsigned int m=0):nb_minutes(m) {}
		void setDuree(unsigned int heures, unsigned int minutes) { if (minutes>59) throw TimeException("erreur: initialisation duree invalide"); nb_minutes=heures*60+minutes; }
        void setDuree(unsigned int minutes) { nb_minutes=minutes; }
		unsigned int getDureeEnMinutes() const { return nb_minutes; } //<!Retourne la duree en minutes
		double getDureeEnHeures() const { return double(nb_minutes)/60; } //<!Retourne la duree en heures
        unsigned int getHeures() const {return nb_minutes/60;}
        unsigned int getMinutes() const {return nb_minutes%60;}
		void afficher(std::ostream& f=std::cout) const { f<<std::setfill('0')<<std::setw(2)<<nb_minutes/60<<"H"<<std::setw(2)<<nb_minutes%60<<std::setfill(' '); } //<!Affiche la duree sous le format hhHmm
        bool operator<(const Duree& d) const;
    private:
		unsigned int nb_minutes;
	};

	/*! \class Horaire
			\brief Classe permettant de manipuler des horaires	
			L'utilisation de cette classe n�cessite des dates valides au sens commun du terme. 
			D�clenchement d'exception dans le cas contraire
	*/	
	class Horaire{
	public:
		//! Constructeur � partir de heure et minute
		/*! \param h heure avec 0<=h<=23
			\param m minute avec 0<=m<=59
			*/
		Horaire(unsigned short int  h, unsigned short int  m):heure(h),minute(m) {if (h>23||m>59) throw TimeException("erreur: initialisation horaire invalide");}
		void setHoraire(unsigned short int h, unsigned short int m) { if (h>23||m>59) throw TimeException("erreur: initialisation horaire invalide"); heure=h; minute=m; }
		void afficher(std::ostream& f=std::cout) const { f<<std::setfill('0')<<std::setw(2)<<heure<<"H"<<std::setfill('0')<<std::setw(2)<<minute<<std::setfill(' '); } //<!Affiche l'horaire sous le format hhHmm
		unsigned short int getHeure() const { return heure; } //<!Retourne l'heure de l'horaire
		unsigned short int getMinute() const { return minute; } //<!Retourne les minutes de l'horaire
		bool operator<(const Horaire& h) const; //<! h1<h2 retourne true si h1 est avant h2 dans le temps
        QString toString() const;
        void setFromString(QString s);
	private:
		unsigned short int  heure;
		unsigned short int  minute;
	};

	/*! \class Periode
			\brief Classe permettant de manipuler des periodes exprim�es en jours/mois/ann�es	
			L'utilisation de cette classe n�cessite des dates valides au sens commun du terme. 
			D�clenchement d'exception dans le cas contraire
	*/	


}

std::ostream& operator<<(std::ostream& f, const TIME::Duree & d);
std::ostream& operator<<(std::ostream& f, const TIME::Horaire & h);


std::istream& operator>>(std::istream&, TIME::Duree&); //lecture format hhHmm

#endif

